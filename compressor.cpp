/**********************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Shea Polansky
 */
#include <WPILib.h>
struct CompressorInputs {
	bool enable;
};

class CompressorController {
	//Relay* compressor;
	Compressor* compressor;
	DriverStationLCD* lcd;
public:
	CompressorController::CompressorController() {
		//compressor = new Relay(8, Relay::kForwardOnly);
		//compressor = new Relay(7);
		lcd = DriverStationLCD::GetInstance();
		compressor = new Compressor(4, 8);
		compressor -> Start();
	}

	void Run(CompressorInputs input) {
		//cout << input.enable;
		//compressor->Set(Relay::kOn);
		//compressor->Set(input.enable ? Relay::kOn : Relay::kOff);
		//cout << compressor->GetPressureSwitchValue();
		lcd->PrintfLine(DriverStationLCD::kUser_Line5, "Pressure Switch: %x", 
				compressor->GetPressureSwitchValue());
	}
};
