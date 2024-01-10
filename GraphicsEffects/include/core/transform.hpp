#pragma once

#include <vector>

#include "core/maths/vector3.h"
#include "core/maths/matrix4x4.h"

class Scene;

class Object;

class Transform
{
private:
	Object& m_Owner;
	std::vector<Transform*> m_Children;
	Transform* m_Parent;

	Matrix4x4 m_LocalTrs;
	Matrix4x4 m_GlobalTrs;

public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scaling;

	Transform() = delete;
	Transform(Object& owner);
	Transform(Object& owner, const Vector3& position, const Vector3& rotation, const Vector3& scaling);
	Transform(Object& owner, const Vector3& position, const Vector3& rotation, const Vector3& scaling, Transform* const parent);

	~Transform();

	void UpdateTransformation();

	bool HasParent() const;
	bool HasChildren() const;
	void SetParent(Transform* const parent);
	void RemoveChildren(Transform* const child);
	void AddChildren(Transform* const child);

	const Matrix4x4& GetGlobalTransform() const;
	Object& GetOwner() const;
	const std::vector<Transform*>& GetChildren() const;
};
