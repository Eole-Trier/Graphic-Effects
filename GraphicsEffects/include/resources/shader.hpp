#pragma once

#include <filesystem>
#include "resources/resource.hpp"

#include "core/maths/vector2.h"
#include "core/maths/vector3.h"
#include "core/maths/vector4.h"
#include "core/maths/matrix2x2.h"
#include "core/maths/matrix3x3.h"
#include "core/maths/matrix4x4.h"

enum class ShaderVariables : uint32_t
{
	NONE = 0 << 0,
	VIEW_POS = 1 << 0,
};

ShaderVariables operator|(ShaderVariables left, ShaderVariables right);

ShaderVariables operator|=(ShaderVariables left, ShaderVariables right);

bool operator&(ShaderVariables left, ShaderVariables right);

class Shader : public Resource
{
private:
	uint32_t m_Handle;
	ShaderVariables m_Variables;

	inline int32_t GetUniform(const std::string& name) const;

public:
	Shader(const std::string& name) : Resource(name) {}
	~Shader() override;

	void Load(const std::filesystem::path& vertex, const std::filesystem::path& fragment);

	void Use() const;
	void Unuse() const;

	bool HasVariable(const ShaderVariables variable) const;

	void SetUniform(const std::string& name, const bool value) const;
	void SetUniform(const std::string& name, const int32_t value) const;
	void SetUniform(const std::string& name, const float_t value) const;
	void SetUniform(const std::string& name, const Vector2 value) const;
	void SetUniform(const std::string& name, const Vector3& value) const;
	void SetUniform(const std::string& name, const Vector4& value) const;
	void SetUniform(const std::string& name, const Matrix2x2& value) const;
	void SetUniform(const std::string& name, const Matrix3x3& value) const;
	void SetUniform(const std::string& name, const Matrix4x4& value) const;
};

