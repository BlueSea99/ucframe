/**********************************************************
*name   : motor.c
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "motor.h"
//#include "stm8s_type.h" 
//#include "stm8s903k.h" 
//#include "gpio.h"
//#include "uart.h"
//#include "stm8_bit.h"
//#include "tim.h"
//#include "adc.h"
#include "mc_config.h"
#include "param.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/

/*  functions ----------------------------------------------------------------*/


/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/


void sys_clk_init()
     {
       CLK_CKDIVR=(0x00|0x00);
	  	}

/************************************************************
* 函数名称: 
* 参数描述: 无
* 返回值:   无
* 描述:     
*************************************************************/
void interrapt_init(void)
{

}

void  RSET_io()
{
  Gpio_Init();
  GPIOC->ODR |= 0x1f;        //PC5_OUT=1;PC6_OUT=1;PC7_OUT=1;
}

//
void delay(void)
     {int i;
		  for(i=0;i<10000;i++);
      
    }


//
void Sys_Init(void)
{   
	u8 i;
//时钟初始化-内部RC -16Mhz== 	
	sys_clk_init();
//==中断优先级初始化========
	Gpio_interruput_Init();
		
//===关所有中断关..=========
	_asm("sim");
//==io端口初始化-===========
		
	Gpio_Init(); 
	PB7_OUT=0;
	PB6_OUT=0;
	PE5_OUT =0;
	PF4_OUT=0;
						
//===pwm方波输出初始化======
//=初始化定时器1位PWM方式===
	PWM_INIT();    
//==adc 初始化==============
//==启动时按注入方式========
//	adc_init();     //adc初始化

//==tim5 16位定时器=========
	TIM5_Conf();	 
//==tim5 8位定时器==========
			
	Tim6Init();
		
		
  #if 0		//-------------------------------
	  POWER_SW_OF	   //继电器初始化
    PER_LED_ON
  	GREEN_LED_ON
	  uart_init();   // 串口初始化--波特率9600
	//=======================================
	//参数初始化�-----------------------------
  //PC5_OUT =1;
	//PD6_OUT=0;
	//check_voltage();//检测电容充电过程=====
//	for(i=0;i<200;i++)delay();//延时充电方式
//	PER_LED_OF
//	GREEN_LED_ON
//	duty=2;
	//--------------------------------------
// 	ioget =ch_sw();
#endif	//--------------------------------


//===启动定时器工作=======================
	TIM5_StartCount();
//  Motordata.station= Frun;
//	ADC_CR1_ADON = 1;  
//	ADC_CR1_ADON = 1;  
	_asm("rim");//中断开.................
	//

}
//========================================

//
void Motor_Init(void)
{
	
	Motordata.station= Ready;
	Adc_SetUp_Init();
	_asm("rim");
}
