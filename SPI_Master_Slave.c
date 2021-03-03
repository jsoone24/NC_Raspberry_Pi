#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <sys/mman.h>
//////////////////////
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <unistd.h>
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

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

static unsigned char spiMode = 0;
static unsigned char spiBPW = 8;
static unsigned short spiDelay = 0;
static unsigned int spiSpeeds[2];

static volatile unsigned int *gpio;
static int spiFds[2];

void pin_25_Mode(int mode);
void digitalWrite_pin_25(int value);
int read_mcp3208_adc(unsigned char adcChannel);
int SPIDataRW(int channel, unsigned char *data, int len);
int digitalRead_pin_25();

int main()
{
    int adcChannel = 0;
    int adcValue = 0;
    ;
    int fd;

    if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("Fail open /dev/mem\n");
        return -1;
    }

    gpio = (unsigned int *)mmap(0, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);

    if ((int)gpio == -1)
    {
        return -1;
    }

    if ((fd = open("/dev/spidev0.0", O_RDWR)) < 0)
    {
        printf("Fail open /dev/spidev0.0\n");
        return -1;
    }

    spiFds[0] = fd;

    pin_25_Mode(OUTPUT);

    while (1)
    {
        adcValue = read_mcp3208_adc(adcChannel);
        printf("adc0 Value = %u\n", 300 - ((adcValue * 500) >> 10));
        sleep(1);
    }

    return 0;
}

int read_mcp3208_adc(unsigned char adcChannel)
{
    unsigned char buff[3];
    int adcValue = 0;

    buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
    buff[1] = ((adcChannel & 0x07) << 6);
    buff[2] = 0x00;

    digitalWrite_pin_25(0);

    SPIDataRW(SPI_CHANNEL, buff, 3);

    buff[1] = 0x0F & buff[1];
    adcValue = (buff[1] << 8) | buff[2];

    digitalWrite_pin_25(1);

    return adcValue;
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

int SPIDataRW(int channel, unsigned char *data, int len)
{
    struct spi_ioc_transfer spi;

    channel &= 1;

    spi.tx_buf = (unsigned long)data;
    spi.rx_buf = (unsigned long)data;
    spi.len = len;
    spi.delay_usecs = spiDelay;
    spi.speed_hz = 1000000;
    spi.bits_per_word = spiBPW;

    return ioctl(spiFds[channel], SPI_IOC_MESSAGE(1), &spi);
}

void digitalWrite_pin_25(int value)