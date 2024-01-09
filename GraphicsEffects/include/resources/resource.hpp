#pragma once

#include <string>

class Resource
{
protected:
	const std::string m_Name;

public:
	Resource(const std::string& name) : m_Name(name) {}
	virtual ~Resource() {}

	virtual void Load() {};
};
