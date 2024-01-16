#include "renderer/spot_light.hpp"
#include "resources/shader.hpp"

#include "glad/glad.h"

#include "core/debug/log.hpp"
#include "core/object.hpp"
#include "core/scene.hpp"

#include "ImGui/imgui.h"

SpotLight::SpotLight(Object* const obj, const Vector3& direction, const float cutOff, const float outerCutoff,
	const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float radius)
	: Light(obj, diffuse, ambient, specular, radius), Direction(direction), CutOff(cutOff), OuterCutOff(outerCutoff)
{
	ConstantAttenuation = 1.f;
	LinearAttenuation = 0.f;
	QuadraticAttenuation = 0.f;

	Scene::CurrentScene()->AddSpotLight(this);
}

SpotLight::SpotLight(Object* const obj, const Vector3& direction, const float cutOff, const float outerCutoff,
	const Vector4& diffuse, const Vector4& ambient, const Vector4& specular,
	const float constantAtt, const float linearAtt, const float quadAtt, const float radius)
	: Light(obj, diffuse, ambient, specular, radius), Direction(direction), CutOff(cutOff), OuterCutOff(outerCutoff),
	ConstantAttenuation(constantAtt), LinearAttenuation(linearAtt),	QuadraticAttenuation(quadAtt)
{
	Scene::CurrentScene()->AddSpotLight(this);
}

SpotLight::~SpotLight()
{
	Scene::CurrentScene()->RemoveSpotLight(this);
}

void SpotLight::ForwardToShader(Shader& shader, uint32_t i) const
{
	std::string baseName = std::string("spotLights[").append(std::to_string(i)).append("].");

	shader.SetUniform(baseName + "position", Owner->Transformation.Position);
	shader.SetUniform(baseName + "direction", Direction);

	shader.SetUniform(baseName + "cutOff", std::cos(CutOff));
	shader.SetUniform(baseName + "outerCutOff", std::cos(OuterCutOff));

	shader.SetUniform(baseName + "constant", ConstantAttenuation);
	shader.SetUniform(baseName + "linear", LinearAttenuation);
	shader.SetUniform(baseName + "quadratic", QuadraticAttenuation);

	shader.SetUniform(baseName + "ambient", Ambient);
	shader.SetUniform(baseName + "diffuse", Diffuse);
	shader.SetUniform(baseName + "specular", Specular);
}

void SpotLight::OnGui()
{
	Light::OnGui();

	ImGui::SliderFloat3("Direction", &Direction.x, -1.f, 1.f);

	ImGui::SliderFloat("Constant att.", &ConstantAttenuation, 0.f, 1.f);
	ImGui::SliderFloat("Linear att.", &LinearAttenuation, 0.f, 1.f);
	ImGui::SliderFloat("Quadratic att.", &QuadraticAttenuation, 0.f, 1.f);

	ImGui::SliderAngle("Cut-off", &CutOff, 0.f, 180.f);
	ImGui::SliderAngle("Outer cut-off", &OuterCutOff, 0.f, 180.f);
}
