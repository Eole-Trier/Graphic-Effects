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

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo);
	glDrawBuffers(size, &drawBuffers[0]);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void GBuffer::Begin()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GBuffer::End()
{
	for (size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		m_RenderTargets[i].End();
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
void GBuffer::OnGui()
{
	for (size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		m_RenderTargets[i].OnGui();
	}
}

void GBuffer::RenderQuad()
{
	if (m_QuadVao == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &m_QuadVao);
		glGenBuffers(1, &m_QuadVbo);
		glBindVertexArray(m_QuadVao);
		glBindBuffer(GL_ARRAY_BUFFER, m_QuadVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	glBindVertexArray(m_QuadVao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void GBuffer::BindTextures()
{
	for (size_t i = 0; i < m_RenderTargets.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		m_RenderTargets[i].Begin();
	}
}

void GBuffer::CreateDepthBuffer()
{
	const Vector2 screenSize = Camera::Instance->ScreenSize;
	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.x, screenSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
}
