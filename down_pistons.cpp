/**********************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Brooke Polansky, Julia Baylon
 */
#include "WPILib.h"
#include <Solenoid.h>

struct DownPistonsInput {
public:
	bool shouldExtend;
};
struct DownPistonsOutput {
	bool Piston1;
};

class DownPistons {

	Solenoid* sol1;

public:
	DownPistons::DownPistons() {
		sol1 = new Solenoid(5);
	}

	DownPistonsOutput DownPistons::Run(DownPistonsInput input) {
		sol1 -> Set(input.shouldExtend);
		DownPistonsOutput output;
		output.Piston1 = sol1->Get();
		return output;
	}

};
