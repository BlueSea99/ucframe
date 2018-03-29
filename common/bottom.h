/* Copyright (c) 2018 ��Ԫ
 * 20180101
 * BOTTOM��
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOTTOM_H
#define __BOTTOM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  KEYUP, KEYDOWNWOBBLE, KEYDOWN, KEYLONGDOWN, KEYUPWOBBLE, DOUBLECLKICKWOBBLE, DOUBLECLKICK
} keystate_t;

typedef struct
{
  keystate_t keystate;
  uint16_t stabletimecnt;
  uint16_t lasttimecnt;		// �����Ч״̬ʱ�䣬���߼�down���� up���㣬˫���ж���
  void (*CreatKey)(void);
  uint8_t (*GetKey)(void);		// 
  void (*RefreshKey)(void);	// ����1ms��ʱ��
} key_t;

typedef struct
{
  uint32_t delay;
  void (*config)(void);
} bottom_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void BottomConfig(void);

#endif