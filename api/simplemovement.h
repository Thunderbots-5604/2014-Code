// simplemovement.h
// Header file for simplemovement.c

#include "api.h"

void drive(byte power);
void strafe(byte power);
//rotate function should be depracated, nearly uncontrolable
void rotate(byte power);
void swingTurn(byte direction, byte power);
void moveDiagonal(byte vector, byte power);

//Need to be implemented
void driveTicks(byte ticks, byte power);
void driveIn(byte dist, byte power);
void driveCm(byte dist, byte power);

void strafeTicks(byte ticks, byte power);
void strafeIn(byte dist, byte power);
void strafeCm(byte dist, byte power);

void rotateTicks(byte ticks, byte power);
void rotateDeg(byte degs, byte power);
void rotateRad(byte rads, byte power);

//Other ideas:
void swingTurnTicks(byte ticks, byte direction, byte power);
void swingTurnDeg(byte degs, byte directions, byte power);
void swingTurnRad(byte rads, byte directions, byte power);

void moveDiagonalTicks(byte dist, byte vector, byte power);
void moveDiagonalIn(byte dist, byte vector, byte power);
void moveDiagonalCm(byte dist, byte vector, byte power);

//Low priority: (Daniel's ideas)
void turnSpiral(byte power, byte distance, byte deg);