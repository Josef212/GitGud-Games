#pragma once

#include "GameElement.h"
#include "Collisions.h"

#include <glm/glm.hpp>

class Obstacle : public GameElement
{
public:
	Obstacle();
	Obstacle(float ostaclePosition, float gapYPosition, float obstacleWidth, float gapHeightPercentage, const glm::vec4& color);
	virtual ~Obstacle();

	virtual void Update(float speed) override;
	virtual void Render() override;

	inline void SetX(float x) { _obstacleXPosition = x; TransformUpdated(); }
	inline float GetX() const { return _obstacleXPosition; }

	inline void SetGapY(float y) { _gapYPosition = y; TransformUpdated(); }
	inline float GetGapY() const { return _gapYPosition; }

	inline void SetObstacleWidth(float width) { _obstacleWidth = width; TransformUpdated(); }
	inline float GetObstacleWidth() const { return _obstacleWidth; }

	inline void SetGapHeightPerdentage(float percentage) { _gapHeightPerdentage = percentage; TransformUpdated(); }
	inline float GetGapHeightPerdentage() const { return _gapHeightPerdentage; }

	inline void SetZ(float z) { _zPosition = z; TransformUpdated(); }
	inline float GetZ() const { return _zPosition; }

	inline const GitGud::Extensions::QuadCollider2D* GetTopCollider() const { return _topCollider; }
	inline const GitGud::Extensions::QuadCollider2D* GetBotCollider() const { return _botCollider; }

protected:
	void TransformUpdated();

protected:
	float _obstacleXPosition, _gapYPosition, _obstacleWidth, _gapHeightPerdentage, _zPosition;
	glm::vec4 _color;
	GitGud::Extensions::QuadCollider2D* _topCollider, *_botCollider;
	glm::vec3 _botPos = glm::vec3(0.0f), _topPos = glm::vec3(0.0f);
	glm::vec2 _botSize = glm::vec2(1.0f), _topSize = glm::vec2(1.0f);
};