#include "core/transform.hpp"
#include "core/object.hpp"

Transform::Transform(Object& owner)
	: m_Owner(owner)
{
	Position = Vector3(0.f);
	Rotation = Vector3(0.f);
	Scaling = Vector3(1.f);

	UpdateTransformation();
	m_Parent = nullptr;
}

Transform::Transform(Object& owner, const Vector3& position, const Vector3& rotation, const Vector3& scaling)
	: m_Owner(owner), Position(position), Rotation(rotation), Scaling(scaling)
{
	UpdateTransformation();
	m_Parent = nullptr;
}

Transform::Transform(Object& owner, const Vector3& position, const Vector3& rotation, const Vector3& scaling, Transform* const parent)
	: m_Owner(owner), Position(position), Rotation(rotation), Scaling(scaling), m_Parent(parent)
{
	UpdateTransformation();
}

Transform::~Transform()
{
	/*
	for (Transform* child : m_Children)
		delete child;
	*/
	// FIXME fix the bad way i'm handling memory
}

void Transform::SetParent(Transform* const parent)
{
	if (m_Parent != nullptr)
		m_Parent->RemoveChildren(this);

	m_Parent = parent;
	parent->AddChildren(this);
}

void Transform::RemoveChildren(Transform* const child)
{
	std::erase(m_Children, child);
}

void Transform::AddChildren(Transform* const child)
{
	m_Children.push_back(child);
}

void Transform::UpdateTransformation()
{
	Matrix4x4::TRS(Position, Rotation, Scaling, m_LocalTrs);

	if (m_Parent != nullptr)
		Matrix4x4::Multiply(m_Parent->m_GlobalTrs, m_LocalTrs, m_GlobalTrs);
	else
		m_GlobalTrs = m_LocalTrs;
}

bool Transform::HasParent() const
{
	return m_Parent != nullptr;
}

bool Transform::HasChildren() const
{
	return m_Children.size() != 0;
}

const Matrix4x4& Transform::GetGlobalTransform() const
{
	return m_GlobalTrs;
}

Object& Transform::GetOwner() const
{
	return m_Owner;
}

const std::vector<Transform*>& Transform::GetChildren() const
{
	return m_Children;
}
