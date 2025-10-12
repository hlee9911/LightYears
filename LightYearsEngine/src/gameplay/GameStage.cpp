#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly
{
	GameStage::GameStage(World* owningWorld) noexcept
		: m_World{ owningWorld },
		m_StageFinished{ false }
	{

	}

	void GameStage::StartStage()
	{
		LOG("Stage Started");
	}

	void GameStage::TickStage(float deltaTime)
	{
		// LOG("Stage Ticking");
	}

	void GameStage::FinishStage()
	{
		onStageFinished.Broadcast();
		m_StageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished");
	}
}
