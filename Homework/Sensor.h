#pragma once

class Sensor {
public:
	void SetValue(const int newValue) { value = newValue;  }
	int GetValue() const { return value; }

protected:
	int value = 0.0f;
};