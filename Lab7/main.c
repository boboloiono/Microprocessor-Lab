/**
 * @file main.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-10-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "drivers/ece315.h"
// #include <list>

int main(void)
{
    bool buzzer_on = false;
    bool status_rx_upstream = false;
    bool status_rx_downstream = false;

    uint8_t upstream_msg[80];
    uint8_t downstream_msg[80];

    /* Enable global interrupts */
    __enable_irq();

    /* Enable the button*/
    ece315_button_init();

    /* Enable LEDs */
    ece315_leds_init();

    // Turn LEDS off
    ece315_leds_all_off();

    /* Initialize the Buzzer to operate at 2.5KHz */
    ece315_buzzer_init(2500);
    // uint16 LED[12] = {1, 2, 3, 4, 'PIN_LED_Y4', 'PIN_LED_Y3', 'PIN_LED_Y2','PIN_LED_Y1','PIN_LED_G4', 'PIN_LED_G3','PIN_LED_G2', "PIN_LED_G1"};
    uint16 index = 0;
    uint16 time = 50;
    uint16 StartofGame = 1;
    
    cyhal_gpio_write(PIN_LED_G4, LED_ON);

    for (;;)
    {
        if(StartofGame) {
            //G4->G3
            cyhal_system_delay_ms(time);

            if (index == 0) {
                cyhal_gpio_write(PIN_LED_G3, LED_ON);
                cyhal_gpio_write(PIN_LED_G4, LED_OFF);
                index++;
            }
            else if(index == 1){
                cyhal_gpio_write(PIN_LED_G2, LED_ON);
                cyhal_gpio_write(PIN_LED_G3, LED_OFF);
                index++;
            }
            else if(index == 2){
                cyhal_gpio_write(PIN_LED_G1, LED_ON);
                cyhal_gpio_write(PIN_LED_G2, LED_OFF);
                index++;
            }
            else if(index == 3){
                cyhal_gpio_write(PIN_LED_R4, LED_ON);
                cyhal_gpio_write(PIN_LED_G1, LED_OFF);
                index++;
            }
            else if(index == 4){
                cyhal_gpio_write(PIN_LED_R3, LED_ON);
                cyhal_gpio_write(PIN_LED_R4, LED_OFF);
                index++;
            }
            else if(index == 5){
                cyhal_gpio_write(PIN_LED_R2, LED_ON);
                cyhal_gpio_write(PIN_LED_R3, LED_OFF);
                index++;
            }
            else if(index == 6){
                cyhal_gpio_write(PIN_LED_R1, LED_ON);
                cyhal_gpio_write(PIN_LED_R2, LED_OFF);
                index++;
            }
            else if(index == 7){
                cyhal_gpio_write(PIN_LED_Y4, LED_ON);
                cyhal_gpio_write(PIN_LED_R1, LED_OFF);
                index++;
            }
            else if(index == 8){
                cyhal_gpio_write(PIN_LED_Y3, LED_ON);
                cyhal_gpio_write(PIN_LED_Y4, LED_OFF);
                index++;
            }
            else if(index == 9){
                cyhal_gpio_write(PIN_LED_Y2, LED_ON);
                cyhal_gpio_write(PIN_LED_Y3, LED_OFF);
                index++;
            }
            else if(index == 10){
                cyhal_gpio_write(PIN_LED_Y1, LED_ON);
                cyhal_gpio_write(PIN_LED_Y2, LED_OFF);
                index++;
            }
            else if(index == 11){
                cyhal_gpio_write(PIN_LED_G4, LED_ON);
                cyhal_gpio_write(PIN_LED_Y1, LED_OFF);
                index = 0;
            }
            
            if (ALERT_BUTTON_PRESSED)
            {
                ALERT_BUTTON_PRESSED = false;
                if(index == 0 || index == 1 || index == 2 || index == 3){
                    ece315_buzzer_start();
                    cyhal_system_delay_ms(250);
                    ece315_buzzer_stop();
                    cyhal_system_delay_ms(1000);
                    time = time - 5;
                }
                else {
                    StartofGame = 0;
                }
            }
        }
        else {
            if(ALERT_LEDS_OFF)
            {
                ALERT_LEDS_OFF = false;
                ece315_leds_all_off();
            }
            
            if(ALERT_LEDS_ON)
            {
                ALERT_LEDS_ON = false;
                ece315_leds_all_on();
            }

            if (ALERT_BUTTON_PRESSED)
            {
                ALERT_BUTTON_PRESSED = false;
                StartofGame = 1;
                time = 50;
            }
        }
        
        /*
        if (ALERT_BUTTON_PRESSED)
        {
            ALERT_BUTTON_PRESSED = false;
            buzzer_on = !buzzer_on;

            if (buzzer_on)
            {
                ece315_buzzer_start();
            }
            else
            {
                ece315_buzzer_stop();
            }
        }

        if(ALERT_LEDS_OFF)
        {
            ALERT_LEDS_OFF = false;
            ece315_leds_all_off();
        }
        
        if(ALERT_LEDS_ON)
        {
            ALERT_LEDS_ON = false;
            ece315_leds_all_on();
        }
        */
    }
}

/* [] END OF FILE */
