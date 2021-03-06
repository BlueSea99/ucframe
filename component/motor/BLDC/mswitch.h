/**********************************************************
*name   : 
*detail : 
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MSWITCH_H_
#define _MSWITCH_H_


/* Includes ------------------------------------------------------------------*/


/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
extern uint8_t adc_sflg;
extern u16 sw_count;

/*  functions ----------------------------------------------------------------*/
void MC_Swbut_Check(void);
extern void Get_adc_vl(void);
uint8_t Get_sw_fr(void);
void Get_adc_sw(void);
void Check_switch_onff(void);
void check_erorr(void);
extern void read_eeprom_vla(void);
extern void Motor_ip(void);
extern void Motor_Limit_Curr(void);

#endif

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/