/**
*************************(C) COPYRIGHT 2017 RuiTu Tech********************************************
* @file         bfm_w5500.h
* @author       zhou
* @version      V1.0
* @date         2018/5/4
* @brief        w5500����ͷ�ļ�
**************************************************************************************************
*/
#ifndef _BFM_W5500_H_
#define _BFM_W5500_H_
#include "include.h"

typedef  void (*pFunction)(void);


/*����SPI1��ΪW5500��Ӳ���ӿ�*/
#define WIZ_SCS                 GPIO_Pin_4                /*����W5500��Ƭѡ�ܽ�*/
#define WIZ_SCLK                GPIO_Pin_5                /*����W5500��ʱ�ӹܽ�*/
#define WIZ_MISO                GPIO_Pin_6                /*����W5500��MISO�ܽ�*/
#define WIZ_MOSI                GPIO_Pin_7                /*����W5500��MOSI�ܽ�*/
#define WIZ_RESET               GPIO_Pin_5                /*����W5500��RESET�ܽ�*/
#define WIZ_INT                 GPIO_Pin_4                /*����W5500��INT�ܽ�*/

/*����SPI2��ΪW5500��Ӳ���ӿ�*/
#define WIZ_SCS2                GPIO_Pin_12               /*����W5500��Ƭѡ�ܽ�*/
#define WIZ_SCLK2               GPIO_Pin_13               /*����W5500��ʱ�ӹܽ�*/
#define WIZ_MISO2               GPIO_Pin_14               /*����W5500��MISO�ܽ�*/
#define WIZ_MOSI2               GPIO_Pin_15               /*����W5500��MOSI�ܽ�*/
#define WIZ_RESET2              GPIO_Pin_7                /*����W5500��RESET�ܽ�*/
#define WIZ_INT2                GPIO_Pin_6                /*����W5500��INT�ܽ�*/

#define FW_VER_HIGH             1
#define FW_VER_LOW              0
#define ON                      1
#define OFF                     0
#define HIGH                    1
#define LOW                     0

#define MAX_BUF_SIZE            1460                       /*����ÿ�����ݰ��Ĵ�С*/
#define KEEP_ALIVE_TIME         30  // 30sec
#define TX_RX_MAX_BUF_SIZE      2048
#define EEPROM_MSG_LEN          sizeof(EEPROM_MSG)

#define IP_FROM_DEFINE                    0                /*ʹ�ó�ʼ�����IP��Ϣ*/
#define IP_FROM_DHCP                      1                /*ʹ��DHCP��ȡIP��Ϣ*/
#define IP_FROM_EEPROM                    2                /*ʹ��EEPROM�����IP��Ϣ*/
extern uint8_t  ip_from;                                     /*ѡ��IP��Ϣ����Դ*/

#pragma pack(1)
/*�˽ṹ�嶨����W5500�ɹ����õ���Ҫ����*/
typedef struct _CONFIG_MSG
{
  uint8_t macAddress[6];                                      //*MAC��ַ*/
  uint8_t localIP[4];                                         //*local IP����IP��ַ*/
  uint8_t subnetMask[4];                                      //*��������*/
  uint8_t gateWay[4];                                         //*����*/
  uint8_t dns[4];                                             //*DNS��������ַ*/
  uint8_t remoteIP[4];                                        //*remote IPԶ��IP��ַ*/
  uint16_t localPort;                                         // ���ض˿�
  uint16_t remotePort;                                        // Զ�̶˿�
}S_W5500_CONFIG;
#pragma pack()

extern S_W5500_CONFIG   ConfigMsg;

/*MCU������غ���*/
void gpio_for_w5500_config(void);                           /*SPI�ӿ�reset ���ж�����*/
void gpio_for_w5500_config1(void);

/*W5500SPI��غ���*/
void w5500_write_byte( uint32_t addrbsb,  uint8_t data);           /*д��һ��8λ���ݵ�W5500*/
uint8_t w5500_read_byte(uint32_t addrbsb);                         /*��W5500����һ��8λ����*/
uint16_t w5500_write_buf(uint32_t addrbsb,uint8_t* buf,uint16_t len); /*��W5500д��len�ֽ�����*/
uint16_t w5500_read_buf(uint32_t addrbsb, uint8_t* buf,uint16_t len); /*��W5500����len�ֽ�����*/


/*--------------- �궨�� --------------*/
#define W5500_WRITE_PARAMETER     1  // д�����궨�壬����ֵ����Ϊ�Ƕ�

// �ܽ�����
#define W5500_CS_HIGH          GPIO_SetBits( W5500_NSS_GPIO_Port,W5500_NSS_Pin);
#define W5500_CS_LOW           GPIO_ResetBits( W5500_NSS_GPIO_Port,W5500_NSS_Pin);
#define W5500_RESET_HIGH       GPIO_SetBits( W5500_RSTN_GPIO_Port,W5500_RSTN_Pin);
#define W5500_RESET_LOW        GPIO_ResetBits( W5500_RSTN_GPIO_Port,W5500_RSTN_Pin);

// spi��д����
#define W5500_SEND_GET_BYTE(sendByte,getByte) spi_send_get_data( sendByte, getByte);

/*--------------- �������� --------------*/

/*--------------- �������� --------------*/
void w5500_config_ip(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_gateway(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_subnetMask(S_W5500_CONFIG *configData, uint8_t readOrWrite);
void w5500_config_macAddress(S_W5500_CONFIG *configData, uint8_t readOrWrite);

void w5500_restart(void);
#endif

