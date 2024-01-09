#pragma once

#include "core/maths/matrix4x4.h"
#include "resources/shader.hpp"

enum class CameraMovement : uint32_t
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
private:
	Matrix4x4 m_View;
	Matrix4x4 m_Projection;
	Matrix4x4 m_ProjView;

	Vector3 m_Front;
	Vector3 m_Right;
	Vector3 m_Up;

	float m_Yaw;
	float m_Pitch;

	float m_Zoom;

	void CalculateProjView();
	void UpdateVectors();

public:
	static Camera* Instance;

	float MovementSpeed;
	float MouseSensi;

	float_t Fov;
	Vector2 ScreenSize;
	float_t DepthNear;
	float_t DepthFar;

	Vector3 Position;
	Vector3 Center;

	Camera(const float_t fov, const Vector2 screenSize, const float_t depthNear,
		const float_t depthFar, const Vector3& position, const Vector3& center);

	void SendToShader(const Shader& shader);
	void Update();

	void CalculateView();
	void CalculateProjection();
	const Matrix4x4& GetProjView();
	const Vector3& GetFront();

	void ProcessKeyboard(const CameraMovement movement, const float deltaTime);
	void ProcessMouse(const float xOffset, const float yOffset);
	void ProcessScroll(const float offset);
};
