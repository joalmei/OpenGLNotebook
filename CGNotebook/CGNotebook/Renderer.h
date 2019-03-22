#pragma once
#include <GLFW/glfw3.h>

class Renderer
{
public:
	virtual void Render(GLFWwindow*) = 0;

protected:
	virtual unsigned int VertexShader() = 0;
	virtual unsigned int FragmentShader() = 0;
};

