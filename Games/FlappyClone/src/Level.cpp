#include <ggpch.h>

#include "FlappyCloneApp.h"
#include "Level.h"
#include "Random.h"

#include "Collisions.h"

#include <imgui/imgui.h>

using namespace GitGud;

Level::Level() : _limits(nullptr), _player(CreateScope<Player>(&_levelProperties))
{
	_limits = new Obstacle(0.0f, 0.0f, 50.0f, 0.8f, { 0.25f, 0.25f, 0.25f, 1.0f });
	_limits->GetTopCollider()->_debugName = "TopLimits";
	_limits->GetBotCollider()->_debugName = "BotLimits";

	_obstacles.reserve(_levelProperties.ObstaclesCount); // TODO: Cehck resize vs reserve about memory allocation

	auto& camera = static_cast<FlappyCloneApp&>(GitGud::Application::Get()).GetCamera();
	float lastX = camera.GetRight();
	for (uint32_t i = 0; i < _levelProperties.ObstaclesCount; ++i)
	{
		_obstacles.emplace_back(CreateScope<Obstacle>());
		GenerateObstacle(*_obstacles[i], lastX);

		_obstacles[i]->GetTopCollider()->_debugName = std::to_string(i) + " : TopObstacle";
		_obstacles[i]->GetBotCollider()->_debugName = std::to_string(i) + " : BotObstacle";

		lastX = _obstacles[i]->GetX();
	}
}

Level::~Level()
{
}

void Level::Update(float dt)
{
	for (Scope<Obstacle>& o : _obstacles)
	{
		auto posX = o->GetX();
		posX += _levelProperties.HorizontalSpeed * dt;
		o->SetX(posX);
	}

	_player->Update(dt);

	auto& camera = static_cast<FlappyCloneApp&>(GitGud::Application::Get()).GetCamera();
	Scope<Obstacle>& currentObstacle = _obstacles[_currentObstacleIndex];
	if (currentObstacle->GetX() + (currentObstacle->GetObstacleWidth() * 0.51f) < camera.GetLeft())
	{
		uint32_t prevObstacleIndex = (_currentObstacleIndex - 1) % _obstacles.size();
		Scope<Obstacle>& prevObstacle = _obstacles[prevObstacleIndex];
		GenerateObstacle(*currentObstacle, prevObstacle->GetX());
		
		_currentObstacleIndex = ++_currentObstacleIndex % _obstacles.size();
	}
}

void Level::Render()
{
	for (Scope<Obstacle>& b : _obstacles)
	{
		b->Render();
	}

	_limits->Render();
	_player->Render();

	if (GitGud::Extensions::CollisionModule::Get()->_drawDebug)
	{
		GitGud::Extensions::CollisionModule::Get()->DrawDebug();
	}
}

void Level::OnImGuiRender()
{
	ImGui::Begin("Level");

	ImGui::Checkbox("Debug collisions", &GitGud::Extensions::CollisionModule::Get()->_drawDebug);
	
	//ImGui::Text("Obstacles");
	//for (uint32_t i = 0; i < _obstacles.size(); ++i)
	//{
	//	ImGui::PushID(i);
	//
	//	Obstacle* o = _obstacles[i];
	//	ImGui::Text("Obstacle %i: %f", i, o->GetX());
	//
	//	ImGui::PopID();
	//}

	_player->ImGuiRender();

	ImGui::Separator();

	LevelPropertiesEditor(_levelProperties);

	ImGui::End();
}

void Level::GenerateObstacle(Obstacle& obstacle, float prevX)
{
	float x = prevX + _levelProperties.ObstaclesSeparation.Value();
	float gapY = _levelProperties.GapeHeightY.Value();
	float gapHeightPercentage = _levelProperties.GapHeightPercentage.Value();
	glm::vec4 color = { 0.4f, 0.4f, 0.4f, 1.0f };

	obstacle.SetX(x);
	obstacle.SetGapY(gapY);
	obstacle.SetObstacleWidth(_levelProperties.ObstacleWidth);
	obstacle.SetGapHeightPerdentage(gapHeightPercentage);
	obstacle.SetColor(color);
}
