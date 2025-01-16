/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"
#include "stdlib.h"
#include "string.h"


void USART3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast"))); //启用快速中断


char RxBuffer_for_3[400]={0}; //接收缓存区
char TxBuffer_for_3[1400]={0}; //发送缓存区
volatile uint8_t Rx3Cnt = 0;
volatile uint8_t tcp_send_enable = 0;

void my_tcp_send(USART_TypeDef *USARTx,uint8_t str[]){
    if(tcp_send_enable){
        int i = 0;
        while(str[i]){
            USART_SendData(USARTx,str[i++]);
            while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET){}
        }
        memset(str, 0, sizeof(str));
        // 清空发送缓存区
    }
}

void my_tcp_receive(void)
{
        if(strstr(RxBuffer_for_3,"succ")){
            printf("TCP connect successful %s\r\n");
            tcp_send_enable = 1;
            Rx3Cnt = 0;
            // 重置接收计数器
            memset(RxBuffer_for_3, 0, sizeof(RxBuffer_for_3));
            // 清空接收缓存区
        }

}
/* Global typedef */

/* Global define */

/* Global Variable */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};    //定义NVIC初始化结构体

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    /* USART2 TX-->A.2   RX-->A.3 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* USART3 TX-->B.10  RX-->B.11 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART2, &USART_InitStructure);
    USART_Init(USART3, &USART_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    //启用 USART3的接收数据寄存器非空中断
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    //配置 NVIC 为 USART3的中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //配置 USART3中断的抢占优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    //配置 USART3中断的子优先级为 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //使能 USART3中断
    NVIC_Init(&NVIC_InitStructure);
    //初始化NVIC
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //启用 USART2的接收数据寄存器非空中断
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    //配置 NVIC 为 USART2的中断通道
    NVIC_Init(&NVIC_InitStructure);
    //初始化NVIC
    USART_Cmd(USART2, ENABLE);
    USART_Cmd(USART3, ENABLE);

}


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);	
	USARTx_CFG();
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
	printf("This is printf example\r\n");
	char test_str[10] = "?shihskan";
	memcpy(TxBuffer_for_3,test_str,10);
	while(!tcp_send_enable){};
	my_tcp_send(USART3, TxBuffer_for_3);
	while(1)
    {

	}
}

/*********************************************************************
 * 函数名       USART3_IRQHandler
 *
 * 函数功能   此函数处理 USART3 全局中断请求。
 *
 * 返回值       无返回值
 */
void USART3_IRQHandler(void)
{
    if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET)
        //
        {
            RxBuffer_for_3[Rx3Cnt++] = USART_ReceiveData(USART3);
            //接收USART3的数据
        }
        my_tcp_receive(); //判断是否建立tcp连接
}
