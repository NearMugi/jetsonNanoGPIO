#include <iostream>
#include <chrono> 
#include <thread>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <signal.h>
#include <JetsonGPIO.h>

#include "SPI.hpp"

using namespace std;

// キー入力
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int isInterrupt(char k)
{
    if ( kbhit() )
    {
        if ( getchar() == k )
        {
            return 1;
        }
    }
    return 0;
}

int main(){

    SPI spi;
    if(!spi.init()) return 0;

    while(1){
        unsigned char tx[3] = {0x00, 0x27, 0x50};
        unsigned char rx[3] = {0x00, 0x00, 0x00};
        bool ret = spi.transfer(tx, rx);
        if(ret){
            printf("0x%02x, 0x%02x, 0x%02x\n", rx[0], rx[1], rx[2]);
        }

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

 		// ESCを押すと終了		
		if (isInterrupt(27)) break;
	}
    cout << "\n SPI quit" << endl;
	spi.quit();	

	cout << "\nend" << endl;	
		
	return 0;
}