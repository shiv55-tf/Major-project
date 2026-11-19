#include "header.h"

#define done ((ADDR>>31)&1)

void adc_init(void)
{
    PINSEL1 |= 0X15400000;
    ADCR = 0X00200400; // Set PDN and PCLK pins
}

unsigned int adc_read(unsigned int ch_num)
{
    unsigned int result;

    ADCR |= (1 << ch_num);   // Select channel
    ADCR |= (1 << 24);       // Start ADC

    while(done == 0);

    ADCR ^= (1 << 24);       // Stop ADC
    ADCR ^= (1 << ch_num);   // Deselect channel

    result = (ADDR >> 6) & 0X3FF; // Extract ADC data

    return result;
}
