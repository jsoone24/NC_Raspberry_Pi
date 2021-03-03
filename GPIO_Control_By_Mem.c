#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
//////////////////////
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
//////////////////////

#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

#define BLOCK_SIZE (4 * 1024)
#define BCM2708_PERI_BASE 0x3F000000
#define GPIO_BASE (BCM2708_PERI_BASE + 0x00200000)

static volatile unsigned int *gpio;

void pin_25_Mode(int mode);

int digitalRead_pin_25();

int main()
{
    int fd;

    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("Fail open /dev/mem\n");
    }

    gpio = (unsigned int *)mmap(0, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
    pin_25_Mode(INPUT);

    while (1)
    {
        printf("%d\n", digitalRead_pin_25());
        sleep(1);
    }

    return 0;
}

void pin_25_Mode(int mode)
{
    int fSel, shift, alt;

    fSel = 2;
    shift = 15;

    if (mode == INPUT)
    {
        *(gpio + fSel) = (*(gpio + fSel) & ~(7 << shift));
    }
    else if (mode == OUTPUT)
    {
        *(gpio + fSel) = (*(gpio + fSel) & ~(7 << shift)) | (1 << shift);
    }
}

int digitalRead_pin_25()
{
    int gpioToGPLEV = 13;

    if ((*(gpio + gpioToGPLEV) & (1 << (25 & 31))) != 0)
        return HIGH;
    else
        return LOW;
}
