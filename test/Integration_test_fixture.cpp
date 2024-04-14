#include "Integration_test_fixture.h"
#include "pch.h"

TestFixture::TestFixture() {
	managerWipers = Manager_Wipers();
}

void TestFixture::SetUp() {
	managerWipers.setSwitchS(SwitchState::Automatic);
}

void TestFixture::SetSwitchInManager(SwitchState ss) {
	managerWipers.setSwitchS(ss);
}

void TestFixture::SetSensorValue(int value) {
	managerWipers.setSensor(value);
}

Manager_Wipers TestFixture::GetMW() const{
	return managerWipers;
}

WipersSpeed TestFixture::GetWippersSpeed() const{
	return wipersSpeed;
}

int TestFixture::GetSensorValue() const {
	return managerWipers.getSensor();
}

void TestFixture::CalculateWipersSpeed() {
	wipersSpeed = managerWipers.CalculateWipersSpeed();
}