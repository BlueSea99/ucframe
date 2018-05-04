#include "platform.h"
//#include "public.h"
#include  "adc.h"
#include "param.h"
/*****************************************************
*define  data
******************************************************/
u16 adc_temp [4];
u8  adc_times=0;


void  Adc_SetUp_Init(void);
void  adcc(void);

// 
void Set_adc_chan(unsigned char channel )
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;    
  ADC1->CSR = 0x03;                     // ADC_CSR=0x03;//0x03;   //4ͨ���򿪣������ж�g
  ADC1->CR1 = 0x20;                     // ADC_CR1=0x20;          // F/8  CONT=1;
  ADC1->CR2 = 0x08;                     // ADC_CR2=0x08;//0x0a;   //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��	
}

// 
void  Adc_SetUp_Init(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x24;                     // ADC_CSR=0x24;          //AIN4ͨ���򿪣����ж�
  ADC1->CR1 = 0x40;                     // ADC_CR1=0x40;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x0a;                     // ADC_CR2=0x0a;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��-----------		
}

// 
void  Adc_SetUp_ch(unsigned char ch)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = ch;       // ADC_CSR=ch;          //AIN4ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;     // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;     // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------		
}

//
void  Adc_SetUp_ch1(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x06;             // ADC_CSR=0x06;          //AIN4ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;             // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;             // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------		
}

// 
void  Adc_SetUp_ch2(void)//2
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x05;             // ADC_CSR=0x05;          //AIN4ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;             // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;             // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------	
}

// 
void  Adc_SetUp_ch3(void)//3
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x04;             // ADC_CSR=0x04;          //AIN4ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;             // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;             // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------	
}

// 
void Adc_Start(void)
 {
   ADC1->CR1 |= ADC1_CR1_ADON;  // ADC_CR1_ADON = 1; ADC_CR1_ADON = 1;
 }

// 
void adcc(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc
  ADC1->CSR = 0x24;                     // ADC_CSR=0x24;          //4ͨ����      �� k
  ADC1->CR1 = 0x70;                     // ADC_CR1=0x70;          // F/8  CONT=1;
  ADC1->CR2 = 0x4a;                     // ADC_CR2=0x4a;//0x0a;   //40 ���������   ɨ��ģʽ
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��
}

// 
void Adc_Scan_timetrig_init()
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //set-off  adc===========  
  ADC1->CSR = 0x24;                     // ADC_CSR=0x24;          //ɨ��ͨ����============== 
  //������ת��CONT=1;=======
  ADC1->CR1 = 0x70;                     // ADC_CR1=0x70;          //ʱ�ӷ�Ƶ F/8 ����ģʽ��Ч
  //����ת����ɴ����ж�
  ADC1->CR2 = 0x0a;                     // ADC_CR2=0x0a;//0x0a;   //40 time����ģʽ-ɨ��ģʽ
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��=================    
}

// Adc_mode_trig_init()
void Adc_Scan_pwmtrig_init()
{  
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      // set-off  adc===========
  ADC1->CSR = 0x25;                     // ADC_CSR=0x25;          //ɨ��ͨ����==============  
  ADC1->CR1 = 0x70;                     // ADC_CR1=0x70;          //ʱ�ӷ�Ƶ F/8 ����ģʽ��Ч
  //������ת��CONT=1;=======
  ADC1->CR2 = 0x4a;                     // ADC_CR2=0x4a;//0x0a;   //40 PWM����ģʽ-ɨ��ģʽ 
  //����ת����ɴ����ж�
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��-----------				 
}

//
void  Getval_prc_updata()
{
  static unsigned char TempCnt = 0;
  
  if( (0<=Motordata.prct.clcount) && (Motordata.prct.clcount<5) )	
  {   			
    Motordata.prct.bufovp += (ADC1->DB1RH<<8)+ADC1->DB1RL;      // ADC_DB1R;
    Motordata.prct.bufsep += (ADC1->DB3RH<<8)+ADC1->DB3RL;      // ADC_DB3R;
    Motordata.prct.bufocp += (ADC1->DB2RH<<8)+ADC1->DB2RL;      // ADC_DB2R;
    Motordata.prct.bufoct += (ADC1->DB0RH<<8)+ADC1->DB0RL;      // ADC_DB0R;
    Motordata.prct.clcount = Motordata.prct.clcount+1;
  }
 
// /**************************************************
// /*		  Motordata.hopeduty  = ADC_DB3R;/**  speed**/
// /*	    Motordata.prct.Anp=ADC_DB2R;     /**  ocp**/
// /*		  Motordata.prct.Volt=ADC_DB1R;    /**  ovp**/
// /*		  Motordata.prct.Tempr=ADC_DB0R;   /**  otp**/
// /*                   u16  bufovp;//Ƿѹ����
//  u16  bufsep;//��ѹ����
//  u16  bufocp;//��������
//  u16  bufoct;//���±���
//  u8   clcount;	//����
// /*************************************************/
 
  if(Motordata.prct.clcount>=5)
  {
    Motordata.hopeduty = Motordata.prct.bufsep>>2;
    Motordata.prct.Anp = Motordata.prct.bufocp/5;
    Motordata.prct.Volt= Motordata.prct.bufovp/5;
    Motordata.prct.Tempr=Motordata.prct.bufoct/5;
		
///////////////////////modify by goldjun//////////////////////////		
//judge curr which  temp
    TempCnt ++;
    if((TempCnt&0x01)==0x01)
    {
//stroe curr mostemp	
      Motordata.prct.MosTemp = Motordata.prct.Tempr;
//switch next mosaddbattemp
//input
      GPIOD->DDR &= 0xef;       // PD_DDR&=0xef;
      GPIOD->CR1 &= 0xef;       // PD_CR1&=0xef;
      GPIOD->CR2 &= 0xef;       // PD_CR2&=0xef;
    }
    else
    {
//store curr mosaddbattemp	
      Motordata.prct.MosAddBatTemp = Motordata.prct.Tempr;
//switch next mostemp
//output 0
      GPIOD->DDR |= 0x10;       // PD_DDR|=0x10;
      GPIOD->CR1 &= 0xef;       // PD_CR1&=0xef;
      GPIOD->CR2 &= 0xef;       // PD_CR2&=0xef;
      GPIOD->ODR &= 0xef;       // PD4_OUT=0;
    }
///////////////////////modify by goldjun//////////////////////////

    Motordata.prct.clcount=0;
    Motordata.prct.bufovp=0;
    Motordata.prct.bufsep=0;
    Motordata.prct.bufocp=0;
    Motordata.prct.bufoct=0;
  }
	/**********************�洢������ ****************/	
	/**************************��������*****************/
}






