#include "resources/resource_manager.hpp"

std::unordered_map<std::string, Resource*> ResourceManager::m_Resources;

void ResourceManager::Delete(const std::string& name)
{
	m_Resources.erase(name);
}

void ResourceManager::DeleteAll()
{
	for (std::pair<const std::string, Resource*>& it : m_Resources)
		delete it.second;

	m_Resources.clear();
}
