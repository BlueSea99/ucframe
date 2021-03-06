/* Copyright (c) 2018 ��Ԫ
 * 20180101
 * virtual file system
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VFS_H
#define __VFS_H

/* Includes ------------------------------------------------------------------*/
#include "common.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t pagesize;
  uint32_t filenum;
  uint32_t fsid;
  char filename[8];
  uint32_t filelength;
  void (*fsinit);
  void (*IOCtrl);
  void (*Creat);
  void (*Open);
  void (*Read);
  void (*Write);
  void (*Delete);
  void (*Close);	
} vfs_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif

