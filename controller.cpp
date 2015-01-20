/*
 * Copyright 2014 FRC Team 4139
 * Author(s): Joshua Taylor
 */

#include <WPILib.h>
#include <math.h>

struct ControllerInput {

};

struct ControllerOutput {

	//Left Stick

	float MoveX;
	float MoveY;
	float Spin;

	//Buttons

	bool Shooter_fire;
	bool Left180;
	bool Right180;
	bool ZapGyro;
	bool Pump;
	bool Grab;
	bool Turbo;

};
class X360Controller {

private:

	Joystick* UDLR;
	ControllerOutput Output;
	bool FullMotor;
	bool RevMotor;
	bool StaleMotor;
	float WasMovingX,
		  WasMovingY;
	bool keepUp, keepUpWasPressed;

public:
	static const float DZ = .15;

	X360Controller::X360Controller() {
		UDLR = new Joystick(1);
		FullMotor = false;
		StaleMotor = false;
		RevMotor = true;
		WasMovingX = 0.0f;
		WasMovingY = 0.0f;
		keepUp = false;
		keepUpWasPressed = false;
	}

	ControllerOutput X360Controller::Run(ControllerInput in) {
		//buttons
		if (UDLR->GetRawButton(2) && !keepUpWasPressed)
		{
			keepUp = !keepUp;
		}
		keepUpWasPressed = UDLR->GetRawButton(2);
		Output.Grab = UDLR->GetRawButton(3);//activate grab ball protocol
		Output.Shooter_fire = keepUp || UDLR->GetRawButton(1);//Make the shooter fire
		Output.Pump = UDLR->GetRawButton(8);//re-compress the airtank
		Output.ZapGyro = UDLR->GetRawButton(7);//reset gyro
		Output.Left180 = UDLR->GetRawButton(5);//spin rapidly 180 degrees
		Output.Right180 = UDLR->GetRawButton(6);//same as above
		Output.Turbo = (bool)UDLR->GetRawButton(9);

		//axis stuff
		//like the triggers and stick

		Output.Spin = UDLR->GetZ() / (Output.Grab ? 2 : 1);//ApplyDZ(UDLR->GetZ()/2, DZ);
		Output.MoveX
				= ApplyDZ(UDLR->GetRawAxis(1) / (Output.Turbo ? 1 : 2), DZ)
						/ (Output.Grab ? 2 : 1);
		Output.MoveY = -ApplyDZ(UDLR->GetRawAxis(2) / (Output.Turbo ? 1 : 2),
				DZ) / (Output.Grab ? 2 : 1);
		if(RevMotor)
			RevMotor = false;
		if (Output.MoveX || Output.MoveY) {
			WasMovingX = Output.MoveX;
			WasMovingY = Output.MoveY;
			if (FullMotor) {
				FullMotor = false;
				StaleMotor = true;
			} else if (!StaleMotor)
				FullMotor = true;
		} else
		{
			if(StaleMotor)
			{
				RevMotor = true;
				StaleMotor = false;
			}
		}
		
		if (FullMotor && !StaleMotor) {
			if (Output.MoveX < 0)
				Output.MoveX = -100;
			if (Output.MoveX > 0)
				Output.MoveX = 100;

			if (Output.MoveY < 0)
				Output.MoveY = -100;
			if (Output.MoveY > 0)
				Output.MoveY = 100;
		}
		cout<<RevMotor;
		if (RevMotor)
		{
			if (WasMovingX < 0)
				Output.MoveX = 100;
			if (Output.MoveX > 0)
				Output.MoveX = -100;

			if (WasMovingY < 0)
				Output.MoveY = 100;
			if (Output.MoveY > 0)
				Output.MoveY = -100;
		}
		if (Output.Left180)
			Output.Spin = .5;
		else if (Output.Right180)
			Output.Spin = -.5;

		return Output;

	}

	float sign(float num) {
		if (num > 0)
			return 1;
		else if (num < 0)
			return -1;
		else
			return 0;
	}

	//Apply deadzone

	float ApplyDZ(float axis, float deadzone) {
		return fabs(axis) < deadzone ? 0 : (fabs(axis) - deadzone) / (1
				- deadzone) * sign(axis);
	}

};
