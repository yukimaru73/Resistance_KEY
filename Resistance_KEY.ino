#include "DigiMouse.h"

//+-+->Global Variables<-+-+//
const int PIN_SWITCH = 0, PIN_LED=1/*, PIN_SENSOR = 2*/;

int DISPLAY_WIDTH = 1080;
int DISPLAY_HEIGHT = 1920;


//bool isSettingMode = false;


//+-+->Presetted Hook Functions<-+-+//
void setup() {
	digiSparkSetUp();

	//if(isSwitchPushed()) isSettingMode = true;
}

void loop() {
	if(isSwitchPushed()) return;


}


//+-+->Unique Functions<-+-+//
bool isSwitchPushed(){
	return digitalRead(PIN_SWITCH)==HIGH;
}

/*
int sensorStatus(){

}
*/

void digiSparkSetUp(){
	pinMode(PIN_SWITCH,INPUT);
	pinMode(PIN_LED,OUTPUT);
	//pinMode(PIN_SENSOR,INPUT);

	digitalWrite(PIN_LED,HIGH);
	DigiMouse.begin();
	digitalWrite(PIN_LED,LOW);
}

void moveCursor(int x, int y, const int px_per_ms, const int ms_delay){
	const int delta_X = x<0 ? px_per_ms : -px_per_ms;
	const int delta_Y = y<0 ? px_per_ms : -px_per_ms;
	
	while(abs(x) > px_per_ms && abs(y) > px_per_ms){
		DigiMouse.move(delta_X, delta_Y, 0);
		DigiMouse.delay(ms_delay);
		DigiMouse.update();
		x += delta_X;
		y += delta_Y;
	}

	if(abs(x) < px_per_ms){
		DigiMouse.moveX(x);
		DigiMouse.delay(ms_delay);
		
		while(abs(y) > px_per_ms){
			DigiMouse.moveY(delta_Y);

			DigiMouse.delay(ms_delay);
			DigiMouse.update();
		}

		DigiMouse.moveY(y);
	}else{
		DigiMouse.moveY(y);
		DigiMouse.delay(ms_delay);

		while(abs(x) > px_per_ms){
			DigiMouse.moveX(delta_X);

			DigiMouse.delay(ms_delay);
			DigiMouse.update();
		}

		DigiMouse.moveX(x);
	}
}
