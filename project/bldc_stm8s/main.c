/**********************************************************
*name   : main.c
*detail : ���������
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "board.h"
#include "motor.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/

// 
int main( void )
{
  PlatfrmInit();
  BoardInit();  
  MotorInit();
  dlay(50000);
  
  while (1)
  {
    Motor_ip();                 // �����������
    Check_switch_onff();        // ����״̬��ȡ

    if( (Motordata.station==Stop) && (Motordata.UI.blink>0) )   
    {
      if(showsp[Motordata.UI.showcount] == 1)
      {
        Disp_error_on();  
      }
      else
      {
        Disp_error_of();  
      }	
    }

    Motor_Run();
  }
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/




