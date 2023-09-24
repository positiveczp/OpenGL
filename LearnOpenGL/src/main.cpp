#include <dinput.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "imgui/gui.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{

	HINSTANCE renderdoc = LoadLibrary("D:/RenderDoc/RenderDoc/renderdoc.dll");
	if(renderdoc == nullptr)
	{
		std::cout << "ERROR" << std::endl;
	}

	const char* glsl_version = "#version 330";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* windows = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if(windows == nullptr)
	{
		std::cout << "Failed to create GLFW windows" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(windows);
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -2;
	}
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(windows, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	glViewport(0,0,800,600);
	glfwSetFramebufferSizeCallback(windows, framebuffer_size_callback);

	Shader ourShader("../shader/test.vs", "../shader/test.fs");

	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0,  // 右上角
		0.5f, -0.5f, 0.0f, 1.0, 1.0, 0.0,// 右下角
		-0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0,// 左下角
		-0.5f, 0.5f, 0.0f, 0.0, 0.0, 1.0,   // 左上角
	};

	unsigned int index[] = {
		0,1,3,
		1,2,3
	};
	
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	ImVec4 clear_color = ImVec4();
	while(!glfwWindowShouldClose(windows))
	{
		processInput(windows);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		static float f = 0.0f;
		ImGui::Begin("Hello, world!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		ImGui::End();
		
		glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();

		float green = sin(f) / 2.0f + 0.5f;
		// float green = sin(glfwGetTime()) / 2.0f + 0.5f;
		glUniform4f(glGetUniformLocation(ourShader.GetProgram(), "testColor"), 1.0, green, 1.0, 1.0);
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(windows);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}