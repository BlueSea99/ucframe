/* Copyright (c) ��Ԫ
 * 20180101
 * ʱ����
 */

/* Includes ------------------------------------------------------------------*/
#include "time.h"

/* Exported define -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* DATATIME */
datatime_t datatime;

void Delay(uint16_t delay)
{
  uint32_t tickstart = 0U;
  
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < delay)
  {
  }
}
// ����ע������ʱ��
void CreatDataTime(void)
{
//  datatime.DatatimeSet = DatatimeSet;
  
  datatime.Delay = Delay;
}