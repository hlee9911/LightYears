#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

#include <SFML/System.hpp>

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& texturePath) noexcept
		: Spaceship{ owningWorld, texturePath },
		m_MoveInput{},
		m_Speed{ 500.0f },
		m_Shooter{ new BulletShooter{this, 0.1f, {50.0f, 0.0f}} }
	{
		SetTeamID(1); // Player team ID is 1
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (m_Shooter)
		{
			m_Shooter->Shoot();
		}
	}

	void PlayerSpaceship::SetShooter(unique<Shooter>&& newShooter)
	{
		if (m_Shooter && typeid(*m_Shooter.get()) == typeid(*newShooter.get()))
		{
			m_Shooter->IncrementLevel();
			return;
		}

		m_Shooter = std::move(newShooter);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_MoveInput.y = -1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_MoveInput.y = 1.0f;
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_MoveInput.x = -1.0f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_MoveInput.x = 1.0f;
		}

		// if left shift is held, slow down the speed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) &&
		    (m_MoveInput.x != 0.0f || m_MoveInput.y != 0.0f))
		{
			m_Speed = 200.0f;
		}
		else
		{
			m_Speed = 500.0f;
		}

		ClampInputOnEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::NormalizeInput()
	{
		NormalizeVector(m_MoveInput);
		// LOG("Move input is now: %f, %f", m_MoveInput.x, m_MoveInput.y);
	}

	void PlayerSpaceship::ClampInputOnEdge()
	{
		sf::Vector2f actorLocation = GetActorLocation();
		// if the actor is at left edge and trying to move left, clamp it
		if (actorLocation.x <= 0.0f && m_MoveInput.x == -1.0f)
		{
			m_MoveInput.x = 0.0f;
		}
		// if the actor is at right edge and trying to move right, clamp it
		if (actorLocation.x >= GetWindowSize().x && m_MoveInput.x == 1.0f)
		{
			m_MoveInput.x = 0.0f;
		}
		// if the actor is at top edge and trying to move up, clamp it
		if (actorLocation.y <= 0.0f && m_MoveInput.y == -1.0f)
		{
			m_MoveInput.y = 0.0f;
		}
		// if the actor is at bottom edge and trying to move down, clamp it
		if (actorLocation.y >= GetWindowSize().y && m_MoveInput.y == 1.0f)
		{
			m_MoveInput.y = 0.0f;
		}
	}

	// Consume the input and apply movement
	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_MoveInput * GetSpeed());
		m_MoveInput.x = m_MoveInput.y = 0.0f;
	}
}
