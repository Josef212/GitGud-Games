#include "Block.h"

#include <GitGud.h>
#include "../Random.h"

using namespace GitGud::Extensions;

Block::Block() : _position({ 0.0f, 0.0f }), _size({ 1.0f, 1.0f }), _normal({ 0.0f, 0.0f }), _color({ 1.0f, 0.1f, 0.5f, 1.0f }), _collider(new QuadCollider2D(_position, _size))
{
	CollisionModule::Get().AddCollider(_collider);
}

Block::Block(const glm::vec2& position, const glm::vec2& size, const glm::vec2& normal, const glm::vec4& color)
	: _position(position), _size(size), _normal(normal), _color(color), _collider(new QuadCollider2D(_position, _size))
{
	CollisionModule::Get().AddCollider(_collider);
}

Block::~Block()
{

}

void Block::Update(float dt)
{
	//const float speed = 2.0f;
	//
	//_position.x += speed * dt * (Random::Float() * 2 - 1.0f);
	//_position.y += speed * dt * (Random::Float() * 2 - 1.0f);
}

void Block::Render()
{
	GitGud::Renderer2D::DrawQuad({ _position.x, _position.y, 0.0f }, _size, _color);
}

void Block::TransformUpdated()
{
	if (_collider)
	{
		_collider->SetPosition(_position.x, _position.y);
		_collider->SetSize(_size.x, _size.y);
	}
}
