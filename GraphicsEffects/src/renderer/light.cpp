#include "renderer/light.hpp"
#include "core/scene.hpp"

#include "core/object.hpp"
#include "resources/shader.hpp"

#include "ImGui/imgui.h"

Light::Light(Object* const obj, const Vector4& diffuse, const Vector4& ambient, const Vector4& specular, const float radius)
	: Component(obj), Diffuse(diffuse), Ambient(ambient), Specular(specular), Radius(radius)
{
}

void Light::OnGui()
{
	ImGui::SliderFloat4("Ambient", &Ambient.x, 0.f, 1.f);
	ImGui::SliderFloat4("Diffuse", &Diffuse.x, 0.f, 1.f);
	ImGui::SliderFloat4("Specular", &Specular.x, 0.f, 1.f);
	ImGui::SliderFloat("Radius", &Radius, 0.f, 100.f);
}
