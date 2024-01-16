#include "core/application.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include "resources/model.hpp"
#include "resources/shader.hpp"
#include "resources/texture.hpp"

#include "renderer/camera.hpp"
#include "renderer/g_buffer.hpp"

#include "core/object.hpp"
#include "core/scene.hpp"

#include "core/debug/assert.hpp"
#include "core/debug/log.hpp"
#include "core/debug/file_logger.hpp"
#include "core/debug/console_logger.hpp"
#include "core/debug/fatal_logger.hpp"

#include "core/engine_ui.hpp"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

bool Application::m_FirstMouse;
float Application::m_LastMouseX;
float Application::m_LastMouseY;

bool Application::m_LookingWithCamera;

GLFWwindow* Application::m_Window;
float Application::m_DeltaTime;
ShaderStatus Application::m_shaderStatus;

void Application::ResizeCallback(GLFWwindow* window, int32_t width, int32_t height)
{
	Camera::Instance->ScreenSize = Vector2(width, height);
	glViewport(0, 0, width, height);
}

void Application::ErrorCallback(int32_t error, const char* const description)
{
    Log::LogFatal(std::string("GLFW error ").append(std::to_string(error)).append(" : ").append(description));
}

void Application::MouseCallback(GLFWwindow* window, double xPosIn, double yPosIn)
{
    const float xPos = static_cast<float>(xPosIn);
    const float yPos = static_cast<float>(yPosIn);

    if (m_FirstMouse)
    {
        m_LastMouseX = xPos;
        m_LastMouseY = yPos;
        m_FirstMouse = false;
    }

    const float xOffset = xPos - m_LastMouseX;
    const float yOffset = m_LastMouseY - yPos; // reversed since y-coordinates go from bottom to top
    m_LastMouseX = xPos;
    m_LastMouseY = yPos;

    if (!m_LookingWithCamera)
        return;

    Camera* const cam = Camera::Instance;
    cam->ProcessMouse(xOffset, yOffset);
}

void Application::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    Camera* const cam = Camera::Instance;
    cam->ProcessScroll(yOffset);
}


void Application::ProcessInput()
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(m_Window, true);
        return;
    }

    Camera* const cam = Camera::Instance;

    if (glfwGetKey(m_Window, GLFW_KEY_W))
        cam->ProcessKeyboard(CameraMovement::FORWARD, m_DeltaTime);

    if (glfwGetKey(m_Window, GLFW_KEY_S))
        cam->ProcessKeyboard(CameraMovement::BACKWARD, m_DeltaTime);

    if (glfwGetKey(m_Window, GLFW_KEY_A))
        cam->ProcessKeyboard(CameraMovement::LEFT, m_DeltaTime);

    if (glfwGetKey(m_Window, GLFW_KEY_D))
        cam->ProcessKeyboard(CameraMovement::RIGHT, m_DeltaTime);

    int32_t cState = glfwGetKey(m_Window, GLFW_KEY_C);
    if (cState == GLFW_PRESS)
        m_LookingWithCamera = true;
    else if (cState == GLFW_RELEASE)
        m_LookingWithCamera = false;

    glfwSetInputMode(m_Window, GLFW_CURSOR, m_LookingWithCamera ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void Application::SetupLogger()
{
    Log::Init();

    Log::AddLogger<ConsoleLogger>();
    Log::AddLogger(new FileLogger("log.txt"));
    Log::AddLogger(new FatalLogger("fatal_log.txt"));
}

void Application::SetupImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable viewports
    io.Fonts->AddFontDefault();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Application::PreLoop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Application::PostLoop()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    GLFWwindow* ctxBackup = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(ctxBackup);

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}


void Application::Init()
{
    m_shaderStatus = DEFFERED;

    m_FirstMouse = true;

    // Setup the logger first so that it can immediatly be used for glfw
    SetupLogger();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!glfwInit())
    {
        Log::LogFatal("Couldn't innitialize glfw");
    }

    glfwSetErrorCallback(ErrorCallback);

    m_Window = glfwCreateWindow(800, 600, "ModernGl", nullptr, nullptr);
    if (m_Window == nullptr)
    {
        glfwTerminate();
        Log::LogFatal("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_Window);

    glfwSetFramebufferSizeCallback(m_Window, ResizeCallback);
    glfwSetCursorPosCallback(m_Window, MouseCallback);
    glfwSetScrollCallback(m_Window, ScrollCallback);

    gladLoadGL();

    glfwSwapInterval(1); // Enable vsync

    SetupImgui();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
        {
            std::string msg = "OpenGL error : ";

            msg.append((char*)glGetString(source)).append((char*)glGetString(type)).append(message);

            Log::LogError(msg);
        }, nullptr);
}

