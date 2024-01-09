#include "renderer/render_target.hpp"
#include "renderer/camera.hpp"

RenderTarget::RenderTarget()
{
	m_RenderTarget = 0;
	m_DepthBuffer = 0;
	m_ClearOnBegin = false;
	m_ClearColor = Vector4(0.f);
	m_InternalFormat = GL_BYTE;
	m_Format = GL_BYTE;
}

RenderTarget::RenderTarget(const bool clearOnBegin, const Vector4 clearColor, const GLenum internalFormat, const GLenum format, const GLenum type)
	: m_ClearOnBegin(clearOnBegin), m_ClearColor(clearColor), m_InternalFormat(internalFormat), m_Format(format), m_Type(type)
{
	Vector2 screenSize = Camera::Instance->ScreenSize;

	glGenTextures(1, &m_RenderTarget);
	glBindTexture(GL_TEXTURE_2D, m_RenderTarget);

	glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, screenSize.x, screenSize.y, 0, m_Format, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderTarget::Begin()
{
	if (m_ClearOnBegin)
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void RenderTarget::End()
{
}

GLuint RenderTarget::GetTextureId() const
{
	return m_RenderTarget;
}
