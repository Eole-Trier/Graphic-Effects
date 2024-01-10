#pragma once

#include <string>

#include "core/object.hpp"

#include "renderer/point_light.hpp"
#include "renderer/directional_light.hpp"
#include "renderer/spot_light.hpp"

class EngineUi;
class Shader;

class Scene
{
#pragma region Static
private:
	static Scene* m_CurrentScene;

public:
	static Scene* CurrentScene();

#pragma endregion

private:
	Object m_Root;
	std::string m_Name;
	
	// Lights need to be handled in a special way and have special properties,
	// so we keep track of them directly in the scene
	std::vector<PointLight*> m_PointLights;
	std::vector<DirectionalLight*> m_DirLights;
	std::vector<SpotLight*> m_SpotLights;

	void UpdateChildren(Object& obj);

public:
	Scene(const std::string& name);

	void AddObject(Object& obj);

	void AddPointLight(PointLight* const light);
	void RemovePointLight(PointLight* const light);

	void AddDirectionalLight(DirectionalLight* const light);
	void RemoveDirectionalLight(DirectionalLight* const light);

	void AddSpotLight(SpotLight* const light);
	void RemoveSpotLight(SpotLight* const light);

	void ApplyLights(Shader& shader);

	void Update();

	friend class EngineUi;
};
