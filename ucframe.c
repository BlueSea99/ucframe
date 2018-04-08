/* Copyright (c) ��Ԫ
 * 20180101
 * ucframe
 */

/* Includes ------------------------------------------------------------------*/
#include "ucframe.h"

/* Exported define -----------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#if 0
void Main_Menu(void)
{
  uint8_t key, failnum;
  uint8_t str[64];
  
  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n=                    (C) COPYRIGHT 2017 PACE                         =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=       chipsailing fingerprint  Application  (Version 1.0.0)        =");
  Serial_PutString("\r\n=                                                                    =");
  Serial_PutString("\r\n=                    By PACE Application Team                        =");
  Serial_PutString("\r\n======================================================================");
  Serial_PutString("\r\n\r\n");

  while (1)
  {
    Serial_PutString("\r\n\r\n");
    Serial_PutString("\r\n=================== Main Menu ============================");
    Serial_PutString("\r\n  ָ��¼��demo --------------------------- 1");
    Serial_PutString("\r\n  ָ��ʶ��demo --------------------------- 2");
    Serial_PutString("\r\n  ָ��ͼ���ӡ --------------------------- 3");
    Serial_PutString("\r\n  ָ��ģ���ӡ --------------------------- 4");
    Serial_PutString("\r\n  SPIFLASHdemo --------------------------- 5");
    Serial_PutString("\r\n  ��оƬIDdemo --------------------------- 6");
    Serial_PutString("\r\n  �������˵� ----------------------------- 0");
    Serial_PutString("\r\n==========================================================\r\n\n");

    /* Clean the input path */
    __HAL_UART_FLUSH_DRREGISTER(&UartHandle);
	
    /* Receive key */
    HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);

    switch (key)
    {
    case '1' :
      Serial_PutString("\r\n 1��ָ��¼��demo: ");
      while (1)
      {
        if (cs3211.enteredfpnum < MAXFIGERNUM) 
        {
          cs3211.enteredfpnum++;
          Serial_PutString("\r\n ��ʼ¼��� ");
          Int2Str(&str[0], cs3211.enteredfpnum);
          Serial_PutString(str);
          Serial_PutString(" ��ָ��...");
        }
        else
        {
          Serial_PutString("\r\n ָ�����ݿռ�¼��������");
          break;
        }
        failnum = 0;
        for (uint32_t i=1; i<3; i++)
        {
  //        Serial_PutString("\r\n �� ");
  //        Int2Str(&str[0], i);
  //        Serial_PutString(str);
  //        Serial_PutString(" ��ָ��¼��:");
          while (cs3211.FingerCheck() != API_ER_FINGER_DOWN)
          {
            HAL_UART_Receive(&UartHandle, &key, 1, 10);
              if (key == '0') break;
          }
          if (key == '0') break;
          cs3211.begaintime = uwTick;
          cs3211.ReadImage(cs3211.rawdata, RAWDATASIZE);
          cs3211.transfertime = uwTick;
          if (1 == cs3211.CreateTemplate(cs3211.rawdata, IMAGEWIDTH, IMAGEHIGH, cs3211.featuredata[0], &cs3211.opncharnum))
          {
            cs3211.arithmetictime = uwTick;
            if ( (cs3211.opncharnum>3) && (cs3211.opncharnum<30) )
            {
              cs3211.matchfpno = 0;
              for (uint8_t j=cs3211.enteredfpnum-1; j>0; j--)
              {
                if (cs3211.MatchScore(cs3211.featuredata[j], cs3211.featuredata[0]) > 15)
                {
                  cs3211.matchfpno = j;    
                  break;
                }
              }
              if (cs3211.matchfpno != 0)
              {
                Serial_PutString("\r\n ��ָ����¼�룡");
                cs3211.enteredfpnum--;
                break;
              }
            
              if (i == 1)
              {
                cs3211.matchtime = uwTick;
//                HAL_UART_Transmit(&UartHandle, cs3211.begaintime, 24, 10);     //
//                HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);  //
                memcpy(cs3211.featuredata[cs3211.enteredfpnum], cs3211.featuredata[0], 1024);
              }
              else
              {
                if (0 == cs3211.MergeFeature(cs3211.featuredata[cs3211.enteredfpnum], cs3211.featuredata[0], cs3211.fifo, &cs3211.pnpnt, &cs3211.pnwidth, &cs3211.pnheight))
                {
                  memcpy(cs3211.featuredata[cs3211.enteredfpnum], cs3211.fifo, 1024);
                  Serial_PutString(" ¼��OK�����뿪��ָ...");
                }
                else
                {
                  Serial_PutString("\r\n �ϲ�ģ��ʧ�ܣ�����¼��ָ��");
                  i--;
                  if (++failnum > 3) 
                  {
                    cs3211.enteredfpnum--;
                    break; 
                  }
                }
              }
            }
            else
            {
              Serial_PutString("\r\n ����ģ��ʧ��2������¼��ָ��");
              i--;
            }
          }
          else
          {
            Serial_PutString("\r\n ����ģ��ʧ��1������¼��ָ��");
            i--;
          }
        }
        if (key == '0')
        {
          cs3211.enteredfpnum--;
          break;
        }
        while (cs3211.FingerCheck() != API_ER_FINGER_LEAVE);
      }
      break;
    case '2' :
      Serial_PutString("\r\n 2��ָ��ʶ��demo:");
      while (1)
      {
        while (cs3211.FingerCheck() != API_ER_FINGER_DOWN)
        {
          HAL_UART_Receive(&UartHandle, &key, 1, 10);
            if (key == '0') break;
        }
        if (key == '0') break;
//        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
        cs3211.ReadImage(cs3211.rawdata, RAWDATASIZE);
        if (1 == cs3211.CreateTemplate(cs3211.rawdata, IMAGEWIDTH, IMAGEHIGH, cs3211.featuredata[0], &cs3211.opncharnum))
        {
          if ( (cs3211.opncharnum>3) && (cs3211.opncharnum<30) )
          {
            cs3211.matchfpno = 0;
            for (uint8_t i=cs3211.enteredfpnum; i>0; i--)
            {
              if (cs3211.MatchScore(cs3211.featuredata[i], cs3211.featuredata[0]) > 15)
              {
                cs3211.matchfpno = i;    
                break;
              }
            }
          }
          else
          {
            Serial_PutString("\r\n ����ģ��ʧ��2");
          }
          
          if (cs3211.matchfpno == 0)
          {
            Serial_PutString("\r\n δ�ҵ�ƥ��ģ��!");
          }
          else
          {
            Serial_PutString("\r\n �ɹ�ƥ��ģ�壺");
            Int2Str(&str[0], cs3211.matchfpno);
            Serial_PutString(str);
          }
        }
        else
        {
          Serial_PutString("\r\n ����ģ��ʧ��1");
        }
        while (cs3211.FingerCheck() != API_ER_FINGER_LEAVE);
      }
      break;
    case '3' :
//      Serial_PutString("\r\n===========3��ָ��ͼ���ӡdemo");
      while (1)
      {
        HAL_Delay(3000);
        while (cs3211.FingerCheck() != API_ER_FINGER_DOWN)
        {
          HAL_UART_Receive(&UartHandle, &key, 1, 10);
            if (key == '0') break;
        }
        if (key == '0') break;
        
        cs3211.ReadImage(cs3211.rawdata, RAWDATASIZE);
        cs3211.GetImageHead(cs3211.imagehead, IMAGEWIDTH, IMAGEHIGH);
        HAL_UART_Transmit(&UartHandle, cs3211.imagehead, 1078, 100);
        for (uint8_t i=0; i<IMAGEHIGH; i++)
        {
          HAL_UART_Transmit(&UartHandle, cs3211.rawdata+IMAGEWIDTH*i, IMAGEWIDTH, 100);
        }
        
        while (cs3211.FingerCheck() != API_ER_FINGER_LEAVE);
      }
      break;
    case '4' :
      for (uint8_t i=1; i<4; i++)
      {
        HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
        HAL_UART_Transmit(&UartHandle, cs3211.featuredata[i], 1024, 100);        
      }
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    case '5' :
      Serial_PutString("\r\n===========5��SPIFLSHAdemo:");
      while(1)
      {
        HAL_UART_Receive(&UartHandle, &key, 1, 10);
        if (key == '0') break;
        
        HAL_SPI_Transmit(&hspi1, &key, 1, 100);
      }
      for (uint8_t i=1; i<4; i++)
      {
        HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
        HAL_UART_Transmit(&UartHandle, cs3211.featuredata[i], 1024, 100);        
      }
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    case '6' :
      cs3211.ReadChipID();
      HAL_UART_Transmit(&UartHandle, cs3211.chipid, 2, 100); 
      HAL_UART_Receive(&UartHandle, &key, 1, HAL_MAX_DELAY);
      break;
    default:
      Serial_PutString("Invalid Number ! ==> The number should be either 1, 2, 3 or 4\r");
      break;
    }
  }
}
#endif