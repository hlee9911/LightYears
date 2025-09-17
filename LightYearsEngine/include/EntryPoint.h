#pragma once
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

namespace ly
{
	class Application;
}

// extern means it needs to be defined in another translation unit (cpp file)
extern ly::Application* GetApplication();

#endif // ENTRYPOINT_H