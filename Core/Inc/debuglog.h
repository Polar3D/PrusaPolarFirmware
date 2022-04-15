/**
  ******************************************************************************
  * @file           : debuglog.h
  * @brief          : Header to provide debug prototypes.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Uzair Chughtai.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUGLOG_H
#define __DEBUGLOG_H

/*
 Private incldue------------------------------------------------------------
#include "stdio.h"
#include "string.h"

 Private define ------------------------------------------------------------
#define DEBUGBUFSIZE						256

 Private function prototype-------------------------------------------------
#define DEBUG_PRINTF(...)			do{ 																			\
											char* tmpBuffer; 														\
											tmpBuffer = pvPortMalloc(DEBUGBUFSIZE * sizeof(char)); 					\
											if(tmpBuffer!=NULL){ 													\
												snprintf(tmpBuffer, DEBUGBUFSIZE, __VA_ARGS__); 					\
												for(int i=0; tmpBuffer[i]!='\0'; i++)								\
													ITM_SendChar((uint32_t)tmpBuffer[i]);							\
											} 																		\
											vPortFree(tmpBuffer); 													\
									}while(0)
*/

#ifdef __cplusplus
}
#endif

#endif /* __DEBUGLOG_H */
