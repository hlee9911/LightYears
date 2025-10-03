#pragma once
#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
	class GameApplication : public Application
	{
	public:
		GameApplication() noexcept;

		// virtual void Tick(float deltaTime) override;
	};
}

#endif // GAMEAPPLICATION_H