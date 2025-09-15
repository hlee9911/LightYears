#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "framework/Application.h"

int main(int argc, char* argv[]) 
{
	// allocating on the heap to avoid stack overflow
	auto app = std::make_unique<ly::Application>();
	app->Run();

	return 0;
}