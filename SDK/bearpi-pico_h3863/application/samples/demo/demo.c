#include "common_def.h"
#include "soc_osal.h"
#include "app_init.h"
#include "pinctrl.h"
#include "uart.h"
#include "lwip/nettool/misc.h"
#include "lwip/ip4_addr.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/sockets.h"
#include "wifi/wifi_connect.h"
#include "demo.h"

#define SLE_GATEWAY_TASK_PRIO                  28
#define SLE_GATEWAY_TASK_DURATION_MS           2000
#define SLE_GATEWAY_TASK_STACK_SIZE            0x1000
#define SLE_GATEWAY_BAUDRATE                   115200
#define SLE_GATEWAY_TRANSFER_SIZE              512

// 在sock_fd 进行监听，在 new_fd 接收新的链接
int my_g_sock_fd;

// 服务器的地址信息
struct sockaddr_in my_g_send_addr;


// #define CONFIG_WIFI_SSID            "Redmi K70"                              // 要连接的WiFi 热点账号
// #define CONFIG_WIFI_PWD             "stm32f103"                        // 要连接的WiFi 热点密码
// #define CONFIG_SERVER_IP            "192.168.172.74"                     // 要连接的服务器IP
// #define CONFIG_SERVER_PORT          8888     


static char CONFIG_WIFI_SSID[32]      =        "Redmi K70"  ;                            // 要连接的WiFi 热点账号
static char CONFIG_WIFI_PWD[32]       =     "stm32f103"   ;                     // 要连接的WiFi 热点密码
static char CONFIG_SERVER_IP[24]      =      "192.168.172.74"  ;                   // 要连接的服务器IP
static int CONFIG_SERVER_PORT     =     8888     ;                              //要连接的端口号
static uint8_t recieve_connect_info_flag = 0; // 是否接收到连接信息
static uint8_t reset_request_flag = 0; // 是否收到重启命令

static uint8_t g_app_uart_rx_buff[SLE_GATEWAY_TRANSFER_SIZE] = { 0 };
static uart_buffer_config_t g_app_uart_buffer_config = {
    .rx_buffer = g_app_uart_rx_buff,
    .rx_buffer_size = SLE_GATEWAY_TRANSFER_SIZE
};

static void uart_init_config(void)
{
    uart_attr_t attr = {
        .baud_rate = SLE_GATEWAY_BAUDRATE,
        .data_bits = UART_DATA_BIT_8,
        .stop_bits = UART_STOP_BIT_1,
        .parity = UART_PARITY_NONE
    };

    uart_pin_config_t pin_config = {
        .tx_pin = MY_CONFIG_UART_TXD_PIN,
        .rx_pin = MY_CONFIG_UART_RXD_PIN,
        .cts_pin = PIN_NONE,
        .rts_pin = PIN_NONE
    };
    uapi_uart_deinit(MY_CONFIG_GATEWAY_BUS);
    uapi_uart_init(MY_CONFIG_GATEWAY_BUS, &pin_config, &attr, NULL, &g_app_uart_buffer_config);
}

static void uart_read_int_handler(const void *buffer, uint16_t length, bool error)
{
    unused(error);
    static char *token; //存储wifi信息分割后的各个数据

    if(strstr(buffer,"reset request")){ //收到重启命令置位重启标志位，使任务重新执行初始化
       reset_request_flag = 1;
    }
    if(strstr(buffer,"reset_wifi_info")){ //收到wifi重连命令置位重启标志位，使任务重新执行初始化
        reset_request_flag = 1;
        recieve_connect_info_flag = 0;
    }

    if(recieve_connect_info_flag){ //先判断是否收到wifi信息，未收到先获取连接的WiFi信息与tcp连接信息
        if (buffer == NULL || length == 0) {
            osal_printk("uart%d int mode transfer illegal data!\r\n", MY_CONFIG_GATEWAY_BUS);
            return;
        }else{
            uint8_t *buff = (uint8_t *)buffer;
            // 直接通过Socket发送数据
            send(my_g_sock_fd, (uint8_t *)buff, length, 0);
        }
    }
    else if(strstr(buffer,"wifi_info")){
        // 创建一个可修改的str的副本
        char* strCopy = (char*)malloc(strlen(buffer) + 1);
        memcpy(strCopy,buffer,strlen(buffer) + 1);
        token = strtok(strCopy,"="); //获取参数部分
        // 再以','为分隔符分割参数部分
        token = strtok(NULL, ",");
        memcpy(CONFIG_WIFI_SSID,token,sizeof(token)); //wifi名字
        token = strtok(NULL, ",");
        memcpy(CONFIG_WIFI_PWD,token,sizeof(token)); //wifi密码
        token = strtok(NULL, ",");
        memcpy(CONFIG_SERVER_IP,token,sizeof(token)); //tcp服务器IP地址
        token = strtok(NULL, "\r\n");
        CONFIG_SERVER_PORT = strtol(token,NULL,10); //端口号
        recieve_connect_info_flag = 1; //表示已获取到wifi信息
        osal_printk("get the wifi info\n");
        free(strCopy); //释放内存
    }
    else{
        osal_printk("waiting for wifi info\n");          
    }
}

