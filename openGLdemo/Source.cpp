#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Callbacks.h"
#include "Utilities.h"
#include "Vectors.h"
#include "Matrix.h"
#include "Grain.h"
#include <vector>
#include "rendering/OpenGLLoader.h"
#include "rendering/OpenGLDraw.h"
#include "Input.h"
#include "rendering/GLSLShaderLoader.h"
#include <iostream>
#include <random>

int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	GLFWwindow* window = glfwCreateWindow(h, w, extract_version(argv[0]), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

	const char* vertshader =
		"#version 450 core                                                  \n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;            \n"
		//"uniform mat4 modelmatrix;                                          \n"
		"void main(){                                                       \n"
		//"  gl_Position = modelmatrix * vec4(vertexPosition_modelspace, 1.0);\n"
		"  gl_Position = vec4(vertexPosition_modelspace, 1.0);\n"
		"}";

	const char* fragshader =
		"#version 450 core   \n"
		"out vec3 color;     \n"
		"uniform vec3 ucolor = vec3(.5,.5,.5);\n"
		"void main() {       \n"
		"  color = ucolor;   \n"
		"}";

	unsigned int mainShader = LoadShader(vertshader, fragshader);
	glClearColor(.0f, .0f, .0f, 0.f);

	std::vector<GrainDraw> DustDraw;
	{
		GLfloat radius = 0.03;
		Vector2D center = Vector2D(-0.3, 0);
		Vector2D velos = Vector2D(0, -0.13);
		Grain(velos, center, radius);
		DustDraw.push_back(UploadMesh(center, radius));

		radius = 0.03;
		center = Vector2D(0.3, 0);
		velos = Vector2D(0, 0.13);
		Grain(velos, center, radius);
		DustDraw.push_back(UploadMesh(center, radius));

		radius = 0.03;
		center = Vector2D(0, 0.5);
		velos = Vector2D(0.1, 0);
		Grain(velos, center, radius, 0.1);
		DustDraw.push_back(UploadMesh(center, radius));
	}

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.f, 1.f);
	double lasttime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		// HANDLE KEYPRESS
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		// RENDER OUR OBJECT
		glUseProgram(mainShader);

		for (int itr = 0; itr < Grain::dust.size(); itr++) {
			Grain::dust[itr]->update();
			DustDraw[itr] = UploadMesh(Grain::dust[itr]->get_center(), Grain::dust[itr]->get_radius());
		}

		Draw(DustDraw);
		glfwSwapBuffers(window);
		glfwPollEvents();
		while (glfwGetTime() < lasttime + 1.0 / 60) {
			// TODO: Put the thread to sleep, yield, or simply do nothing
		}
		lasttime += 1.0 / 60;
	}

	// UNLOAD DATA FROM GRAPHICS CARD
	UnloadMesh(DustDraw);

	glfwTerminate();
	return 0;
}