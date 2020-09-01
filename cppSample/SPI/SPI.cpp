#include "SPI.hpp"


//  SPI モジュールの初期化（最初に１回だけ呼び出す: "/dev/spidev0.0", 8MHz）
bool SPI::init ()
{
    return init("/dev/spidev0.0", SPI_SPEED);
}
//  マニュアル初期化
//  ex) spi_init("/dev/spidev0.1", 1000000);  //  1MHz clock
bool SPI::init (const char *device, int clockInHz)
{
    int  ret;
    mode = SPI_MODE_0;
    clock = clockInHz;
    bits = SPI_BITS;
    delay = SPI_DELAY;

    // Open SPI Device
    fd = open(device, O_RDWR);
    if (fd < 0) {
        printf("error: cannot open %s (SPI::init)\n", device);
        return false;
    }

    // SPI Mode
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret < 0) {
        printf("error: cannot set WR_MODE to %d (SPI::init)\n", mode);
        close(fd);
        return false;
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret < 0) {
        printf("error: cannot set RD_MODE to %d (SPI::init)\n", mode);
        close(fd);
        return false;
    }

    // Bits per word
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error: cannot set WR_BITS_PER_WORD to %d (SPI::init)\n", bits);
        close(fd);
        return false;
    }
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error: cannot set RD_BITS_PER_WORD to %d (SPI::init)\n", bits);
        close(fd);
        return false;
    }

    printf("SPI Device : %s (%dHz)\n", device, clockInHz);
    printf("fd : %d\n", fd);
    printf("Mode : %d\n", mode);
    printf("BitPerWord : %d\n", bits);

    return true;
}

// quit
void SPI::quit ()
{
    close(fd);
}

bool SPI::transfer(unsigned char* tx, unsigned char* rx)
{
    
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = sizeof(tx) / sizeof(tx[0]),
        .speed_hz = clock,
        .delay_usecs = delay,
        .bits_per_word = bits,
        .cs_change = 0,
    };

    //  send this byte
    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (ret < 0) {
        printf("error: cannot send spi message (%d)\n", ret);
        return false;
    }
    
    return true;
}
