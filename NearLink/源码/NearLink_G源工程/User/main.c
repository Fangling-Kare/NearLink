

#include "debug.h"
#include "string.h"

char RxBuffer[8000];
//接收缓冲区

volatile u8 RxCnt = 0;

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));



/*********************************************************************
 * @函数名         extract_address
 *
 * @功能             解包提取星闪地址
 *
 * @参数             input- 源数据
 *          output - 解包后的数据
 *
 * @返回值         无返回值
 */
void extract_address(const char *input, char *output) {
    const char *start = strchr(input, ','); // 查找第一个逗号
    if (start == NULL) {
        output[0] = '\0'; // 输入字符串格式不正确，返回空字符串
        return;
    }

    start++; // 跳过第一个逗号
    const char *end = strchr(start, ','); // 查找第二个逗号
    if (end == NULL) {
        output[0] = '\0'; // 输入字符串格式不正确，返回空字符串
        return;
    }

    // 计算所需字符串的长度，并复制到输出缓冲区
    size_t length = end - start ;
    strncpy(output, start, length);
}

/*********************************************************************
 * @函数名         extract_data
 *
 * @功能             解包提取数据
 *
 * @参数             input- 源数据
 *          output - 解包后的数据
 *
 * @返回值         无返回值
 */
void extract_data(const char *input, char *output) {
    const char *start = strchr(input, ','); // 查找第一个逗号
    if (start == NULL) {
        output[0] = '\0'; // 输入字符串格式不正确，返回空字符串
        return;
    }

    start++; // 跳过第一个逗号
    start = strchr(start, ','); // 查找第二个逗号
    if (start == NULL) {
        output[0] = '\0'; // 输入字符串格式不正确，返回空字符串
        return;
    }

    start++; // 跳过第二个逗号
    const char *end = strchr(start, '\0'); // 查找字符串结尾
    if (end == NULL) {
        output[0] = '\0'; // 输入字符串格式不正确，返回空字符串
        return;
    }

    // 计算所需字符串的长度，并复制到输出缓冲区
    size_t length = end - start;
    strncpy(output, start, length);
}

/*********************************************************************
 * @函数名         NearLink_SendData
 *
 * @功能             通过USART发送数据给NearLink星闪
 *
 * @参数              USARTx- 选择USART串口
 *          Data - 发送的数据
 *
 * @返回值         无返回值
 */

void NearLink_SendData(USART_TypeDef *USARTx,const char *Data)
{
    memset(RxBuffer, 0, sizeof(RxBuffer));
    RxCnt = 0;
    while(*Data)
    {
        USART_SendData(USARTx,*Data++);
        while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET)
        {
        }
    }
}

/*********************************************************************
 * @函数名         USARTx_CFG
 *
 * @功能             初始化USART2外设
 *
 *
 * @返回值         无返回值
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    //定义GPIO初始化结构体
    USART_InitTypeDef USART_InitStructure = {0};
    //定义USART初始化结构体
    NVIC_InitTypeDef  NVIC_InitStructure = {0};
    //定义NVIC初始化结构体

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    //使能USART2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //使能GPIOA的时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    //配置PA2引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //设置频率
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //复用推挽输出模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //初始化GPIOA的PA2引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    //配置PA3引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //悬空输入模式
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //初始化GPIOA的PA3引脚

    //配置USART参数
    USART_InitStructure.USART_BaudRate = 115200;
    //设置波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    //配置每个数据帧包含8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    //配置停止位数
    USART_InitStructure.USART_Parity = USART_Parity_No;
    //配置不使用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //配置不使用硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //启用发送接收模式

    USART_Init(USART2, &USART_InitStructure);
    //初始化USART2
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //启用 USART2的接收数据寄存器非空中断

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    //配置 NVIC 为 USART2的中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //配置 USART2中断的抢占优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    //配置 USART2中断的子优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //使能 USART2中断
    NVIC_Init(&NVIC_InitStructure);
    //初始化NVIC

    USART_Cmd(USART2, ENABLE);
    //使能USART2
}

/*********************************************************************
 * 函数名        main
 *
 * 函数功能    主函数
 *
 * 返回值        无返回值
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //配置NVIC的中断优先级分组
    SystemCoreClockUpdate();
    //更新系统核心时钟频率
    Delay_Init();
    //延迟函数初始化
    USART_Printf_Init(115200);
    //USART初始化并配置波特率为115200

    //打印系统信息
    printf("SystemClk:%d\r\n", SystemCoreClock);
    //打印系统时钟频率
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    //打印芯片信息
    printf("NearLink_G Test\r\n");
    //打印字符串“USART Interrupt TEST”
    USARTx_CFG();
    //对 USART2外设进行初始化。

    //STEP1:发送AT等待星闪初始化
    NearLink_SendData(USART2, "AT\r\n");
    Delay_Ms(100);

    //STEP2:等待OK
    while(strstr((char *)RxBuffer, "OK") == NULL){}


    //STEP3:接收数据
    while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != SET){}
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "RECEIVEDATA") == NULL){}
    printf("NearLink Receive Data Succeed\r\n");

    //STEP4:处理数据
    char Data[128] = {0};
    char Address[128] = {0};
    extract_data(RxBuffer, Data);
    extract_address(RxBuffer, Address);


    //STEP4:转发数据
    char Nearlink_Send_Data[128]={0};
    sprintf(Nearlink_Send_Data,"AT+SENDDATA=0,%s,%s\r\n",Address,Data);
    NearLink_SendData(USART2,Nearlink_Send_Data);
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "OK") == NULL){}
    printf("NearLink Send Data Succeed\r\n");

    while(1)
    {

    }
}

/*********************************************************************
 * 函数名       USART2_IRQHandler
 *
 * 函数功能   此函数处理 USART2 全局中断请求。
 *
 * 返回值       无返回值
 */
void USART2_IRQHandler(void)
{
   if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET)
   //判断 USART2 接收中断是否发生
   {
       RxBuffer[RxCnt++] = USART_ReceiveData(USART2);
   }
}



