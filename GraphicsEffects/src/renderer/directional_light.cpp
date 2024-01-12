#include "renderer/directional_light.hpp"
#include "resources/shader.hpp"
#include "core/object.hpp"
#include "core/scene.hpp"

DirectionalLight::DirectionalLight(Object* const obj, const Vector3& direction, const Vector4& diffuse,
	const Vector4& ambient, const Vector4& specular, const float intensity)
	: Light(obj, diffuse, ambient, specular, intensity)
{
	Scene::CurrentScene()->AddDirectionalLight(this);
}

DirectionalLight::~DirectionalLight()
{
	Scene::CurrentScene()->RemoveDirectionalLight(this);
}

void DirectionalLight::ForwardToShader(Shader& shader, uint32_t i) const
{
	std::string baseName = std::string("dirLights[").append(std::to_string(i)).append("].");

	shader.SetUniform(baseName + "direction", Direction);
	shader.SetUniform(baseName + "ambient", Ambient);
	shader.SetUniform(baseName + "diffuse", Diffuse);
	shader.SetUniform(baseName + "specular", Specular);
	shader.SetUniform(baseName + "radius", Radius);
}

void DirectionalLight::OnGui()
{
	Light::OnGui();

	ImGui::SliderFloat3("Direction", &Direction.x, -1.f, 1.f);
	ImGui::SliderFloat("Intensity", &Intensity, 0.f, 5.f);
}

void DirectionalLight::UpdateRadius()
{
	Light::UpdateRadius();
}

