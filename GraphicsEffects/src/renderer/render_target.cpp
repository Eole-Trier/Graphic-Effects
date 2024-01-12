#include "renderer/render_target.hpp"
#include "renderer/camera.hpp"
#include "ImGui/imgui.h"

RenderTarget::RenderTarget()
{
	m_TextureBuffer = 0;
	m_DepthBuffer = 0;
	m_ClearOnBegin = false;
	m_ClearColor = Vector4(0.f);
	m_InternalFormat = GL_BYTE;
	m_Format = GL_BYTE;
	m_Type = GL_BYTE;
}

RenderTarget::RenderTarget(const std::string&& name, const bool clearOnBegin, const Vector4 clearColor, const GLenum internalFormat, const GLenum format, const GLenum type)
	: m_Name(name), m_ClearOnBegin(clearOnBegin), m_ClearColor(clearColor), m_InternalFormat(internalFormat), m_Format(format), m_Type(type)
{
	Vector2 screenSize = Camera::Instance->ScreenSize;

	glGenTextures(1, &m_TextureBuffer);
	glBindTexture(GL_TEXTURE_2D, m_TextureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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
	
	glBindTexture(GL_TEXTURE_2D, m_TextureBuffer);
}

void RenderTarget::End()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint RenderTarget::GetTextureId() const
{
	return m_TextureBuffer;
}

void RenderTarget::OnGui()
{
	ImGui::Begin(m_Name.c_str());

	Vector2 size = Camera::Instance->ScreenSize;

	ImGui::Image((ImTextureID)m_TextureBuffer, ImVec2(size.x, size.y));

	ImGui::End();
}
