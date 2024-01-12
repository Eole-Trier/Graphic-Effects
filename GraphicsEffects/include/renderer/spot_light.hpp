#pragma once

#include "renderer/light.hpp"
#include "core/maths/vector3.h"

class SpotLight : public Light
{
public:
	Vector3 Direction;

	float CutOff;
	float OuterCutOff;

	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;

	SpotLight(Object* const obj, const Vector3& direction, const float cutOff, const float outerCutoff,
		const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float intensity);
	SpotLight(Object* const obj, const Vector3& direction, const float cutOff, const float outerCutoff,
		const Vector4& diffuse, const Vector4& ambient, const Vector4& specular,
		const float constantAtt, const float linearAtt, const float quadAtt, const float intensity);

	~SpotLight() override;

	void ForwardToShader(Shader& shader, uint32_t i) const override;
	void OnGui() override;

	void UpdateRadius() override;
};
