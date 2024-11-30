/**
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2023. All rights reserved.
 *
 * Description: Application core main function for standard \n
 *
 * History: \n
 * 2022-07-27, Create file. \n
 */

#include "lwip/nettool/misc.h"  // LWIP网络工具库
#include "lwip/ip4_addr.h"     // LWIP IPv4地址库
#include "lwip/netif.h"       // LWIP网络接口库
#include "lwip/netifapi.h"    // LWIP网络接口API库
#include "lwip/sockets.h"     // LWIP套接字库

#include "pinctrl.h"          // 引脚控制库
#include "soc_osal.h"         // 系统抽象层库
#include "spi.h"             // SPI通信库
#include "gpio.h"            // GPIO库
#include "osal_debug.h"       // OSAL调试库

#include "cmsis_os2.h"        // CMSIS-RTOS v2库
#include "app_init.h"        // 应用初始化库
#include "wifi_connect.h"     // WiFi连接库

// 定义配置宏
#define CONFIG_SPI_MASTER_BUS_ID 0                // SPI主设备总线ID
#define CONFIG_SPI_DI_MASTER_PIN 11               // SPI主设备数据线引脚
#define CONFIG_SPI_DO_MASTER_PIN 9                // SPI主设备输出线引脚
#define CONFIG_SPI_CLK_MASTER_PIN 7               // SPI主设备时钟线引脚

#define UDP_CLIENT_TASK_PRIO                  (osPriority_t)(13)  // UDP客户端任务优先级
#define UDP_CLIENT_TASK_DURATION_MS           2000             // UDP客户端任务持续时间(ms)
#define UDP_UPDATE_TASK_DURATION_MS           2000             // UDP更新任务持续时间(ms)
#define UDP_CLIENT_TASK_STACK_SIZE            0x1000           // UDP客户端任务堆栈大小

#define CONFIG_WIFI_SSID                  "Redmi K70"            // 要连接的WiFi热点账号
#define CONFIG_WIFI_PWD                   "stm32f103"           // 要连接的WiFi热点密码
#define CONFIG_SERVER_IP                  "192.168.148.74"       // 要连接的服务器IP
#define CONFIG_SERVER_PORT                8888                   // 要连接的服务器端口
#define MAX_DATA_SIZE                     512                    // 最大数据大小

#define SPI_SLAVE_NUM                   1                       // SPI从设备数量
#define SPI_FREQUENCY                   2                      // SPI通信频率(MHz)
#define SPI_CLK_POLARITY                1                       // SPI时钟极性
#define SPI_CLK_PHASE                   1                       // SPI时钟相位
#define SPI_FRAME_FORMAT                1                       // SPI帧格式
#define SPI_FRAME_FORMAT_STANDARD       0                       // SPI标准帧格式
#define SPI_FRAME_SIZE_8                0x1f                    // SPI 8位帧大小
#define SPI_TMOD                        0                       // SPI传输模式
#define SPI_WAIT_CYCLES                 0x10                    // SPI等待周期

#define SPI_TASK_STACK_SIZE             0x1000                  // SPI任务堆栈大小
#define SPI_TASK_DURATION_MS            1000                    // SPI任务持续时间(ms)
#define SPI_TASK_PRIO                   (osPriority_t)(13)         // SPI任务优先级

// 共享数据结构
typedef struct {
    char data[MAX_DATA_SIZE];  // 共享数据缓冲区
    size_t size;             // 共享数据大小
    //osMutexId_t mutex;      // 互斥锁(未使用)
} SharedData;

SharedData shared_data;  // 共享数据实例

void my_app_spi_init_pin(void)
{
    // 初始化SPI引脚配置
    if (CONFIG_SPI_MASTER_BUS_ID == 0) {
        uapi_pin_set_mode(CONFIG_SPI_DI_MASTER_PIN, 3);  // 设置SPI数据线引脚模式
        uapi_pin_set_mode(CONFIG_SPI_DO_MASTER_PIN, 3);   // 设置SPI输出线引脚模式
        uapi_pin_set_mode(CONFIG_SPI_CLK_MASTER_PIN, 3);  // 设置SPI时钟线引脚模式
    }
}

void my_app_spi_master_init_config(void)
{
    // 初始化SPI主设备配置
    spi_attr_t config = { 0 };  // SPI属性结构体
    spi_extra_attr_t ext_config = { 0 };  // SPI额外属性结构体

    config.is_slave = false;  // 设备为SPI主模式
    config.slave_num = SPI_SLAVE_NUM;  // 从设备数量
    config.bus_clk = 32000000;  // 总线时钟频率
    config.freq_mhz = SPI_FREQUENCY;  // SPI通信频率(MHz)
    config.clk_polarity = SPI_CLK_POLARITY;  // 时钟极性
    config.clk_phase = SPI_CLK_PHASE;  // 时钟相位
    config.frame_format = SPI_FRAME_FORMAT;  // 帧格式
    config.spi_frame_format = HAL_SPI_FRAME_FORMAT_STANDARD;  // 标准SPI帧格式
    config.frame_size = HAL_SPI_FRAME_SIZE_8;  // 8位帧大小
    config.tmod = SPI_TMOD;  // 传输模式
    config.sste = 1;  // 片选信号

    ext_config.qspi_param.wait_cycles = SPI_WAIT_CYCLES;  // 等待周期
    uapi_spi_init(CONFIG_SPI_MASTER_BUS_ID, &config, &ext_config);  // 初始化SPI
}

