/**
 * Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2023-2023. All rights reserved.
 *
 * 描述：SLE UART 示例源文件。\n
 *
 * 历史：\n
 * 2023-07-17, 创建文件。\n
 */
#include "common_def.h"          // 包含通用定义
#include "soc_osal.h"            // 包含系统OS抽象层头文件
#include "app_init.h"            // 包含应用程序初始化头文件
#include "pinctrl.h"             // 包含引脚控制头文件
#include "uart.h"                // 包含UART驱动头文件
// #include "pm_clock.h"         // 包含电源管理时钟头文件
#include "sle_low_latency.h"     // 包含SLE低延迟头文件
#if defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_SERVER)   // 如果定义了SLE_UART_SERVER模式
#include "securec.h"             // 包含安全库头文件
#include "sle_uart_server.h"     // 包含SLE UART服务器头文件
#include "sle_uart_server_adv.h" // 包含SLE UART服务器高级头文件
#include "sle_device_discovery.h" // 包含SLE设备发现头文件
#include "sle_errcode.h"         // 包含SLE错误代码头文件
#elif defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT) // 如果定义了SLE_UART_CLIENT模式
#define SLE_UART_TASK_STACK_SIZE            0x600 // 定义SLE UART任务栈大小
#include "sle_connection_manager.h"       // 包含SLE连接管理头文件
#include "sle_ssap_client.h"              // 包含SLE SSAP客户端头文件
#include "sle_uart_client.h"              // 包含SLE UART客户端头文件
#endif  /* CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT */

#define SLE_UART_TASK_PRIO                  28 // 定义SLE UART任务优先级
#define SLE_UART_TASK_DURATION_MS           2000 // 定义SLE UART任务持续时间，毫秒
#define SLE_UART_BAUDRATE                   115200 // 定义SLE UART波特率
#define SLE_UART_TRANSFER_SIZE              512 // 定义SLE UART传输大小

static uint8_t g_app_uart_rx_buff[SLE_UART_TRANSFER_SIZE] = { 0 }; // 定义全局UART接收缓冲区并初始化为0

static uart_buffer_config_t g_app_uart_buffer_config = { // 定义全局UART缓冲区配置
    .rx_buffer = g_app_uart_rx_buff, // 接收缓冲区
    .rx_buffer_size = SLE_UART_TRANSFER_SIZE // 接收缓冲区大小
};

static void uart_init_pin(void) // UART初始化引脚配置函数
{
    if (CONFIG_SLE_UART_BUS == 0) {
        uapi_pin_set_mode(CONFIG_UART_TXD_PIN, PIN_MODE_1); // 如果UART总线为0，设置TXD引脚模式
        uapi_pin_set_mode(CONFIG_UART_RXD_PIN, PIN_MODE_1); // 设置RXD引脚模式       
    }else if (CONFIG_SLE_UART_BUS == 1) {
        uapi_pin_set_mode(CONFIG_UART_TXD_PIN, PIN_MODE_1); // 如果UART总线为1，设置TXD引脚模式
        uapi_pin_set_mode(CONFIG_UART_RXD_PIN, PIN_MODE_1); // 设置RXD引脚模式       
    }
}

static void uart_init_config(void) // UART初始化配置函数
{
    uart_attr_t attr = { // 定义UART属性
        .baud_rate = SLE_UART_BAUDRATE, // UART波特率
        .data_bits = UART_DATA_BIT_8, // UART数据位
        .stop_bits = UART_STOP_BIT_1, // UART停止位
        .parity = UART_PARITY_NONE // UART奇偶校验位
    };

    uart_pin_config_t pin_config = { // 定义UART引脚配置
        .tx_pin = CONFIG_UART_TXD_PIN, // UART TXD引脚
        .rx_pin = CONFIG_UART_RXD_PIN, // UART RXD引脚
        .cts_pin = PIN_NONE, // UART CTS引脚（无）
        .rts_pin = PIN_NONE // UART RTS引脚（无）
    };
    uapi_uart_deinit(CONFIG_SLE_UART_BUS); // 反初始化指定UART总线
    uapi_uart_init(CONFIG_SLE_UART_BUS, &pin_config, &attr, NULL, &g_app_uart_buffer_config); // 初始化指定UART总线

}

