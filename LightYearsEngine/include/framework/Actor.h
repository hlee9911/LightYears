#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <string>

#include "framework/Core.h"
#include "framework/Object.h"

class b2Body; // Forward declaration of Box2D body

namespace ly
{
	class World; // Forward declaration of World class
	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "") noexcept;
		virtual ~Actor() noexcept;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		virtual void Destroy() override;

		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

		// Transformations
		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot); // in degrees
		void SetActorScale(const sf::Vector2f& newScale);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt); // in degrees
		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const; // in degrees
		sf::Vector2f GetActorScale() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const noexcept;

		const World* GetWorld() const noexcept { return m_OwningWorld; }
		World* GetWorld() noexcept { return m_OwningWorld; }

		bool IsActorOutOfWindowsBounds(float allowance = 10.0f) const;

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* otherActor);
		virtual void OnActorEndOverlap(Actor* otherActor);

		static uint8 GetNeutralTeamID() noexcept { return neutralTeamID; }

		void SetTeamID(uint8 newTeamID) noexcept { m_TeamID = newTeamID; }

		uint8 GetTeamID() const noexcept { return m_TeamID; }
		bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float damageAmt);

		sf::Sprite& GetSprite() noexcept { return m_Sprite; }
		const sf::Sprite& GetSprite() const noexcept { return m_Sprite; }

	private:
		void CenterPivot();

		void InitializePhysics();
		void UnInitializePhysics();

		void UpdatePhysicsBodyTransform();

	private:
		World* m_OwningWorld;
		bool m_HasBegunPlay;
	
		sf::Sprite m_Sprite;
		shared<sf::Texture> m_Texture;

		b2Body* m_PhysicsBody; // Box2D body pointer
		bool m_PhysicsEnabled;

		uint8 m_TeamID;

		constexpr static uint8 neutralTeamID = 255;
	};
}

#endif // ACTOR_H
