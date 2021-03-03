#include <wiringPi.h>

int main()
{
    int pin16 = 16, pin20 = 20, pin21 = 21;

	wiringPiSetupGpio();
	
	while(1)
	{
		pinMode(pin16, OUTPUT);
		digitalWrite(pin16, HIGH);
		delay(1000);
		digitalWrite(pin16, LOW);

		pinMode(pin20, OUTPUT);
		digitalWrite(pin20, HIGH);
		delay(1000);
		digitalWrite(pin20, LOW);
		
		pinMode(pin21, OUTPUT);
		digitalWrite(pin21, HIGH);
		delay(1000);
		digitalWrite(pin21, LOW);
	}

    return 0;
}

