#include "resources/model.hpp"
#include "core/debug/assert.hpp"

#include "glad/glad.h"

#include "core/debug/log.hpp"

#include <fstream>

void Model::SetupMesh()
{
	glGenVertexArrays(1, &m_Vao);
	glGenBuffers(1, &m_Vbo);
	glGenBuffers(1, &m_Ebo);

	glBindVertexArray(m_Vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data(), GL_STATIC_DRAW);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
	glEnableVertexAttribArray(0);

	// Uv
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Uv));
	glEnableVertexAttribArray(1);

	// Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
}

void Model::Load()
{
	std::ifstream file(m_Name);
	std::vector<Vector3> positions;
	std::vector<Vector2> uvs;
	std::vector<Vector3> normals;

	Assert::IsTrue(file.is_open(), std::string("Couldn't load model : ").append(m_Name).c_str());

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line);

		if (line[0] == '#')
			continue;

		if (line[0] == 'f')
		{
			uint32_t indices[3][3];
			int32_t a = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&indices[0][0], &indices[0][1], &indices[0][2],
				&indices[1][0], &indices[1][1], &indices[1][2],
				&indices[2][0], &indices[2][1], &indices[2][2]
			);

			m_Vertices.push_back(Vertex(
				positions[indices[0][0] - 1],
				uvs[indices[0][1] - 1],
				normals[indices[0][2] - 1]
			));

			m_Vertices.push_back(Vertex(
				positions[indices[1][0] - 1],
				uvs[indices[1][1] - 1],
				normals[indices[1][2] - 1]
			));

			m_Vertices.push_back(Vertex(
				positions[indices[2][0] - 1],
				uvs[indices[2][1] - 1],
				normals[indices[2][2] - 1]
			));
			continue;
		}
		
		if (line[0] == 'v')
		{
			if (line[1] == 't')
			{
				Vector2 v;
				// Ignore no discard warning
				int32_t a = sscanf_s(line.c_str(), "vt %f %f", &v.x, &v.y);
				// Invert Y uvs
				v.y = 1.f - v.y;
				uvs.push_back(v);
			}
			else if (line[1] == 'n')
			{
				Vector3 v;
				// Ignore no discard warning
				int32_t a = sscanf_s(line.c_str(), "vn %f %f %f", &v.x, &v.y, &v.z);
				normals.push_back(v);
			}
			else
			{
				Vector3 v;
				// Ignore no discard warning
				int32_t a = sscanf_s(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
				positions.push_back(v);
			}
		}
	}

	file.close();
	SetupMesh();
}

void Model::Render()
{
	glBindVertexArray(m_Vao);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_Vertices.size()));
	glBindVertexArray(0);
}
