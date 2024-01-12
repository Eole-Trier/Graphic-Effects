#pragma once

#include <vector>
#include "glad/glad.h"
#include "renderer/render_target.hpp"

class GBuffer
{
public:
	GBuffer();
	~GBuffer();

	void AddTarget(RenderTarget target);
	void FinishInit();

	void Begin();
	void End();

	void OnGui();
	void RenderQuad();

	void BindTextures();

private:
	GLuint m_Fbo;
	GLuint m_QuadVao;
	GLuint m_QuadVbo;
	GLuint m_DepthBuffer;
	std::vector<RenderTarget> m_RenderTargets;

	void CreateDepthBuffer();
	
};
