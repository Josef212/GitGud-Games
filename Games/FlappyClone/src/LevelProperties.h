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
	int ObstaclesCount = 8;
	float Speed = -4.0f;
	MinMax ObstaclesSeparation = { 6.0f, 8.0f };

	float ObstacleWidth = 1.5f;
	MinMax GapHeightPercentage = { 0.15f, 0.2f };
};

bool DragMinMax(const char* label, MinMax& value, float speed = 1.0f, float minValue = 0.0f, float maxValue = 0.0f, const char* format = "%.3f", float power = 1.0f);
void LevelPropertiesEditor(LevelProperties& properties);