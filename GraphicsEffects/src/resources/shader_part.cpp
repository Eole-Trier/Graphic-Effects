#include "resources/shader_part.hpp"
#include "core/debug/log.hpp"
#include "core/debug/assert.hpp"

#include <fstream>

#include "glad/glad.h"

uint32_t ShaderPart::GetShaderTypeEnum(const ShaderType type)
{
	switch (type)
	{
		case ShaderType::VERTEX:
			return GL_VERTEX_SHADER;

		case ShaderType::FRAGMENT:
			return GL_FRAGMENT_SHADER;

		case ShaderType::GEOMETRY:
			return GL_GEOMETRY_SHADER;

		case ShaderType::COMPUTE:
			return GL_COMPUTE_SHADER;

		default:
			__assume(false);
	}
}

void ShaderPart::SetVertexVariables(const std::string& source)
{

}

void ShaderPart::SetFragmentVariables(const std::string& source)
{
	if (source.find("viewPos") != std::string::npos)
		m_Variables |= ShaderVariables::VIEW_POS;
}

void ShaderPart::SetVariables(const std::string& source)
{
	m_Variables = ShaderVariables::NONE;
	switch (m_Type)
	{
		case ShaderType::VERTEX:
			SetVertexVariables(source);
			break;

		case ShaderType::FRAGMENT:
			SetFragmentVariables(source);
			break;
	}
}

ShaderPart::ShaderPart(const std::string& name, const ShaderType type, const std::filesystem::path& path)
	: Resource(name), m_Type(type)
{
	std::ifstream file(path);

	Assert::IsTrue(file.is_open() && file.good(), std::string("Couldn't load shader : ").append(m_Name).c_str());
	
	std::string source = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	const char* const sourceRaw = source.c_str();
	
	m_Handle = glCreateShader(GetShaderTypeEnum(m_Type));
	SetVariables(source);

	glShaderSource(m_Handle, 1, &sourceRaw, nullptr);
	glCompileShader(m_Handle);

	int32_t success;
	glGetShaderiv(m_Handle, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(m_Handle, sizeof(infoLog), nullptr, infoLog);
		Log::LogError(std::string("Failed to compile shader : ").append(m_Name).append(" : ").append(infoLog));
	}
}

ShaderPart::~ShaderPart()
{
	glDeleteShader(m_Handle);
}
