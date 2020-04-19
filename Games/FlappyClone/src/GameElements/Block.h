#pragma once

#include "GameElement.h"
#include "Collisions.h"

#include <glm/glm.hpp>

class Block : public GameElement
{
public:
	Block();
	Block(const glm::vec2& position, const glm::vec2& size, const glm::vec2& normal, const glm::vec4& color);
	virtual ~Block();

	virtual void Update(float dt) override;
	virtual void Render() override;

	inline const glm::vec2& GetPosition() const { return _position; }
	inline void SetPosition(const glm::vec2& position) { _position = position; TransformUpdated(); }

	inline const glm::vec2& GetSize() const { return _size; }
	inline void SetSize(const glm::vec2& size) { _size = size; TransformUpdated(); }

	inline const glm::vec2& GetNormal() const { return _normal; }
	inline void SetNormal(const glm::vec2& normal) { _normal = normal; TransformUpdated(); }

	inline const GitGud::Extensions::QuadCollider2D* GetCollider() const { return _collider; }

protected:
	void TransformUpdated();

protected:
	glm::vec2 _position, _size, _normal;
	glm::vec4 _color;
	GitGud::Extensions::QuadCollider2D* _collider;
};