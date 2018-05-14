/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         can.h
* @author       zhou
* @version      V1.0
* @date         2017-08-11
* @brief        can��ͨ��ͷ�ļ�
**************************************************************************************************
*/
#ifndef  _CAN_H_
#define  _CAN_H_

#include "include.h"

/********* �궨�� *************/

/********* �������� *************/
#define CAN_BUF_LENGTH    150
typedef struct
{
  volatile uint8_t top;
  uint8_t          tail;
  uint8_t          length;
  CanRxMsg         rxMsg[CAN_BUF_LENGTH];
}sCAN_BUF;
typedef struct
{
  uint8_t canCmd;  // ������Canͨ�����ݼ��е�һ��������
  uint8_t canType; // ������ݵ���Դcan1����can2
  uint8_t cmd;     // ����ָ��
  uint8_t dir;     // ���ݷ��ͷ��򣬹̶�Ϊ����
  uint8_t addr;    // �������ݵ�Դ��ַ
  uint8_t data[8]; // ��������
}sCAN_PROTOCOL;

/********* �������� *************/

void can1_init(void);
uint8_t can_tx_data_package(CAN_TypeDef *hcan, uint8_t *buf, uint8_t len, uint32_t identifier,uint8_t frameMode);
#endif




/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/




