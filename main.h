/*
 * main.h
 *
 *  Created on: May 8, 2023
 *      Author: krcur
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>


#define RCC 0x40021000
#define GPIOC 0x40011000


// LED on PC13
// Port C runs on APB2


// RCC Registers - Address 0x4002 1000
typedef volatile struct {
	uint32_t RCC_CR;
	uint32_t RCC_CFGR;
	uint32_t RCC_CIR;
	uint32_t RCC_APB2RSTR;
	uint32_t RCC_APB1RSTR;
	uint32_t RCC_AHBENR;
	uint32_t RCC_APB2ENR;
	uint32_t RCC_APB1ENR;
	uint32_t RCC_BDCR;
	uint32_t RCC_CSR;
}RCC_REGISTERS_t;

// GPIO Registers - Address 0x4001 1000
typedef volatile struct {
	uint32_t GPIOx_CRL;
	uint32_t GPIOx_CRH;
	uint32_t GPIOx_IDR;
	uint32_t GPIOx_ODR;
	uint32_t GPIOx_BSRR;
	uint32_t GPIOx_BRR;
	uint32_t GPIOx_LCKR;
}GPIO_REGISTERS_t;



// Functions

void enable_hse(){

	// set a pointer to point to the RCC address of type RCC struct
	RCC_REGISTERS_t *rcc_ptr = (RCC_REGISTERS_t*)RCC;

	// set the HSEON bit to 1 in the CR register
	rcc_ptr->RCC_CR |= (1 << 16);

	// wait for the HSE to stabilize by waiting for the RDY flag
	while(!(rcc_ptr->RCC_CR & (1 << 17)));

	// configure the PLL

	// set the PLL source to HSE
	rcc_ptr->RCC_CFGR |= (1 << 16);

	// set the PLL multiplication factor to 3
	// but clear 18-21 first
	rcc_ptr->RCC_CFGR &= ~(0xF << 18);
	rcc_ptr->RCC_CFGR |= (1 << 18);

	// turn the PLL ON
	rcc_ptr->RCC_CR |= ( 1 << 24);

	// wait for the PLL to lock
	while(!(rcc_ptr->RCC_CR & ( 1 << 25)));

	// set the PLL as the SYSCLK source
	rcc_ptr->RCC_CFGR |= (1 << 1);

	// wait until the SYSCLK source has changed
	// the register needs to be set to 0x2 ( or 0b10 ) to select the PLL
	while( (rcc_ptr->RCC_CFGR & (0x3 << 2)) != 0x2 );


}

void enable_apb2(){

	// set a pointer to point to the RCC address of type RCC struct
	RCC_REGISTERS_t *rcc_ptr = (RCC_REGISTERS_t*)RCC;

	// enable the apb2 bus clk for PORT C
	rcc_ptr->RCC_APB2ENR |= ( 1 << 4);

}

void configure_gpio_pin(){

	// create a pointer to the GPIOC register
	GPIO_REGISTERS_t *gpioc_ptr = (GPIO_REGISTERS_t*)GPIOC;

	// set pin 13 to output and open-drain
	gpioc_ptr->GPIOx_CRH |= ( 1 << 20 );
	gpioc_ptr->GPIOx_CRH |= ( 1 << 22 );

}

void toggle_LED(){

	// create a pointer to the GPIOC register
	GPIO_REGISTERS_t *gpioc_ptr = (GPIO_REGISTERS_t*)GPIOC;

	// if the pin is 0, set it to 1, if the pin is 1, set it to 0
	// effectively toggling the pin
	gpioc_ptr->GPIOx_ODR ^= ( 1 << 13 );

}




#endif /* MAIN_H_ */
