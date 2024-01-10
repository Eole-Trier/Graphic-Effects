#include "core/object.hpp"
#include "renderer/camera.hpp"
#include <glad/glad.h>

std::vector<Object*> Object::m_Objects;

Object::Object(Shader* const shader, Model* const model, Texture* const texture)
	: m_Shader(shader), m_Model(model), m_Texture(texture), Transformation(*this)
{
	if (shader == nullptr || model == nullptr || texture == nullptr)
		m_Hidden = true;
	else
		m_Hidden = false;

	m_Objects.push_back(this);
	OnCreation();
}

Object::Object(Shader* const shader, Model* const model, Texture* const texture,
	const Vector3& position, const Vector3& rotation, const Vector3& scaling)
	: m_Shader(shader), m_Model(model), m_Texture(texture), Transformation(*this, position, rotation, scaling)
{
	if (shader == nullptr || model == nullptr || texture == nullptr)
		m_Hidden = true;
	else
		m_Hidden = false;

	m_Objects.push_back(this);
	OnCreation();
}

Object::~Object()
{
	for (size_t i = 0; i < m_Components.size(); i++)
		delete m_Components[i];
}

bool Object::HasParent() const
{
	return Transformation.HasParent();
}

bool Object::HasChildren() const
{
	return Transformation.HasChildren();
}

void Object::SetParent(Object* const parent)
{
	Transformation.SetParent(&parent->Transformation);
}

void Object::RemoveChildren(Object* const child)
{
	Transformation.RemoveChildren(&child->Transformation);
}

void Object::AddChildren(Object* const child)
{
	Transformation.AddChildren(&child->Transformation);
}


void Object::SetEnabled(bool value)
{
	m_Enabled = value;

	value ? OnEnable() : OnDisable();
}

void Object::SetHidden(bool value)
{
	m_Hidden = value;

	value ? OnDisable() : OnHide();
}

void Object::AddComponent(Component* const component)
{
	m_Components.push_back(component);
}

bool Object::HasShader() const
{
	return m_Shader != nullptr;
}

Shader& Object::GetShader()
{
	return *m_Shader;
}

void Object::Render()
{
	Transformation.UpdateTransformation();

	if (m_Hidden)
		return;

	OnPreRender();
	Camera* cam = Camera::Instance;

	Matrix4x4 mvp;
	const Matrix4x4& model = Transformation.GetGlobalTransform();
	Matrix4x4::Multiply(cam->GetProjView(), model, mvp);

	m_Texture->Use();
	m_Shader->Use();

	m_Shader->SetUniform("mvp", mvp);
	m_Shader->SetUniform("model", model);
	cam->SendToShader(*m_Shader);

	m_Shader->Use();

	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(4);

	m_Model->Render();
        
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	m_Model->Render();

	OnPostRender();
}

void Object::OnGui()
{
	for (Component* const c : m_Components)
	{
		ImGui::PushID(c);
		
		ImGui::Separator();
		ImGui::Text("%s", typeid(*c).name());
		c->OnGui();
		ImGui::PopID();
	}
}
