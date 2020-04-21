#pragma once

#include <GitGud.h>
#include <glm/glm.hpp>

class TestEditorLayer : public GitGud::Layer
{
public:
	TestEditorLayer();
	~TestEditorLayer() = default;

	virtual void OnUpdate(GitGud::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(GitGud::Event& event) override;

private:
	void UpdateCamera(uint32_t width, uint32_t height);
	bool OnWindowResize(GitGud::WindowResizeEvent& e);

private:
	GitGud::Scope<GitGud::OrthographicCamera> _camera;
	glm::vec2 _position, _size;
	glm::vec4 _color;
	char _name[50];
	bool _renderQuad = true;
};

inline std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
{
	return os << vec2.x << " x " << vec2.y;
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec4& vec4)
{
	return os << vec4.x << " - " << vec4.y << " - " << vec4.z << " - " << vec4.w;
}
