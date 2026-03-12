#pragma once

namespace ly
{
	class Application;
}

// extern means it needs to be defined in another translation unit (cpp file)
extern ly::Application* GetApplication();