#if defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_SERVER) // 如果定义了SLE_UART_SERVER模式
// ...省略部分代码...
#endif  /* CONFIG_SAMPLE_SUPPORT_SLE_UART_SERVER */

#elif defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT) // 如果定义了SLE_UART_CLIENT模式

void sle_uart_notification_cb(uint8_t client_id, uint16_t conn_id, ssapc_handle_value_t *data,
    errcode_t status) // SLE UART通知回调函数
{
    unused(client_id);
    unused(conn_id);
    unused(status);
    osal_printk("\n sle uart recived data : %s\r\n", data->data); // 打印接收到的数据
    uapi_uart_write(CONFIG_SLE_UART_BUS, (uint8_t *)(data->data), data->data_len, 0); // 通过UART写数据
}

void sle_uart_indication_cb(uint8_t client_id, uint16_t conn_id, ssapc_handle_value_t *data,
    errcode_t status) // SLE UART指示回调函数
{
    unused(client_id);
    unused(conn_id);
    unused(status);
    osal_printk("\n sle uart recived data : %s\r\n", data->data); // 打印接收到的数据
    uapi_uart_write(CONFIG_SLE_UART_BUS, (uint8_t *)(data->data), data->data_len, 0); // 通过UART写数据
}

static void sle_uart_client_read_int_handler(const void *buffer, uint16_t length, bool error) // SLE UART客户端接收中断处理函数
{
    unused(error);
    ssapc_write_param_t *sle_uart_send_param = get_g_sle_uart_send_param(); // 获取全局UART发送参数
    uint16_t g_sle_uart_conn_id = get_g_sle_uart_conn_id(); // 获取全局UART连接ID
    sle_uart_send_param->data_len = length; // 设置发送数据长度
    sle_uart_send_param->data = (uint8_t *)buffer; // 设置发送数据缓冲区
    ssapc_write_req(0, g_sle_uart_conn_id, sle_uart_send_param); // 发送SSAP写请求
}

static void *sle_uart_client_task(const char *arg) // SLE UART客户端任务函数
{
    unused(arg);
    /* UART pinmux. */
    uart_init_pin(); // 初始化UART引脚配置

    /* UART init config. */
    uart_init_config(); // 初始化UART配置

    uapi_uart_unregister_rx_callback(CONFIG_SLE_UART_BUS); // 注销UART接收回调
    errcode_t ret = uapi_uart_register_rx_callback(CONFIG_SLE_UART_BUS, // 注册UART接收回调
                                                   UART_RX_CONDITION_FULL_OR_IDLE,
                                                   1, sle_uart_client_read_int_handler);
    sle_uart_client_init(sle_uart_notification_cb, sle_uart_indication_cb); // 初始化SLE UART客户端
    
    if (ret != ERRCODE_SUCC) { // 如果注册失败
        osal_printk("Register uart callback fail."); // 打印失败信息
        return NULL; // 返回NULL
    }

    return NULL; // 返回NULL
}
#endif  /* CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT */

static void sle_uart_entry(void) // SLE UART入口函数
{
    osal_task *task_handle = NULL; // 定义任务句柄
    osal_kthread_lock(); // 锁定内核线程
#if defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_SERVER) // 如果定义了SLE_UART_SERVER模式
    task_handle = osal_kthread_create((osal_kthread_handler)sle_uart_server_task, 0, "SLEUartServerTask", // 创建内核线程作为服务器任务
                                      SLE_UART_TASK_STACK_SIZE);
#elif defined(CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT) // 如果定义了SLE_UART_CLIENT模式
    task_handle = osal_kthread_create((osal_kthread_handler)sle_uart_client_task, 0, "SLEUartDongleTask", // 创建内核线程作为客户端任务
                                      SLE_UART_TASK_STACK_SIZE);
#endif /* CONFIG_SAMPLE_SUPPORT_SLE_UART_CLIENT */
    if (task_handle != NULL) { // 如果任务句柄不为空
        osal_kthread_set_priority(task_handle, SLE_UART_TASK_PRIO); // 设置任务优先级
    }
    osal_kthread_unlock(); // 解锁内核线程
}

/* Run the sle_uart_entry. */ // 运行sle_uart_entry
app_run(sle_uart_entry);