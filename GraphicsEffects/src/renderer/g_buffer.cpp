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

void GBuffer::AddTarget(RenderTarget target)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_RenderTargets.size(), GL_TEXTURE_2D, target.GetTextureId(), 0);

	m_RenderTargets.push_back(target);
}

void GBuffer::CreateDepthBuffer()
{
	const Vector2 screenSize = Camera::Instance->ScreenSize;

	glGenTextures(1, &m_DepthBuffer);
	glBindTexture(GL_TEXTURE_2D, m_DepthBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, screenSize.x, screenSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer, 0);
}
