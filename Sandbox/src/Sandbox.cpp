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
		ImGui::Text("Hello GitGud::Sandbox");
	}
};

class SandboxApp : public GitGud::Application
{
public:
	SandboxApp()
	{
		PushLayer(new TestLayer());
	}

	~SandboxApp()
	{

	}
};

GitGud::Application* GitGud::CreateApplication()
{
	return new SandboxApp();
}