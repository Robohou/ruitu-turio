/******************** (C) COPYRIGHT PEOPLE ******************************
* File Name          : log.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.12.2
* Description        : ��־�ļ�ͷ�ļ�
*******************************************************************************/
#ifndef  _LOG_H_
#define  _LOG_H_

#include "include.h"
/*******************�궨��*************************/
#define PRINTF_LENGTH              TX_BUF_SIZE  // ���Ȳ�����tx���ͳ���

#define PRINTF_CHANNEL_DISABLE     1
#define PRINTF_CHANNEL_ENABLE      3

#define PRINTF_MESSAGE_DISABLE     1
#define PRINTF_MESSAGE_ENABLE      5
//*************������ض���***********************/

/**************������ض���**********************/
void PrintfInit(void);
void LogPrintf(const char *format, ...);
void TestPrintf(const char *format, ...);
void PrintfChannel(uint8_t length);
#endif

