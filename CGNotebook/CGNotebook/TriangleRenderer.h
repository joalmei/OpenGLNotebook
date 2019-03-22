#pragma once
#include "Renderer.h"

class TriangleRenderer : public Renderer
{
private:
	const char* vertexShaderSource = "#version 330 core\nlayout(location = 0) in vec3 aPos;\nvoid main()\n{\n\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";
	const char* fragmentShaderSource = "#version 330 core \n out vec4 FragColor; \n void main(){FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}";


public:
	TriangleRenderer();
	~TriangleRenderer();

	void Render(GLFWwindow*);

protected:
	unsigned int VertexShader();
	unsigned int FragmentShader();

private:
	void drawTriangle(GLFWwindow* w);
};

