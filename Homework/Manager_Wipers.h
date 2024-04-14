#pragma once
#include "Switch.h"
#include "Sensor.h"

class Manager_Wipers {

	Switch switchS;
	Sensor sensor;

public:
	SwitchState getSwitchS() const { 
		return switchS.GetState();
	}

	void setSwitchS(const SwitchState newState) {
		switchS.SetState(newState);
	}

	void setSensor(const int value) {
		sensor.SetValue(value);
	}

	int getSensor() const {
		return sensor.GetValue();
	}

	WipersSpeed CalculateWipersSpeed() {
		auto wipersSpeed = WipersSpeed::OffSpeed;
		switch (switchS.GetState()) {

		case SwitchState::Low: {
			wipersSpeed = WipersSpeed::LowSpeed;
			break;
		}

		case SwitchState::High: {
			wipersSpeed = WipersSpeed::HighSpeed;
			break;
		}

		case  SwitchState::Automatic: {
			if (sensor.GetValue() >= RainStatus::NoRainLimit && sensor.GetValue() < RainStatus::LowRainLimit)
				wipersSpeed = WipersSpeed::OffSpeed; // No Rain
			else if (sensor.GetValue() >= RainStatus::LowRainLimit && sensor.GetValue() < RainStatus::HighRainLimit)
				wipersSpeed = WipersSpeed::LowSpeed; // Low Speed Rain
			else if (sensor.GetValue() >= RainStatus::HighRainLimit && sensor.GetValue() <= RainStatus::MaxRainLimit){
				wipersSpeed = WipersSpeed::HighSpeed; // High Speed Rain
			}
			break;
		}

		case SwitchState::Off:
		default:
		{
			wipersSpeed = WipersSpeed::OffSpeed;
		}
		}
		return wipersSpeed;
	}
};