#pragma once

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
