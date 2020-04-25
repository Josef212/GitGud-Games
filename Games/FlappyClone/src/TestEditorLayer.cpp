#include "FlappyCloneApp.h"
#include "TestEditorLayer.h"

#include <imgui/imgui.h>

using namespace GitGud;

TestEditorLayer::TestEditorLayer() : Layer("TestEditorLayer")
{
	_position = glm::vec2(0.0f);
	_size = glm::vec2(1.0f);
	_color = glm::vec4(1.0f);
	_name[0] = '\n';
}

void TestEditorLayer::OnUpdate(GitGud::Timestep ts)
{
	Renderer2D::BeginScene(static_cast<FlappyCloneApp&>(Application::Get()).GetCamera());

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
