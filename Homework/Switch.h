#pragma once
#include "Data_Type.h"

class Switch
{
public:
	SwitchState GetState() const { return state; }
	void SetState(const SwitchState sw_state) { state = sw_state; }

protected:
	SwitchState state;
};