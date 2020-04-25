#pragma once

#include <GitGud.h>
#include <glm/glm.hpp>
#include "GameElements/Obstacle.h"

class TestEditorLayer : public GitGud::Layer
{
public:
	TestEditorLayer();
	~TestEditorLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(GitGud::Timestep ts) override;
	virtual void OnImGuiRender() override;

private:
	glm::vec2 _position, _size;
	glm::vec4 _color;
	char _name[50];
	bool _renderQuad = true, _renderTestObstacle = true, _renderCollisions = false;
	Obstacle* _testObstacle = nullptr;
	glm::vec4 _colliderDebugColor = { 0.9f, 0.2f, 0.3f, 0.8f };
};

inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
{
	return os << vec2.x << " x " << vec2.y;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec4)
{
	return os << vec4.x << " - " << vec4.y << " - " << vec4.z << " - " << vec4.w;
}
