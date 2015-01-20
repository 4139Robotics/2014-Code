/**************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Brooke Polansky, Julia Baylon
 */

#include "WPILib.h"

struct PressureInputs {

};

struct PressureOutputs {
	bool LowPressure;

};

class Pressure {
	//DigitalInput* Switch;
public:
	Pressure::Pressure() {
		//Switch=new DigitalInput(1);

	}
	PressureOutputs Pressure::Run() {
		PressureOutputs output;
		//output.LowPressure = Switch->Get();
		return output;
	}
};
