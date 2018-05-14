/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         api_motor.h
* @author       zhou
* @version      V1.0
* @date         2018/5/7
* @brief        ����ӿں���ͷ�ļ�
**************************************************************************************************
*/
#ifndef _API_MOTOR_H_
#define _API_MOTOR_H_
#include "include.h"
/*--------------- �궨�� --------------*/
// ���canopen����
// nmt��ָ����
#define START_REMOTE_NODE              1 // ����Զ�̽ڵ�
#define STOP_REMOTE_NODE               2 // �ر�Զ�̽ڵ�
#define ENTER_PREOPERATIONAL_STATE     128 // ����Ԥ����״̬
#define RESET_NODE                     129 // ��λ���
#define RESET_COMMUNICTION             130 // ��λͨ��

// ID����
#define SYNCHRONIZATION_CYCLE_ID       0x000601 // ͬ��������������� Cycle synchronization
#define SYNCHRONIZATION_START_ID       0x000601 // ��������ͬ��
#define NMT_BROADCAST_ID               0x000000 // NMT�õĹ㲥ID
#define NMT_BROADCAST_ID               0x000000 // NMT�õĹ㲥ID
/*--------------- �������� --------------*/

/*--------------- �������� --------------*/

#endif

