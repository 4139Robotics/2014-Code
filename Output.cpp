/***********************************
 * Copyright (c) 2014 FRC Team 4139: Easy as Pi
 * Authors: Elliot Yoon
 */

#include "WPILib.h"
#include "pistons.cpp"
#include "wheels.cpp"
#include "compressor.cpp"

struct OutputOut {
};

struct OutputIn {
	bool returnshouldExtend1, returnshouldExtend2;
	float returnrotation, returnxmovement, returnymovement, returnangle;
	bool returnspinleft, returnspinright, enableCompressor;
};

class Output {
	Pistons* pistons;
	Wheels* wheels;
	CompressorController* compressor;

public:

	Output::Output() {
		pistons = new Pistons();
		wheels = new Wheels();
		compressor = new CompressorController();
	}
	OutputOut Output::Run(OutputIn in) {
		OutputOut out;

		PistonInputs pin;

		pin.shouldExtend1 = in.returnshouldExtend1;
		pin.shouldExtend2 = in.returnshouldExtend2;

		WheelInput win;

		win.rotation = in.returnrotation;
		win.xmovement = in.returnxmovement;
		win.ymovement = in.returnymovement;
		win.angle = in.returnangle;
		win.spinleft = in.returnspinleft;
		win.spinright = in.returnspinright;

		CompressorInputs compin;
		compin.enable = in.enableCompressor;

		pistons->Run(pin);
		wheels->Run(win);
		compressor->Run(compin);
		return out;
	}
};
