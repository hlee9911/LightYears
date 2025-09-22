#include "player/PlayerSpaceship.h"

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
	}

	// Consume the input and apply movement
	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_MoveInput * GetSpeed());
		m_MoveInput.x = m_MoveInput.y = 0.0f;
	}
}
