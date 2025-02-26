
#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Logger.h"
#include "Texture.h"
#include "Camera.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 1028;
const unsigned int SCR_HEIGHT = 720;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightPos1(1.2f, 1.0f, 2.0f);



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	
	//glfwSwapInterval();
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
  {

		float gpositions[] = {
			// positions          // normals           // texture coords
		-20.5f,  -03.5f, -20.5f,  0.0f,  1.0f,  0.0f,  0.0f,  5.0f,
		 20.5f,  -03.5f, -20.5f,  0.0f,  1.0f,  0.0f,  5.0f,  5.0f,
		 20.5f,  -03.5f,  20.5f,  0.0f,  1.0f,  0.0f,  5.0f,  0.0f,
		 20.5f,  -03.5f,  20.5f,  0.0f,  1.0f,  0.0f,  5.0f,  0.0f,
		-20.5f,  -03.5f,  20.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-20.5f,  -03.5f, -20.5f,  0.0f,  1.0f,  0.0f,  0.0f,  5.0f
		};
	float positions[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};




	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	VertexArray va;
	VertexBuffer vb(positions, 8 * 6 * 6 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb,layout);

	VertexArray va1;
	VertexBuffer vb1(gpositions, 8 * 6 * sizeof(float));
	VertexBufferLayout layout1;
	layout1.Push<float>(3);
	layout1.Push<float>(3);
	layout1.Push<float>(2);
	va1.AddBuffer(vb1, layout1);



	//IndexBuffer ib(indices, 6); 

	

	Shader shader("res/shaders/Basic1.shader");
	shader.Bind();
	//shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

	Shader shader1("res/shaders/Lighting.shader");


	Texture texture("res/textures/container2.png",0);
	shader.SetUniform1i("material.diffuse", 0);


	Texture texture1("res/textures/container2_specular.png",0);
	shader.SetUniform1i("material.specular", 1);

	Texture texture2("res/textures/matrix.png", 0);
	shader.SetUniform1i("material.emission", 2);

	
	


	Texture texture3("res/textures/batman.png", 0);

	
	shader.SetUniform1i("material.emission", 3);

	texture.Bind(0);
	texture1.Bind(1);
	texture3.Bind(3);
	//texture2.Bind(2);
	//texture3.Bind(3);

	va.Unbind();
	vb.Unbind();
	//ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	//glm::vec3 translation(200, 200, 0);
	float mul = 1.0f;
	float r = 0.1f, g = 0.9f, b = 0.5f;
	float increment = 0.01f;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		
		// input
		// -----
		processInput(window);

		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		renderer.Clear();
		renderer.DepthEnable();

		ImGui_ImplGlfwGL3_NewFrame();

		
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		// world transformation
		glm::mat4 model = glm::mat4(1.0f);

		

		glm::vec3 lightColor[] = {
			glm::vec3(0.4f, 0.8f, 0.1f),
			glm::vec3(1.0f, 1.0f, 0.08f),
			glm::vec3(1.0f, 0.1f, 1.0f),
			glm::vec3(0.9f, 0.4f, 0.5f),
		};

		shader.Bind();
		
		// directional light
		shader.SetUniform3f("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.SetUniform3f("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.SetUniform3f("dirLight.diffuse", 0.2f, 0.4f, 0.8f);
		shader.SetUniform3f("dirLight.specular", 0.2f, 0.4f, 0.8f);
		// point light 1
		shader.SetUniform3f("pointLights[0].position", pointLightPositions[0]);
		shader.SetUniform3f("pointLights[0].ambient",  lightColor[0].x*0.1f, lightColor[0].g*0.1f, lightColor[0].b*0.1f);
		shader.SetUniform3f("pointLights[0].diffuse",  lightColor[0].x*1.0f, lightColor[0].g*1.0f, lightColor[0].b*1.0f);
		shader.SetUniform3f("pointLights[0].specular", lightColor[0].x*1.0f, lightColor[0].g*1.0f, lightColor[0].b*1.0f);
		shader.SetUniform1f("pointLights[0].constant", 1.0f);
		shader.SetUniform1f("pointLights[0].linear", 0.07);
		shader.SetUniform1f("pointLights[0].quadratic", 0.017);
		// point light 2
		shader.SetUniform3f("pointLights[1].position", pointLightPositions[1]);
		shader.SetUniform3f("pointLights[1].ambient",  lightColor[1].x*0.1f, lightColor[1].g*0.1f, lightColor[1].b*0.1f);
		shader.SetUniform3f("pointLights[1].diffuse",  lightColor[1].x*1.0f, lightColor[1].g*1.0f, lightColor[1].b*1.0f);
		shader.SetUniform3f("pointLights[1].specular", lightColor[1].x*1.0f, lightColor[1].g*1.0f, lightColor[1].b*1.0f);
		shader.SetUniform1f("pointLights[1].constant", 1.0f);
		shader.SetUniform1f("pointLights[1].linear", 0.07);
		shader.SetUniform1f("pointLights[1].quadratic", 0.017);
		// point light 3
		shader.SetUniform3f("pointLights[2].position", pointLightPositions[2]);
		shader.SetUniform3f("pointLights[2].ambient",  lightColor[2].x*0.1f, lightColor[2].g*0.1f, lightColor[2].b*0.1f);
		shader.SetUniform3f("pointLights[2].diffuse",  lightColor[2].x*1.0f, lightColor[2].g*1.0f, lightColor[2].b*1.0f);
		shader.SetUniform3f("pointLights[2].specular", lightColor[2].x*1.0f, lightColor[2].g*1.0f, lightColor[2].b*1.0f);
		shader.SetUniform1f("pointLights[2].constant", 1.0f);
		shader.SetUniform1f("pointLights[2].linear", 1.0f);
		shader.SetUniform1f("pointLights[2].quadratic", 1.0f);
		// point light 4
		shader.SetUniform3f("pointLights[3].position", pointLightPositions[3]);
		shader.SetUniform3f("pointLights[3].ambient",  lightColor[3].x*0.1f, lightColor[3].g*0.1f, lightColor[3].b*0.1f);
		shader.SetUniform3f("pointLights[3].diffuse",  lightColor[3].x*1.0f, lightColor[3].g*1.0f, lightColor[3].b*1.0f);
		shader.SetUniform3f("pointLights[3].specular", lightColor[3].x*1.0f, lightColor[3].g*1.0f, lightColor[3].b*1.0f);
		shader.SetUniform1f("pointLights[3].constant", 1.0f);
		shader.SetUniform1f("pointLights[3].linear", 0.07);
		shader.SetUniform1f("pointLights[3].quadratic", 0.017);
		// spotLight
		shader.SetUniform3f("spotLight.position", camera.Position);
		shader.SetUniform3f("spotLight.direction", camera.Front);
		shader.SetUniform3f("spotLight.ambient",  0.0f, 0.0f, 0.0f);
		shader.SetUniform3f("spotLight.diffuse",  0.0f, 1.0f, 0.0f);
		shader.SetUniform3f("spotLight.specular", 0.0f, 1.0f, 0.0f);
		shader.SetUniform1f("spotLight.constant", 1.0f);
		shader.SetUniform1f("spotLight.linear", 0.07);
		shader.SetUniform1f("spotLight.quadratic", 0.017);
		shader.SetUniform1f("spotLight.cutOff", glm::cos(glm::radians(7.0f)));
		shader.SetUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(10.0f)));

		shader.SetUniform3f("viewPos", camera.Position);

		

		

		// material properties
		//shader.SetUniform3f("material.ambient", 1.0f, 0.5f, 0.31f);
		//shader.SetUniform3f("material.diffuse", 1.0f, 0.5f, 0.31f);
		//shader.SetUniform3f("material.specular", 0.5f, 0.5f, 0.5f); //specular lighting doesn't have full effect on this object's material
		shader.SetUniform1f("material.shininess", 64.0f);
		float offset = rand();
		shader.SetUniform1f("time", offset * glfwGetTime() );


		

		shader.SetUniformMat4f("model", model);
		shader.SetUniformMat4f("view", view);
		shader.SetUniformMat4f("projection",projection);
		//shader.SetUniformMat4f("u_MVP", mvp);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 25.0f * (i + 2) * (float)glfwGetTime();
			model = glm::rotate(model, glm::radians(angle)*mul, glm::vec3(1.0f, 0.3f, 0.5f));
			shader.SetUniformMat4f("model", model);
			
			shader.SetUniform1f("time", mul*i+2+glfwGetTime());

			renderer.DrawArray(va, shader, 36);
		}

		

		model = glm::mat4(1.0f);
		shader.SetUniformMat4f("model", model);
		renderer.DrawArray(va1, shader, 6);

		



		shader1.Bind();
		shader1.SetUniformMat4f("u_View", view);
		shader1.SetUniformMat4f("u_Projection", projection);
		
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));

			shader1.SetUniformMat4f("u_Model", model);

			shader1.SetUniform3f("color", lightColor[i]);
			renderer.DrawArray(va, shader1, 36);
		}


		model = glm::mat4(1.0f);
		shader1.SetUniformMat4f("u_Model", model);
		//renderer.DrawArray(va1, shader1, 6);

		

		if (r > 1.0f)
		{
			increment = -0.02f;

		}
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;
		g -= increment;
		b += increment;
		//glClearColor(r, g, b, 1.0f);

		{

			ImGui::SliderFloat("Multiplier", &mul, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		
		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}
	
  }
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}