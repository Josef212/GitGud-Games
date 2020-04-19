#include "GameLayer.h"

#include "GameElements/Block.h"
#include "Random.h"

using namespace GitGud;
using namespace GitGud::Extensions;

GameLayer::GameLayer() : Layer("FlappyClone"), _camera(CreateScope<OrthographicCamera>(0.0f, 0.0f, 0.0f, 0.0f))
{
	auto& win = Application::Get().GetWindow();
	UpdateCamera(win.GetWidth(), win.GetHeight());
	
	Random::Init();

	_level = new Level();
}

GameLayer::~GameLayer()
{
	delete _level;
}

void GameLayer::OnAttach()
{

}

void GameLayer::OnDetach()
{

}

void GameLayer::OnUpdate(Timestep ts)
{
	_level->Update(ts);

	RenderCommand::SetClearColor(glm::vec4(0.15f));
	RenderCommand::Clear();

	Renderer2D::BeginScene(*_camera);

	_level->Render();

	Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender()
{
}

void GameLayer::OnEvent(Event& event)
{
}

void GameLayer::UpdateCamera(uint32_t width, uint32_t height)
{
	float ar = (float)width / (float)height;

	float halfHeight = 8.0f;
	float halfWidth = halfHeight * ar;

	_camera->SetProjection(-halfWidth, halfWidth, -halfHeight, halfHeight);
}