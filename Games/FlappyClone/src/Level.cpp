#include <ggpch.h>

#include "Level.h"
#include "Random.h"

#define BLOCKS_COUNT 5
#define MIN_SEPARATION 4
#define MAX_SEPARATION 8

Level::Level() : _topLimit(nullptr), _bottomLimit(nullptr), _levelSpeed(5.0f)
{
	_topLimit = new Block({ 0.0f, 8.0f }, { 30.0f, 3.0f }, { 0.0f, -1.0f }, { 0.25f, 0.25f, 0.25f, 1.0f });
	_bottomLimit = new Block({ 0.0f, -8.0f }, { 30.0f, 3.0f }, { 0.0f, 1.0f }, { 0.25f, 0.25f, 0.25f, 1.0f });

	float lastX = 0.0f;
	for (uint32_t i = 0; i < BLOCKS_COUNT; ++i)
	{
		float separation = Random::Float(MIN_SEPARATION, MAX_SEPARATION);
		float x = lastX + separation;

		GG_TRACE("{0}, {1}", separation, x);

		glm::vec2 pos = { x, 0.0f };
		glm::vec2 size = { 1.0f, 1.0f };
		glm::vec2 normal = { 0.0f, 0.0f };
		glm::vec4 color = { 0.4f, 0.4f, 0.4f, 1.0f };

		_blocks.push_back(new Block(pos, size, normal, color));

		lastX = x;
	}
}

Level::~Level()
{
}

void Level::Update(float dt)
{
	for (Block* b : _blocks)
	{
		auto pos = b->GetPosition();
		pos.x -= _levelSpeed * dt;
		b->SetPosition(pos);
	}
}

void Level::Render()
{
	for (Block* b : _blocks)
	{
		b->Render();
	}

	_topLimit->Render();
	_bottomLimit->Render();
}
