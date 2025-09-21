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
		// Check if texture is already loaded
		auto found = m_LoadedTextureMap.find(path);
		if (found != m_LoadedTextureMap.end())
		{
			return found->second;
		}

		// Load new texture if not found
		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(path))
		{
			m_LoadedTextureMap.insert({ path, newTexture });
			return newTexture;
		}

		// if failed to load texture, return nullptr
		LOG("Failed to load texture from path: %s", path.c_str());
		return shared<sf::Texture>{ nullptr };
	}

	AssetManager::AssetManager() noexcept
	{

	}
}
