#include <iostream>
#include <chrono> 
#include <thread>

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <signal.h>
#include <JetsonGPIO.h>
using namespace std;
// Pin Definitions
int output_pin = 33;

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
	GPIO::setmode(GPIO::BOARD);
	GPIO::setup(output_pin, GPIO::OUT, GPIO::HIGH);
	GPIO::PWM p(output_pin, 50);
	cout << "BOARD "<< output_pin << "pin, set to OUTPUT, HIGH" << endl;
	int idx = 0;
	while(1){
		p.start(idx);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if(++idx > 100) idx =0;

 		// ESCを押すと終了		
		if (isInterrupt(27)) break;
	}
	p.stop();
	GPIO::cleanup();	

	cout << "\nend" << endl;	
		
	return 0;
}
