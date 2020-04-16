#include <GitGud.h>
#include <GitGud/Core/EntryPoint.h>

#include <imgui/imgui.h>

class TestLayer : public GitGud::Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{
	}

	~TestLayer()
	{

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Text("Hello FlappyClone");
	}
};

class FlappyCloneApp : public GitGud::Application
{
public:
	FlappyCloneApp()
	{
		PushLayer(new TestLayer());
	}

	~FlappyCloneApp()
	{

	}
};

GitGud::Application* GitGud::CreateApplication()
{
	return new FlappyCloneApp();
}