#define TEST 0

#include <GitGud.h>
#include <GitGud/Core/EntryPoint.h>

#if TEST
#include "Collisions.h"
#endif

#include "GameLayer.h"

#include <glm/glm.hpp>
#include <imgui/imgui.h>

#if TEST
class TestLayer : public GitGud::Layer
{
public:
	TestLayer() : Layer("TestLayer"), _position(glm::vec2(0.0f)), _size(glm::vec2(1.0f)), _debugColor({ 0.2f, 0.8f, 0.2f, 0.7f }),
		_c0(nullptr), _c1(nullptr), _colliding(false), _cameraController(1280.0f / 720.0f)
	{
		_c0 = new GitGud::Extensions::QuadCollider2D(_position, _size, GG_BIND_EVENT_FN(TestLayer::OnCollide));
		_c1 = new GitGud::Extensions::QuadCollider2D({ 2.0f, 2.0f }, { 1.0f, 1.0f });

		_collisionModule.AddCollider(_c0);
		_collisionModule.AddCollider(_c1);
	}

	~TestLayer()
	{
		_c0 = _c1 = nullptr;
	}

	virtual void OnUpdate(GitGud::Timestep ts) override
	{
		_colliding = false;

		_cameraController.OnUpdate(ts);
		_collisionModule.Update(ts);

		GitGud::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		GitGud::RenderCommand::Clear();

		GitGud::Renderer2D::BeginScene(_cameraController.GetCamera());

		for (auto it = _collisionModule.begin(); it != _collisionModule.end(); ++it)
		{
			auto c = *it;
			glm::vec3 p = { c->GetPositoon().x, c->GetPositoon().y, 0.5f };
			glm::vec4 color = c == _c0 ? _debugColor : glm::vec4(0.8f, 0.1f, 0.1f, 0.7f);
			
			GitGud::Renderer2D::DrawQuad(p, static_cast<GitGud::Extensions::QuadCollider2D*>(c)->GetSize(), color);
		}

		if (_colliding)
		{
			GitGud::Renderer2D::DrawQuad({ -1.2f, 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 0.7f });
		}
		
		GitGud::Renderer2D::EndScene();
	}

	virtual void OnEvent(GitGud::Event& e) override
	{
		_cameraController.OnEvent(e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Text("Hello FlappyClone");

		bool a = ImGui::DragFloat2("Position", glm::value_ptr(_position), 0.1f);
		bool b = ImGui::DragFloat2("Size", glm::value_ptr(_size), 0.1f);

		if (a || b)
		{
			_c0->SetPosition(_position.x, _position.y);
			_c0->SetSize(_size.x, _size.y);
		}
	}

	void OnCollide(GitGud::Extensions::Collider2D* c)
	{
		_colliding = true;
	}

private:
	glm::vec2 _position, _size;
	glm::vec4 _debugColor;
	GitGud::Extensions::QuadCollider2D* _c0, *_c1;
	bool _colliding;

	GitGud::OrthographicCameraController _cameraController;
	GitGud::Extensions::CollisionModule _collisionModule;
};
#endif

class FlappyCloneApp : public GitGud::Application
{
public:
	FlappyCloneApp()
	{
		_collisionModule = new GitGud::Extensions::CollisionModule();

#if TEST
		PushLayer(new TestLayer());
#endif
		PushLayer(new GameLayer());
	}

	~FlappyCloneApp()
	{
		delete _collisionModule;
	}

private:
	GitGud::Extensions::CollisionModule* _collisionModule = nullptr;
};

GitGud::Application* GitGud::CreateApplication()
{
	return new FlappyCloneApp();
}
