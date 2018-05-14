/******************** (C) COPYRIGHT NOPEOPLE ******************************
* File Name          : log.c
* Author             : ME
* Version            : V1.0
* Date               : 2017.7.18
* Description        : log��
*******************************************************************************/

#include "include.h"
/**
*@brief	 ��ӡ������ʼ��
*@param	 ��
*@return ��
*/
void PrintfInit(void)
{
	PrintfChannelNet   = PRINTF_CHANNEL_DISABLE;  // ��ͨ�������ӡ
	PrintfChannelRS485 = PRINTF_CHANNEL_DISABLE;  // ��ͨ��485��ӡ
	PrintfChannelUsart = PRINTF_CHANNEL_ENABLE;   // ͨ�����ڴ�ӡ
	
	PrintfMessageTest = PRINTF_MESSAGE_DISABLE;  // ��ӡ������Ϣ��ֹ ����ʵû����
	PrintfMessageLog   = PRINTF_MESSAGE_ENABLE;   // �����ӡlog��Ϣ
}
/**
*@brief	  ѡ���ӡ��ͨ������Ҫ�ⲿ���ã�����Ӳ����Դ��ͬ�޸ģ�
					�ڲ����ﶨ��ȫ�ֱ���ѡ��Ĭ�϶�����ӡ
					�˰汾���ƴ�ӡ����Ϊ
*@param	  *format�������ʽ����
*@return  ��
*/
void PrintfChannel(uint8_t length)
{

	if (PrintfChannelNet == PRINTF_CHANNEL_ENABLE)   // �����ڴ�ӡ����
		;//tcp_write(0,printBuf,length);                       // ��ӡ����
	if (PrintfChannelRS485 == PRINTF_CHANNEL_ENABLE) // ��485�ڴ�ӡ
	{
//		 SetTxDMA(&sUart2TxDMA_,printBuf,length);      // ��ӡ����д�뻺��
//		_TaskUart2Tx.state = TASK_STATE_RUN;           // ����������������
	}
	if (PrintfChannelUsart == PRINTF_CHANNEL_ENABLE) // �����ڴ�ӡ
	{
//		SetTxDMA(&sUart5TxDMA_,printBuf,length);       // ��ӡ����д�뻺��   
//		_TaskUart5Tx.state = TASK_STATE_RUN;           // ��Э������������
	}
  
}

/**
*@brief	  log��ӡ�ô˺�����Ȼ��ת��PrintfChannel
*@param	  format����Ҫ��ӡ������
*@return  ��
*/
void LogPrintf(const char *format, ...)
{
	uint8_t length;
	if (PrintfMessageLog == PRINTF_MESSAGE_ENABLE)    // ��ӡLOG����
	{
		// �����ǽ���ӡ����ת��uint8_t��������
	  va_list args;
		va_start(args, format);
		length = vsnprintf((char*)printBuf, sizeof(printBuf), (char*)format, args); //��ʽ������
		va_end(args);
		if (length > PRINTF_LENGTH) // ���ݲ��ܳ�����ӡ����
			return;
		PrintfChannel(length);     // ������ӡ
	}
}

/**
*@brief	 test�����ô�ӡ�ô˺�����Ȼ��ת��PrintfChannel
*@param	 format����Ҫ��ӡ������
*@return ��
*/
void TestPrintf(const char *format, ...) // ��LOG��ӡ��ȫ��ͬ
{
	uint8_t length;
	if (PrintfMessageTest == PRINTF_MESSAGE_ENABLE)
	{
		va_list args;
		va_start(args, format);
		length = vsnprintf((char*)printBuf, sizeof(printBuf), (char*)format, args);//��ʽ������
		va_end(args);
		if (length > PRINTF_LENGTH)
			return;
		PrintfChannel(length);
	}
	
}









