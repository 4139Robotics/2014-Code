#ifndef UP_PISTONS_H
#define UP_PISTONS_H

#include "WPILib.h"
struct UpPistonsInput {
public:
	bool ShouldExtend;
};
struct UpPistonsOutput {

};

class UpPistons {
public:
	UpPistons();
	void Run(UpPistonsInput input);
};

#endif
