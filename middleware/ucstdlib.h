/* Copyright (c) 2018 ��Ԫ
 * 20180101
 * Ƕ��ʽ��׼�⺯��
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UCSTDLIB_H
#define __UCSTDLIB_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  void (*strlen);
  void (*strcmp);
  void (*memcpy);
  void (*fgetc);
  void (*fputc);
  void (*printf);
} ucstdlib_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

