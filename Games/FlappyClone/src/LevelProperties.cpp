#include "LevelProperties.h"

#include <imgui/imgui.h>

bool DragMinMax(const char* label, MinMax& value, float speed, float minValue, float maxValue, const char* format, float power)
{
	ImGui::PushID(label);

	ImGui::Text(label);

	ImGui::SetNextItemWidth(200);
	bool minChanged = ImGui::DragFloat("Min", &value.Min, speed, minValue, maxValue, format, power);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(200);
	bool maxChanged = ImGui::DragFloat("Max", &value.Max, speed, minValue, maxValue, format, power);

	ImGui::PopID();

	return minChanged || maxChanged;
}

void LevelPropertiesEditor(LevelProperties& properties)
{
	ImGui::TextColored({ 1, 1, 0, 1 }, "Level Properties");
	ImGui::DragInt("Obstacles count", &properties.ObstaclesCount);
	ImGui::DragFloat("Speed", &properties.Speed, 0.1f);
	DragMinMax("Separation", properties.ObstaclesSeparation, 0.1f);

	ImGui::TextColored({ 1, 1, 0, 1 }, "Obstacle Properties");
	ImGui::DragFloat("Obstacle width", &properties.ObstacleWidth, 0.1f);
	DragMinMax("Gap height %", properties.GapHeightPercentage, 0.01f, 0.0f, 1.0f);
}
