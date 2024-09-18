

#include "debug.h"
#include "string.h"

char RxBuffer[8000]={};
//���ջ�����

volatile uint8_t RxCnt = 0;

void USART2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @������         extract_address
 *
 * @����             �����ȡ������ַ
 *
 * @����             input- Դ����
 *          output - ����������
 *
 * @����ֵ         �޷���ֵ
 */
void extract_address(const char *input, char *output) {
    const char *start = strchr(input, ','); // ���ҵ�һ������
    if (start == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }

    start++; // ������һ������
    const char *end = strchr(start, ','); // ���ҵڶ�������
    if (end == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }

    // ���������ַ����ĳ��ȣ������Ƶ����������
    size_t length = end - start ;
    strncpy(output, start, length);
}


/*********************************************************************
 * @������         extract_data
 *
 * @����             �����ȡ����
 *
 * @����             input- Դ����
 *          output - ����������
 *
 * @����ֵ         �޷���ֵ
 */
void extract_data(const char *input, char *output) {
    const char *start = strchr(input, '+'); // ���ҵ�һ��+��
    if (start == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }
    start++; // ������һ��+��

    start = strchr(start, '+'); // ���ҵڶ���+��
    if (start == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }
    start++; // �����ڶ���+��

    start = strchr(start, ','); // ���ҽ��յ�����������ĵ�һ������
    if (start == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }
    start++; // �������յ�����������ĵ�һ������

    start = strchr(start, ','); // ���ҽ��յ�����������ĵڶ�������
    if (start == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }
    start++; // �������յ�����������ĵڶ�������

    const char *end = strchr(start, '\0'); // �����ַ�����β
    if (end == NULL) {
        output[0] = '\0'; // �����ַ�����ʽ����ȷ�����ؿ��ַ���
        return;
    }

    // ���������ַ����ĳ��ȣ������Ƶ����������
    size_t length = end - start;
    strncpy(output, start, length);
}


/*********************************************************************
 * @������         NearLink_SendData
 *
 * @����             ͨ��USART�������ݸ�NearLink����
 *
 * @����              USARTx- ѡ��USART����
 *          Data - ���͵�����
 *
 * @����ֵ         �޷���ֵ
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
 * @������         USARTx_CFG
 *
 * @����             ��ʼ��USART2����
 *
 *
 * @����ֵ         �޷���ֵ
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    //����GPIO��ʼ���ṹ��
    USART_InitTypeDef USART_InitStructure = {0};
    //����USART��ʼ���ṹ��
    NVIC_InitTypeDef  NVIC_InitStructure = {0};
    //����NVIC��ʼ���ṹ��

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    //ʹ��USART2��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    //ʹ��GPIOA��ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    //����PA2����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    //����Ƶ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    //�����������ģʽ
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //��ʼ��GPIOA��PA2����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    //����PA3����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //��������ģʽ
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //��ʼ��GPIOA��PA3����

    //����USART����
    USART_InitStructure.USART_BaudRate = 115200;
    //���ò�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    //����ÿ������֡����8λ����
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    //����ֹͣλ��
    USART_InitStructure.USART_Parity = USART_Parity_No;
    //���ò�ʹ����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //���ò�ʹ��Ӳ������
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    //���÷��ͽ���ģʽ

    USART_Init(USART2, &USART_InitStructure);
    //��ʼ��USART2
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //���� USART2�Ľ������ݼĴ����ǿ��ж�

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    //���� NVIC Ϊ USART2���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //���� USART2�жϵ���ռ���ȼ�Ϊ 1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    //���� USART2�жϵ������ȼ�Ϊ 1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    //ʹ�� USART2�ж�
    NVIC_Init(&NVIC_InitStructure);
    //��ʼ��NVIC

    USART_Cmd(USART2, ENABLE);
    //ʹ��USART2
}

/*********************************************************************
 * ������        main
 *
 * ��������    ������
 *
 * ����ֵ        �޷���ֵ
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //����NVIC���ж����ȼ�����
    SystemCoreClockUpdate();
    //����ϵͳ����ʱ��Ƶ��
    Delay_Init();
    //�ӳٺ�����ʼ��
    USART_Printf_Init(115200);
    //USART��ʼ�������ò�����Ϊ115200

    //��ӡϵͳ��Ϣ
    printf("SystemClk:%d\r\n", SystemCoreClock);
    //��ӡϵͳʱ��Ƶ��
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    //��ӡоƬ��Ϣ
    printf("NearLink_T Test\r\n");
    //��ӡ�ַ�����NearLink_T Test��
    USARTx_CFG();
    //�� USART2������г�ʼ����

    //STEP1:����AT�ȴ�������ʼ��
    NearLink_SendData(USART2, "AT\r\n");
    Delay_Ms(100);

    //STEP2:�ȴ�OK
    while(strstr((char *)RxBuffer, "OK") == NULL){}

    //STEP3:����AT+SEEK=1�ȴ���������OK
    NearLink_SendData(USART2,"AT+SEEK=1\r\n");
    Delay_Ms(200);
    while(strstr((char *)RxBuffer,"SEEKDATA") == NULL){}

    //STEP4:�����ص����ݣ��������ַ
    char NearLink_Address[100] = {0};
    extract_address(RxBuffer, NearLink_Address);

    //STEP5:����AT+SEEK=0�ȴ���������OK
    NearLink_SendData(USART2, "AT+SEEK=0\r\n");
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "OK") == NULL){}

    //STEP6:������һ���������ȴ�����OK
    char Nearlink_SetAddress[128]={0};
    sprintf(Nearlink_SetAddress,"AT+CONNECT=0,%s\r\n",NearLink_Address);
    NearLink_SendData(USART2, Nearlink_SetAddress);
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "OK") == NULL){}

    //STEP7:��������
    char Data[128]={"1234"};
    char Nearlink_Send_Data[128]={0};
    sprintf(Nearlink_Send_Data,"AT+SENDDATA=0,%s,%s\r\n",NearLink_Address,Data);
    NearLink_SendData(USART2,Nearlink_Send_Data);
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "OK") == NULL){}
    printf("NearLink Send Data Succeed\r\n");

    //STEP8:���շ�������
    while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != SET){}
    Delay_Ms(100);
    while(strstr((char *)RxBuffer, "RECEIVEDATA") == NULL){}
    printf("NearLink Receive Data Succeed\r\n");

    //STEP9:�����ص�����
    memset(Data, 0, sizeof(Data));
    extract_data(RxBuffer,Data);
    printf("Receive Data:%s\r\n",Data);


    while(1)
    {

    }
}

/*********************************************************************
 * ������       USART2_IRQHandler
 *
 * ��������   �˺������� USART2 ȫ���ж�����
 *
 * ����ֵ       �޷���ֵ
 */
void USART2_IRQHandler(void)
{
   if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET)
   //�ж� USART2 �����ж��Ƿ���
   {
       RxBuffer[RxCnt++] = USART_ReceiveData(USART2);
   }
}




