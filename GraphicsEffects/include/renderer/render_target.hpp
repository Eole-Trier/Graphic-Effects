#pragma once

#include <stdint.h>
#include "glad/glad.h"
#include "core/maths/vector4.h"

class RenderTarget
{
public:
	RenderTarget();
	RenderTarget(const bool clearOnBegin, const Vector4 clearColor, const GLenum internalFormat, const GLenum format, const GLenum type);

	void Begin();
	void End();

	GLuint GetTextureId() const;

private:
	GLuint m_RenderTarget;
	GLuint m_DepthBuffer;
	bool m_ClearOnBegin;
	Vector4 m_ClearColor;

	GLenum m_InternalFormat;
	GLenum m_Format;
	GLenum m_Type;
};
