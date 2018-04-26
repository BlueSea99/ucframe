/*************************************************************
*name:      gpio.h
*version:   v1.0
*mcu:       903k3
*sdk:       stvd
*detail:    gpio 
*author:    hongwei luo
*date:      2016-4-6
**************************************************************/
#ifndef _MC_CONTROL_H_
#define _MC_CONTROL_H_
#endif

/*************************************************************
*��������
*************************************************************/
#define  POWER_OFF_PWM  100     //�ػ���Сռ�ձ�
#define  POWER_ON_PWM   150     //����ռ�ձ�===
#define  MOTOR_OFF      4
#define  MOTOR_ON       6
#define  RUNUP_TIME     200      //����ʱ��ɱ�
//=============================================
#define  MAXRPM       20000      //�������ת��
#define  MINRPM       1800       //��С����ת��

//MIN_POLE_TIME  20000/60=333r/s**250us/p
//MAX_POLE_TIME  1800/60******** 2000us/p
//============================================
#define  SDSWITCH_MIN_OFF  150     //�رտ���ֵ
#define  SDSWITCH_MIN_ON   330//410     //��������ֵ
//============================================
/***********************************************************
*ת������
************************************************************/
#define  CW  1  ////===
#define  CCW 0  ///===
//���ط���
#define  SW_POS		CW//CCW
#define  SW_REVS	CCW//CW

//����ת����
#define  DIR_POS		CW//CW
#define  DIR_REVS	CCW//CCW

#define  FR   CW
//============================================
#define  PSN1      1
#define  PSN2      2
#define  PSN3      3
#define  PSN4      4
#define  PSN5      5
#define  PSN6      6

#define  PSNLV     50
/*************************************************************
*��λ
*************************************************************/
#define  INJAB    0x42
#define  INJBA    0x42
//--------------------
#define  INJAC    0x42
#define  INJCA    0x42
//--------------------
#define  INJBC    0x42
#define  INJCB    0x42
//--------------------
#define  INJTIM   0x80
/***********************************************************
*����Լ�
************************************************************/
#define  CHANGE_T  0x88

/***********************************************************
*�Լ����
************************************************************/
#define  MCHECK_A   0x01
#define  MCHECK_V   0x01
#define  MCHECK_PH  0x01

//==============================

#define  MCHECK_A  0x01
#define  MCHECK_A  0x01
//==============================

#define  MCHECK_A  0x01
#define  MCHECK_A  0x01

/***************************************************************
* ��������������������
* ��������: ȫ�֣��ֲ�
* ����    :  �� 2016��   
***************************************************************/
extern     u8 Pcount;
extern  const poztable[];
extern  const phztable[];

//===================================
//ϵͳ���к���=======================
extern   void      mrun(void);
//===================================
//״̬���ȵ�=========================
void  Motor_Run(void);
void  Motor_Init(void);

void TS_ch_ph(u8 ky);
void TSR_ch_ph(u8 ky);
void TS_lpv(void);
//void  MC_Switch_Check(void);
//==================================
void     MCTask_CheckMe(void);
void       MCTask_Ready(void);
void       MCTask_Start(void);
void       MCTask_StRun(void);
void      MCTask_NorRun1(void);
void        MCTask_Stop(void);
//==================================
//������غ�������------------------
void           check_ph(void);
void        Iject_Check(void);
void	           dlay (u16 d);
void         INject_prc(void);
void      InJect_ST_Prc(void);
//void       STrun_init(void);
//==========inj=====================


//INJECT  --------------------------
//==================================







