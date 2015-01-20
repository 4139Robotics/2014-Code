/***********************************
 * Copyright (c) 2014 FRC Team 4139: Easy as Pi
 * Authors: Christie Wang, and Elliot Yoon
 */

#include "WPILib.h"
#include <Solenoid.h>

struct UpPistonInput {
	bool shouldExtend;
};

struct UpPistonOutput {
	bool UpPistonStatus1;
	bool UpPistonStatus2;
};
class UpPiston {
public:
	Solenoid *UpPiston1, *UpPiston2;
	UpPiston::UpPiston() {
		UpPiston1 = new Solenoid(1);
		UpPiston2 = new Solenoid(3);
	}

	UpPistonOutput UpPiston::Run(UpPistonInput input) {
		UpPiston1->Set(!input.shouldExtend);
		UpPiston2->Set(input.shouldExtend);
		UpPistonOutput output = UpPistonOutput();
		output.UpPistonStatus1 = UpPiston1->Get();
		output.UpPistonStatus2 = UpPiston2->Get();
		return output;
	}

};
