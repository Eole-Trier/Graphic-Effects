#include "core/component.hpp"

#include "core/object.hpp"

Component::Component(Object* const obj)
	: Owner(obj)
{
}
