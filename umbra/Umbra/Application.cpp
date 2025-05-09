#include "Application.h"

#include "Screen.h"

Screen* Application::m_screen = nullptr;

Screen* Application::GetScreen()
{
	return m_screen;
}

Application::Application()
{
	m_screen = new Screen;
}

Application::~Application()
{
	delete m_screen;
	m_screen = nullptr;
}

int Application::Run()
{
	// Attempt to initialize the window
	// Return failure if failed
	if (!m_screen->Open())
	{
		return EXIT_FAILURE;
	}

	while (!WindowShouldClose())
	{
		m_screen->NewFrame();

		m_screen->EndFrame();
	}

	m_screen->Close();

	return EXIT_SUCCESS;
}
