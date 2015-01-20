/**************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Brooke Polansky, Julia Baylon
 */

#include "WPILib.h"
#include "up_pistons.cpp"
#include "down_pistons.cpp"

struct PistonInputs {
	bool shouldExtend1;
	bool shouldExtend2;
};
struct PistonOutputs {
public:
	bool OutDownPistons;
	bool OutUpPistons;
};

class Pistons {
	DownPistons* DPistons;
	UpPiston* UPistons;
public:
	Pistons::Pistons() {
		DPistons = new DownPistons();
		UPistons = new UpPiston();
	}
	void Pistons::Run(PistonInputs input) {
		if (input.shouldExtend1 && input.shouldExtend2)
			input.shouldExtend1 = false;

		DownPistonsInput dinput;
		dinput.shouldExtend = input.shouldExtend1;

		UpPistonInput uinput;
		uinput.shouldExtend = input.shouldExtend2;

		DPistons->Run(dinput);
		UPistons->Run(uinput);

	}

};

