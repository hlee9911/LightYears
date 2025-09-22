#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication() noexcept
		: Application{ 600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		m_ActorToDestroy = newWorld.lock()->SpawnActor<Actor>();
		m_ActorToDestroy.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		m_ActorToDestroy.lock()->SetActorLocation(sf::Vector2f{ 300.0f, 490.0f });
		m_ActorToDestroy.lock()->SetActorRotation(90.0f);
		m_Counter = 0.0f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		//m_Counter += deltaTime;
		//if (m_Counter >= 2.0f)
		//{
		//	if (!m_ActorToDestroy.expired())
		//	{
		//		m_ActorToDestroy.lock()->Destroy();
		//		// LOG("Actor marked for destruction");
		//	}
		//}
	}
}
