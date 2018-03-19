/* Copyright (c) ��Ԫ
 * 20180101
 * ͨ����
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include <stdarg.h>
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
//#include "key.h"
//#include "comgui.h"
//#include "menugui.h"
//#include "bufferlist.h"
//#include "flash.h"
//#include "datamanager.h"

/* Private define -----------------------------------------------------------*/
#define BUFFERSIZE      64
extern uint8_t txbuffer[BUFFERSIZE];
extern uint8_t rxbuffer[BUFFERSIZE];
extern uint8_t begainposition;
extern uint8_t endposition;     // ������������Դ����жϽ���

/* Exported define -----------------------------------------------------------*/
#ifndef NULL
  #define NULL ((void *)0)
#endif

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

typedef enum {FAILED = 0, PASSED = !FAILED} status_t;



/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* IC proc */
typedef struct
{
  uint8_t cmd[2];
  uint8_t cmdsize;
  uint8_t addrsize; 
  uint8_t addr[4];
  uint8_t reg[4];
  uint16_t readsize;
  uint16_t writesize;
  uint8_t *data;
  void (*read)(void *pointhandle, ...);
  void (*write)(void *pointhandle, ...);
} cmdparam_t;   // ���ܲ�������ͨ�ñ�׼оƬ��д�ṹ

/* POINT */
#define SMOOTHDEP 6
typedef struct
{
  void (*CreatPoint)(void);
  void (*Calibration)(void);
  void (*Smooth)(int32_t data);
} point_t;

/* BITMAP */
typedef struct
{
  uint16_t bftype;      // 0x424d
  uint32_t bfsize;      // 
  uint32_t bfreserved;  // 0
  uint32_t bfoffbits;   // 0x00000436
} bitmapfileheader_t;
typedef struct
{
  uint32_t biSize;              //ָ���˽ṹ��ĳ��ȣ�Ϊ40  
  uint32_t biWidth;             //λͼ�� //160
  uint32_t biHeight;            //λͼ�� //160
  uint16_t biPlanes;            //ƽ������Ϊ1                   
  uint16_t biBitCount;          //������ɫλ����������1��2��4��8��16��24���µĿ�����32  //8
  uint32_t biCompression;       //ѹ����ʽ��������0��1��2������0��ʾ��ѹ�� 
  uint32_t biSizeImage;         //ʵ��λͼ����ռ�õ��ֽ���,����Ϊ4�ı��� //160*160
  uint32_t biXPelsPerMeter;     //X����ֱ��� 
  uint32_t biYPelsPerMeter;     //Y����ֱ���  
  uint32_t biClrUsed;           //ʹ�õ���ɫ�������Ϊ0�����ʾĬ��ֵ(2^��ɫλ��) 
  uint32_t biClrImportant;      //��Ҫ��ɫ�������Ϊ0�����ʾ������ɫ������Ҫ�� 
} bitmapinfoheader_t;
typedef struct 
{
  uint8_t rgbBlue;              //����ɫ����ɫ���� 
  uint8_t rgbGreen;             //����ɫ����ɫ���� 
  uint8_t rgbRed;               //����ɫ�ĺ�ɫ���� 
  uint8_t rgbReserved;          //����ֵ 
} rgbquad_t;            // λͼ����8�ı���ʱ���������     

typedef struct
{
  bitmapfileheader_t bitmapfileheader;
  bitmapinfoheader_t bitmapinfoheader;
//  palette_t palette;
  uint8_t *imagedata;
} bitmap_t;

/* ENCRYPT */
typedef struct
{
  void (*CreatEncrypt)(void);
} encrypt_t;

/* interface */
typedef struct
{
  uint8_t sfd;          // ֡��ʼ�� #define �̶� 0xA5
  uint8_t devid;        // һ���һ��ֻ��0x01��0x00������0xff�㲥��ַ
  uint16_t length;      // Ҫ��Ҫ���һ��flag��ǰ�棿�ط�������
  uint8_t cmd;          // ָ��
  uint8_t cmdplusl;     // ��չָ��
  uint8_t cmdplush;     // ��չָ��
  uint8_t checkcode;    // ��ʲôУ����õ�
  uint8_t *pdata;       //
//  uint16_t eop;         // 0x0d 0x0a�����س�����
} cmdpackets_t;         //comprotocol_t; datacom


