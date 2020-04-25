#pragma once

#include <GitGud.h>
#include "Collisions.h"
#include "Level.h"

class GameLayer : public GitGud::Layer
{
public:
	GameLayer();
	~GameLayer();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(GitGud::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(GitGud::Event& event) override;

	const GitGud::OrthographicCamera& GetCamera() { return *_camera; }

private:
	void UpdateCamera(uint32_t width, uint32_t height);
	bool OnWindowResize(GitGud::WindowResizeEvent& e);

private:
	GitGud::Scope<GitGud::OrthographicCamera> _camera;
	Level* _level = nullptr;
};
