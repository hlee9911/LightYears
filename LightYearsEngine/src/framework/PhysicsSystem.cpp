#include "framework/PhysicsSystem.h"

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

	PhysicsSystem::PhysicsSystem() noexcept
		: m_PhysicsWorld{ b2Vec2(0.0f, 0.0f) }, // No gravity in space
		m_PhysicsScale{ 0.01f }
	{

	}
}
