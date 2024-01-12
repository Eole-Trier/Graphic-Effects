#pragma once

#include "renderer/light.hpp"

class PointLight : public Light
{
public:
	float ConstantAttenuation;
	float LinearAttenuation;
	float QuadraticAttenuation;
	

	PointLight(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float intensity);
	PointLight(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float intensity,
		const float constantAtt, const float linearAtt, const float quadAtt);
	~PointLight() override;

	void ForwardToShader(Shader& shader, uint32_t i) const override;

	void OnGui() override;

	void UpdateRadius() override;
};