void my_spi_recieve(void)
{
    // 从SPI总线接收数据
    static hal_spi_xfer_data_t spi_xfer_data = {0};  // SPI传输数据结构体
    static hal_spi_xfer_data_t spi_tx_data = {0};
    uint8_t tx_buff[8] = {1,2,3,4,5,6,7,8};
    spi_tx_data.tx_buff = &tx_buff[0];
    //spi_xfer_data.tx_buff = malloc(50);  // 分配发送缓冲区
    spi_xfer_data.rx_buff = malloc(50);  // 分配接收缓冲区

    spi_xfer_data.tx_bytes = 8;  // 设置发送数据大小
    spi_xfer_data.rx_bytes = 50;  // 设置接收数据大小
    uapi_spi_master_write(CONFIG_SPI_MASTER_BUS_ID, &spi_tx_data, sizeof(spi_tx_data));
    // 从SPI总线读取数据
    if(uapi_spi_master_read(CONFIG_SPI_MASTER_BUS_ID, &spi_xfer_data, sizeof(spi_xfer_data)) != ERRCODE_FAIL)
    {
        // 将接收到的数据存储到共享数据结构中
        memcpy(shared_data.data, spi_xfer_data.rx_buff, spi_xfer_data.rx_bytes);
        shared_data.size = spi_xfer_data.rx_bytes;
    }   
    else
    {
        // 如果SPI接收失败，设置错误消息
        strcpy(shared_data.data, "No spi msg");
        shared_data.size = strlen("No spi msg");  // 设置大小为字符串的实际长度
        printf("spi receive error!\n");
        osDelay(100);  // 延时100ms
    }    

    // 释放分配的内存
    free(spi_xfer_data.tx_buff);
    free(spi_xfer_data.rx_buff);
}

int udp_client_sample_task(void *param)
{
    param = param;  // 避免未使用参数警告

    // 创建UDP客户端任务
    int sock_fd;  // 套接字文件描述符

    // 服务器地址信息
    struct sockaddr_in send_addr;  // 发送地址结构体
    socklen_t addr_length = sizeof(send_addr);  // 地址长度
    char recvBuf[512];  // 接收缓冲区

    // 连接WiFi
    wifi_connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PWD);

    // 创建套接字
    printf("create socket start!\r\n");
    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("create socket failed!\r\n");
        return 0;
    }
    printf("create socket end!\r\n");

    // 初始化预连接的服务端地址
    send_addr.sin_family = AF_INET;  // 地址族
    send_addr.sin_port = htons(CONFIG_SERVER_PORT);  // 端口号
    send_addr.sin_addr.s_addr = inet_addr(CONFIG_SERVER_IP);  // IP地址
    addr_length = sizeof(send_addr);

    while (1) {
        // 从SPI接收数据
        my_spi_recieve();

        bzero(recvBuf, sizeof(recvBuf));  // 清空接收缓冲区

        // 发送数据到服务器
        printf("sendto start!\r\n");
        sendto(sock_fd, shared_data.data, shared_data.size, 0, (struct sockaddr *)&send_addr, addr_length);  // 发送数据
        printf("sendto end!\r\n");

        // 线程休眠一段时间
        osDelay(100);

        // 接收服务器返回的数据
        recvfrom(sock_fd, recvBuf, sizeof(recvBuf), 0, (struct sockaddr *)&send_addr, &addr_length);
        printf("%s:%d=>%s\n", inet_ntoa(send_addr.sin_addr), ntohs(send_addr.sin_port), recvBuf);
    }

    // 关闭套接字
    lwip_close(sock_fd);
    return 0;
}

static void udp_client_sample_entry(void)
{
    osThreadAttr_t attr;
    attr.name       = "udp_client_sample_task";
    attr.attr_bits  = 0U;
    attr.cb_mem     = NULL;
    attr.cb_size    = 0U;
    attr.stack_mem  = NULL;
    attr.stack_size = UDP_CLIENT_TASK_STACK_SIZE;
    attr.priority   = UDP_CLIENT_TASK_PRIO;
    if (osThreadNew((osThreadFunc_t)udp_client_sample_task, NULL, &attr) == NULL) {
        printf("Create udp_client_sample_task fail.\r\n");
    }
    printf("Create udp_client_sample_task succ.\r\n");
    my_app_spi_init_pin();

    /* SPI master init config. */
    my_app_spi_master_init_config();
}

/* Run the udp_client_sample_task. */
app_run(udp_client_sample_entry);