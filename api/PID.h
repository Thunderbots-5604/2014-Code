//PID.h
//header file for PID.c
//This is where we code the PID.

#define PID_INCLUDEGUARD

void correctLinear(); //the correction algorithm for linear movement (driving)
void correctRotate(); //the correction algorithm for rotation

#ifndef setting_twoMotors
void correctSwing(int speed); //corrects for swing, will only be necessary if there is a four wheel drive
#endif