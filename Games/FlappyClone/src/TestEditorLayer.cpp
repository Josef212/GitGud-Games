#include "FlappyCloneApp.h"
#include "TestEditorLayer.h"
#include "Collisions.h"

#include <imgui/imgui.h>

using namespace GitGud;

TestEditorLayer::TestEditorLayer() : Layer("TestEditorLayer")
{
	_position = glm::vec2(0.0f);
	_size = glm::vec2(1.0f);
	_color = glm::vec4(1.0f);
	_name[0] = '\n';
}

TestEditorLayer::~TestEditorLayer()
{
	
}

void TestEditorLayer::OnAttach()
{
	_testObstacle = new Obstacle(0.0f, 0.0f, 1.0f, 0.0f, { 0.8, 0.8f, 0.8f, 1.0f });
	_testObstacle->SetZ(1.0f);
}

void TestEditorLayer::OnDetach()
{
	delete _testObstacle;
	_testObstacle = nullptr;
}

void TestEditorLayer::OnUpdate(GitGud::Timestep ts)
{
	Renderer2D::BeginScene(static_cast<FlappyCloneApp&>(Application::Get()).GetCamera());

	if (_renderQuad)
		Renderer2D::DrawQuad({ _position.x, _position.y, 1.0f }, _size, _color);

	if(_renderTestObstacle)
		_testObstacle->Render();

	if (_renderCollisions)
	{
		auto collisions = GitGud::Extensions::CollisionModule::Get();

		for (auto col : *collisions)
		{
			if (col->GetColliderType() == GitGud::Extensions::Collider2DType::Quad)
			{
				auto quadCollider = static_cast<GitGud::Extensions::QuadCollider2D*>(col);

				auto pos = quadCollider->GetPositon();
				auto size = quadCollider->GetSize();

				Renderer2D::DrawQuad({ pos.x, pos.y, 1.0f }, size, _colliderDebugColor);
			}
		}
	}

	Renderer2D::EndScene();
}

void TestEditorLayer::OnImGuiRender()
{
	ImGui::Begin("Editor");
	
	ImGui::Checkbox("Render quad", &_renderQuad);
	ImGui::Checkbox("Debug collisions", &_renderCollisions);
	ImGui::Checkbox("Render test block", &_renderTestObstacle);

	if (_renderQuad)
	{
		ImGui::Text("Debug quad");

		ImGui::InputText("Label", _name, 50);
		ImGui::DragFloat2("Position", &_position.x, 0.1f);
		ImGui::DragFloat2("Size", &_size.x, 0.1f);
		ImGui::ColorEdit4("Color", &_color.r);

		if (ImGui::Button("Print"))
		{
			GG_INFO("Position: {0}, Size: {1}, Color: {2} -> {0}", _position, _size, _color, _name);
			// TODO: Would be nice to print into a file
		}
	}

	if (_renderCollisions)
	{
		ImGui::Text("Debug collisions");

		ImGui::ColorEdit4("Collider color", &_colliderDebugColor.r);
	}
	
	if (_renderTestObstacle)
	{
		ImGui::Text("Debug block obstacle");

		float blockX = _testObstacle->GetX();
		float gapY = _testObstacle->GetGapY();
		float blockWidth = _testObstacle->GetObstacleWidth();
		float gapHeightPercentage = _testObstacle->GetGapHeightPerdentage();

		if (ImGui::DragFloat("Block X", &blockX, 0.1f))
		{
			_testObstacle->SetX(blockX);
		}

		if (ImGui::DragFloat("Gap Y", &gapY, 0.1f))
		{
			_testObstacle->SetGapY(gapY);
		}

		if (ImGui::DragFloat("Block Width", &blockWidth, 0.1f))
		{
			_testObstacle->SetObstacleWidth(blockWidth);
		}

		if (ImGui::DragFloat("Gap height %", &gapHeightPercentage, 0.05f, 0.0f, 1.0f))
		{
			_testObstacle->SetGapHeightPerdentage(gapHeightPercentage);
		}
	}
	
	ImGui::End();
}
