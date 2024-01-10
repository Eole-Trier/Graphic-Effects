#pragma once

class Object;

class Component
{
public:
	Object* const Owner;

	Component() = delete;
	Component(Object* const obj);

	virtual ~Component() {}

	virtual void OnGui() = 0;
};
