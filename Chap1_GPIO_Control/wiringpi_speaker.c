#include <wiringPi.h>
#include <softTone.h>

int main()
{
    wiringPiSetupGpio();
    softToneCreate(25);
    softToneWrite(25, 440);
    delay(100);

    return 0;
}
