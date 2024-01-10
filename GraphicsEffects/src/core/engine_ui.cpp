#include "core/engine_ui.hpp"

#include "ImGui/imgui.h"

#include "core/debug/log.hpp"

Object* EngineUi::m_SelectedObject;

void EngineUi::DrawSceneGraph(Scene& scene)
{
	ImGui::Begin("Scene graph");
	DrawSceneGraph_Object(scene.m_Root);
	ImGui::End();
	
	DrawSelectedObject();
}

void EngineUi::DrawSceneGraph_Object(Object& obj)
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

	const Transform& t = obj.Transformation;
	if (!t.HasChildren())
		flags |= ImGuiTreeNodeFlags_Leaf;

	if (ImGui::TreeNodeEx(obj.Name.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
			m_SelectedObject = &obj;

		for (Transform* t : obj.Transformation.GetChildren())
			DrawSceneGraph_Object(t->GetOwner());

		ImGui::TreePop();
	}
}

void EngineUi::DrawSelectedObject()
{
	if (m_SelectedObject == nullptr)
		return;

	ImGui::Begin("Inspector");

	Transform& t = m_SelectedObject->Transformation;

	ImGui::PushID(m_SelectedObject);
	ImGui::Text(m_SelectedObject->Name.c_str());

	ImGui::Checkbox("Outlined", &m_SelectedObject->Outlined);
	ImGui::DragFloat3("Position", &t.Position.x, .1f);
	ImGui::SliderAngle("Rot. X", &t.Rotation.x);
	ImGui::SliderAngle("Rot. Y", &t.Rotation.y);
	ImGui::SliderAngle("Rot. Z", &t.Rotation.z);
	ImGui::DragFloat3("Scaling", &t.Scaling.x, .1f);

	ImGui::Separator();

	m_SelectedObject->OnGui();

	ImGui::PopID();
	ImGui::End();
}
