#ifndef SPI_H
#define SPI_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#define SPI_DEVICE "/dev/spidev0.0"     //  SPI デバイス（デフォルト）
#define SPI_SPEED 1000000              //  クロック 8MHz（デフォルト）
#define SPI_BITS 8                    //  ビット数（8bit のみ可能）
#define SPI_DELAY 0

class SPI {
public:
    bool init ();
    bool init (const char *_device, int clockInHz);
    void quit ();
    bool send(unsigned char* tx);
    bool receive(unsigned char* rx);
    bool transfer(unsigned char* tx, unsigned char* rx);
private:
    int fd;
    unsigned int clock;
    unsigned char mode;
    unsigned char bits;
    unsigned short int delay;
};
#endif