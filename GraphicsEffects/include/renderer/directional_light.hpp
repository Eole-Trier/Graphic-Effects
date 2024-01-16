#pragma once

#include "renderer/light.hpp"
#include "core/maths/vector3.h"

class DirectionalLight : public Light
{
public:
	Vector3 Direction;

	DirectionalLight(Object* const obj, const Vector3& direction, const Vector4& diffuse,
		const Vector4& ambient, const Vector4& specular);
	~DirectionalLight() override;

	void ForwardToShader(Shader& shader, uint32_t i) const override;

	void OnGui() override;
};