/* COMMON */
typedef struct
{
  uint8_t indata[64];
  uint8_t outdata[64];
  uint8_t *pbuf;
//  void (*CommonInit)(void);
//  void (*CommonDeInit)(void);
  void (*printf)(void);
  void (*TxData)(int8_t *pdata, uint16_t size);
  void (*RxData)(int8_t *pdata, uint16_t size);
} common_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
#define MV2ADC(__X__)           ( (__X__*4095) / 3300 )
#define ADC2MV(__X__)           ( (__X__*3300) / 4095 )
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#define ABS(A,B) ((A) <= (B) ? (B-A) : (A-B))
#define PORTPIN(PORT, PIN, MODE)  	{ PORT, GPIO_PIN_ ## PIN, MODE }

// �õ�ָ����ַ�ϵ�����
#define  MEM_B( x )  ( *( (byte *) (x) ) ) 
#define  MEM_W( x )  ( *( (word *) (x) ) )  

// �õ��ṹ�������г�Ա��ƫ���� struct type field offset
#define STFO(type, field) ((int) &((type *) 0)-> field)
// �ṹ���е��ֽ���
#define FSIZ(type, field) sizeof( ((type *) 0)->field ) 

// ��ȡ�������ĳ���
#define countof(array)      (sizeof(array) / sizeof(*(array)))

//��һ����ĸת��Ϊ��д
#define UPCASE( c ) ( ((c) >= ��a' && (c) <= ��z') ? ((c) - 0��20) : (c) )

#define IS_CAP_LETTER(c)    (((c) >= 'A') && ((c) <= 'F'))
#define IS_LC_LETTER(c)     (((c) >= 'a') && ((c) <= 'f'))
#define IS_09(c)            (((c) >= '0') && ((c) <= '9'))
#define ISVALIDHEX(c)       (IS_CAP_LETTER(c) || IS_LC_LETTER(c) || IS_09(c))
#define ISVALIDDEC(c)       IS_09(c)
#define CONVERTDEC(c)       (c - '0')

#define CONVERTHEX_ALPHA(c) (IS_CAP_LETTER(c) ? ((c) - 'A'+10) : ((c) - 'a'+10))
#define CONVERTHEX(c)       (IS_09(c) ? ((c) - '0') : CONVERTHEX_ALPHA(c))
/* Exported functions ------------------------------------------------------- */
/*
 * Macros to concatenate 2 - 4 tokens together to form a single token.
 * Multiple levels of nesting are required to convince the preprocessor to
 * expand currently-defined tokens before concatenation.
 *
 * For example, if you have
 *     #define FOO 1
 *     #define BAR1 42
 * Then
 *     #define BAZ CONCAT2(BAR, FOO)
 * Will evaluate to BAR1, which then evaluates to 42.
 */
#define CONCAT_STAGE_1(w, x, y, z) w ## x ## y ## z
#define CONCAT2(w, x) CONCAT_STAGE_1(w, x, , )
#define CONCAT3(w, x, y) CONCAT_STAGE_1(w, x, y, )
#define CONCAT4(w, x, y, z) CONCAT_STAGE_1(w, x, y, z)

/*
 * Macros to turn the argument into a string constant.
 *
 * Compared to directly using the preprocessor # operator, this 2-stage macro
 * is safe with regards to using nested macros and defined arguments.
 */
#define STRINGIFY0(name)  #name
#define STRINGIFY(name)  STRINGIFY0(name)

/* Macros to access registers */
#define REG32_ADDR(addr) ((volatile uint32_t *)(addr))
#define REG16_ADDR(addr) ((volatile uint16_t *)(addr))
#define REG8_ADDR(addr)  ((volatile uint8_t  *)(addr))

#define REG32(addr) (*REG32_ADDR(addr))
#define REG16(addr) (*REG16_ADDR(addr))
#define REG8(addr)  (*REG8_ADDR(addr))

/* Exported functions ------------------------------------------------------- */

extern void CommonInit(void);
extern void Serial_PutString(uint8_t *p_string);
//extern HAL_StatusTypeDef Serial_PutByte( uint8_t param );
extern uint32_t Str2Int(uint8_t *p_inputstr, uint32_t *p_intnum);



#endif  /* __COMMON_H */
