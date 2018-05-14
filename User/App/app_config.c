/**
*************************(C) COPYRIGHT 2017 ********************************************
* @file         app_config.c
* @author       zhou
* @version      V1.0
* @date         2018/1/12
* @brief        �����ļ�
**************************************************************************************************
*/
#include "include.h"


void set_platform(void);
uint8_t version_[16] = {'R','I','O','-','V','1','0','0','-','1','8','0','1','1','0','0'};
/**
*@brief
*@param
*@return
*/
void task_config_init(void)
{
    _TaskConfig.fun     = task_config;
    _TaskConfig.rxBuf   = &sParamConfig_;
    _TaskConfig.command = CMD_TASK_CONFIG;
}

/**
*@brief
*@param
*@return
*/
void task_config(void)
{
    switch(sParamConfig_.configCMD)
    {

    }
    memset(&sParamConfig_,0,sizeof(sParamConfig_));
    _TaskConfig.state = TASK_STATE_SLEEP;
}
///*--------------------�����ϴ�ң�ر���----------------*/
///**
//*@brief     ����һ���ϴ�ң�ر��룬ͨ������
//*@param     ��
//*@return  ��
//*/
//void GetRemote(void)
//{
//  remoteUpFlag_ = _TaskConfig.port;
//}
/*---------------------IP����--------------------------*/
/**
*@brief   ����IP��ַ
*@param   ��
*@return  ��
*/
//void SetIP(void)
//{
//  Param_now.local_ip2[0] = sParamConfig_.param0; // ȡ�·���4λIP
//  Param_now.local_ip2[1] = sParamConfig_.param1;
//  Param_now.local_ip2[2] = sParamConfig_.param2;
//  Param_now.local_ip2[3] = sParamConfig_.param3;
//  Param_SAVE();   // ����
//
//  GetIP();  // �ϴ�������ɵ�IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   ��ȡIP���ϴ�
*@param   ��
*@return  ��
*/
void GetIP(void)
{

}

///*------------------------��������-------------------------*/
///**
//*@brief     ��������
//*@param     ��
//*@return  ��
//*/
//void SetGateWay(void)
//{
//  Param_now.gateway2[0] = sParamConfig_.param0; // ȡ�·���4λIP
//  Param_now.gateway2[1] = sParamConfig_.param1;
//  Param_now.gateway2[2] = sParamConfig_.param2;
//  Param_now.gateway2[3] = sParamConfig_.param3;
//  Param_SAVE();   // ����
//
//  GetGateWay();   // �ϴ�������ɵ�IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   ��ȡ���ز��ϴ�
*@param   ��
*@return  ��
*/
void GetGateWay(void)
{

}
///*------------------�˿�����---------------------------------*/
///**
//*@brief     ���ö˿�
//*@param     ��
//*@return  ��
//*/
//void SetPort(void)
//{
//  Param_now.local_port = ((sParamConfig_.param1 << 8) | (sParamConfig_.param0));
//  Param_SAVE();   // ����
//  GetPort();
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   ��ȡ�˿ڲ��ϴ�
*@param   ��
*@return  ��
*/
void GetPort(void)
{

}
///*------------------------MAC��ַ-------------------------------*/
///**
//*@brief     ����MAC��ַ
//*@param     ��
//*@return  ��
//*/
//void SetMACAddress(void)
//{
//  Param_now.mac2[0] = sParamConfig_.param0;
//  Param_now.mac2[1] = sParamConfig_.param1;
//  Param_now.mac2[2] = sParamConfig_.param2;
//  Param_now.mac2[3] = sParamConfig_.param3;
//  Param_now.mac2[4] = sParamConfig_.param4;
//  Param_now.mac2[5] = sParamConfig_.param5;
//
//  Param_SAVE();   // ����
//
//  GetMACAddress();   // �ϴ�������ɵ�IP
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}

