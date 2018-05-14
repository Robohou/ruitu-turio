/******************** (C) COPYRIGHT PEOPLE ******************************
* File Name          : task.h
* Author             : ME
* Version            : V1.0
* Date               : 2016.12.2
* Description        : �����ļ�ͷ�ļ�
*******************************************************************************/
#ifndef  _TASK_H_
#define  _TASK_H_

#include "include.h"
/*******************�궨��*************************/

//*************������ض���***********************/
//#define TASK_MAX                28
//#define NULL                   0
#define TASK_BAR_CMD             0
#define TASK_INFO_NORMAL         1
#define TASK_INFO_ERROR          0
// ����״̬
#define   TASK_STATE_RUN     0x01
#define   TASK_STATE_DELAY   0x02
#define   TASK_STATE_SLEEP   0x03
// ����������
#define CMD_TASK_IDLE         0xE0     // ��������ָ��-������
// ����ṹ��
typedef uint8_t  TASK;
typedef struct
{
    volatile TASK        state;               // ����״̬
    TASK                 progressBar;         // ������
    TASK                 command;             // ָ��
    TASK                 port;           // �ӿ�
    volatile TASK        info;                // ��Ϣ
    TASK                 rxLen;               // �������ݳ���
    TASK                 txLen;               // �������ݳ���
    uint32_t             interval;            // ��϶
    volatile uint32_t    timeOut;             // ��ʱ
    void                 *rxBuf;              // �������ݴ���������ʼ��ʱ��ֵ
    void                 *txBuf;              // ����
    void                 (*init)(void);       // ��ʼ������
    void                 (*alteration)(void); // �������
    void                 (*fun)(void);        // ������
}sTASK;

/**********************��������**********************/
void task_init(void);
void task_add(uint8_t taskId,sTASK* taskname,void (*init)(void));
void task_cmd(uint8_t *buf, uint8_t len,uint8_t port);
void task_run(void);
void task_idle_init(void);
void task_idle(void);

#endif



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/




