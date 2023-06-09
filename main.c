/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{

	// Enable HSE
	enable_hse();

	// enable the APB2 bus
	enable_apb2();

	// set PC13 to be OUTPUT and OPEN-DRAIN
	configure_gpio_pin();

    /* Loop forever */
	for(;;){

		// Toggle the LED ON & OFF every 1s
		toggle_LED();

		// Delay to make the toggling visible
		for (volatile uint32_t i = 0; i < 1000000; i++);

	}

}
