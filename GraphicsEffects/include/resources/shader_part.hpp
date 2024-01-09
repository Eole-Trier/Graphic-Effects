#pragma once

#include <filesystem>
#include <string>

#include "resources/resource.hpp"
#include "resources/shader.hpp"

enum class ShaderType : uint8_t
{
	VERTEX,
	GEOMETRY,
	FRAGMENT,
	COMPUTE
};

class ShaderPart : Resource
{
private:
	ShaderType m_Type;
	uint32_t m_Handle;

	static uint32_t GetShaderTypeEnum(const ShaderType type);

public:
	ShaderPart(const std::string& name) : Resource(name) {}
	ShaderPart(const std::string& name, const ShaderType type, const std::filesystem::path& path);

	~ShaderPart() override;

	friend class Shader;
};
