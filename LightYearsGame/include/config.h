#pragma once
#include <string>

// preprocessor definitions for resource paths
std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else // debug build
	return "D:/Documents_Samsung/OtherProjects/LightYears/LightYearsGame/assets/";
#endif
}
