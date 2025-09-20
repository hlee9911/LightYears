#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	Object::Object() noexcept
		: m_IsPendingDestroy{ false }
	{

	}

	Object::~Object() noexcept
	{
		LOG("Object Destroyed");
	}

	// we will not actually destroy the object here, just mark it for destruction
	// and we will actually destroy at the next tick of the world
	void Object::Destroy()
	{
		m_IsPendingDestroy = true;
	}
}
