

void adc_init(void){
    // Set the division factor
    ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
    ADCSRA |= (1<<ADEN);    // Enable ADC module
    ADMUX = (1<<REFS0);     // Set the volage reference for ADC to VCC
}

uint16_t read_adc(uint8_t channel){
    // Keep the exising setting and set the passed channel
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    /* ADMUX = (ADMUX & 0b11111000) | (channel & 0b00000111); */

    ADCSRA |= (1<<ADSC);        // Start conversion
    while(ADCSRA & (1<<ADSC));  // Wait for conversion
    return ADC;
}


