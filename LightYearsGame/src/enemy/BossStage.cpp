#include "enemy/BossStage.h"
#include "enemy/Boss.h"
#include "framework/World.h"

namespace ly
{
	BossStage::BossStage(World* owningWorld) noexcept
		: GameStage{ owningWorld }
	{

	}

	void BossStage::StartStage()
	{
		SpawnBoss();
	}

	void BossStage::SpawnBoss()
	{
		weak<Boss> newBoss = GetWorld()->SpawnActor<Boss>();
		auto windowSize = GetWorld()->GetWorldSize();
		newBoss.lock()->SetActorLocation({ windowSize.x / 2.0f, 200.0f });
		newBoss.lock()->onActorDestroyed.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
	}

	void BossStage::BossDestroyed(Actor* bossActor)
	{
		FinishStage();
	}
}
