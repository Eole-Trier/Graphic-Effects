#include "renderer/point_light.hpp"
#include "resources/shader.hpp"
#include "core/object.hpp"
#include "core/scene.hpp"

PointLight::PointLight(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float intensity)
	: Light(obj, diffuse, ambient, specular, intensity)
{
	ConstantAttenuation = 1.f;
	LinearAttenuation = 0.f;
	QuadraticAttenuation = 0.f;
	Radius = 10 * sqrt(Intensity);

	Scene::CurrentScene()->AddPointLight(this);
}

PointLight::PointLight(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float intensity,
	const float constantAtt, const float linearAtt, const float quadAtt)
	: Light(obj, diffuse, ambient, specular, intensity), ConstantAttenuation(constantAtt), LinearAttenuation(linearAtt),
	  QuadraticAttenuation(quadAtt)
{
	Scene::CurrentScene()->AddPointLight(this);
}

PointLight::~PointLight()
{
	Scene::CurrentScene()->RemovePointLight(this);
}

void PointLight::ForwardToShader(Shader& shader, uint32_t i) const
{
	std::string baseName = std::string("pointLights[").append(std::to_string(i)).append("].");

	shader.SetUniform(baseName + "position", Owner->Transformation.Position);

	shader.SetUniform(baseName + "ambient", Ambient);
	shader.SetUniform(baseName + "diffuse", Diffuse);
	shader.SetUniform(baseName + "specular", Specular);

	shader.SetUniform(baseName + "constant", ConstantAttenuation);
	shader.SetUniform(baseName + "linear", LinearAttenuation);
	shader.SetUniform(baseName + "quadratic", QuadraticAttenuation);
	shader.SetUniform(baseName + "radius", Radius);
}

void PointLight::OnGui()
{
	Light::OnGui();
	
	ImGui::SliderFloat("Constant att.", &ConstantAttenuation, 0.f, 1.f);
	ImGui::SliderFloat("Linear att.", &LinearAttenuation, 0.f, 1.f);
	ImGui::SliderFloat("Quadratic att.", &QuadraticAttenuation, 0.f, 1.f);
	ImGui::SliderFloat("Intensity", &Intensity, 0.f, 5.f);
	ImGui::Text("Radius %f", Radius);
}

void PointLight::UpdateRadius()
{
	Light::UpdateRadius();
}
