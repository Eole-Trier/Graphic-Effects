#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Application
{
private:
	static bool m_FirstMouse;
	static float m_LastMouseX;
	static float m_LastMouseY;

	static bool m_LookingWithCamera;

	static GLFWwindow* m_Window;
	static float m_DeltaTime;

	static void ResizeCallback(GLFWwindow* window, int32_t width, int32_t height);
	static void ErrorCallback(int32_t error, const char* const description);
	static void MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	static void ProcessInput();
	
	static void SetupLogger();
	static void SetupImgui();
	static void PreLoop();
	static void PostLoop();

public:
	static void Init();
	static void MainLoop();
	static void Shutdown();
};
