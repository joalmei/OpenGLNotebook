#include "Window.h"
#include <iostream>

// ===========================================================================================
// PUBLIC MEMBERS
// ===========================================================================================
Window::Window()
{
	window = InitOpenGlWindow();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::RenderLoop()
{
	return runRenderLoop(window);
}

void Window::SubscribeOnRender(std::function<void(GLFWwindow *)> renderer)
{
	renderers.push_back(renderer);
}

// ===========================================================================================
// PROTECTED MEMBERS
// ===========================================================================================
void Window::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow * Window::InitOpenGlWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWorld", NULL, NULL);

	if (window == NULL)
	{
		return NULL;
	}

	glfwMakeContextCurrent(window);

	// load openGL fcts for this OS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return NULL;
	}

	// defines the viewport
	glViewport(0, 0, 800, 600);

	// resizes the viewport if window is rescaled (callback)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/* OBS:
	There are many callbacks functions we can set to register our own functions.
	For example, we can make a callback function to process joystick input changes, process error messages etc.
	We register the callback functions after we've created the window and before the game loop is initiated. */

	return window;
}

void Window::ProcessInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::Render(GLFWwindow * window)
{
	// clear all color buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	std::list<std::function<void(GLFWwindow *)>>::iterator r;
	for (r = renderers.begin(); r != renderers.end(); r++)
	{
		(*r)(window);
	}
}

void Window::runRenderLoop(GLFWwindow * window)
{
	while (!glfwWindowShouldClose(window))
	{
		// PRE PROCESS
		ProcessInput(window);

		// PROCESS
		Render(window);

		// POST PROCESS
		// swap front and back image buffer
		// (avois flickering caused by the screen's drawing delay)
		glfwSwapBuffers(window);

		// checks if registered callbacks can be called
		glfwPollEvents();
	}

	return;
}
