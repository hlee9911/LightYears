#include "gameFramework/GameApplication.h"
#include "level/GameLevelOne.h"
#include "level/MainMenuLevel.h"
#include "framework/AssetManager.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication() noexcept
		: Application{ 600, 980, "2D Bullet Hell", sf::Style::Titlebar | sf::Style::Close}
	{
		// Set the asset root directory for the AssetManager
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());

		weak<MainMenuLevel> newLevelOne = LoadWorld<MainMenuLevel>();
	}
}
