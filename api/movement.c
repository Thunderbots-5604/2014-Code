// movement.h
// Contains all code related to the positional movement of the robot
// Lifting code and other functional systems should be defined somewhere else
// Wrappers such as drive, strafe, and rotate should be placed in simplemovement.c

#include "movement.h"

static const byte joyRange[3] = {JOYSTICK_MIN_VALUE, JOYSTICK_MAX_VALUE, JOYSTICK_MAX_VALUE - JOYSTICK_MIN_VALUE};
static const byte driveRange[3] = {DRIVE_MIN_POWER, DRIVE_MAX_POWER, DRIVE_MAX_POWER - DRIVE_MIN_POWER};
static const byte strafeRange[3] = {STRAFE_MIN_POWER, STRAFE_MAX_POWER, STRAFE_MAX_POWER - STRAFE_MIN_POWER};
static const byte rotateRange[3] = {ROTATE_MIN_POWER, ROTATE_MIN_POWER, ROTATE_MAX_POWER - ROTATE_MIN_POWER};
static const byte motorRange[3] = {MOTOR_MIN_POWER, MOTOR_MAX_POWER, MOTOR_MAX_POWER - MOTOR_MIN_POWER};
// Array format: min, max, difference

void setMovement(byte forward, byte right, byte clockwise) {
	// Scale from the range of the motors to the range of the specific movement
	forward = scaleTo(forward, &motorRange[0], &driveRange[0]);
	right = scaleTo(right, &motorRange[0], &strafeRange[0]);
	clockwise = scaleTo(clockwise, &motorRange[0], &rotateRange[0]);

	forward *= DRIVE_POWER_WEIGHT;
	right *= STRAFE_POWER_WEIGHT;
	clockwise *= ROTATE_POWER_WEIGHT;

	// Next, assign wheel powers using the mecanum algorithm
	float frontLeft = (-forward - right - clockwise);
	float frontRight = (forward - right - clockwise);
	float backLeft = (-forward + right - clockwise);
	float backRight = (forward + right - clockwise);
	//add note about why/how this works in engineering notebook


	float power[4] = {frontLeft, frontRight, backLeft, backRight};

	// find max of all wheel powers
	byte max = arrAbsmax(power, 4);

	// scale all wheels to fit within motor_max
	if (max > MOTOR_MAX_POWER) {
		float scale = (float)max / MOTOR_MAX_POWER;
		for (int i = 0; i < 4; i++)
			power[i] /= scale;
	}

	for(int i = 0; i < 4; i++)
		power[i] *= MOVE_POWER_SCALE;

   // please leave the motor names how they are
   // update other files to reflect these names
	motor[leftmotor_1] = frontLeft;
	motor[rightmotor_1] = frontRight;
	#ifndef setting_twoMotors
	motor[leftmotor_2] = backLeft;
	motor[rightmotor_2] = backRight;
	#endif
}

void setMovementFromJoystick(byte forward, byte right, byte clockwise) {
	// Scale from the range of the joystick to the range of the motors
	forward = correctJoystick(forward);
	right = correctJoystick(right);
	clockwise = correctJoystick(clockwise);

   // the rest of the code is in setMovement()
   setMovement(forward, right, clockwise);
}

//for tank drive
/*void setMovement(byte forward, byte clockwise) {
   setMovement(forward, 0, clockwise);
}*/

void setMovement(byte forward, byte clockwise) {
	// Scale from the range of the motors to the range of the specific movement

	scaleByteInputs(&forward, &clockwise);

	// Next, assign wheel powers using the mecanum algorithm
	float frontLeft = (-forward - clockwise);
	float frontRight = (forward - clockwise);
	float backLeft = (-forward - clockwise);
	float backRight = (forward - clockwise);
	//add note about why/how this works in engineering notebook


	float power[4] = {frontLeft, frontRight, backLeft, backRight};
	/*
	// find max of all wheel powers
	byte max = arrAbsmax(power, 4);

	// scale all wheels to fit within motor_max
	if (max > MOTOR_MAX_POWER) {
		float scale = (float)max / MOTOR_MAX_POWER;
		byte polarity = 1;
		//byte newPolarity = 1;
		for (int i = 0; i < 4; i++) {
			polarity = power[i] / abs(power[i]); //should be 1 or -1
			power[i] /= scale;
			if (power[i]/abs(power[i]) != polarity)
				power[i] *= polarity;
		}
	}

	for(int i = 0; i < 4; i++)
		power[i] *= MOVE_POWER_SCALE;

   // please leave the motor names how they are
   // update other files to reflect these names*/
	motor[leftmotor_1] = frontLeft;
	motor[rightmotor_1] = frontRight;
	#ifndef setting_twoMotors
	motor[leftmotor_2] = backLeft;
	motor[rightmotor_2] = backRight;
	#endif
}

void setMovementFromJoystick(byte forward, byte clockwise) {
	setMovementFromJoystick(forward, 0, clockwise);
}

byte correctJoystick(byte joyval) {
	return scaleTo(joyval, &joyRange[0], &motorRange[0]);
}

void scaleByteInputs(byte* x, byte* y) {
	if (abs(*x) > 100)
	{
		*y *= (100.0 / (float)abs(*x));
		*x *= (100.0 / (float)abs(*x));
	}
	if (abs(*y) > 100)
	{
		*x *= (100.0 / (float)abs(*y));
		*y *= (100.0 / (float)abs(*y));
	}
}

void scaleInputs(int* x, int* y) {
	if (abs(*x) > 100)
	{
		*y *= (100.0 / (float)abs(*x));
		*x *= (100.0 / (float)abs(*x));
	}
	if (abs(*y) > 100)
	{
		*x *= (100.0 / (float)abs(*y));
		*y *= (100.0 / (float)abs(*y));
	}
}
