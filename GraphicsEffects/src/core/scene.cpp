#include "core/scene.hpp"

#include "resources/shader.hpp"

#include "ImGui/imgui.h"

#include "core/debug/log.hpp"
#include "core/debug/assert.hpp"

Scene* Scene::m_CurrentScene;

Scene* Scene::CurrentScene()
{
	Assert::IsTrue(m_CurrentScene != nullptr, "No scene is currently loaded");
	return m_CurrentScene;
}

Scene::Scene(const std::string& name)
	: m_Root(nullptr, nullptr, nullptr), m_Name(name)
{
	if (m_CurrentScene == nullptr)
		m_CurrentScene = this;

	m_Root.Name = m_Name;
}

void Scene::AddObject(Object& obj)
{
	if (!obj.HasParent())
		obj.SetParent(&m_Root);
}

void Scene::AddPointLight(PointLight* const light)
{
	m_PointLights.push_back(light);
}

void Scene::RemovePointLight(PointLight* const light)
{
	std::erase(m_PointLights, light);
}

void Scene::AddDirectionalLight(DirectionalLight* const light)
{
	m_DirLights.push_back(light);
}

void Scene::RemoveDirectionalLight(DirectionalLight* const light)
{
	std::erase(m_DirLights, light);
}

void Scene::AddSpotLight(SpotLight* const light)
{
	m_SpotLights.push_back(light);
}

void Scene::RemoveSpotLight(SpotLight* const light)
{
	std::erase(m_SpotLights, light);
}

void Scene::ApplyLights(Shader& shader)
{
	// There is probably a better way to do this
	shader.Use();

	shader.SetUniform("nbrDirLights", static_cast<int32_t>(m_DirLights.size()));
	for (size_t i = 0; i < m_DirLights.size(); i++)
	{
		const DirectionalLight* l = m_DirLights[i];

		l->ForwardToShader(shader, static_cast<uint32_t>(i));
	}

	shader.SetUniform("nbrPointLights", static_cast<int32_t>(m_PointLights.size()));
	for (size_t i = 0; i < m_PointLights.size(); i++)
	{
		const PointLight* l = m_PointLights[i];

		l->ForwardToShader(shader, static_cast<uint32_t>(i));
	}

	shader.SetUniform("nbrSpotLights", static_cast<int32_t>(m_SpotLights.size()));
	for (size_t i = 0; i < m_SpotLights.size(); i++)
	{
		const SpotLight* l = m_SpotLights[i];

		l->ForwardToShader(shader, static_cast<uint32_t>(i));
	}

	shader.Unuse();
}

void Scene::Update()
{
	UpdateChildren(m_Root);
}

void Scene::UpdateChildren(Object& obj)
{
	if (obj.HasShader())
		ApplyLights(obj.GetShader());

	obj.Render();

	for (Transform* t : obj.Transformation.GetChildren())
	{
		UpdateChildren(t->GetOwner());
	}
}
