#include "core/object.hpp"
#include "renderer/camera.hpp"
#include <glad/glad.h>

std::vector<Object*> Object::m_Objects;
Shader* Object::m_OutlineShader;


Object::Object(Shader* const shader, Model* const model, Texture* const texture, const Vector4 outlineColor)
	: m_Shader(shader), m_Model(model), m_Texture(texture), Transformation(*this), m_OutlineColor(outlineColor)
{
	if (shader == nullptr || model == nullptr || texture == nullptr)
		m_Hidden = true;
	else
		m_Hidden = false;

	m_Objects.push_back(this);
	OnCreation();
}

Object::Object(Shader* const shader, Model* const model, Texture* const texture, const Vector4 outlineColor,
	const Vector3& position, const Vector3& rotation, const Vector3& scaling)
	: m_Shader(shader), m_Model(model), m_Texture(texture), m_OutlineColor(outlineColor), Transformation(*this, position, rotation, scaling)
{
	m_Components.clear();
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

	glActiveTexture(GL_TEXTURE0);
	m_Texture->Use();
	m_Shader->Use();

	m_Shader->SetUniform("mvp", mvp);
	m_Shader->SetUniform("model", model);
	cam->SendToShader(*m_Shader);

	m_Shader->Use();
	
	if (Outlined)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
	}
	
	m_Model->Render();

	if (Outlined)
	{
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);

		m_OutlineShader->Use();
		m_OutlineShader->SetUniform("Color", m_OutlineColor);
		Vector3 scale = Transformation.Scaling;
		Transformation.Scaling *= 1.1f;
		Transformation.UpdateTransformation();
		const Matrix4x4& model = Transformation.GetGlobalTransform();
		Matrix4x4::Multiply(cam->GetProjView(), model, mvp);
		m_OutlineShader->SetUniform("mvp", mvp);
		m_Model->Render();
		Transformation.Scaling = scale;

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

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
