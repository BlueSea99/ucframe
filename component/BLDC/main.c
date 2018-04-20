/***************************************************************
*-------------------- ������λ������----------------------------
*���      ��  motor volt:18vdc----------------------------
*Ӧ��      ��  �޸���ˢ�綯����----------------------------
*�汾&ʱ�� ��  v3.0 8��5��---------------------------------
*Ӳ���汾  ��  SST15-461-1.1-------------------------------
*--------------------------------------------------------------
**************************************************************/

/*======================================
*BLDCM  CONTROL  SYSTERM  FOR ETOOLS
*TWO  POLOS  VDC 18V  20000RPM SPEED
**************************************/
//=======================================
#include "stm8s903k.h"
#include "stm8s_type.h"
#include "stm8_bit.h"
#include "public.h"
//=======================================
#include "mc_config.h"
#include "adc.h"
#include "mc_control.h"
#include "param.h"
#include "mswitch.h"
#include "tim.h"
#include "mdisply.h"
/****************************************/
#define  MCU    _sys_903_
#define  CMP     PACE_WL
//==============================


//==ȫ�����ݽṹ��װ=============
param   Motordata;
collect Injection;
//===������������ʹ��============
void UI_Functiong_init(void);


//===��ʼ����ʱ�������==========
void UI_Functiong_init()
{

//===�ᴥ���ؼ��Ĵ�����ʼ��===
	Motordata.SWhkey.sakeyflg=0;
	Motordata.SWhkey.SSkey=0;
	Motordata.SWhkey.SWkey=0;
//===Ready��ʱ����ʼ��==========	



//====adc���ģʽ��ʼ��=========
	 Adc_Scan_timetrig_init();
	 TIM5_Ready_StartCount();
	 Adc_Start();
	 
//=====�����ӳٳ�ʼ��===========	
	Motordata.SWhkey.ONbuf=0;
	Motordata.SWhkey.OFbuf=0;
	PD4_OUT=0;
	PD2_OUT=0;
	//Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
//==============================
  //���Ź���ʼ��
	 dlay (50000);
	 Motordata.UI.BKcount=0;
	 Motordata.UI.adspeedt=3;
	 Motordata.UI.Blink=0;	
	 
//========================
	if(Get_sw_fr()==0)	//=�ж�����ת==
	{ 
		Motordata.MFR=SW_POS;			//CW		
	}
	if(Get_sw_fr()==1)
	{ 
		Motordata.MFR=SW_REVS;			//CCW
	}//---------
								
	Motordata.UI.MFRch= Motordata.MFR;
								
	PD2_OUT=1;
	Motordata.SWhkey.TRdelay=PWR_DELAY_TIME;
  //�ж����ȼ���ʼ��============
	Motordata.prct.clcount=0;
//===��ʾ�Ĵ�����ʼ��===========
	Motordata.Disstatus=6;
	 //====================
	Motordata.prct. DIStp=0;
	Motordata.prct.DISvsm=0;
	Motordata.prct.DISism=0;
	Motordata.prct.DISois=0;
//=============================	 
//==��eeprom===================
	Motordata.UI.Mroller=450;
	read_eeprom_vla();
#ifdef	PROJ_SST16_195
	Motordata.SWhkey.FRstop=0xaa;
#endif   
}




//=============================

main()
{
  	u8 usx;
 //===ϵͳ ��ʼ������========
	Sys_Init();

 //===���ϵͳ��ʼ��=========
	Motor_Init();
 
//==���ư壣�����ʼ��======
	UI_Functiong_init();
	 
 //===�ȴ���ѹ�ȶ�===========
	Motordata.Dswitch=MOTOR_OFF;
	dlay (50000);
	
	 // _asm("sim");
	// Motordata.Flgsw=1;
	
	while (1)
	{	
	//	MCTask_Start();
	 
			
//һ����ȫ��������� *********
		Motor_ip();
			  
//���� ״̬��ȡ*******
		Check_switch_onff();
	
//������б���********
			  
		if( Motordata.station==Stop&&Motordata.UI.Blink>0)   
		{     
			usx= showsp[Motordata.UI.showcount];
		       if(usx==1)
			{ 
				Disp_error_on();  
			}
			else
			{ 
				Disp_error_of();  
			}	
		}
		 
//�������״̬--------
		Motor_Run();
	}

}














