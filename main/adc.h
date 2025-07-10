#ifndef ADC_H
#define ADC_H

void adc_task(void *pvParameters);
double adc_get_brightness();
double adc_get_temp();

#endif