/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : mbedtls.c
  * Description        : This file provides code for the configuration
  *                      of the mbedtls instances.
  ******************************************************************************
  ******************************************************************************
   * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "mbedtls.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "cmsis_os.h"
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* Global variables ---------------------------------------------------------*/
mbedtls_ssl_context ssl;
mbedtls_ssl_config conf;
mbedtls_x509_crt cert;
mbedtls_ctr_drbg_context ctr_drbg;
mbedtls_entropy_context entropy;

/* USER CODE BEGIN 2 */
struct t_MBEDTLS_RTOS_timerContext{
	int f_state;
	int int_delay_ms;
	int final_delay_ms;
	TickType_t StartPoint;
	uint8_t f_expire_int;
	uint8_t f_expire_final;
	osTimerId MbedTLS_timerIntHandle;
	osTimerId MbedTLS_timerFinalHandle;
} MBEDTLS_RTOS_timerContext;

void MbedTLS_TimerIntCallback(void const * argument)
{
	MBEDTLS_RTOS_timerContext.f_expire_int = 1;
}

void MbedTLS_TimerFinalCallback(void const * argument)
{
	MBEDTLS_RTOS_timerContext.f_expire_final = 1;
}

void mbedtls_timing_set_delay( void *data, uint32_t int_ms, uint32_t fin_ms )
{
	if(fin_ms==0){
		osTimerStop(MBEDTLS_RTOS_timerContext.MbedTLS_timerIntHandle);
		osTimerStop(MBEDTLS_RTOS_timerContext.MbedTLS_timerFinalHandle);
		MBEDTLS_RTOS_timerContext.int_delay_ms = 0;
		MBEDTLS_RTOS_timerContext.final_delay_ms = 0;
		MBEDTLS_RTOS_timerContext.f_expire_int = 0;
		MBEDTLS_RTOS_timerContext.f_expire_final = 0;
		return;
	}
	MBEDTLS_RTOS_timerContext.int_delay_ms = int_ms;
	MBEDTLS_RTOS_timerContext.final_delay_ms = fin_ms;
	MBEDTLS_RTOS_timerContext.f_expire_int = 0;
	MBEDTLS_RTOS_timerContext.f_expire_final = 0;
	if(int_ms > fin_ms)
		return;
	if(int_ms!=0)
		osTimerStart(MBEDTLS_RTOS_timerContext.MbedTLS_timerIntHandle, int_ms);
	else
		osTimerStop(MBEDTLS_RTOS_timerContext.MbedTLS_timerIntHandle);
	osTimerStart(MBEDTLS_RTOS_timerContext.MbedTLS_timerFinalHandle, fin_ms);
	MBEDTLS_RTOS_timerContext.StartPoint = xTaskGetTickCount();
}

int mbedtls_timing_get_delay( void *data )
{
	if(MBEDTLS_RTOS_timerContext.final_delay_ms==0)
		return -1;
	if((MBEDTLS_RTOS_timerContext.f_expire_int==0)&&(MBEDTLS_RTOS_timerContext.f_expire_final==0))
		return 0;
	else if(MBEDTLS_RTOS_timerContext.f_expire_int==1)
		return 1;
	else if(MBEDTLS_RTOS_timerContext.f_expire_final==1)
		return 2;

	return 0;
}
/* USER CODE END 2 */

/* MBEDTLS init function */
void MX_MBEDTLS_Init(void)
{
   /**
  */
  mbedtls_ssl_init(&ssl);
  mbedtls_ssl_config_init(&conf);
  mbedtls_x509_crt_init(&cert);
  mbedtls_ctr_drbg_init(&ctr_drbg);
  mbedtls_entropy_init( &entropy );
  /* USER CODE BEGIN 3 */
  MBEDTLS_RTOS_timerContext.MbedTLS_timerIntHandle = xTimerCreate(  "MbedTLS_timerInt", 1, osTimerOnce, 0, (TimerCallbackFunction_t)MbedTLS_TimerIntCallback );
  MBEDTLS_RTOS_timerContext.MbedTLS_timerFinalHandle = xTimerCreate(  "MbedTLS_timerFin", 1, osTimerOnce, 0, (TimerCallbackFunction_t)MbedTLS_TimerFinalCallback );
  /* USER CODE END 3 */

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @}
  */

/**
  * @}
  */

