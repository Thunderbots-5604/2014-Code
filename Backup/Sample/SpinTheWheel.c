#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     wheel,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

void setWheelPower(int cheeseburger){
	motor[wheel] = cheeseburger;
	//int i = 2;
}

int correctJoystick(int joystick) {
	if (abs(joystick) <= 15) // if joystick is between -15 and +15
		return 0; //completely disregard the input from the joystick
	else
		return joystick; //leave the input unchanged
}

task main()
{
	while (true) {
		 getJoystickSettings(joystick);
		 //int wheelPower = joystick.joy1_y1 / 1.28; 				<-- Old way
		 int wheelPower = correctJoystick(joystick.joy1_y1); // 	<-- New way
		 wheelPower /= 1.28; //divide wheelPower by 1.28
		 setWheelPower(wheelPower);
		 //wait1Msec(10);
	}
}