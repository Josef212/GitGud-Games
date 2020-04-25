#include "Block.h"
#include "../FlappyCloneApp.h"

#include <GitGud.h>
#include "../Random.h"

using namespace GitGud::Extensions;

Block::Block() : _blockPosition(0.0f), _gapYPosition(0.0f), _blockWidth(2.0f), _gapHeightPerdentage(0.15f), _color({ 1.0f, 0.1f, 0.5f, 1.0f }), 
_topCollider(new QuadCollider2D({0.0f, 0.0f}, { 1.0f, 1.0f })), _botCollider(new QuadCollider2D({ 0.0f, 0.0f }, { 1.0f, 1.0f }))
{
	CollisionModule::Get().AddCollider(_topCollider);
	CollisionModule::Get().AddCollider(_botCollider);
}

Block::Block(float blockPosition, float gapYPosition, float blockWidth, float gapHeightPercentage, const glm::vec4& color)
	: _blockPosition(blockPosition), _gapYPosition(gapYPosition), _blockWidth(blockWidth), _gapHeightPerdentage(gapHeightPercentage), _color(color),
	_topCollider(new QuadCollider2D({ 0.0f, 0.0f }, { 1.0f, 1.0f })), _botCollider(new QuadCollider2D({0.0f, 0.0f}, { 1.0f, 1.0f }))
{
	CollisionModule::Get().AddCollider(_topCollider);
	CollisionModule::Get().AddCollider(_botCollider);
	TransformUpdated();
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
	GitGud::Renderer2D::DrawQuad(_botPos, _botSize, _color);
	GitGud::Renderer2D::DrawQuad(_topPos, _topSize, _color);
}

void Block::TransformUpdated()
{
	auto camera = static_cast<FlappyCloneApp&>(GitGud::Application::Get()).GetCamera();

	// Will assume _gapYHeight goes from 0(bot) to camera height(top)

	float totalHeight = camera.GetHeight();
	float gapHeight = totalHeight * _gapHeightPerdentage;
	float blocksHeight = totalHeight - gapHeight;

	// Bottom block top corner Y pos
	float botTopY = _gapYPosition + (totalHeight * 0.5f) - (gapHeight * 0.5f);

	_botSize.y = botTopY;
	_botPos.y = (_botSize.y * 0.5f) + camera.GetBottom();

	_topSize.y = blocksHeight - _botSize.y;
	_topPos.y = totalHeight - (_topSize.y * 0.5f) + camera.GetBottom();

	_botSize.x = _topSize.x = _blockWidth;
	_botPos.x = _topPos.x = _blockPosition;
	_botPos.z = _topPos.z = 0.0f;

	if (_topCollider)
	{
		_topCollider->SetPosition(_topPos.x, _topPos.y);
		_topCollider->SetSize(_topSize.x, _topSize.y);
	}

	if (_botCollider)
	{
		_botCollider->SetPosition(_botPos.x, _botPos.y);
		_botCollider->SetSize(_botSize.x, _botSize.y);
	}
}
