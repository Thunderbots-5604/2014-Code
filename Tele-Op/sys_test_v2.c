#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftmotor_1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     sweep,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightmotor_1,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     rightmotor_2,  tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     grab,          tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C1_1,     leftmotor_2,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     backboard,     tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define setting_twoEncoders

#include "../api/api.c"

typedef enum {
	SETPOWER,
	LEFT,
	RIGHT,
	DRIVE,
	ROTATE,
	SWEEPER,
	CONVEYOR,
	BACKBOARD,
	GOALHOOK,
	LIFT
} Mode;

const string modeStrings[10] = {"Change power", "Left drive",
	"Right drive", "Parallel Drive", "Rotational Drive",
	"Sweep Motor", "Conveyor motor", "Backboard shield",
	"Goal hook", "Lift motor"};

Mode nextMode(Mode m);
Mode lastMode(Mode m);
void waitRelease(int button);
task cycleModes();

Mode currentMode = SETPOWER;
short power = 80;
const short powerIncrement = 5;

task main()
{
	nNxtExitClicks = 3;
	waitRelease(3);
	StartTask(cycleModes);

	while (power >= 0) {
		while (currentMode == SETPOWER) {
			while (nNxtButtonPressed == 2) {
				power -= powerIncrement;
				waitRelease(2);
			}
			while (nNxtButtonPressed == 1) {
				power += powerIncrement;
				waitRelease(1);
			}
			EndTimeSlice();
		}

		while (currentMode == LEFT) {
			if (nNxtButtonPressed == 2)
				setMovement(-power, -power);
			else if (nNxtButtonPressed == 1)
				setMovement(power, power);
			else setMovement(0, 0);
			EndTimeSlice();
		}

		while (currentMode == RIGHT) {
			if (nNxtButtonPressed == 2)
				setMovement(-power, power);
			else if (nNxtButtonPressed == 1)
				setMovement(power, -power);
			else
				setMovement(0, 0);
			EndTimeSlice();
		}

		while (currentMode == DRIVE) {
			if (nNxtButtonPressed == 2)
				setMovement(-power, 0);
			else if (nNxtButtonPressed == 1)
				setMovement(power, 0);
			else
				setMovement(0, 0);
			EndTimeSlice();
		}

		while (currentMode == ROTATE) {
			if (nNxtButtonPressed == 2)
				setMovement(0, -power);
			else if (nNxtButtonPressed == 1)
				setMovement(0, power);
			else
				setMovement(0, 0);
			EndTimeSlice();
		}

		while (currentMode == SWEEPER) {
			if (nNxtButtonPressed == 2)
				motor[sweep] = -power;
			else if (nNxtButtonPressed == 1)
				motor[sweep] = power;
			else
				motor[sweep] = 0;
			EndTimeSlice();
		}

		while (currentMode == CONVEYOR) {
			if (nNxtButtonPressed == 2)
				motor[conveyor] = -power;
			else if (nNxtButtonPressed == 1)
				motor[conveyor] = power;
			else
				motor[conveyor] = 0;
			EndTimeSlice();
		}

		while (currentMode == BACKBOARD) {
			if (nNxtButtonPressed == 2)
				//motor[backboard] = power;
				//StartTask(disengageBackboardTask);
				disengageBackboard();
			else if (nNxtButtonPressed == 1)
				//motor[backboard] = -power;
				//StartTask(engageBackboardTask);
				engageBackboard();
			else
				motor[backboard] = 0;
			EndTimeSlice();
		}

		while (currentMode == GOALHOOK) {
			if (nNxtButtonPressed == 2)
				//motor[grab] = power;
				StartTask(releaseGoalTask);
			else if (nNxtButtonPressed == 1)
				//motor[grab] = -power;
				StartTask(grabGoalTask);
			else
				motor[grab] = 0;
			EndTimeSlice();
		}

		while (currentMode == LIFT) {
			if (nNxtButtonPressed == 2)
				motor[lift] = power;
			else if (nNxtButtonPressed == 1)
				motor[lift] = -power;
			else
				motor[lift] = 0;
			EndTimeSlice();
		}
	}
}

task cycleModes() {
	while (true) {
		nxtDisplayCenteredTextLine(0, modeStrings[currentMode]);
		nxtDisplayCenteredTextLine(1, "Power: %d", power);
      		nxtDisplayCenteredTextLine(2, "Exit: back x3"); // 21 characters, will this fit?
		if (nNxtButtonPressed == 3) {
			currentMode = nextMode(currentMode);
			waitRelease(3);
		}
		if (nNxtButtonPressed == 0) {
			currentMode = lastMode(currentMode);
			waitRelease(0);
		}
		EndTimeSlice();
	}
}

Mode nextMode(Mode m) {
	if (m == SETPOWER)
		return LEFT;
	else if (m == LEFT)
		return RIGHT;
	else if (m == RIGHT)
		return DRIVE;
	else if (m == DRIVE)
		return ROTATE;
	else if (m == ROTATE)
		return SWEEPER;
	else if (m == SWEEPER)
		return CONVEYOR;
	else if (m == CONVEYOR)
		return BACKBOARD;
	else if (m == BACKBOARD)
		return GOALHOOK;
	//else if (m == GOALHOOK)
	//	return LIFT;
	else
		return SETPOWER;
}

Mode lastMode(Mode m) {
	//if (m == LIFT)
	//	return GOALHOOK;
	else if (m == GOALHOOK)
		return BACKBOARD;
	else if (m == BACKBOARD)
		return CONVEYOR;
	else if (m == CONVEYOR)
		return SWEEPER;
	else if (m == SWEEPER)
		return ROTATE;
	else if (m == ROTATE)
		return DRIVE;
	else if (m == DRIVE)
		return RIGHT;
	else if (m == RIGHT)
		return LEFT;
	else if (m == LEFT)
		return SETPOWER;
	else
		return GOALHOOK;
}

void waitRelease(int button) {
	while (nNxtButtonPressed == button) {
		nxtDisplayCenteredTextLine(0, modeStrings[currentMode]);
		EndTimeSlice();
	}
}