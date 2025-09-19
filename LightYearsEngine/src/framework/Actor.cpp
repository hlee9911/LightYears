#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld) noexcept
		: m_OwningWorld{ owningWorld },
		m_HasBegunPlay{ false }
	{

	}

	Actor::~Actor() noexcept
	{

	}

	void Actor::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor ticking at frame rate: %f", 1.0f / deltaTime);
	}
}
