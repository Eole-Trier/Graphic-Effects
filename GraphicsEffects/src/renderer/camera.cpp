#include "renderer/camera.hpp"
#include "core/debug/log.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Camera* Camera::Instance;

Camera::Camera(const float_t fov, const Vector2 screenSize, const float_t depthNear,
	const float_t depthFar, const Vector3& position, const Vector3& center)
	: Fov(fov), ScreenSize(screenSize), DepthNear(depthNear),
	  DepthFar(depthFar), Position(position), Center(center)
{
	m_Up = Vector3(0.f, 1.f, 0.f);
	m_Front = Vector3(0.f, 0.f, -1.f);

	MouseSensi = .001f;
	MovementSpeed = 2.5f;
	m_Yaw = -M_PI / 2;
	m_Pitch = 0.f;

	UpdateVectors();

	if (Instance == nullptr)
		Instance = this;
	else
		Log::LogWarning("Creating a camera even though one already exists");
}

void Camera::SendToShader(const Shader& shader)
{
	shader.Use();

	if (shader.HasVariable(ShaderVariables::VIEW_POS))
		shader.SetUniform("viewPos", Position);

	shader.Unuse();
}

void Camera::Update()
{
	Matrix4x4::View(
		Position, Position + m_Front, m_Up, m_View
	);

	Matrix4x4::Projection(
		Fov, ScreenSize.x / ScreenSize.y, DepthNear, DepthFar, m_Projection
	);

	CalculateProjView();
}

void Camera::CalculateView()
{
	Matrix4x4::View(
		Position, Position + m_Front, m_Up, m_View
	);

	CalculateProjView();
};

void Camera::CalculateProjection()
{
	Matrix4x4::Projection(
		Fov, ScreenSize.x / ScreenSize.y, DepthNear, DepthFar, m_Projection
	);

	CalculateProjView();
};

const Matrix4x4& Camera::GetProjView()
{
	return m_ProjView;
}

const Vector3& Camera::GetFront()
{
	return m_Front;
}

void Camera::CalculateProjView()
{
	Matrix4x4::Multiply(m_Projection, m_View, m_ProjView);
}

void Camera::UpdateVectors()
{
	m_Front = Vector3(
		std::cos(m_Yaw) * std::cos(m_Pitch),
		std::sin(m_Pitch),
		std::sin(m_Yaw) * std::cos(m_Pitch)
	).Normalize();

	m_Right = Vector3::CrossProduct(m_Front, Vector3(0.f, 1.f, 0.f)).Normalize();
	m_Up = Vector3::CrossProduct(m_Right, m_Front).Normalize();
}

void Camera::ProcessKeyboard(const CameraMovement movement, const float deltaTime)
{
	const float velocity = MovementSpeed * deltaTime;

	switch (movement)
	{
		case CameraMovement::FORWARD:
			Position += m_Front * velocity;
			break;

		case CameraMovement::BACKWARD:
			Position -= m_Front * velocity;
			break;

		case CameraMovement::LEFT:
			Position -= m_Right * velocity;
			break;

		case CameraMovement::RIGHT:
			Position += m_Right * velocity;
			break;

		default:
			__assume(false);
	}
}

void Camera::ProcessMouse(const float xOffset, const float yOffset)
{
	m_Yaw += xOffset * MouseSensi;
	m_Pitch += yOffset * MouseSensi;

	m_Pitch = std::clamp<float>(m_Pitch, -M_PI / 2.f, M_PI / 2.f);
	UpdateVectors();
}

void Camera::ProcessScroll(const float offset)
{
	Fov -= offset;
	Fov = std::clamp<float>(Fov, 0.01f, M_PI / 4.f);
}

