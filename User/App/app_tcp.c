/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_tcp.c
* @author       zhou
* @version      V1.0
* @date         2018/5/8
* @brief        ����w5500��tcpӦ�ó�
**************************************************************************************************
*/
#include "include.h"
uint8_t buff[1000];
/**
*@brief   TCP Server�ػ���ʾ������
*@param   ��
*@return  ��
*/
void do_tcp_server(void)
{
  uint16_t len=0;
  switch(getSn_SR(SOCK_TCPS))                                   /*��ȡsocket��״̬*/
  {
    case SOCK_CLOSED:                                           /*socket���ڹر�״̬*/
      socket(SOCK_TCPS, Sn_MR_TCP, sDefaultNetConfig_.localPort, Sn_MR_ND);         /*��socket*/
      break;

    case SOCK_INIT:                                             /*socket�ѳ�ʼ��״̬*/
      listen(SOCK_TCPS);                                        /*socket��������*/
      break;

    case SOCK_ESTABLISHED:                                      /*socket�������ӽ���״̬*/
      if(getSn_IR(SOCK_TCPS) & Sn_IR_CON)
      {
        setSn_IR(SOCK_TCPS, Sn_IR_CON);                         /*��������жϱ�־λ*/
      }
      len=getSn_RX_RSR(SOCK_TCPS);                              /*����lenΪ�ѽ������ݵĳ���*/
      if(len>0)
      {
        recv(SOCK_TCPS,buff,len);                               /*��������Client������*/
        send(SOCK_TCPS,buff,len);
      }
      break;
    case SOCK_CLOSE_WAIT:                                       /*socket���ڵȴ��ر�״̬*/

      close(SOCK_TCPS);
      break;
  }
}
