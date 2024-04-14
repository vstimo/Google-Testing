#pragma once
#include "pch.h"
#include <gtest/gtest.h>

class TestFixture : public ::testing::Test
{
	Manager_Wipers managerWipers;
	WipersSpeed wipersSpeed;

public:
	TestFixture();
	void SetUp();

	// Setters
	void SetSwitchInManager(SwitchState switchState);
	void SetSensorValue(int);

	// Getters
	WipersSpeed GetWippersSpeed() const;
	Manager_Wipers GetMW() const;
	int GetSensorValue() const;

	// Helpers
	void CalculateWipersSpeed();
};