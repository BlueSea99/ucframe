/* Copyright (c) 2018 pace ��Ԫ
 * 20180101
 * ͨ�Žӿ�
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CI_H
#define __CI_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"
#include "cmsis_os.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t delay;
  void (*Config)(void);
} ci_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CIConfig(void);

#endif