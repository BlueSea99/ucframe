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

// AIN3��SPEED������ת��
void Set_adc_chan(unsigned char channel )
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;    
  ADC1->CSR = 0x03;                     // AIN3ͨ���򿪣����ж�
  ADC1->CR1 = 0x20;                     // Ԥ��ƵF/4  CONT=1;
  ADC1->CR2 = 0x08;                     // ADC_CR2=0x08;//0x0a;   //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��	
}

// AIN4��EBMFR��ɨ���ж�ģʽ
void  Adc_SetUp_Init(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0; 
  ADC1->CSR = 0x24;                     // AIN4ͨ����,���ж�
  ADC1->CR1 = 0x40;                     // Ԥ��ƵF/8������ת��
  ADC1->CR2 = 0x0a;                     // ɨ��ģʽ(����ͨ����ûʹ��)���Ҷ���
  ADC1->CR1 |= ADC1_CR1_ADON;           // ����ת��
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

// AIN6,EBMFT,
void  Adc_SetUp_ch1(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x06;             // ADC_CSR=0x06;          //AIN6ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;             // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;             // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------		
}

// AIN5,EBMFS,
void  Adc_SetUp_ch2(void)//2
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc============
  ADC1->CSR = 0x05;             // ADC_CSR=0x05;          //AIN5ͨ���򿪣����ж�
  ADC1->CR1 = 0x00;             // ADC_CR1=0x00;          // F/8 ���� CONT=0;
  ADC1->CR2 = 0x08;             // ADC_CR2=0x08;          //40 ������������
  ADC1->CR1 |= ADC1_CR1_ADON;   // ADC_CR1_ADON = 1;      //����ת��-----------	
}

// AIN4,EBMFR,
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
  ADC1->CR1 |= ADC1_CR1_ADON;  // 
}

// AIN4,EBMFR,
void adcc(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      //��adc
  ADC1->CSR = 0x24;                     // ADC_CSR=0x24;          //4ͨ����      �� k
  ADC1->CR1 = 0x70;                     // ADC_CR1=0x70;          // F/8  CONT=1;
  ADC1->CR2 = 0x4a;                     // ADC_CR2=0x4a;//0x0a;   //40 ���������   ɨ��ģʽ
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��
}

// AIN4,EBMFR,
void Adc_Scan_timetrig_init(void)
{
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // set-off  adc
  ADC1->CSR = 0x24;                     // ����״̬�Ĵ�����AIN4�ж�ʹ��
  ADC1->CR1 = 0x70;                     // ����ת����Ԥ��ƵF/18
  ADC1->CR2 = 0x0a;                     // �Ҷ��룬ɨ��ģʽ
  ADC1->CR1 |= ADC1_CR1_ADON;           // ʹ��ADC  
}

// Adc_mode_trig_init()
void Adc_Scan_pwmtrig_init(void)
{  
  ADC1->CR1 &= (~ADC1_CR1_ADON);        // ADC_CR1_ADON = 0;      // set-off  adc===========
  ADC1->CSR = 0x25;                     // AIN5ɨ���ж� 
  ADC1->CR1 = 0x70;                     // ʱ�ӷ�Ƶ F/12,����ת��
  ADC1->CR2 = 0x4a;                     // PWM����ģʽ-ɨ��ģʽ 
  ADC1->CR1 |= ADC1_CR1_ADON;           // ADC_CR1_ADON = 1;      //����ת��-----------				 
}

//
void Getval_prc_updata(void)
{
  static unsigned char TempCnt = 0;
  
  if(Motordata.prct.clcount < 5)	
  {
    Motordata.prct.bufoct += (ADC1->DB0RH<<8);
    Motordata.prct.bufoct += ADC1->DB0RL;
    Motordata.prct.bufovp += (ADC1->DB1RH<<8);
    Motordata.prct.bufovp += ADC1->DB1RL;
    Motordata.prct.bufocp += (ADC1->DB2RH<<8);
    Motordata.prct.bufocp += ADC1->DB2RL;
    Motordata.prct.bufsep += (ADC1->DB3RH<<8);
    Motordata.prct.bufsep += ADC1->DB3RL;
    Motordata.prct.clcount++;
  }
  else
  {
    Motordata.hopeduty = Motordata.prct.bufsep>>2;
    Motordata.prct.Anp = Motordata.prct.bufocp/5;
    Motordata.prct.Volt= Motordata.prct.bufovp/5;
    Motordata.prct.Tempr=Motordata.prct.bufoct/5;	
    // judge curr which temp
    TempCnt++;
    if((TempCnt&0x01)==0x01)
    { // stroe curr mostemp // switch next mosaddbattemp	
      Motordata.prct.MosTemp = Motordata.prct.Tempr;
      GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT); // PD_DDR&=0xef; PD_CR1&=0xef; PD_CR2&=0xef;
    }
    else
    { // store curr mosaddbattemp // switch next mostemp
      Motordata.prct.MosAddBatTemp = Motordata.prct.Tempr;
      GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_OD_LOW_SLOW); // PD_DDR|=0x10; PD_CR1&=0xef; PD_CR2&=0xef; PD4_OUT=0;
    }
    Motordata.prct.clcount=0;
    Motordata.prct.bufovp=0;
    Motordata.prct.bufsep=0;
    Motordata.prct.bufocp=0;
    Motordata.prct.bufoct=0;
  }
}






