#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
	unsigned int Object::s_UniqueIDCounter = 0;

	Object::Object() noexcept
		: m_IsPendingDestroy{ false },
		m_UniqueID{ GetNexAvailableID() }
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
		onDestroyed.Broadcast(this); // notify everyone that this object is being destroyed
		m_IsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef() noexcept
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const noexcept
	{
		return weak_from_this();
	}

	unsigned int Object::GetNexAvailableID() noexcept
	{
		return s_UniqueIDCounter++;
	}
}
