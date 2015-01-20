/************************************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi *
 * File Authors: Zack Mudd, Elliot Yoon         *
 ************************************************/

#include <WPILIB.h>
#include <math.h>

struct WheelOutput {

};

struct WheelInput {
	float rotation; // Rotating
	float xmovement; // Forward/Backward
	float ymovement; // Left/Right
	bool spinleft; // 180 degree left turn
	bool spinright; // 180 degree right turn
	float angle; // Robot's current rotation
};
class Wheels {
private:
	RobotDrive* drive;
	int state; // State 1: Normal      State 2: Left      State 3: Right
	float targetangle;
public:

	Wheels() {
		drive = new RobotDrive(1, 3, 2, 4);
		state = 1;
		drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true); // 2 is front left wheel
		drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true); // 4 is back left wheel
	}
	WheelOutput Wheels::Run(WheelInput input) {
		float xmove = 0;
		float ymove = 0;
		float rotate = 0;
		if (input.spinleft && !input.spinright) {
			state = 2;
		} else if (input.spinright && !input.spinleft) {
			state = 3;
		} else if (input.spinleft && input.spinright) {
			state = 1;
		}

		if (state == 1) {
			//cout << input.ymovement << " " << input.rotation << endl;
			if (fabs(input.ymovement) > .05 || fabs(input.xmovement) > 0.05) //backward
				input.rotation -= .025;
			if (input.rotation > 1)
				input.rotation = 1;
			else if (input.rotation < -1)
				input.rotation = -1;
			xmove = input.xmovement;
			ymove = input.ymovement;
			rotate = input.rotation;
			//drive->MecanumDrive_Cartesian(input.xmovement, input.ymovement,
			//input.rotation / 2, input.angle);
		} else if (state == 2) {
			if (fabs(input.angle - targetangle) > 5) {
				xmove = input.xmovement;
				ymove = input.ymovement;
				rotate = -1;
				//drive->MecanumDrive_Cartesian(input.xmovement, input.ymovement,
				//-1.0, input.angle);
			} else {
				state = 1;
			}
		} else if (state == 3) {
			if (fabs(input.angle - targetangle) > 5) {
				xmove = input.xmovement;
				ymove = input.ymovement;
				rotate = -1;
				//drive->MecanumDrive_Cartesian(input.xmovement, input.ymovement,
				//1.0, input.angle);
			} else {
				state = 1;
			}
		}
		drive->MecanumDrive_Cartesian(xmove, ymove, rotate, input.angle);
		return WheelOutput();
	}

};
