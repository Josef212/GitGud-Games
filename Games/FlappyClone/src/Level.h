#pragma once

#include "GameElements/Obstacle.h"
#include "LevelProperties.h"

class Level
{
public:
	Level();
	~Level();

	void Update(float dt);
	void Render();
	void OnImGuiRender();

private:
	void GenerateObstacle(Obstacle& obstacle, float prevX);

private:
	std::vector<Obstacle*> _obstacles;
	Obstacle* _limits;

	uint32_t _currentObstacleIndex = 0;
	LevelProperties _levelProperties;
};

