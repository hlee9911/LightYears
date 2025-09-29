#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 900.0f, float damage = 10.0f) noexcept;

		void SetSpeed(float speed) noexcept { m_Speed = speed; }
		void SetDamage(float damage) noexcept { m_Damage = damage; }
		float GetDamage() const noexcept { return m_Damage; }

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;
	
	private:
		void Move(float deltaTime);

		virtual void OnActorBeginOverlap(Actor* otherActor) override;

	private:
		Actor* m_Owner;
		float m_Speed;
		float m_Damage;
	};
}

#endif // BULLET_H
