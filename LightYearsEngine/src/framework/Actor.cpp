#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath) noexcept
		: m_OwningWorld{ owningWorld },
		m_HasBegunPlay{ false },
		m_Sprite{},
		m_Texture{},
		m_PhysicsBody{ nullptr },
		m_PhysicsEnabled{ false },
		m_TeamID{ GetNeutralTeamID() }
	{
		SetTexture(texturePath);
	}

	Actor::~Actor() noexcept
	{
		LOG("Actor Destroyed");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingDestroy()) return;

		Tick(deltaTime);
	}

	void Actor::BeginPlay()
	{
		// LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		// LOG("Actor ticking at frame rate: %f", 1.0f / deltaTime);
	}

	void Actor::Destroy()
	{
		UnInitializePhysics(); // clean up physics body first
		onActorDestroyed.Broadcast(this);
		Object::Destroy();
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_Texture = AssetManager::Get().LoadTexture(texturePath);
		if (!m_Texture) return;
		m_Sprite.setTexture(*m_Texture);

		int textureWidth = m_Texture->getSize().x;
		int textureHeight = m_Texture->getSize().y;
		// Set the texture rectangle to match the texture size
		m_Sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy()) return;

		window.draw(m_Sprite);
	}

	// Transformations

	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		m_Sprite.setPosition(newLoc);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(float newRot)
	{
		m_Sprite.setRotation(newRot);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorScale(const sf::Vector2f& newScale)
	{
		m_Sprite.setScale(newScale);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return m_Sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return m_Sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorScale() const
	{
		return m_Sprite.getScale();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation() + 270.0f);
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const noexcept
	{
		return m_OwningWorld->GetWorldSize();
	}

	bool Actor::IsActorOutOfWindowsBounds(float allowance) const
	{
		float windowWidth = GetWorld()->GetWorldSize().x;
		float windowHeight = GetWorld()->GetWorldSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if (actorPos.x < -width - allowance || actorPos.x > windowWidth + width + allowance ||
			actorPos.y < -height - allowance || actorPos.y > windowHeight + height + allowance)
		{
			return true;
		}
		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		m_PhysicsEnabled = enable;
		if (m_PhysicsEnabled)
		{
			InitializePhysics();
		}
		else if (!m_PhysicsEnabled)
		{
			InitializePhysics();
		}
	}

	void Actor::OnActorBeginOverlap(Actor* otherActor)
	{
		// LOG("Overlapped");
	}

	void Actor::OnActorEndOverlap(Actor* otherActor)
	{
		// LOG("End Overlapped");
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (!other) return false;

		if (GetTeamID() == GetNeutralTeamID() || other->GetTeamID() == GetNeutralTeamID())
		{
			return false; // neutral teams are not hostile to anyone
		}
		return GetTeamID() != other->GetTeamID();
	}

	void Actor::ApplyDamage(float damageAmt)
	{

	}

	// make the pivot point the center of the sprite
	void Actor::CenterPivot()
	{
		if (!m_Texture) return;
		sf::FloatRect spriteBound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(spriteBound.width / 2.0f, spriteBound.height / 2.0f);
	}

	void Actor::InitializePhysics()
	{
		if (!m_PhysicsBody)
		{
			// add the body to the physics world
			m_PhysicsBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if (m_PhysicsBody)
		{
			PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
			m_PhysicsBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (m_PhysicsBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos{ GetActorLocation().x * physicsScale, 
						GetActorLocation().y * physicsScale};
			float rotation = DegreesToRadians(GetActorRotation());
			// could have scale too but we dont support it yet

			m_PhysicsBody->SetTransform(pos, rotation);
		}
	}
}
