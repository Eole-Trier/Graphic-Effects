#pragma once

#include <functional>

#include "core/maths/matrix4x4.h"
#include "core/maths/vector3.h"

#include "resources/shader.hpp"
#include "resources/texture.hpp"
#include "resources/model.hpp"

#include "core/component.hpp"

#include "core/transform.hpp"

template<class T>
concept ObjectClass = std::is_base_of<Object, T>::value;

class Object
{
#pragma region Static
private:
	static std::vector<Object*> m_Objects;

public:
	template<ObjectClass T>
	static T* FindByName(const std::string& name)
	{
		for (Object* obj : m_Objects)
		{
			if (obj->Name == name)
				return dynamic_cast<T*>(obj);
		}

		return nullptr;
	}

	template<ObjectClass T>
	static T* FindByType()
	{
		for (Object* obj : m_Objects)
		{
			if (dynamic_cast<T*>(obj))
				return obj;
		}

		return nullptr;
	}

	template<ObjectClass T>
	static T* FindByPredicate(std::function<bool (Object*)>& predicate)
	{
		for (Object* obj : m_Objects)
		{
			if (predicate(obj))
				return obj;
		}

		return nullptr;
	}
#pragma endregion

private:
	Shader* m_Shader;
	Model* m_Model;
	Texture* m_Texture;

	bool m_Enabled;
	bool m_Hidden;

	std::vector<Component*> m_Components;

public:
	Transform Transformation;
	std::string Name;

	Object(Shader* const shader, Model* const model, Texture* const texture);
	Object(Shader* const shader, Model* const model, Texture* const texture,
		const Vector3& position, const Vector3& rotation, const Vector3& scaling);

	~Object();

	bool HasParent() const;
	bool HasChildren() const;
	void SetParent(Object* const parent);
	void RemoveChildren(Object* const child);
	void AddChildren(Object* const child);

	void SetEnabled(bool value);
	void SetHidden(bool value);

	void AddComponent(Component* const component);

	bool HasShader() const;
	Shader& GetShader();

	void Render();

	/// <summary>
	/// Called when the object is created
	/// </summary>
	virtual void OnCreation() {}

	/// <summary>
	/// Called every frame
	/// </summary>
	virtual void OnUpdate() {}

	/// <summary>
	/// Called right before the object is rendered
	/// </summary>
	virtual void OnPreRender() {}

	/// <summary>
	/// Called right after the object is rendered
	/// </summary>
	virtual void OnPostRender() {}

	/// <summary>
	/// Called when the object is enabled
	/// </summary>
	virtual void OnEnable() {}

	/// <summary>
	/// Called when the object is disabled
	/// </summary>
	virtual void OnDisable() {}

	/// <summary>
	/// Called when the object gets hidden
	/// </summary>
	virtual void OnHide() {}

	/// <summary>
	/// Called when the object gets un-hidden
	/// </summary>
	virtual void OnDisplay() {}

	/// <summary>
	/// Called during the gui window of the object
	/// </summary>
	virtual void OnGui();
};
