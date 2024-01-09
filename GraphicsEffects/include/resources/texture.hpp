#pragma once

#include "resources/resource.hpp"

class Texture : public Resource
{
private:
	uint32_t m_Handle;

public:
	Texture(const std::string& name) : Resource(name) {}
	~Texture() override;

	void Load() override;

	void Use();
};

