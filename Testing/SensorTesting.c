#pragma config(Sensor, S1,     infrared,       sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S2,     compass,        sensorI2CHiTechnicCompass)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while (nNxtButtonPressed != 0) {
		nxtDisplayCenteredBigTextLine(1, "%d", SensorValue[infrared]);
		nxtDisplayCenteredBigTextLine(5, "%d", SensorValue[compass]);
	}

}