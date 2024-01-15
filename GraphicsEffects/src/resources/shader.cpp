#include "resources/shader.hpp"
#include "resources/shader_part.hpp"

#include "core/debug/log.hpp"

#include "glad/glad.h"

ShaderVariables operator|(ShaderVariables left, ShaderVariables right)
{
	return static_cast<ShaderVariables>(static_cast<uint32_t>(left) | static_cast<uint32_t>(right));
}

ShaderVariables operator|=(ShaderVariables left, ShaderVariables right)
{
	return static_cast<ShaderVariables>(static_cast<uint32_t>(left) | static_cast<uint32_t>(right));
}

bool operator&(ShaderVariables left, ShaderVariables right)
{
	return static_cast<uint32_t>(left) & static_cast<uint32_t>(right);
}

void Shader::Load(const std::filesystem::path& vertex, const std::filesystem::path& fragment)
{
	const ShaderPart vShader(m_Name + " vertex", ShaderType::VERTEX, vertex);
	const ShaderPart fShader(m_Name + " fragment", ShaderType::FRAGMENT, fragment);

	m_Variables = vShader.m_Variables | fShader.m_Variables;

	m_Handle = glCreateProgram();
	glAttachShader(m_Handle, vShader.m_Handle);
	glAttachShader(m_Handle, fShader.m_Handle);
	glLinkProgram(m_Handle);

	int32_t success;
	glGetProgramiv(m_Handle, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_Handle, sizeof(infoLog), nullptr, infoLog);
		Log::LogError(std::string("Failed to link shader : ").append(m_Name).append(" : ").append(infoLog));
	}
}

void Shader::Use() const
{
	glUseProgram(m_Handle);
}

void Shader::Unuse() const
{
	glUseProgram(0);
}

bool Shader::HasVariable(const ShaderVariables variable) const
{
	return m_Variables & variable;
}

void Shader::SetUniform(const std::string& name, const bool value) const
{
	glUniform1i(GetUniform(name), value);
}

void Shader::SetUniform(const std::string& name, const int32_t value) const
{
	glUniform1i(GetUniform(name), value);
}

void Shader::SetUniform(const std::string& name, const float_t value) const
{
	glUniform1f(GetUniform(name), value);
}

void Shader::SetUniform(const std::string& name, const Vector2 value) const
{
	glUniform2fv(GetUniform(name), 1, &value.x);
}

void Shader::SetUniform(const std::string& name, const Vector3& value) const
{
	glUniform3fv(GetUniform(name), 1, &value.x);
}

void Shader::SetUniform(const std::string& name, const Vector4& value) const
{
	glUniform4fv(GetUniform(name), 1, &value.x);
}

void Shader::SetUniform(const std::string& name, const Matrix2x2& value) const
{
	glUniformMatrix2fv(GetUniform(name), 1, GL_TRUE, &value.Row0.x);
}

void Shader::SetUniform(const std::string& name, const Matrix3x3& value) const
{
	glUniformMatrix3fv(GetUniform(name), 1, GL_TRUE, &value.Row0.x);
}

void Shader::SetUniform(const std::string& name, const Matrix4x4& value) const
{
	glUniformMatrix4fv(GetUniform(name), 1, GL_TRUE, &value.Row0.x);
}

inline int32_t Shader::GetUniform(const std::string& name) const
{
	int32_t result = glGetUniformLocation(m_Handle, name.c_str());
	if (result == -1)
	{
		Log::LogWarning(std::string("Variable ").append(name).append(" doesn't exist in shader ").append(m_Name));
	}
	return result;
}



Shader::~Shader()
{
	glDeleteProgram(m_Handle);
}
