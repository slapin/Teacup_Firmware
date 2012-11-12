/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */


#include "ch.h"
#include "hal.h" 

#include "timer.h"

volatile uint8_t	clock_flag_10ms;
volatile uint8_t	clock_flag_250ms;
volatile uint8_t	clock_flag_1s;


static void timer_Handler(GPTDriver *gptp);

GPTConfig gpt3cfg = {1000000,  // 1MHz clock? 
	timer_Handler};

static void timer_Handler(GPTDriver *gptp)
{      
}  

void timer_init(void) 
{
  	//
	gptStart (&GPTD3, &gpt3cfg);
	gptStartContinuous (&GPTD3, 1000);

}

void setTimer(uint32_t delay)
{
	
}

void timer_stop(void)
{
}