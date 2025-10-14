#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	WaitStage::WaitStage(World* owningWorld, float waitDuration) noexcept
		: GameStage{ owningWorld },
		m_WaitDuration{ waitDuration }
	{

	}

	void WaitStage::StartStage()
	{
		TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, m_WaitDuration);
	}
}
