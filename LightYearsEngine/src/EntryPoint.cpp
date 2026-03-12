#include "EntryPoint.h"
#include "framework/Application.h"

// ensure main function is hidden and encapsulated within a namespace
int main(int argc, char* argv[])
{
	ly::Application* app = GetApplication();
	app->Run();
	delete app;

	return 0;
}
