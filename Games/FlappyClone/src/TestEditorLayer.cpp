#include "TestEditorLayer.h"

#include <imgui/imgui.h>

using namespace GitGud;

TestEditorLayer::TestEditorLayer() : Layer("TestEditorLayer"), 
	_camera(CreateScope<OrthographicCamera>(0.0f, 0.0f, 0.0f, 0.0f))
{
	_position = glm::vec2(0.0f);
	_size = glm::vec2(1.0f);
	_color = glm::vec4(1.0f);
	_name[0] = '\n';

	auto& win = Application::Get().GetWindow();
	UpdateCamera(win.GetWidth(), win.GetHeight());
}

void TestEditorLayer::OnUpdate(GitGud::Timestep ts)
{
	Renderer2D::BeginScene(*_camera);

	if (_renderQuad)
		Renderer2D::DrawQuad({ _position.x, _position.y, 1.0f }, _size, _color);

	Renderer2D::EndScene();
}

void TestEditorLayer::OnImGuiRender()
{
	ImGui::Begin("Editor");

	ImGui::Checkbox("Render quad", &_renderQuad);
	ImGui::InputText("Label", _name, 50);
	ImGui::DragFloat2("Position", &_position.x, 0.1f);
	ImGui::DragFloat2("Size", &_size.x, 0.1f);
	ImGui::ColorEdit4("Color", &_color.r);

	if (ImGui::Button("Print"))
	{
		GG_INFO("Position: {0}, Size: {1}, Color: {2} -> {0}", _position, _size, _color, _name);
		// TODO: Would be nice to print into a file
	}

	ImGui::End();
}

void TestEditorLayer::OnEvent(GitGud::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<WindowResizeEvent>(GG_BIND_EVENT_FN(TestEditorLayer::OnWindowResize));
}

void TestEditorLayer::UpdateCamera(uint32_t width, uint32_t height)
{
	float ar = (float)width / (float)height;

	float halfHeight = 8.0f;
	float halfWidth = halfHeight * ar;

	_camera->SetProjection(-halfWidth, halfWidth, -halfHeight, halfHeight);
}

bool TestEditorLayer::OnWindowResize(GitGud::WindowResizeEvent& e)
{
	UpdateCamera(e.GetWidth(), e.GetHeight());
	return false;
}
