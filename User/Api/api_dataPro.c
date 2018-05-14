/*
*************************(C) COPYRIGHT 2017 ********************************************
* @file         api_dataPro.c
* @author       zhou
* @version      V1.0
* @date         2018/1/11
* @brief        cte���ݴ�����
**************************************************************************************************
*/
#include "include.h"

void rx_data_processing(uint8_t *buf,uint16_t len,uint8_t mode)
{
    //TcpWriteData(buf,len);
    uint8_t recData[30];
    uint16_t i = 0;
    uint16_t recLen = 0;
    // �ж������ֽ�
    while (i < len)
    {
      // �����ͷ��ID���Լ��Ľ������ݴ���
      if ((buf[i] == 0xFD) && (buf[i + 1] == 0xF7))// && ((buf[i + 4] == GetID()) ||(buf[i + 4] == 0xF7) ))
      {
        recLen = ((buf[i + 2] << 8) + buf[i + 3]); // ֻ����������ĳ���
        if ((recLen < 9) || (recLen > 1032))
        {
//            printf("err cmd = %d",recData[0]);
//            printf("err len = %d",recLen);
            break;
        }
        else
            recLen -= 8;
        task_cmd(&buf[i + 5], recLen + 2, mode);                   // ִ��������
        i += (recLen + 7);
      }
      i++;
    }
}

/**
*@brief    �������ݴ������
*@param     buf����Ҫ��������� len����Ҫ��������ݳ��� instr:ָ�� mode��ģʽ
*@return 0:ʧ�� 1���ɹ�
*/
uint8_t tx_data_processing(uint8_t *buf, uint16_t len, uint8_t instr, uint8_t mode)
{
   uint8_t cteTxData_[100];
   // 8�ֽڣ���ͷ2bytes+����2bytes+ID 1byte+ָ��1byte+��ʷ���1byte+��β1byte
   cteTxData_[0] = 0xFD;
   cteTxData_[1] = 0xF7;
   cteTxData_[2] = (uint8_t)(((len + 8) & 0xFF00) >> 8); // ȡ���ݳ��ȸ��ֽ�
   cteTxData_[3] = (uint8_t)((len + 8) & 0x00FF);        // ȡ���ݳ��ȵ��ֽ�
//   cteTxData_[4] = GetID();                              // ��ȡID
   cteTxData_[5] = instr;                                // ָ��
   memcpy(&cteTxData_[6], buf, len);
   cteTxData_[len + 6] = cmdTick_++;
   cteTxData_[len + 7] = 0x16;
   if (mode == COM_TYPE_ETHERNET)                       // ͨ������ͨ��
   {

   }
   else if (mode == COM_TYPE_RS485)                  // ͨ��������PC���ʹ�ӡ����
   {
      Circle_Write_Data(&sUart1TxCircleBuf_, cteTxData_, len + 8);       // ��ӡ����д�뻺��
   }

   return 1;
}



/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/




