#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
	World::World(Application* owningApp) noexcept
		: m_OwningApp{ owningApp },
		m_HasBegunPlay{ false },
		m_Actors{},
		m_PendingActors{}
	{

	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (auto actor : m_PendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		m_PendingActors.clear();

		for (auto& actor : m_Actors)
		{
			actor->Tick(deltaTime);
		}

		Tick(deltaTime);
	}

	World::~World() noexcept
	{

	}

	void World::BeginPlay()
	{
		LOG("Begun play");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Ticking at frame rate: %f", 1.0f / deltaTime);
	}
}
