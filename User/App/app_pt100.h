/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         app_pt100.h
* @author       zhou
* @version      V1.0
* @date         2018/5/11
* @brief        pt100���Ƴ���ͷ�ļ�
**************************************************************************************************
*/
#ifndef _APP_PT100_H_
#define _APP_PT100_H_
#include "include.h"
/*--------------- �궨�� --------------*/
#define REFERENCE_RESISTANCE            200   // �ο�����ֵ
#define REFERENCE_GAIN                  (REFERENCE_RESISTANCE * 10000) // �ο�����ֵ
#define DIVIDER_RESISTANCE              1000 // ��ѹ����
#define REFERENCE_AD_VALUE              2048  // �ο���ѹ��Ӧ��ADֵ
#define A_ACCURACY                      3908 // 0.390802
#define GAIN                            10
#define AD_GANI                         (4096*GAIN)
/**
    ������ѹ���㣺Vsamp = ��adc_value/4096��*3.3
    �����ű�ѹ�Vdif = (Rx/(divider_resistance + Rx))
                       - (refernce_resistance/(divider_resistance +refernce_resistance))
    �Ŵ��ѹ:��Ϊ�л�׼��ѹΪ3.3/2,�Ŵ��ѹ Vamp = Vsamp - 3.3/2
    ����:A = 80
    Vamp = A * Vdif
    �����õ�:Rx = (2048-adc_value��*computer_factor+refernce_resistance
    computer_factor = ����3.3/4096��/ 80��* divider_resistance
    */
#define COMPUTER_FACTOR                     1007  // ��������0.1007080078125 ����10000�������ý���float����
/*--------------- �������� --------------*/

/*--------------- �������� --------------*/

uint16_t computer_tempature(uint16_t adcValue);
#endif


/*********************************************************************************************************
**                                        End Of File
*********************************************************************************************************/




