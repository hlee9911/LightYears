#pragma once
#ifndef WAITSTAGE_H
#define WAITSTAGE_H

#include "gameplay/GameStage.h"

namespace ly
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* owningWorld, float waitDuration = 5.0f) noexcept;

		virtual void StartStage() override;
		
	private:
		float m_WaitDuration;

	};
}

#endif // WAITSTAGE_H