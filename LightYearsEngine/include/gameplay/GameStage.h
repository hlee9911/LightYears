#pragma once
#ifndef GAMESTAGE_H
#define GAMESTAGE_H

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* owningWorld) noexcept;

		const World* GetWorld() const noexcept { return m_World; }
		World* GetWorld() noexcept { return m_World; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		bool IsStageFinished() const noexcept { return m_StageFinished; }

	private:
		virtual void StageFinished();

	private:
		World* m_World;
		bool m_StageFinished;
	};
}

#endif // GAMESTAGE_H