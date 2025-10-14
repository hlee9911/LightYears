#pragma once
#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "spaceship/Spaceship.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png") noexcept;
		virtual void Tick(float deltaTime) override;

		void SetSpeed(float newSpeed) noexcept { m_Speed = newSpeed; }
		float GetSpeed() const noexcept { return m_Speed; }

		virtual void Shoot() override;

	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);
	
	private:
		sf::Vector2f m_MoveInput;
		float m_Speed;

		unique<Shooter> m_Shooter;
	};
}

#endif // PLAYERSPACESHIP_H
