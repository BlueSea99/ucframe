/**********************************************************
*name   : key.c
*detail : ������غ���
*version&time: v1.0 (2018-4-1)
*author&team : wang yuan
***********************************************************/

/* Includes ------------------------------------------------------------------*/
#include "key.h"

/*  defines&macro ------------------------------------------------------------*/

/*  typedef ------------------------------------------------------------------*/

/*  variables&constants  -----------------------------------------------------*/
key_t key;

/*  functions ----------------------------------------------------------------*/

// ��ȡ����״̬����Ҫ�����Ӧ��IO״̬�ж�
uint8_t GetKey(void)
{
  return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
}

// ����1ms��ʱ��
void RefreshKey(void)
{
  key.stabletimecnt++;
  if (key.stabletimecnt > 1000)
  {
    key.laststate = IDLESTATE;
  }
  
  switch (key.keystate)
  {
  case KEYUP:
    if (key.GetKey() == 1)
    {
      key.keystate = KEYDOWNWOBBLE;
      key.stabletimecnt = 0;
    }
    break;
  case KEYDOWNWOBBLE:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUP;
    }
    if (key.stabletimecnt > 20)
    {
      key.keystate = KEYDOWN;
      key.keycallbackflag = KEYDOWN;
      key.stabletimecnt = 0;
    }
    break;
  case KEYDOWN:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUPWOBBLE;
    }
    if (key.stabletimecnt > 1000)
    {
      key.keystate = KEYLONGDOWN;
    }
    break;
  case KEYLONGDOWN:
    if (key.GetKey() == 0)
    {
      key.keystate = KEYUPWOBBLE;
    }
    break;
  case KEYUPWOBBLE:
    if (key.GetKey() == 1)
    {
      key.keystate = KEYDOWN;
    }
    if (key.stabletimecnt > 20)
    {
      key.keystate = KEYUP;
      key.stabletimecnt = 0;
      key.keycallbackflag = KEYUP;
    }
    break;
  case DOUBLECLKICKWOBBLE:
    break;
  case DOUBLECLKICK:
    break;
  }
}
// ����ע�ᰴ��
void CreatKey(void)
{
  key.keystate = KEYUP;
  key.laststate = IDLESTATE;
  key.stabletimecnt = 0;
  key.GetKey = GetKey;
  key.RefreshKey = RefreshKey;
}

/************************ (C) COPYRIGHT ucframe team ******* END OF FILE ******/