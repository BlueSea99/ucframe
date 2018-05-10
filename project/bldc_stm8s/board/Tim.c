/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

#include "platform.h"
#include "tim.h"
#include "param.h"

/******************************************************************
*  Description    : It initializes PWM and ADC peripherals
*  TRG0 for TIM6 COUNT CLK,TIMI1 DO not stop 
*******************************************************************/
void PWM_INIT(void)
{
  TIM1->SR1 = 0x00;     // clear int flag
  TIM1->CR1 = 0x05;     // 0x81;//TIM1_CR1_CEN=1 //start count  UDIS =1 
  TIM1->CR2 = 0x71;     // 0x21 ccpc=1; TRGO=UPDATE
  TIM1->SMCR = 0x00;    // ��ģʽ���ƼĴ���
  TIM1->PSCRH = 0;
  TIM1->PSCRL = 0;
  TIM1->ARRH = (uint8_t)(PWM_PERIOD>>8);        
  TIM1->ARRL = (uint8_t)PWM_PERIOD;     // 80us
  TIM1->IER = 0;        //0x80; // only brk int
  TIM1->CCMR1 = 0X60;   // ����Ƚ�ģʽ�Ĵ���
  TIM1->CCMR2 = 0X60;
  TIM1->CCMR3 = 0X60;
  TIM1->CCMR4 = 0X00;
  TIM1->CCER1 = 0x00;   // ����Ƚ�ʹ�ܼĴ���
  TIM1->CCER2 = 0x00;
  TIM1->OISR = 0x00;    // �������״̬�Ĵ���
  TIM1->DTR = 0x00;     // �����Ĵ��� 0X4a;//0x32;//0X0a;//死区时间，4*62NS
#ifdef	FUNC_HOC_PROTECT_EN
  TIM1->BKR |= 0X90;    // ����ɲ��ʹ��
#else
  TIM1->BKR |= 0X80;    // 同OSSI，OSSR 状态  unable tim brk
#endif
  TIM1->EGR |= TIM1_EGR_UG;     // ���������¼�
  TIM1->CR1 |= TIM1_CR1_CEN;    // ʹ�ܼ�����
  // Clear Update Flag
  /*TIM1_IER_UIE=1;*/
  DisAllPwmOut();
}

/***************************************************************/
void pwm_reset()
{
  TIM1->SR1=0x00;       // 
  TIM1->CR1=0x00;       //
  TIM1->CR2=0x00;       // 
  TIM1->SMCR=0x00;
  TIM1->PSCRH=0;
  TIM1->PSCRL=0;
  //TIM1_DCR=;
  TIM1->ARRH=0;
  TIM1->ARRL=0;
  TIM1->IER=0;  //0x80;// only brk int
  TIM1->CCMR1=0X00;
  TIM1->CCMR2=0X00;
  TIM1->CCMR3=0X00;
  TIM1->CCMR4=0X00;
  TIM1->CCER1=0x00;
  TIM1->CCER2=0x00;
  TIM1->OISR=0x00;
  TIM1->DTR=0x00;//0X4a;//0x32;//0X0a;//死区时间，4*62NS
  TIM1->BKR=0X00;// 同OSSI，OSSR 状态  unable tim brk
  // Resynch to have the Update evend during Undeflow
  //TIM1_EGR_UG=1;
  //TIM1_CR1_CEN=1;
  //TIM1_EGR|=0x01;
  TIM1->CR1|=0x01;
  // Clear Update Flag
  /*TIM1_IER_UIE=1;*/
  DisAllPwmOut();
}

// 
void TIM1_BRK_EVENT(void)
{
  DisAllPwmOut();
//  ChangeDuty(0x00);
}

// 
void DisAllPwmOut(void)
{
  TIM1->CCER1 &= (~TIM1_CCER1_CC1E);    // 
  TIM1->CCER1 &= (~TIM1_CCER1_CC1NE);   // 
  TIM1->CCER1 &= (~TIM1_CCER1_CC2E);    // 
  TIM1->CCER1 &= (~TIM1_CCER1_CC2NE);   // 
  TIM1->CCER2 &= (~TIM1_CCER2_CC3E);    // 
  TIM1->CCER2 &= (~TIM1_CCER2_CC3NE);   // 
  TIM1->EGR |= TIM1_EGR_UG;             // 
}

// 
void TIM5_Conf(void)
{
  TIM5->IER = 0x00;
  TIM5->EGR |= TIM5_EGR_UG;     // �¼������Ĵ���
  TIM5->PSCR = 0x03;    // Ԥ��Ƶ�Ĵ����� psc=4 2^4  1us
  TIM5->ARRH = 0x00;    // �Զ�װ�ؼĴ���
  TIM5->ARRL = 0x01;
  TIM5->SR1 = 0x00;     // clear int flag
  TIM5->CR1 = 0x01;     // ʹ�ܼ�����
  TIM5->CR2 = 0x00;
  TIM5->SMCR = 0x00;    // ��ģʽ�Ĵ���
  TIM5->IER = 0x01;     // only update event
}

// 
void TIM5_Start(void)
{
  TIM5->ARRH = 0x00;    //00
  TIM5->ARRL = 0x6c;    //B6		//6c
  TIM5->CR1 |= TIM5_CR1_CEN;
}

// 
void TIM5_StartCount(void)
{
  TIM5->ARRH=0x00;      //00
  TIM5->ARRL=0x6c;      //B6---6c	//6c 108 = 54us
  TIM5->CR1 |= TIM5_CR1_CEN;    // =1;
}

// 
void TIM5_StopCount(void)
{
  TIM5->CR1 &= (~TIM5_CR1_CEN);     // TIM5_CR1_CEN=0;
  TIM5->CNTRH = 0x00;
  TIM5->CNTRL = 0x00;
}


void TIM5_Getbemf_StartCount(void)
{
  TIM5->ARRH=0x00;      //00
  TIM5->ARRL=0x50;      //B6---6c 40us
  TIM5->CR1 |= TIM5_CR1_CEN;      // TIM5_CR1_CEN=1;
}


void TIM5_Ready_StartCount(void)
{ 
  TIM5->ARRH = 0x00;    //00
  TIM5->ARRL = 0x50;    //B6---6c
  TIM5->CR1 |= TIM5_CR1_CEN;    // TIM5_CR1_CEN=1;
}

// generat 16.3MS inttruput 
void Tim6Init(void)
{
  TIM6->SR1 = 0x00;     // ���״̬�Ĵ���
  TIM6->SMCR = 0x00;    // ��ģʽ���ƼĴ�����δ���ã�
  TIM6->CR1 = 0x04;     // only ov event ����ж�
  TIM6->IER |= TIM6_IER_UIE;    // �����ж�
  // TIM6_IER_TIE=1;    // �����ж�
  TIM6->PSCR = 0x07;    // Ԥ��Ƶ 2^7 = 128 = 8us
  TIM6->ARR = 0xff;     // 8λ�Զ�װ�ؼĴ��� 8*255 = 2ms
  TIM6->EGR |= TIM6_EGR_UG;     // ����ʱ��������ʼ��
  TIM6->CR1 |= TIM6_CR1_CEN;    // ʹ�ܼ�����
  TIM6->IER = 0x01;
}

// 
void TIM5_Star(void)
{
  TIM5->ARRH=0x22;      //48
  TIM5->ARRL=0x22;      //00
  TIM5->CR1 |= TIM5_CR1_CEN;    // TIM5_CR1_CEN=1;
}