#include "Player.h"

#include <GitGud.h>
#include <iostream>
#include <imgui/imgui.h>

using namespace GitGud;
using namespace GitGud::Extensions;

Player::Player(LevelProperties* levelProperties) : _levelProperties(levelProperties), _yPos(0.0f), _jumpForce(0.5f), _velocity(0.0f),
_color({ 0.2f, 0.8f, 0.4f, 1.0f }),
_collider(new QuadCollider2D({0.0f, _yPos}, { 1.0f, 1.0f }, GG_BIND_EVENT_FN(Player::OnPlayerCollision)))
{
	_collider->_debugName = "Player";
	CollisionModule::Get()->AddCollider(_collider);
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	_colliding = false;

	if (Input::IsKey(GG_KEY_SPACE))
	{
		_velocity += _jumpForce;
		if(_velocity < 0.0f)
			_velocity += _jumpForce * 2.0f;
	}
	else
	{
		_velocity += _levelProperties->Gravity;
	}

	_velocity = std::clamp(_velocity, -20.0f, 20.0f);

	_yPos += _velocity * dt;
	
	auto pos = _collider->GetPositon();
	_collider->SetPosition(pos.x, _yPos);
}

void Player::Render()
{
	Renderer2D::DrawQuad({ 0.0f, _yPos, 0.1f }, { 1.0f, 1.0f }, _color);
}

void Player::ImGuiRender()
{
	ImGui::Begin("Player");

	ImGui::DragFloat("Y pos", &_yPos, 0.1f);
	ImGui::DragFloat("Jump force", &_jumpForce, 0.1f);
	ImGui::Text("Y pos: %f", _yPos);
	ImGui::Text("Y velocity: %f", _velocity);

	ImGui::Text("Last collided with: %s", _lastCollision);
	ImGui::TextColored((_colliding ? ImVec4(1, 0, 0, 1) : ImVec4(0, 1, 0, 1)), "Colliding: %s", _colliding ? "true" : "false");

	ImGui::End();
}

void Player::Jump()
{
}

void Player::OnPlayerCollision(GitGud::Extensions::Collider2D* other)
{
	_lastCollision = other->_debugName.c_str();
	_colliding = true;
}
