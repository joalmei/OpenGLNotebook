#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include <functional>


class Window
{
private:
	GLFWwindow * window;
	std::list<std::function<void(GLFWwindow *)>> renderers;
	
public:
	Window();
	~Window();
	void RenderLoop();
	void SubscribeOnRender(std::function<void(GLFWwindow*)>);

protected:
	virtual void ProcessInput(GLFWwindow *window);
	virtual void Render(GLFWwindow* window);


private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow* InitOpenGlWindow();
	
	void runRenderLoop(GLFWwindow* window);
};

