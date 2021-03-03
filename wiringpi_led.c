#include <wiringPi.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pin = 18;

    wiringPiSetupGpio();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);

    return 0;
}
