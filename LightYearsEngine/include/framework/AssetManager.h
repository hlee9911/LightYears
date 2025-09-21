#pragma once
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>

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

	protected:
		AssetManager() noexcept;

	private:
		static unique<AssetManager> s_AssetManager;
		Dictionary<std::string, shared<sf::Texture>> m_LoadedTextureMap;
	};
}

#endif // ASSETMANAGER_H
