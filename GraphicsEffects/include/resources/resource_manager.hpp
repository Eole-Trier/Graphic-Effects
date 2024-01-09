#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "resources/resource.hpp"
#include "resources/texture.hpp"
#include "core/debug/log.hpp"

template<class T>
concept ResourceClass = std::is_base_of<Resource, T>::value;

class ResourceManager
{
private:
	static std::unordered_map<std::string, Resource*> m_Resources;

public:
	ResourceManager() = delete;

	template<ResourceClass T>
	_NODISCARD static T* Create(const std::string& name)
	{
		T* const res = new T(name);

		// Check aloready exists
		auto&& result = m_Resources.try_emplace(name, res);
		if (!result.second)
		{
			// Delete and replace
			delete result.first->second;
			m_Resources.emplace(name, res);
		}

		return res;
	}

	template<ResourceClass T>
	_NODISCARD static T* Get(const std::string& name)
	{
		auto search = m_Resources.find(name);

		if (search == m_Resources.end())
		{
			Log::LogWarning(std::string("Couldn't find the resource named : ").append(name));
			return nullptr;
		}

		return static_cast<T*>(search->second);
	}

	static void Delete(const std::string& name);

	static void DeleteAll();
};
