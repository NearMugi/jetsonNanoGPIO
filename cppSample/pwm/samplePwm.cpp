#include <iostream>
#include <chrono> 
#include <thread>

#include <signal.h>
#include <JetsonGPIO.h>
using namespace std;
// Pin Definitions
int output_pin = 33;

int main(){
	int output_pin = 18;
	GPIO::setmode(GPIO::BOARD);
	GPIO::setup(output_pin, GPIO::OUT, GPIO::HIGH);
	cout << "BOARD "<< output_pin << "pin, set to OUTPUT, HIGH" << endl;
	
	GPIO::output(output_pin, GPIO::LOW);

	GPIO::cleanup();	

	cout << "end" << endl;	
		
	return 0;
}
