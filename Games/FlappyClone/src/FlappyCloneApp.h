#pragma once

#define TEST 0

#include <GitGud.h>
#include "Collisions.h"
#include "GameLayer.h"

class FlappyCloneApp : public GitGud::Application
{
public:
	FlappyCloneApp();
	~FlappyCloneApp();

	const GitGud::OrthographicCamera& GetCamera() { return _gameLayer->GetCamera(); }

private:
	GitGud::Extensions::CollisionModule* _collisionModule = nullptr;
	GameLayer* _gameLayer = nullptr;
};