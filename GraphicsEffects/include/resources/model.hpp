#pragma once

#include "resources/resource.hpp"
#include "renderer/vertex.hpp"
#include <vector>

#include "core/maths/vector3.h"
#include "core/maths/vector2.h"

class Model : public Resource
{
private:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;

	uint32_t m_Vbo;
	uint32_t m_Vao;
	uint32_t m_Ebo;

	void SetupMesh();

public:
	Model(const std::string& name) : Resource(name) {}

	void Load() override;

	void Render();
};

