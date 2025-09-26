#pragma once
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <box2d/b2_world.h>

#include "framework/Core.h"

namespace ly
{
	class Actor;

	class PhysicsContactlistener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	// Physics system is a singleton class that manages the Box2D physics world
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get() noexcept;
		void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* bodyToRemove);
		float GetPhysicsScale() const noexcept { return m_PhysicsScale; }

		static void Cleanup();

	protected:
		PhysicsSystem() noexcept;

	private:
		void ProcessPendingRemoveListeners();

	private:
		static unique<PhysicsSystem> s_PhysicsSystemInstance;
		b2World m_PhysicsWorld;
		float m_PhysicsScale;
		int m_VelocityIterations;
		int m_PositionIterations;

		PhysicsContactlistener m_ContactListener;

		Set<b2Body*> m_PendingRemoveListeners;
	};
}

#endif // PHYSICSSYSTEM_H
