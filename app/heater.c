/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "heater.h"

void heater_init(void)
{
	//TODO
}

void heater_save_settings(void)
{
	//TODO
}

void heater_set(heater_t index, uint8_t value)
{
	//TODO
}

void heater_tick(heater_t h, temp_type_t type, uint16_t current_temp, uint16_t target_temp)
{
	//TODO
}

uint8_t heaters_all_off(void)
{
	//TODO
}

void pid_set_p(heater_t index, int32_t p)
{
	//TODO
}

void pid_set_i(heater_t index, int32_t i)
{
	//TODO
}

void pid_set_d(heater_t index, int32_t d)
{
	//TODO
}

void pid_set_i_limit(heater_t index, int32_t i_limit)
{
	//TODO
}


void heater_print(uint16_t i)
{
	//TODO
}
