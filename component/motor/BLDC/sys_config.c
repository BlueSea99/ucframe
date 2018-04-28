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
* ��������: 
* ��������: ��
* ����ֵ:   ��
* ����:     
*************************************************************/
void interrapt_init(void)
{

}

void  RSET_io()
{
  Gpio_Init();
   PC5_OUT=1;
   PC6_OUT=1;
   PC7_OUT=1;
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
//ʱ�ӳ�ʼ��-�ڲ�RC -16Mhz== 	
	sys_clk_init();
//==�ж����ȼ���ʼ��========
	Gpio_interruput_Init();
		
//===�������жϹ�..=========
	_asm("sim");
//==io�˿ڳ�ʼ��-===========
		
	Gpio_Init(); 
	PB7_OUT=0;
	PB6_OUT=0;
	PE5_OUT =0;
	PF4_OUT=0;
						
//===pwm���������ʼ��======
//=��ʼ����ʱ��1λPWM��ʽ===
	PWM_INIT();    
//==adc ��ʼ��==============
//==����ʱ��ע�뷽ʽ========
//	adc_init();     //adc��ʼ��

//==tim5 16λ��ʱ��=========
	TIM5_Conf();	 
//==tim5 8λ��ʱ��==========
			
	Tim6Init();
		
		
  #if 0		//-------------------------------
	  POWER_SW_OF	   //�̵�����ʼ��
    PER_LED_ON
  	GREEN_LED_ON
	  uart_init();   // ���ڳ�ʼ��--������9600
	//=======================================
	//������ʼ���-----------------------------
  //PC5_OUT =1;
	//PD6_OUT=0;
	//check_voltage();//�����ݳ�����=====
//	for(i=0;i<200;i++)delay();//��ʱ��緽ʽ
//	PER_LED_OF
//	GREEN_LED_ON
//	duty=2;
	//--------------------------------------
// 	ioget =ch_sw();
#endif	//--------------------------------


//===������ʱ������=======================
	TIM5_StartCount();
//  Motordata.station= Frun;
//	ADC_CR1_ADON = 1;  
//	ADC_CR1_ADON = 1;  
	_asm("rim");//�жϿ�.................
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
