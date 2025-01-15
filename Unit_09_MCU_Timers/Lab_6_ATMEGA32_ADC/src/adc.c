#include "adc.h"

#include <avr/io.h>
#include <util/delay.h>

// Function to initialize ADC
void ADC_Init(void) {
    // Configure ADC
    // 1. Select voltage reference (AVCC with external capacitor at AREF pin)
    ADC_VREF_AVCC();
    
    // 2. Select input channel (ADC0/PC0)
    ADC_IN_CH0();
    
    // 3. Enable ADC and set prescaler
    // Prescaler of 128 for 16MHz clock (125kHz ADC clock)
    ADC_EN();
    ADC_PRE_128();
    
    // 4. Optional: Enable auto-trigger
    ADC_AUTO_TRIG_EN();
    
    // 5. Select auto-trigger source (free running mode)
    ADC_ATS_FREE();
}

// Function to read ADC value
uint16_t ADC_Read(void) {
    // Start conversion
    ADC_START_CONV();
    
    // Wait for conversion to complete
    while (ADC->ADCSRA & (1 << 6));
    
    // Read and return ADC value (right-adjusted)
    return ADC_READ_DATA_RA();
}

// Optional: Function to convert ADC value to voltage
float ADC_ToVoltage(uint16_t adcValue) {
    // Assuming AVCC is 5V and 10-bit resolution
    return (adcValue * 5.0) / 1024.0;
}

int main(void) {
    // Initialize UART or other communication method for output
    // (not shown in this example)
    
    // Initialize ADC
    ADC_Init();
    
    while (1) {
        // Read ADC value
        uint16_t adcResult = ADC_Read();
        
        // Convert to voltage
        float voltage = ADC_ToVoltage(adcResult);
        
        // Here you would typically send the result via UART, 
        // update an LCD, or perform further processing
        
        // Delay between readings
        _delay_ms(100);
    }
    
    return 0;
}