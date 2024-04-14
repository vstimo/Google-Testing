#pragma once

typedef enum SwitchState
{
	Off, //0
	Low, 
	High,
	Automatic
};

typedef enum WipersSpeed
{
	OffSpeed, //0
	LowSpeed,
	HighSpeed
};

typedef enum RainStatus {
	NoRainLimit = 0,
	LowRainLimit = 2,
	HighRainLimit = 5,
	MaxRainLimit = 12
};