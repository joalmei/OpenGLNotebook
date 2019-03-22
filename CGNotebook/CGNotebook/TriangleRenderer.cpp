#include <iostream>
#include <glad/glad.h>
#include "TriangleRenderer.h"


// ===========================================================================================
// PUBLIC MEMBERS
// ===========================================================================================
TriangleRenderer::TriangleRenderer()
{
}

TriangleRenderer::~TriangleRenderer()
{
}

void TriangleRenderer::Render(GLFWwindow *w)
{
	drawTriangle(w);
}

// ===========================================================================================
// PROTECTED MEMBERS
// ===========================================================================================
unsigned int TriangleRenderer::VertexShader()
{
	unsigned int shader;
	shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(shader, 1, &vertexShaderSource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

unsigned int TriangleRenderer::FragmentShader()
{
	unsigned int shader;
	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}

// ===========================================================================================
// PRIVATE MEMBERS
// ===========================================================================================
void TriangleRenderer::drawTriangle(GLFWwindow * w)
{
	// =====================> GPU DATA SETUP

	// STORE THE TRIAGLE VERTICES IN THE GPU (VERTEX SHADER'S INPUT)
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//  Sending data to the graphics card from the CPU is relatively slow,
	//  so wherever we can, we try to send as much data as possible at once.
	// Once the data is in the graphics card's memory the vertex shader has almost instant access
	// to the vertices making it extremely fast

	// !!!!! VAO WRAPPER FOR EVERYTHING
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// creates a Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// only 1 buffer of each type (GL_ARRAY_BUFFER stands for Vectex Buffers)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// data transfer from CPU to GPU
	// (buffer type, size, size in bytes, buffer, GPU data mgmt {static, dynamic, stream})
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);



	// =====================> GPU PROGRAM SETUP

	// COMPILE THE VERTEX SHADER
	unsigned int vertexShader = VertexShader();

	// COMPILE FRAGMENT SHADER
	unsigned int fragShader = FragmentShader();


	// LINK SHADERS (input[i+1] = output[i])
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	// no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// =====================> LINKING ATTRIBUTES (HOW TO INTERPRET DATA IN THE GPU BUFFER [VBO])
	glVertexAttribPointer(
		0,						// (location [as in VERTEX SHADER]
		3,						// size of vetex attribute
		GL_FLOAT,				// data type
		GL_FALSE,				// FALSE == is already normalized
		3 * sizeof(float),		// stride == size of 1 VERTEX in the memory
		(void*)0);				// offset from the beginning of the buffer

	glEnableVertexAttribArray(0);


	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);


	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
