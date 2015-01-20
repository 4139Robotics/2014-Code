/**********************************
 * Copyright (C) 2014 FRC Team 4139: Easy As Pi
 * File authors: Shea Polansky
 */

#include "WPILib.h"
#include <math.h>
#include "config.h"
#include "input.cpp"
#include "Output.cpp"

class ProjectFujin: public IterativeRobot {
	Output* outputs;
	Input* inputs;
	int autonomousStage, autonomousDelayCount;
	Timer* timer;
	bool timerEnabled;
public:
	ProjectFujin() {
		cout << "Robot Loaded";
		outputs = new Output();
		inputs = new Input();
		timer = new Timer();
		autonomousStage = 0;
		autonomousDelayCount = 0;
	}

	void ProjectFujin::RobotInit() {
		GetWatchdog().SetEnabled(true);
	}
	void ProjectFujin::TeleopPeriodic() {
		InputOutput out = inputs->Run();
		DriverStationLCD* lcd = DriverStationLCD::GetInstance();
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Gyro: %f",
				out.returnRotation);
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Sonar: %f",
				out.returnDistance);
		lcd->UpdateLCD();
		OutputIn in;
		in.returnangle = 0;
		in.returnrotation = out.controllerOutput.Spin;
		in.returnxmovement = out.controllerOutput.MoveX;
		in.returnymovement = out.controllerOutput.MoveY;
		in.returnspinleft = false;
		in.returnspinright = false;
		in.returnshouldExtend2 = out.controllerOutput.Shooter_fire;
		in.returnshouldExtend1 = out.controllerOutput.Grab;
		in.enableCompressor = out.controllerOutput.Pump;
		outputs->Run(in);
		GetWatchdog().Feed();
	}
	void ProjectFujin::AutonomousInit() {
		autonomousStage = 0;
		autonomousDelayCount = 0;
		timer->Stop();
		timerEnabled = false;
	}
	void ProjectFujin::AutonomousPeriodic() {
#ifdef AUTONOMOUS_ENABLED
		InputOutput out = inputs->Run();
		OutputIn in;
		in.enableCompressor = false;
		in.returnangle = out.returnRotation;
		in.returnrotation = 0;
		in.returnshouldExtend1 = false;
		in.returnshouldExtend2 = true;
		in.returnspinleft = false;
		in.returnspinright = false;
		in.returnxmovement = 0;
		in.returnymovement = 0;
		switch (autonomousStage) {
		case 0: //Move forward
			if (!timerEnabled)
				timer->Start();
			timerEnabled = true;
			in.returnshouldExtend2 = true;
			in.returnymovement = -.3;
			if (timer->HasPeriodPassed(2) || out.returnDistance <= 110) {
				autonomousDelayCount++;
			} else
				autonomousDelayCount = 0;
			if (autonomousDelayCount >= 5) {
				timer -> Reset();
				autonomousStage++;
			}
			break;
		case 1: //jerk backward to compensate for crap wheels
			in.returnymovement = 1;
			if (timer->HasPeriodPassed(.2)) {
				autonomousStage++;
				timer->Reset();
			}
			break; 
		case 2: //drop ball to shooting position
			in.returnshouldExtend1 = true;
			in.returnshouldExtend2 = false;
			if (timer->HasPeriodPassed(2.0)) {
				autonomousStage++;
				timer->Reset();
			}
			break;
		case 3: //Drop loader piston just before fire
			in.returnshouldExtend1 = false;
			if (timer->HasPeriodPassed(0.5))
			{
				autonomousStage++;
				timer->Reset();
			}
		case 4: //fire
			in.returnshouldExtend2 = true;
			if (timer->HasPeriodPassed(1.5)) {
				autonomousStage++;
				timer->Reset();
			}
			break;
		case 5: //do nothing
			break;
		}
		outputs->Run(in);
#endif
		DriverStationLCD* lcd = DriverStationLCD::GetInstance();
		lcd->PrintfLine(DriverStationLCD::kUser_Line1, "Gyro: %f",
				out.returnRotation);
		lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Sonar: %f",
				out.returnDistance);
		lcd->PrintfLine(DriverStationLCD::kUser_Line3, "Autonomous Stage: %d",
				autonomousStage);
		lcd->PrintfLine(DriverStationLCD::kUser_Line4, "Time: %f", timer->Get());
		lcd->UpdateLCD();
		GetWatchdog().Feed();
	}

	void ProjectFujin::AutonomousDisabled() {
		autonomousStage = 0;
		autonomousDelayCount = 0;
		timer->Stop();
		timer->Reset();
		timerEnabled = false;
	}
};

START_ROBOT_CLASS(ProjectFujin)
;