/**
*@brief   ��ȡMAC��ַ���ϴ�
*@param   ��
*@return  ��
*/
void GetMACAddress(void)
{

}
/*---------------------��ȡվ̨���---------------------*/
/**
*@brief   ��ȡվ̨��Ų��ϴ������뿪��ֵ
*@param   ��
*@return  ��
*/
void GetPlatform(void)
{

}
void set_platform(void)
{

}

/*----------------------�汾��----------------------------*/
/**
*@brief   ��ȡ�汾�Ų��ϴ�,VΪ��ʽ�棬TΪ���԰棬FΪ�������԰棬BΪ��֧�棬�������ܲ��Զ���
*@param   ��
*@return  ��
*/
void GetVersion(void)
{
   // tx_data_processing(version_,16,CMD_GET_VER,_TaskConfig.port);
}
/*----------------------SN��-------------------------------*/
/**
*@brief   ��ȡSN�Ų��ϴ�
*@param   ��
*@return  ��
*/
void GetSN(void)
{
    uint8_t snData[12];
    snData[0]   = *(char*)(0x1FFFF7F3); // ��ȡSN�룬����ST�����Flash��
    snData[1]   = *(char*)(0x1FFFF7F2);
    snData[2]   = *(char*)(0x1FFFF7F1);
    snData[3]   = *(char*)(0x1FFFF7F0);
    snData[4]   = *(char*)(0x1FFFF7EF);
    snData[5]   = *(char*)(0x1FFFF7EE);
    snData[6]   = *(char*)(0x1FFFF7ED);
    snData[7]   = *(char*)(0x1FFFF7EC);
    snData[8]   = *(char*)(0x1FFFF7EB);
    snData[9]   = *(char*)(0x1FFFF7EA);
    snData[10]  = *(char*)(0x1FFFF7E9);
    snData[11]  = *(char*)(0x1FFFF7E8);

  //  tx_data_processing(snData,12,CMD_GET_SN,_TaskConfig.port);
}
///*---------------��������---------------------*/
///**
//*@brief     �ָ���������
//*@param     ��
//*@return  ��
//*/
//void ResetFactory(void)
//{
//  uint8_t empty[2];
//  Param_Init();
//  Param_READ();
//  ConfigSendPackage(CMD_FACTORY_SET,empty,0,_TaskConfig.port);
//  _TaskTcpConfig.state = TASK_STATE_RUN;
//}
/*----------------����--------------------------*/
/**
*@brief   ������·�壬ͨ�����Ź���ʱ
*@param   ��
*@return  ��
*/
void RestartBoard(void)
{
    SystemReset();
}
/*------------------------���ʹ������-----------------------*/
/**
*@brief   ͳһ���ʹ������
*@param   instruct:ָ��
*@return  ��
*/
//void ConfigSendPackage(uint8_t instruct,uint8_t *buf,uint8_t len,uint8_t sendType)
//{
//  uUINT16 crc16;
//  uint8_t i;
//  uint8_t sendData[30];
//  sendData[0] = 0xFD;      // ��ͷ
//  sendData[1] = 0xF7;
//  sendData[2] = cmdTick_++;   // ָ�����
//  sendData[3] = len + 7;          // ���ݰ�����
//  sendData[4] = instruct;     // ָ����
//  for (i = 0; i < len; i++)   // ����
//  {
//      sendData[5 + i] = buf[i];
//  }
//  crc16.word = CRC16(sendData,len + 5);        // У��
//  sendData[len + 5] = crc16.HL.H;
//  sendData[len + 6] = crc16.HL.L;
//  if (sendType == COM_TYPE_UART3)
//  {
//      SetTxDMA(&sUart3TxDMA_,sendData,len + 7);   // ���뷢�ͻ���
//      _TaskUart3Tx.state   = TASK_STATE_RUN;      // ��������
//  }
//  if (sendType == COM_TYPE_UART2)
//  {
//      SetTxDMA(&sUart5TxDMA_,sendData,len + 7);   // ���뷢�ͻ���
//      _TaskUart2Tx.state   = TASK_STATE_RUN;      // ��������
//  }
//  if (sendType == COM_TYPE_NET)
//  {
//      send(0,sendData,len + 7);
//  }
//}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/




