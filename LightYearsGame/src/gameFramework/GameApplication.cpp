#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication() noexcept
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		m_ActorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		m_Counter = 0.0f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		m_Counter += deltaTime;
		if (m_Counter >= 2.0f)
		{
			if (!m_ActorToDestroy.expired())
			{
				m_ActorToDestroy.lock()->Destroy();
				LOG("Actor marked for destruction");
			}
		}
	}
}
