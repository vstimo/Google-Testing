#pragma once
#include "Data_Type.h"

class Wipers
{
public:
	WipersSpeed GetSpeed() const { return speed; }
	void SetSpeed(const WipersSpeed wipping_speed) { speed = wipping_speed;  }

protected:
	WipersSpeed speed;
};