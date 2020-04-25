#pragma once

#include "GameElement.h"
#include "Collisions.h"

#include <glm/glm.hpp>

class Block : public GameElement
{
public:
	Block();
	Block(float blockPosition, float gapYPosition, float blockWidth, float gapHeightPercentage, const glm::vec4& color);
	virtual ~Block();

	virtual void Update(float dt) override;
	virtual void Render() override;

	inline void SetX(float x) { _blockPosition = x; TransformUpdated(); }
	inline float GetX() const { return _blockPosition; }

	inline const GitGud::Extensions::QuadCollider2D* GetCollider() const { return _topCollider; }

protected:
	void TransformUpdated();

protected:
	float _blockPosition, _gapYPosition, _blockWidth, _gapHeightPerdentage;
	glm::vec4 _color;
	GitGud::Extensions::QuadCollider2D* _topCollider, *_botCollider;
	glm::vec3 _botPos = glm::vec3(0.0f), _topPos = glm::vec3(0.0f);
	glm::vec2 _botSize = glm::vec2(1.0f), _topSize = glm::vec2(1.0f);
};