#pragma once
#ifndef PLAYERSPACESHIP_H
#define PLAYERSPACESHIP_H

#include "spaceship/Spaceship.h"
#include "framework/TimerManager.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png") noexcept;
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

		void SetSpeed(float newSpeed) noexcept { m_Speed = newSpeed; }
		float GetSpeed() const noexcept { return m_Speed; }

		virtual void Shoot() override;

		void SetShooter(unique<Shooter>&& newShooter);

		virtual void ApplyDamage(float damageAmt) override;

	private:
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnEdge();
		void ConsumeInput(float deltaTime);
		void StopInvulnerable();
		void UpdateInvulnerable(float deltaTime);

	private:
		sf::Vector2f m_MoveInput;
		float m_Speed;

		unique<Shooter> m_Shooter;

		// Invulnerability after respawn
		float m_InvulnerableDuration;
		TimerHandle m_InvulnerableTimerHandle;
		bool m_IsInvulnerable;

		float m_InvulnerableBlinkInterval;
		float m_InvulnerableBlinkTimer;
		float m_InvulnerableBlinkDir; // reflashing to a darker color or normal color
	};
}

#endif // PLAYERSPACESHIP_H
