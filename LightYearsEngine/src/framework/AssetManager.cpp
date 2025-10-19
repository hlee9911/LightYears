#include "framework/AssetManager.h"

namespace ly
{
	unique<AssetManager> AssetManager::s_AssetManager{ nullptr };

	AssetManager& AssetManager::Get() noexcept
	{
		if (!s_AssetManager)
		{
			// we do move here to avoid copying the unique_ptr
			// s_AssetManager = std::move(unique<AssetManager>{ new AssetManager });
			s_AssetManager = unique<AssetManager>{ new AssetManager };
		}
		return *s_AssetManager;
	}

	shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		return LoadAsset<sf::Texture>(path, m_LoadedTextureMap);
	}

	shared<sf::Font> AssetManager::LoadFont(const std::string& path)
	{
		return LoadAsset<sf::Font>(path, m_LoadedFontMap);
	}

	void AssetManager::CleanCycle()
	{
		CleanUniqueRef<sf::Texture>(m_LoadedTextureMap);
		CleanUniqueRef<sf::Font>(m_LoadedFontMap);
	}

	void AssetManager::SetAssetRootDirectory(const std::string& rootDir)
	{
		m_RootDirectory = rootDir;
	}

	AssetManager::AssetManager() noexcept
		: m_RootDirectory{}
	{

	}
}
