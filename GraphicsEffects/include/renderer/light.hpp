#pragma once

#include "core/component.hpp"

#include "core/maths/vector4.h"

class Object;
class Shader;

class Light : public Component
{
public:
	Vector4 Diffuse;
	Vector4 Ambient;
	Vector4 Specular;

	Light(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular);
	virtual ~Light() {};

	virtual void ForwardToShader(Shader& shader, uint32_t i) const = 0;

	virtual void OnGui() override;
};

