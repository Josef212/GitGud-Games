#include "GameLayer.h"

#include "Random.h"

#include <imgui/imgui.h>

using namespace GitGud;
using namespace GitGud::Extensions;

GameLayer::GameLayer() : Layer("FlappyClone"), _camera(CreateScope<OrthographicCamera>(0.0f, 0.0f, 0.0f, 0.0f))
{
	auto& win = Application::Get().GetWindow();
	UpdateCamera(win.GetWidth(), win.GetHeight());
	
	Random::Init();
}

GameLayer::~GameLayer()
{

}

void GameLayer::OnAttach()
{
	_level = new Level();
}

void GameLayer::OnDetach()
{
	delete _level;
}

void GameLayer::OnUpdate(Timestep ts)
{
	_level->Update(ts);

	CollisionModule::Get()->Update(ts);

	RenderCommand::SetClearColor(glm::vec4(0.15f));
	RenderCommand::Clear();
	
	Renderer2D::BeginScene(*_camera);
	
	_level->Render();
	
	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
	_level->OnImGuiRender();
}

void GameLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(GG_BIND_EVENT_FN(GameLayer::OnWindowResize));
}

void GameLayer::UpdateCamera(uint32_t width, uint32_t height)
{
	float ar = (float)width / (float)height;

	float halfHeight = 8.0f;
	float halfWidth = halfHeight * ar;

	_camera->SetProjection(-halfWidth, halfWidth, -halfHeight, halfHeight);
}

bool GameLayer::OnWindowResize(WindowResizeEvent& e)
{
	UpdateCamera(e.GetWidth(), e.GetHeight());
	return false;
}
