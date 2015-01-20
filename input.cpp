/***********************************
 * Copyright (c) 2014 FRC Team 4139: Easy as Pi
 * Authors: John DiIorio
 */

#include "WPILib.h"
#include "sensors.cpp"
#include "controller.cpp"

struct InputOutput {
	ControllerOutput controllerOutput;
	float returnDistance, returnRotation;
	SensorOutput sensorOutput;
	bool lowPressure;
};
class Input {
public:
	X360Controller* controller;
	Sensors* sensors;
	Pressure* pressure;

	Input::Input() {
		controller = new X360Controller();
		sensors = new Sensors();
		//pressure = new Pressure();
	}
	InputOutput Input::Run() {
		InputOutput output;
		output.controllerOutput = controller->Run(ControllerInput());
		SensorInput sensorInput;
		 sensorInput.GyroReset = output.controllerOutput.ZapGyro;
		 SensorOutput sensorOutput = sensors->Run(sensorInput);
		 
		 output.lowPressure = sensorOutput.lowPressure;
		 output.returnRotation = sensorOutput.Rotation;
		 output.returnDistance = sensorOutput.Distance;
		 
		return output;
	}
};
