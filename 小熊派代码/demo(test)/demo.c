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


#define CONFIG_WIFI_SSID            "Redmi K70"                              // 要连接的WiFi 热点账号
#define CONFIG_WIFI_PWD             "stm32f103"                        // 要连接的WiFi 热点密码
#define CONFIG_SERVER_IP            "192.168.172.74"                     // 要连接的服务器IP
#define CONFIG_SERVER_PORT          8888     

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
    if (buffer == NULL || length == 0) {
        osal_printk("uart%d int mode transfer illegal data!\r\n", MY_CONFIG_GATEWAY_BUS);
        return;
    }

    uint8_t *buff = (uint8_t *)buffer;
    // 直接通过Socket发送数据
    send(my_g_sock_fd, (uint8_t *)buff, length, 0);
}

static void *sle_uart_client_task(const char *arg)
{
    unused(arg);
    /* UART init config. */
    uart_init_config();

    /* 注册UART接收回调函数 */
    uapi_uart_register_rx_callback(MY_CONFIG_GATEWAY_BUS,
                                   UART_RX_CONDITION_FULL_OR_SUFFICIENT_DATA_OR_IDLE,
                                   1, uart_read_int_handler);
                                   
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
        char txBuf[64] = "connect server failed!\r\n";
        osal_printk("connect failed!\r\n");
        uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
        osal_msleep(SLE_GATEWAY_TASK_DURATION_MS);
        return 0;
    }
    else{ //告诉ch32已经连接到服务器
        char txBuf[64] = "connect server succ!\r\n";
        osal_printk("connect succ!\r\n");
        uapi_uart_write(MY_CONFIG_GATEWAY_BUS, (uint8_t *)txBuf, strlen(txBuf), 0);
    }

    while (1) {
        // 接收服务端返回的数据并通过UART发送
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