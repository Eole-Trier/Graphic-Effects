#pragma once

#include "core/maths/vector2.h"
#include "core/maths/vector3.h"

struct Vertex
{
	Vector3 Position;
	Vector2 Uv;
	Vector3 Normal;

	Vertex(const Vector3& position, const Vector2 uv, const Vector3& normal)
		: Position(position), Uv(uv), Normal(normal)
	{}
};

