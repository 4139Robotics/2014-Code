/*
 * Copyright 2014 FRC Team 4139
 * Author(s): Joshua Taylor, Brett Galkowski
 */

#include <WPILib.h>
#include "gyro.cpp"
#include "sonar.cpp"
#include "pressure.cpp"

struct SensorInput {
	bool GyroReset;

};

struct SensorOutput {

	float Distance;
	float Rotation;
	bool lowPressure;

};

class Sensors {
private:
	GyroSensor* gyro;
	Sonar* ping;
	Pressure* pressure;
public:
	Sensors::Sensors() {
		gyro = new GyroSensor();
		ping = new Sonar();
		pressure = new Pressure();
	}
	SensorOutput Sensors::Run(SensorInput input) {
		SensorOutput output;
		GyroInput gyroInput;
		gyroInput.reset = input.GyroReset;
		output.Rotation = gyro->Run(gyroInput).rotation;
		output.Distance = ping->Run().dist;
		output.lowPressure = pressure->Run().LowPressure;
		return output;
	}

};
