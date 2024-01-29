#include <KlemmUI/Application.h>

int main()
{
	// Point the program to the KlemmUI shaders directory.
	Application::SetShaderPath("../KlemmUI/Shaders");

	// Initialize the app window with a window title, window flag and window resolution.
	Application::Initialize("Hello, World!", Application::NO_RESIZE_BIT, Vector2ui(640, 480));

	// Application will be true if the program should be closed.
	while (!Application::Quit)
	{
		// Update the window, respond to events, re-render the UI if necessary.
		Application::UpdateWindow();
	}
}

#if _WIN32
// On Windows, the entry point for GUI apps is called WinMain() instead of main()
int WinMain()
{
	return main();
}
#endif