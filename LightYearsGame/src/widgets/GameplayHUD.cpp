#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD() noexcept
		: HUD{},
		m_FrameRateText{ "FPS: " }
	{
		m_FrameRateText.SetTextSize(25);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		m_FrameRateText.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = static_cast<int>(1.0f / deltaTime);
		std::string frameRateStr = "FPS: " + std::to_string(frameRate);
		m_FrameRateText.SetTextString(frameRateStr);
	}
}
