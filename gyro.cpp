/**********************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Nick Chase, Shea Polansky
 */

#include "WPILib.h"

struct GyroInput {
	bool reset;

};
struct GyroOutput {
	float rotation;
};

class GyroSensor {
public:

	//Gyro* gyro;

	GyroSensor::GyroSensor() {
		//gyro = new Gyro(1);
	}

	GyroOutput GyroSensor::Run(GyroInput input) {
		/*if (input.reset) {
			gyro->Reset();

		}*/

		GyroOutput output = GyroOutput();
		//output.rotation = gyro->GetAngle();
		output.rotation = 0;
		return output;

	}

};
