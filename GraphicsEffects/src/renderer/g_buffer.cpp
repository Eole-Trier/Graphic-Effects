#include "renderer/g_buffer.hpp"
#include "renderer/camera.hpp"

#include "core/debug/log.hpp"

GBuffer::GBuffer()
{
	glGenFramebuffers(1, &m_Fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo);

	CreateDepthBuffer();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Log::LogError("G-buffer couldn't be created");
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

GBuffer::~GBuffer()
{
	glDeleteFramebuffers(1, &m_Fbo);

	glDeleteTextures(1, &m_DepthBuffer);
}

void GBuffer::AddTarget(RenderTarget target)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_RenderTargets.size(), GL_TEXTURE_2D, target.GetTextureId(), 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	m_RenderTargets.push_back(target);
}

void GBuffer::FinishInit()
{
	const size_t size = m_RenderTargets.size();
	std::vector<GLenum> drawBuffers(size);

	for (size_t i = 0; i < size; i++)
		drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i,

	glDrawBuffers(size, &drawBuffers[0]);
}

void GBuffer::Begin()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo);

	for (size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		m_RenderTargets[i].Begin();
	}
}

void GBuffer::End()
{
	for (size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		m_RenderTargets[i].End();
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::CreateDepthBuffer()
{
	const Vector2 screenSize = Camera::Instance->ScreenSize;

	glGenTextures(1, &m_DepthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, screenSize.x, screenSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer, 0);
}
