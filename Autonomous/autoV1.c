#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     leftmotor_1,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     sweep,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightmotor_1,  tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     rightmotor_2,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     grab,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     leftmotor_2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     backboard,     tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C4_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    servo6,               tServoNone)
#define INFRARED infrared
//USE DEFAULT CONFIG

#define setting_twoEncoders

#include "../api/api.c"

task main()
{
    initializeAPI();
    initializeRobot();
    waitForStart();

    setInitial();       // Initialize the Compass and
    setDefaults();      // Coordinate system values

    moveWithDirection(60, 50);
    wait1Msec(500);
   	rotateWithOrientation(180, 50);
   	wait1Msec(500);
   	moveWithDirection(12, -50);
   	wait1Msec(500);
		grabGoal_time();
		wait1Msec(500);
		rotateWithOrientation(30, 50);
		wait1Msec(500);
		moveWithDirection(108, 50);
		wait1Msec(500);
		rotateWithOrientation(180, 50);
		wait1Msec(500);
		moveWithDirection(60, 50);
		wait1Msec(500);
		rotateWithOrientation(60, -50);
		wait1Msec(500);
		rotateWithOrientation(180, -50);
		wait1Msec(500);
		moveWithDirection(60, -50);
		wait1Msec(500);
		grabGoal_time();
		wait1Msec(500);
		rotateWithOrientation(30, 50);
		wait1Msec(500);
		moveWithDirection(24, 50);
		wait1Msec(500);
		rotateWithOrientation(30, -50);
		wait1Msec(500);
		moveWithDirection(48, 50);
		wait1Msec(500);
		rotateWithOrientation(90, 50);
		wait1Msec(500);
		moveWithDirection(24, 50);
		wait1Msec(500);
		rotateWithOrientation(90, 50);
		wait1Msec(500);
		releaseGoal_time();
		wait1Msec(500);
		moveWithDirection(12, 50);
		rotateWithOrientation(180, 50);
		rotateWithOrientation(180, 50);
		rotateWithOrientation(180, 50);
		rotateWithOrientation(180, 50);

    while (true) {
			nxtDisplayCenteredTextLine(0, "X is: %0.01f", readValues('x'));
			nxtDisplayCenteredTextLine(1, "Z is: %0.01f", readValues('z'));
			nxtDisplayCenteredTextLine(2, "O is: %0.01f", readValues('o'));
			nxtDisplayCenteredTextLine(3, "Compass: %d", SensorValue[compass]);
		}
}
