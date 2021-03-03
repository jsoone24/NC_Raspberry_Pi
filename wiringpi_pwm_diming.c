#include <wiringPi.h>

int main()
{
    int pin18 = 18, pin23 = 23;

    wiringPiSetupGpio();

    softPwmCreate(pin18, 0, 100);
    softPwmCreate(pin23, 0, 100);

    while(1)
    {
        softPwmWrite(pin18, 0);
        softPwmWrite(pin23, 100);
        delay(500);
        softPwmWrite(pin18, 25);
        softPwmWrite(pin23, 75);
        delay(500);
        softPwmWrite(pin18, 50);
        softPwmWrite(pin23, 50);
        delay(500);
        softPwmWrite(pin18, 75);
        softPwmWrite(pin23, 25);
        delay(500);
        softPwmWrite(pin18, 100);
        softPwmWrite(pin23, 0); 
        delay(500);
        softPwmWrite(pin23, 0);
        softPwmWrite(pin18, 100);
        delay(500);
        softPwmWrite(pin23, 25);
        softPwmWrite(pin18, 75);
        delay(500);
        softPwmWrite(pin23, 50);
        softPwmWrite(pin18, 50);
        delay(500);
        softPwmWrite(pin23, 75);
        softPwmWrite(pin18, 25);
        delay(500);
        softPwmWrite(pin23, 100);
        softPwmWrite(pin18, 0); 
        delay(500);
    }

    return 0;
}
