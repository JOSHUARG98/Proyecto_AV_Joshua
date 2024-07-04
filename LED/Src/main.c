/**
 * LIESE 2024-2
 *
 * MCU: STM32L452
 * Title: Blinking led
 *
 * Description: code to show the use of a GPIO
 * in STM32L452 with bare metal programming in C.
 * Macro pointer memory mapping technique is used
 * to access to registers
 * */

// Header for the use of fixed width integers
#include <stdint.h>

// ********   Macro definitions  ***********

// RCC base address. RM0394 page 68
#define RCC_base	(uint32_t)0x40021000	// Casting to uint32_t
#define GPIOB_base	(uint32_t)0x48000000	// Casting to uint32_t

// RCC_AHB2ENR address from RCC base. RM0394 page
#define RCC_AHB2ENR (*((volatile uint32_t*)(RCC_base + 0x0000004C)))

// GPIOB_ODR address from GPIOB_base. RM0394 page 269
#define GPIOB_ODR   (*((volatile uint32_t*)(GPIOB_base + 0x00000414)))
// GPIOB_MODER address from GPIOB_base. RM0394 page 267
#define GPIOB_MODER (*((volatile uint32_t*)(GPIOB_base + 0x00000400)))

// Function for delay
// Default clock in STM32L452 is 4 MHz
// delay[s] = (5/4x10^6)*n
void delay(uint32_t n)
{
	while(n--);
}

int main(void)
{
    // Enable clock for PORTB. RM0394 page 218
    RCC_AHB2ENR |= 0X00000002;

    // Configure pin mode for PORTB. RM0394 page 267
    // PB13 as output
    // ~0x0C000000 = 0xF3FFFFFF
    // [GPIOB_MODER &= ~0x0C000000] is equal to [GPIOB_MODER = GPIOB_MODER & 0xF3FFFFFF]
    GPIOB_MODER &= ~0x0C000000; // Clears bit field MODE13[1:0]
    GPIOB_MODER |=  0x04000000; // Set bit field MODE13[1:0] to 01 (Output mode)

    while(1)
    {
    	// Commute bit 13 with a xor operation
        GPIOB_ODR ^= 0x00002000;
        // delay = 250ms
        delay(200000);
    }
}
