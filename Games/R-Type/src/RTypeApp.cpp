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
		ImGui::Text("Hello R-Type");
	}
};

class RtypeApp : public GitGud::Application
{
public:
	RtypeApp()
	{
		PushLayer(new TestLayer());
	}

	~RtypeApp()
	{

	}
};

GitGud::Application* GitGud::CreateApplication()
{
	return new RtypeApp();
}