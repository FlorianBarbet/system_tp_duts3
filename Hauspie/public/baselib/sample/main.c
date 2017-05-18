#include "peripherals.h"


#define ADDR_OFFSET(addr, offset) ((uint32_t*)((uint8_t*)(addr) + 0x20 * GET_PORT(p)))

void select_gpio_out_mode(uint32_t p)
{
    uint32_t register_idx = 2*GET_PORT(p);
    uint32_t pin = GET_PIN(p);
    volatile uint32_t *dir_register;

    if (pin >= 16)
    {
    	pin -= 16;
    	register_idx++;
    }
    /* Configure function */
    PINSEL[register_idx] &= ~(3 << (pin * 2)); /* Clear the two function bits -> gpio mode (p. 108) */

    /* Configure mode */
    PINMODE[register_idx] &= ~(3 << (pin * 2)); /* Clear the two mode bit -> pull-up resistor */

    /* Configure opendrain */
    PINMODE_OD[GET_PORT(p)] &= ~(1 << GET_PIN(p)); /* Clear bit -> normal (not opendrain) mode */

    /* Set GPIO mode to output */
    dir_register = ADDR_OFFSET(&FIO0DIR, 0x20 * GET_PORT(p));
    *dir_register |= (1 << GET_PIN(p)); /* set bit to 1 -> set pin to output */
}

/* Set pin to HIGH */
void set_pin(uint32_t p)
{
    volatile uint32_t *set_register = ADDR_OFFSET(&FIO0SET, 0x20 * GET_PORT(p));
    volatile uint32_t *mask_register = ADDR_OFFSET(&FIO0MASK, 0x20 * GET_PORT(p));

    *mask_register = ~(1 << GET_PIN(p)); /* Affected pin are those whose mask is 0 */
    *set_register = (1 << GET_PIN(p)); /* Set pin to HIGH */
}

/* Clear pin to GND */
void clr_pin(uint32_t p)
{
    volatile uint32_t *clr_register = ADDR_OFFSET(&FIO0CLR, 0x20 * GET_PORT(p));
    volatile uint32_t *mask_register = ADDR_OFFSET(&FIO0MASK, 0x20 * GET_PORT(p));

    *mask_register = ~(1 << GET_PIN(p)); /* Affected pin are those whose mask is 0 */
    *clr_register = (1 << GET_PIN(p)); /* Set pin to GND */
}


void wait(void)
{
    int i;
    uint32_t j;

    for (i=0 ; i < (10000) ; ++i)
    	j = FIO0MASK;
    /* avoids an unused variable 'j' warning */
    if (j == (1000000))
    	return ;
}

void main(void)
{
    /* First select GPIO mode of LED PINS */
    select_gpio_out_mode(MBED_BASE_LED1);
    select_gpio_out_mode(MBED_BASE_LED2);
    select_gpio_out_mode(MBED_BASE_LED3);
    select_gpio_out_mode(MBED_BASE_LED4);


    while(1)
    {
	/* Turn all leds on */
	set_pin(MBED_BASE_LED1);
	set_pin(MBED_BASE_LED2);
	clr_pin(MBED_BASE_LED3);
	clr_pin(MBED_BASE_LED4);

	wait();

	/* Clear leds */
	clr_pin(MBED_BASE_LED1);
	clr_pin(MBED_BASE_LED2);
	set_pin(MBED_BASE_LED3);
	set_pin(MBED_BASE_LED4);
	
	wait();

    }
}
