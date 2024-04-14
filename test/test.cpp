#include "pch.h"
#include <gtest/gtest.h>
#include <tuple>

// Unit Test Switch / 13.04.2024 / Future Up      --IN PLUS
class SwitchTestFixture : public testing::TestWithParam<std::tuple<SwitchState, SwitchState>> {};

INSTANTIATE_TEST_CASE_P(
	GivenValue_ExpectedSameValue_Inst,
	SwitchTestFixture,
	::testing::Values(std::make_tuple(SwitchState::Off, SwitchState::Off),
		std::make_tuple(SwitchState::Low, SwitchState::Low),
		std::make_tuple(SwitchState::High, SwitchState::High),
		std::make_tuple(SwitchState::Automatic, SwitchState::Automatic)));

TEST_P(SwitchTestFixture, GivenValue_ExpectedSameValue_Params) {
	EXPECT_EQ(std::get<0>(GetParam()), std::get<1>(GetParam()));
}

// Unit Test Wipers / 13.04.2024 / Future Up
class WipersTestFixture : public testing::TestWithParam<std::tuple<WipersSpeed, WipersSpeed>> {};

INSTANTIATE_TEST_CASE_P(
	GivenValue_ExpectedSameValue_Inst,
	WipersTestFixture,
	::testing::Values(std::make_tuple(WipersSpeed::OffSpeed, WipersSpeed::OffSpeed),
		std::make_tuple(WipersSpeed::LowSpeed, WipersSpeed::LowSpeed),
		std::make_tuple(WipersSpeed::HighSpeed, WipersSpeed::HighSpeed)));

TEST_P(WipersTestFixture, GivenValue_ExpectedSameValue_Params) {
	EXPECT_EQ(std::get<0>(GetParam()), std::get<1>(GetParam()));
}

// - - - - SPECIFIC REQUIREMENTS - - - - - 

// Unit Test Sensor / 13.04.2024 / Future Up
struct RainSensorTestParams {
    int rainIntensity;
};

class RainSensorTestFixture : public testing::TestWithParam<RainSensorTestParams> {};

INSTANTIATE_TEST_CASE_P(
    RandomRainIntensities,
    RainSensorTestFixture,
    ::testing::Values(
        RainSensorTestParams{ -2 },
        RainSensorTestParams{ 0 },
        RainSensorTestParams{ 1 },
        RainSensorTestParams{ 3 },
        RainSensorTestParams{ 4 },
        RainSensorTestParams{ 6 },
        RainSensorTestParams{ 10 },
        RainSensorTestParams{ 14 }
    )
);

TEST_P(RainSensorTestFixture, RainIntensityInRange) {
    const int minNoRain = 0;
    const int minLowRain = 2;
    const int minHighRain = 5;
    const int maxHighRain = 12;
    Sensor s;

    const RainSensorTestParams& params = GetParam();
    s.SetValue(params.rainIntensity);

    // Check if the rain intensity is within the correct range
    if (params.rainIntensity < minLowRain && params.rainIntensity >= minNoRain)
        EXPECT_TRUE(s.GetValue() < minLowRain && s.GetValue() >= minNoRain); //No rain
    else if (params.rainIntensity >= minLowRain && params.rainIntensity < minHighRain)
        EXPECT_TRUE(s.GetValue() >= minLowRain && s.GetValue() < minHighRain); //Low Rain
    else if (params.rainIntensity >= minHighRain && params.rainIntensity <= maxHighRain)
        EXPECT_TRUE(s.GetValue() >= minHighRain && s.GetValue() <= maxHighRain); //High Rain
    else
        EXPECT_FALSE(false); //out of bound rain amount
}

//INTEGRATION TESTS

class AutomaticWipersControlTest : public TestFixture, public testing::WithParamInterface<std::tuple<int, WipersSpeed>> {};

INSTANTIATE_TEST_CASE_P(RainIntensityToWipersSpeed, AutomaticWipersControlTest,
    ::testing::Values(
        std::make_tuple(-2, WipersSpeed::OffSpeed), // No rain
        std::make_tuple(0, WipersSpeed::OffSpeed), // No rain
        std::make_tuple(2, WipersSpeed::LowSpeed), // Low rain
        std::make_tuple(4, WipersSpeed::LowSpeed), // Low rain
        std::make_tuple(5, WipersSpeed::HighSpeed), // High rain
        std::make_tuple(10, WipersSpeed::HighSpeed), // High rain
        std::make_tuple(14, WipersSpeed::HighSpeed) // High rain
    )
);

TEST_P(AutomaticWipersControlTest, WipersSpeedMatchesRainIntensity) {

    int rainIntensity = std::get<0>(GetParam());
    if (rainIntensity >= RainStatus::NoRainLimit && rainIntensity <= RainStatus::MaxRainLimit) {
        WipersSpeed expectedSpeed = std::get<1>(GetParam());

        SetSensorValue(rainIntensity);
        CalculateWipersSpeed();

        Manager_Actuators managerActuators(GetMW());
        managerActuators.SetWipers();

        // Check if the wipers speed matches the expected speed
        EXPECT_EQ(managerActuators.GetWipers().GetSpeed(), expectedSpeed);
    }
    else {
        EXPECT_FALSE(false);
    }
}
