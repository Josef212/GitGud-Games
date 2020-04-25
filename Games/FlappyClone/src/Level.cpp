#include <ggpch.h>

#include "FlappyCloneApp.h"
#include "Level.h"
#include "Random.h"

#include <imgui/imgui.h>

Level::Level() : _limits(nullptr)
{
	_limits = new Obstacle(0.0f, 0.0f, 50.0f, 0.8f, { 0.25f, 0.25f, 0.25f, 1.0f });

	_obstacles.reserve(_levelProperties.ObstaclesCount); // TODO: Cehck resize vs reserve about memory allocation

	auto& camera = static_cast<FlappyCloneApp&>(GitGud::Application::Get()).GetCamera();
	float lastX = camera.GetRight();
	for (uint32_t i = 0; i < _levelProperties.ObstaclesCount; ++i)
	{
		float separation = _levelProperties.ObstaclesSeparation.Value();
		float x = lastX + separation;
		glm::vec4 color = { 0.4f, 0.4f, 0.4f, 1.0f };

		_obstacles.emplace_back(new Obstacle(x, 0.0f, _levelProperties.ObstacleWidth, 0.15f, color));

		lastX = x;
	}
}

Level::~Level()
{
}

void Level::Update(float dt)
{
	for (Obstacle* o : _obstacles)
	{
		auto posX = o->GetX();
		posX += _levelProperties.Speed * dt;
		o->SetX(posX);
	}

	auto& camera = static_cast<FlappyCloneApp&>(GitGud::Application::Get()).GetCamera();
	Obstacle* currentObstacle = _obstacles[_currentObstacleIndex];
	if (currentObstacle->GetX() + (currentObstacle->GetObstacleWidth() * 0.51f) < camera.GetLeft())
	{
		uint32_t prevObstacleIndex = (_currentObstacleIndex - 1) % _obstacles.size();
		Obstacle* prevObstacle = _obstacles[prevObstacleIndex];
		currentObstacle->SetX(prevObstacle->GetX() + _levelProperties.ObstaclesSeparation.Value());
		_currentObstacleIndex = ++_currentObstacleIndex % _obstacles.size();
	}
}

void Level::Render()
{
	for (Obstacle* b : _obstacles)
	{
		b->Render();
	}

	_limits->Render();
}

void Level::OnImGuiRender()
{
	ImGui::Begin("Level");
	
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

	ImGui::Text("Level properties");
	LevelPropertiesEditor(_levelProperties);

	ImGui::End();
}
