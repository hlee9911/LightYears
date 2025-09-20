#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include "framework/Object.h"

namespace ly
{
	class World; // Forward declaration of World class

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld) noexcept;
		virtual ~Actor() noexcept;

		void BeginPlayInternal();
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		World* m_OwningWorld;
		bool m_HasBegunPlay;
	};
}

#endif // ACTOR_H
