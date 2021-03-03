#include <wiringPi.h>

int main()
{
    int led_pin = 18; 
    int switch_pin = 24; 
    int i, led_state;   //led_state == 1 on, led_state == 0 off, 
    
    wiringPiSetupGpio();

    pinMode(led_pin, OUTPUT);
    pinMode(switch_pin, INPUT);

    while (1)
    {
        if((led_state == 1) && (digitalRead(switch_pin) == LOW))
        {
            digitalWrite(led_pin, LOW);
            led_state = 0;
            delay(1000);
            printf("h\n");
        }
        else if((led_state == 0) && (digitalRead(switch_pin) == LOW))
        {
            digitalWrite(led_pin, HIGH);
            led_state = 1;
            delay(1000);
            printf("p\n");
        }
        printf("d\n");
    }

    return 0;
}
