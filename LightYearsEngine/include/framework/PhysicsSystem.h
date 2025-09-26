#pragma once
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <box2d/b2_world.h>

#include "framework/Core.h"

namespace ly
{
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get() noexcept;

	protected:
		PhysicsSystem() noexcept;

	private:
		static unique<PhysicsSystem> s_PhysicsSystemInstance;
		b2World m_PhysicsWorld;
		float m_PhysicsScale;
	};
}

#endif // PHYSICSSYSTEM_H
