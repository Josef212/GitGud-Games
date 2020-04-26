#pragma once

#include "Random.h"

struct MinMax
{
	float Min, Max;

	MinMax(float min, float max) : Min(min), Max(max) {}

	inline float Value() const { return Random::Float(Min, Max); }
};

struct LevelProperties
{
	float Gravity = -0.4f;
	float HorizontalSpeed = -5.0f;

	int ObstaclesCount = 8;
	MinMax ObstaclesSeparation = { 6.0f, 8.0f };

	float ObstacleWidth = 1.5f;
	MinMax GapeHeightY = { -4.5f, 4.5f };
	MinMax GapHeightPercentage = { 0.2f, 0.25f };
};

bool DragMinMax(const char* label, MinMax& value, float speed = 1.0f, float minValue = 0.0f, float maxValue = 0.0f, const char* format = "%.3f", float power = 1.0f);
void LevelPropertiesEditor(LevelProperties& properties);