/* Copyright (c) 2017 pace ��Ԫ
 * 
 * fingerprint identification
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KEY_H
#define __KEY_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported define -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* KEY */
typedef enum
{
  KEYUP, KEYDOWNWOBBLE, KEYDOWN, KEYLONGDOWN, KEYUPWOBBLE, DOUBLECLKICKWOBBLE, DOUBLECLKICK, IDLESTATE
} keystate_t;

typedef struct
{
  keystate_t keystate;
  keystate_t laststate;         // �����Ч״̬����ʱ����IDLE��˫���ж���
  keystate_t keycallbackflag;
  uint16_t stabletimecnt;	
//  void (*CreatKey)(void);
  uint8_t (*GetKey)(void);      // ��ȡ����״̬����Ҫ�����Ӧ��IO״̬�ж�
  void (*RefreshKey)(void);	// ����1ms��ʱ��
} key_t;
extern key_t key;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void CreatKey(void);
#endif