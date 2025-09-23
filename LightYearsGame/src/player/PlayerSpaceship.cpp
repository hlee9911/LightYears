#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"

#include <SFML/System.hpp>

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* owningWorld, const std::string& texturePath) noexcept
		: Spaceship{ owningWorld, texturePath },
		m_MoveInput{},
		m_Speed{ 500.0f }
	{
		
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		HandleInput();
		ConsumeInput(deltaTime);
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
		ClampInputOnEdge();
		NormalizeInput();
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
