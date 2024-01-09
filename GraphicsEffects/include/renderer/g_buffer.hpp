#pragma once

#include <vector>
#include "glad/glad.h"
#include "renderer/render_target.hpp"

class GBuffer
{
public:
	GBuffer();

	void AddTarget(RenderTarget target);

private:
	GLuint m_Fbo;
	GLuint m_DepthBuffer;
	std::vector<RenderTarget> m_RenderTargets;

	void CreateDepthBuffer();
};
