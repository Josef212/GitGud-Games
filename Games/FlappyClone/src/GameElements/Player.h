#pragma once

#include "GameElement.h"
#include "../LevelProperties.h"
#include "Collisions.h"

#include <glm/glm.hpp>

class Player : public GameElement
{
public:
	Player(LevelProperties* levelProperties);
	~Player();

	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void ImGuiRender();

private:
	void Jump();
	void OnPlayerCollision(GitGud::Extensions::Collider2D* other);

private:
	LevelProperties* _levelProperties = nullptr;
	float _yPos, _jumpForce, _velocity;
	glm::vec4 _color;
	GitGud::Extensions::QuadCollider2D* _collider;

	const char* _lastCollision = "";
	bool _colliding = false;
};