//重启的再初始化函数
static void reset_handler(void){
    while(reset_request_flag){
        while(!recieve_connect_info_flag){//阻塞等待获得wifi信息
            osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
        }
        
        // 连接Wifi
        wifi_connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PWD);
        // 创建socket
        printf("create socket start!\r\n");

        /* 创建Socket */
        if ((my_g_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            osal_printk("create socket failed!\r\n");
            return;
        }

        my_g_send_addr.sin_family = AF_INET;
        my_g_send_addr.sin_port = htons(CONFIG_SERVER_PORT);
        my_g_send_addr.sin_addr.s_addr = inet_addr(CONFIG_SERVER_IP);
        socklen_t my_g_addr_length = sizeof(my_g_send_addr);

        // 连接到服务器
        if (connect(my_g_sock_fd, (struct sockaddr *)&my_g_send_addr, my_g_addr_length) < 0) {
            char txBuf[64] = "connect failed!\r\n";
            osal_printk("connect failed!\r\n");
            uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
            osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
            return;
        }
        else{ //告诉ch32已经连接到服务器
            for(int i = 0; i<3 ; i++){
                char txBuf[64] = "connect succ!\r\n";
                uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
                osal_msleep(SLE_GATEWAY_TASK_DURATION_MS/10);
            }
            osal_printk("connect succ!\r\n");
        }
    }
}

//任务执行函数
static void *sle_uart_client_task(const char *arg)
{
    unused(arg);
    /* UART init config. */
    uart_init_config();

    /* 注册UART接收回调函数 */
    uapi_uart_register_rx_callback(MY_CONFIG_GATEWAY_BUS,
                                   UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA_OR_IDLE,
                                   1, uart_read_int_handler);

     while(!recieve_connect_info_flag){//阻塞等待获得wifi信息
        osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
     }
     
    // 连接Wifi
    wifi_connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PWD);
    // 创建socket
    printf("create socket start!\r\n");

    /* 创建Socket */
    if ((my_g_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        osal_printk("create socket failed!\r\n");
        return 0;
    }

    my_g_send_addr.sin_family = AF_INET;
    my_g_send_addr.sin_port = htons(CONFIG_SERVER_PORT);
    my_g_send_addr.sin_addr.s_addr = inet_addr(CONFIG_SERVER_IP);
    socklen_t my_g_addr_length = sizeof(my_g_send_addr);

    // 连接到服务器
    if (connect(my_g_sock_fd, (struct sockaddr *)&my_g_send_addr, my_g_addr_length) < 0) {
        char txBuf[64] = "connect failed!\r\n";
        osal_printk("connect failed!\r\n");
        uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
        osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
        return 0;
    }
    else{ //告诉ch32已经连接到服务器
        for(int i = 0; i<3 ; i++){
            char txBuf[64] = "connect succ!\r\n";
            uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
            osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
        }
        osal_printk("connect succ!\r\n");
    }

    while (1) {
        reset_handler(); //每次循环检查一次是否收到重启信号
        // 接收服务端返回的数据并通过UART发送(服务端数据一般频率不高，1s转发一次即可)
        char recvBuf[512];
        bzero(recvBuf, sizeof(recvBuf));
        recv(my_g_sock_fd, recvBuf, sizeof(recvBuf), 0);
        uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)recvBuf, strlen(recvBuf), 0);
        osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
    }
    return NULL;
}

static void sle_uart_entry(void)
{
    osal_task *task_handle = NULL;
    osal_kthread_lock();
    task_handle = osal_kthread_create((osal_kthread_handler)sle_uart_client_task, 0, "SLEUartDongleTask",
                                      SLE_GATEWAY_TASK_STACK_SIZE);
    if (task_handle != NULL) {
        osal_kthread_set_priority(task_handle, SLE_GATEWAY_TASK_PRIO);
    }
    osal_kthread_unlock();
}

/* Run the sle_uart_entry. */
app_run(sle_uart_entry);