#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace ly
{
	unique<PhysicsSystem> PhysicsSystem::s_PhysicsSystemInstance{ nullptr };

	PhysicsSystem& PhysicsSystem::Get() noexcept
	{
		if (!s_PhysicsSystemInstance)
		{
			s_PhysicsSystemInstance = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
		}
		return *s_PhysicsSystemInstance;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners(); // Right before stepping the physics world, remove any pending listeners
		m_PhysicsWorld.Step(deltaTime, m_VelocityIterations, m_PositionIterations);
	}

	/// <summary>
	/// Adds a listener actor to the physics world and returns the Box2D body pointer.
	/// </summary>
	/// <param name="listener"></param>
	/// <returns></returns>
	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy()) return nullptr;

		// create a dynamic body
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener); // this pointer will be the pointer that points the listener actor, this is okay since it is guaranteed to be that listener actor
		bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
							 listener->GetActorLocation().y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
		
		// create the body in the physics world
		b2Body* body = m_PhysicsWorld.CreateBody(&bodyDef);
		
		// create a box shape for the body
		b2PolygonShape shape;
		auto bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width / 2.0f * GetPhysicsScale(),
					   bound.height / 2.0f * GetPhysicsScale());

		// create a fixture for the body
		b2FixtureDef fixtureDef; // actual geometry called body fixture
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f; // mass density, higher means heavier
		fixtureDef.friction = 0.3f; // surface friction, higher means more friction
		fixtureDef.isSensor = true; // we want to detect collisions but not apply physics response

		// attach the fixture to the body
		body->CreateFixture(&fixtureDef);

		// return the body pointer
		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		m_PendingRemoveListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::Cleanup()
	{
		s_PhysicsSystemInstance = std::move(unique<PhysicsSystem>{ new PhysicsSystem });
	}

	PhysicsSystem::PhysicsSystem() noexcept
		: m_PhysicsWorld{ b2Vec2(0.0f, 0.0f) }, // No gravity in space
		m_PhysicsScale{ 0.01f },
		m_VelocityIterations{ 8 },
		m_PositionIterations{ 3 },
		m_ContactListener{},
		m_PendingRemoveListeners{}
	{
		m_PhysicsWorld.SetContactListener(&m_ContactListener);
		m_PhysicsWorld.SetAllowSleeping(false); // we want all bodies to be active
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (auto listener : m_PendingRemoveListeners)
		{
			m_PhysicsWorld.DestroyBody(listener);
		}

		m_PendingRemoveListeners.clear();
	}

	void PhysicsContactlistener::BeginContact(b2Contact* contact)
	{
		// LOG("Contact");
		Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (ActorA && !ActorA->IsPendingDestroy())
		{
			ActorA->OnActorBeginOverlap(ActorB);
		}
		if (ActorB && !ActorB->IsPendingDestroy())
		{
			ActorB->OnActorBeginOverlap(ActorA);
		}
	}

	void PhysicsContactlistener::EndContact(b2Contact* contact)
	{
		// LOG("End Contact");

		Actor* ActorA = nullptr;
		Actor* ActorB = nullptr;

		// need to check if the fixtures and bodies are valid
		// becuase it is possible that one of the bodies has been destroyed
		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}
		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}

		if (ActorA && !ActorA->IsPendingDestroy() /*&& ActorB*/)
		{
			ActorA->OnActorEndOverlap(ActorB);
		}
		if (ActorB && !ActorB->IsPendingDestroy() /*&& ActorA*/)
		{
			ActorB->OnActorEndOverlap(ActorA);
		}
	}
}
