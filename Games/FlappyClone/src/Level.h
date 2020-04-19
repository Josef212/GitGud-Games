#pragma once

#include "GameElements/Block.h"

class Level
{
public:
	Level();
	~Level();

	void Update(float dt);
	void Render();

private:
	std::vector<Block*> _blocks;
	Block* _topLimit, * _bottomLimit;

	float _levelSpeed;
};
