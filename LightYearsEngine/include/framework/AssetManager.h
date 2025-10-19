#pragma once
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "framework/Core.h"

namespace ly
{
	// Manages loading and unloading of game assets
	// Singleton class
	class AssetManager
	{
	public:
		static AssetManager& Get() noexcept;
		shared<sf::Texture> LoadTexture(const std::string& path);
		shared<sf::Font> LoadFont(const std::string& path);
		void CleanCycle();
		void SetAssetRootDirectory(const std::string& rootDir);

	protected:
		AssetManager() noexcept;

	private:
		template<typename T>
		shared<T> LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& container);

		template<typename T>
		void CleanUniqueRef(Dictionary<std::string, shared<T>>& container);

	private:
		static unique<AssetManager> s_AssetManager;
		Dictionary<std::string, shared<sf::Texture>> m_LoadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> m_LoadedFontMap;
		std::string m_RootDirectory;
	};

	template<typename T>
	inline shared<T> AssetManager::LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& container)
	{
		// Check if asset is already loaded
		auto found = container.find(path);
		if (found != container.end())
		{
			return found->second;
		}

		// Load new asset if not found
		shared<T> newAsset{ new T };
		if (newAsset->loadFromFile(m_RootDirectory + path))
		{
			container.insert({ path, newAsset });
			return newAsset;
		}

		// if failed to load asset, return nullptr
		ERROR("Failed to load Asset from path: %s", path.c_str());
		return shared<T>{ nullptr };
	}

	template<typename T>
	inline void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& container)
	{
		// Remove unused assets from the map
		for (auto iter = container.begin(); iter != container.end();)
		{
			if (iter->second.unique()) // only held by the map
			{
				LOG("Cleaning asset: %s", iter->first.c_str());
				iter = container.erase(iter);
			}
			else // still used somewhere else
			{
				++iter;
			}
		}
	}
}

#endif // ASSETMANAGER_H