void Application::MainLoop()
{
    Scene scene("Test scene");
    Texture* const tex = new Texture("assets/textures/viking_room.jpg");
    tex->Load();

    Model* const model = new Model("assets/models/viking_room.obj");
    model->Load();

    Shader* const gBufferShader = new Shader("g_buffer");
    gBufferShader->Load("shaders/g_buffer.vs", "shaders/g_buffer.fs");

    Shader* const deferredShader = new Shader("deferred");
    deferredShader->Load("shaders/deferred.vs", "shaders/deferred.fs");

    Shader* const toonShader = new Shader("tooned");
    toonShader->Load("shaders/toon.vs", "shaders/toon.fs");

    Shader* const goochShader = new Shader("gooched");
    goochShader->Load("shaders/gooch.vs", "shaders/gooch.fs");

    Object vikingRoom(gBufferShader, model, tex, Vector4(1.f, 1.f, 1.f, 1.0f), Vector3(0.f), Vector3(0, -M_PI / 2, -M_PI / 2), Vector3(1.f));
    vikingRoom.Name = "Viking sphere";
    scene.AddObject(vikingRoom);

    Object lightObj(nullptr, nullptr, nullptr, Vector4(0), Vector3(0.f, 2.f, 0.f), Vector3(0.f), Vector3(1.f));
    lightObj.Name = "Light";
    lightObj.AddComponent(new PointLight(&lightObj,
        Vector4(1.0f), Vector4(0.5f, 0.5f, 0.5f, 1.0f), Vector4(0.5f, 0.5f, 0.5f, 1.0f), 1.0f));
    scene.AddObject(lightObj);

    Camera camera(M_PI / 2.f, Vector2(800, 600), 0.1f, 100.f, Vector3(0.f, 0.f, 2.f), Vector3(0.f, 0.f, 0.f));

    GBuffer gBuffer;
    gBuffer.AddTarget(RenderTarget("Position pass", false, Vector4(0.f), GL_RGBA16F, GL_RGBA, GL_FLOAT));
    gBuffer.AddTarget(RenderTarget("Normal pass", false, Vector4(0.f), GL_RGBA16F, GL_RGBA, GL_FLOAT));
    gBuffer.AddTarget(RenderTarget("Specular pass", false, Vector4(0.f), GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE));
    gBuffer.FinishInit();

    float lastFrame = 0.f;
    float time = 0.f;

    int toonColorLevel = 1;

    

    while (!glfwWindowShouldClose(m_Window))
    {
        const float currentFrame = static_cast<float>(glfwGetTime());
        m_DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        PreLoop();
        ProcessInput();

        gBuffer.Begin();

        time += m_DeltaTime;

        const char* items[] = {"DEFFERED", "GOOCHED", "TOONED" };

        ImGui::Combo("Render status", (int*)&m_shaderStatus, items, IM_ARRAYSIZE(items));

        camera.Update();

        scene.Update();
        Shader* usedShader = deferredShader;

        if (m_shaderStatus == TOONED)
        {
            ImGui::SliderInt("toon color level", &toonColorLevel, 1, 100);
            toonShader->SetUniform("toon_color_levels", toonColorLevel);
            usedShader = toonShader;
        }
        else if (m_shaderStatus == GOOCHED)
        {
            usedShader = goochShader;
        }
        else if (m_shaderStatus == DEFFERED)
        {
            usedShader = deferredShader;
        }

        usedShader->SetUniform("gPosition", 0);
        usedShader->SetUniform("gNormal", 1);
        usedShader->SetUniform("gAlbedoSpec", 2);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        usedShader->Use();
        camera.SendToShader(*usedShader);
        scene.ApplyLights(*usedShader);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gBuffer.BindTextures();
        usedShader->Use();
        gBuffer.RenderQuad();
        gBuffer.End();

        EngineUi::DrawSceneGraph(scene);

        PostLoop();
    }

    delete tex;
    delete model;
    delete gBufferShader;
    delete deferredShader;
    delete toonShader;
    delete goochShader;
}

void Application::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    Log::Stop();
}
