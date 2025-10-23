#pragma once
#ifndef MAINMENULEVEL_H
#define MAINMENULEVEL_H

#include "framework/World.h"

namespace ly
{
	class MainMenuHUD;
	class MainMenuLevel : public World
	{
	public:
		MainMenuLevel(Application* owningApp) noexcept;

		virtual void BeginPlay() override;

	private:
		void StartGame();
		void QuitGame();

	private:
		weak<MainMenuHUD> m_MainMenuHUD;
	};
}

#endif // MAINMENULEVEL_H
