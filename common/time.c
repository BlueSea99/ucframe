/**********************************************************
*name   : time.c
*detail : ʱ����غ���
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "time.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
datatime_t datatime;

/*  functions ----------------------------------------------------------------*/
// 
void Delay(uint16_t delay)
{
//  uint32_t tickstart = 0U;
  
//  tickstart = HAL_GetTick();
//  while((HAL_GetTick() - tickstart) < delay)
  {
  }
}

// ����ע������ʱ��
void CreatDataTime(void)
{
//  datatime.DatatimeSet = DatatimeSet;
  
  datatime.Delay = Delay;
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


