/************************************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi *
 * File Authors: Zack Mudd, Tyler Jones         *
 ************************************************/

#include "WPILib.h"

struct SonarOutput {
	float dist;
};

class Sonar {
	AnalogChannel* dist;
public:

	Sonar::Sonar() {
		dist = new AnalogChannel(3);
	}

	SonarOutput Sonar::Run() {
		SonarOutput output = SonarOutput();
		output.dist = dist->GetVoltage() * 512 / 5;
		return output;

	}

};
