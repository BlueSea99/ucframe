/* Copyright (c) 2018 ��Ԫ
 * 20180101
 * LED
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCU_H
#define __MCU_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  char company[8];
  uint32_t chipid;
  uint32_t clock;
//  uint32_t ramsize;
//  uint32_t ramaddr;
//  uint32_t romsize;
//  uint32_t romaddr;
//  void (*EnISR);
//  void (*DisISR);	// �������ú궨���ʾ�õ�
//  void (*GetChipID);
//  void (*TaskSwitch);
#if 0
  uint32_t appaddr;
  uint32_t paramaddr;   // ������ַ�������ַ���ɷ��ڹ̶���ַ
  uint32_t externram;
  uint32_t externrom;
#endif
} mcu_t;
extern mcu_t mcu;

typedef struct
{
  uint8_t *configreg;
  uint8_t *controlreg;
  uint8_t *statusreg;
  uint8_t *datareg;
  uint8_t *inbuf;
  uint8_t *outbuf;
} register_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void MCUInit(void);

#endif

