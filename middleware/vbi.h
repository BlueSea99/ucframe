/* Copyright (c) 2018 ��Ԫ
 * 20180101
 * �������߽ӿ�
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VBI_H
#define __VBI_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/

//typedef struct
//{
//  void bustype;
//  void datatype;
//  void *data;
//  uint32_t lenth;
//} interface_t;

typedef enum
{
  USBIN, USBOUT, USARTTX, USARTRX, SPIREAD, SPIWRITE
} interface_t;


/* circular queue */

typedef struct
{
  interface_t bustype;
  uint8_t size;
  uint8_t *data;
  uint8_t checkcode;
} circularqueue_t;      // fifo_t?
//extern circularqueue_t *circularqueue;

/* COMMON */
typedef struct
{
  uint8_t indata[64];
  uint8_t outdata[64];
  uint8_t *pbuf;
//  void (*CommonInit)(void);
//  void (*CommonDeInit)(void);
  void (*printf)(void);
  void (*TxData)(int8_t *pdata, uint16_t size);
  void (*RxData)(int8_t *pdata, uint16_t size);
} common_t;

/* IC proc */
typedef struct
{
  uint8_t cmd[2];
  uint8_t cmdsize;
  uint8_t addrsize; 
  uint8_t addr[4];
  uint8_t reg[4];
  uint16_t readsize;
  uint16_t writesize;
  uint8_t *data;
  void (*read)(void *pointhandle, ...);
  void (*write)(void *pointhandle, ...);
} cmdparam_t;   // ���ܲ�������ͨ�ñ�׼оƬ��д�ṹ
/* interface */
typedef struct
{
  uint8_t sfd;          // ֡��ʼ�� #define �̶� 0xA5
  uint8_t devid;        // һ���һ��ֻ��0x01��0x00������0xff�㲥��ַ
  uint16_t length;      // Ҫ��Ҫ���һ��flag��ǰ�棿�ط�������
  uint8_t cmd;          // ָ��
  uint8_t cmdplusl;     // ��չָ��
  uint8_t cmdplush;     // ��չָ��
  uint8_t checkcode;    // ��ʲôУ����õ�
  uint8_t *pdata;       //
//  uint16_t eop;         // 0x0d 0x0a�����س�����
} cmdpackets_t;         //comprotocol_t; datacom

typedef struct
{
  uint8_t cmd;
  uint8_t param;
  uint16_t checkcode;
  uint8_t data[64];
  void (*CheckPackets)(void);
  void (*PacketsParse)(void);
  void (*Handshake)(void);      // ����ָ��
} vbi_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

