#pragma once

#include "core/scene.hpp"

class EngineUi
{
private:
	static Object* m_SelectedObject;

	static void DrawSceneGraph_Object(Object& obj);
	static void DrawSelectedObject();

public:
	static void DrawSceneGraph(Scene& scene);
};
