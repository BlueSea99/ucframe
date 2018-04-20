/**********************************************************
*name:  public.h
*version: v1.0 (2018-4-1)
*detail:  include public head file
*author:  ??
***********************************************************/

#ifndef __PARAM_H
#define __PARAM_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/*  defines ------------------------------------------------------------------*/
// #define PROJ_SST16_194 
// #define PROJ_SST16_DK
// #define PROJ_SST17_1a1
#define PROJ_SST17_1A4
// #define PROJ_SST17_1B3

#define PWR_DELAY_TIME	80	// ??????8?


/*  typedef ------------------------------------------------------------------*/
// 
typedef enum
{
  checkme = 1,
  ready = 2,
  startup = 3,
  startrun = 4,
  norrun = 5,
  fause = 6,
  brake = 7,
  stop = 8
} mstate_t;

//
typedef struct
{
  uint8_t hallnow;
  uint8_t hallold;
  uint8_t hallnext;
  uint8_t halllp;
  uint8_t halllf;
} hall_t;

//
typedef struct
{
  uint8_t nwstep;
  uint8_t nestep;
  uint8_t odstep;
} rstep_t;

//
typedef struct
{
  uint16_t gduty;
  uint16_t mroller;
  uint16_t mledcount;
  uint16_t showstep;
  uint16_t showbuf;
  uint16_t bkcount;
  uint16_t showcount;
  uint16_t showtime;
  uint8_t  adspeedt;
  uint8_t  blink;
  uint8_t  mfrch;
} mui_t;

// 
typedef enum
{
  eno = 0,
  ehall = 6,    // ��������
  eovp = 3,     // ��ѹ
  eocp = 1,     // ����
  eoct = 5,     // ����
  ebkr = 4,     // ��ת
  elvp = 2      // Ƿѹ
} mert_t;

// 
typedef struct
{
  uint8_t mgear;        // ��λ
  uint8_t swkey;
  uint8_t sskey;
  uint8_t sakeyflg;
  uint8_t abkeyflg;
  uint8_t frstop;
  uint8_t tiwno;
  uint8_t tiwoff;
  uint8_t readkey;
  uint8_t spkey;
  uint16_t trdelay;
  uint16_t trdealy1;
  uint16_t onbuf;
  uint16_t ofbuf;
  uint16_t killrun;
} swh_t;

//  
typedef struct
{
  uint8_t clcount;
  uint16_t volt;
  uint16_t anp;
  uint16_t tempr;
  uint16_t mostemp;
  uint16_t mosaddbattemp;
  uint16_t battemp;
  // �����˲�
  uint16_t disv;
  uint16_t distp;       // �¶�
  uint16_t disvsm;      // ��ѹ
  uint16_t disism;      // ����
  uint16_t disois;
  
  uint16_t bufovp;      // Ƿѹ����
  uint16_t bufsep;      // ��ѹ����
  uint16_t bufocp;      // ��������
  uint16_t bufoct;      // ���±���
} mprc_t;

//
typedef struct
{
  mstate_t station;
  hall_t bhall;
  rstep_t bstep;
  mui_t ui;
  mert_t fault;
  swh_t swhkey;
  mprc_t prct;

  uint16_t outduty;
  uint16_t hopeduty;
  uint16_t trcount;
  uint16_t tqcount;
  uint16_t tvcount;
  uint8_t batpower;
  uint8_t dswitch;
  uint8_t injgph;
  uint8_t mfr;
  uint8_t flgsw;
  uint8_t disstatus;
  uint8_t mstep;
  uint8_t test;
} motorparam_t;
/*  variables  ---------------------------------------------------------------*/
extern motorparam_t Motordata;

/*  functions ----------------------------------------------------------------*/


#endif