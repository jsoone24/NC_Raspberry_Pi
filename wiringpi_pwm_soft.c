#include <wiringPi.h>
#include <softPwm.h>

int main()
{
    wiringPiSetupGpio();
    softPwmCreate(18, 0, 100);
    delay(1000);
    softPwmWrite(18, 25);
    delay(1000);
    softPwmWrite(18, 50);
    delay(1000);
    softPwmWrite(18, 75);
    delay(1000);
    softPwmWrite(18, 100);
    delay(1000);
    softPwmWrite(18, 0); 
    delay(1000);
    return 0;
}
