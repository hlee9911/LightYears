#pragma once
#ifndef BOSSSTAGE_H
#define BOSSSTAGE_H

#include "gameplay/GameStage.h"

namespace ly
{
	class Actor;
	class BossStage : public GameStage
	{
	public:
		BossStage(World* owningWorld) noexcept;
		virtual void StartStage() override;

	private:
		void SpawnBoss();
		void BossDestroyed(Actor* bossActor);

	};
}

#endif // BOSSSTAGE_H
