#pragma once

#include <random>

class Random
{
public:
	static void Init()
	{

	}

	static float Float()
	{
		static std::default_random_engine e;
		static std::uniform_real_distribution<> dis; // rage 0 - 1

		return dis(e);
		//return (float)s_distribution(s_random) / (float)std::numeric_limits<uint32_t>::max();
	}

	static float Float(float min, float max)
	{
		float random = Float();
		float diff = max - min;
		float r = random * diff;
		return min + r;
	}
};
