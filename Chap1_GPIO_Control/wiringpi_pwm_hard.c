#include <wiringPi.h>

int main()
{
    int pin = 18;

    wiringPiSetupGpio();

    pinMode(pin, PWM_OUTPUT);

    pwmWrite(pin, 0);
    delay(500);
    pwmWrite(pin, 128);
    delay(500);
    pwmWrite(pin, 256);
    delay(500);
    pwmWrite(pin, 512);
    delay(500);
    pwmWrite(pin, 1024);
    delay(500);
    pwmWrite(pin, 0);

    return 0;
}
