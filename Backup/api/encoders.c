// encoders.c
// Contains code for accessing encoder values at the lowest possible level

// Unit conversions


long degreesToTurnTicks(float degrees) {
	return ENCODER_TICKS_PER_TURN_DEGREE * degrees;
}

long degreesToTicks(float degrees) {
	return degreesToTurnTicks(degrees);
}


long degreesToSwingTicks(float degrees) {
	return ENCODER_TICKS_PER_SWING_DEGREE * degrees;
}