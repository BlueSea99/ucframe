/**********************************************************
*name   : inject.h
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

//#include "stm8s903k.h"
//#include "stm8s_type.h"
//#include "stm8_bit.h"
//========================================================

#define	WAIT_US_PULSE_ON_TIME	16		////16
#define	WAIT_ADC_SAMPLE_TIME		2		////2
#define	WAIT_US_STEP_OFF_TIME	1		////400
#define	WAIT_US_PULSE_OFF_TIME	400		////400

#define	INSERT_PULSE_ADC_SAMPLE_CNT		8

typedef struct _INSERT_DATA
{

//��ǰ����ֵ
	//unsigned short AdcCurrSample[6][10];		//��ǰ����BUFF
	unsigned short AdcCurrSam[6][8];		//��ǰ����BUFF
	//unsigned short AdcCurrMax[6];				//��ǰ�������ֵ
	//unsigned short AdcCurrMin[6];				//��ǰ������Сֵ
	unsigned short AdcCurrAvg[6];				//��ǰƽ��ֵ
	//unsigned short AdcCurrAddRate[6];			//��ǰ������


}INSERT_DATA;

extern INSERT_DATA gInsert;


extern unsigned char   Get_Step_ForInsertPulse(void);






extern void     InJect_AB_Task(void);
extern void     InJect_AC_Task(void);
extern void     InJect_BC_Task(void);

void     InJect_AB_Task(void);
void     InJect_AC_Task(void);
void     InJect_BC_Task(void);




