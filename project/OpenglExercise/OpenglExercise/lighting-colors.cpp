#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include <iostream>
namespace lightingColors
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);


	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	// camera
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// lighting
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	int lightingColorsProcess()
	{
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// glfw window creation
		// --------------------
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, lightingColors::framebuffer_size_callback);
		glfwSetCursorPosCallback(window, lightingColors::mouse_callback);
		glfwSetScrollCallback(window, lightingColors::scroll_callback);

		// tell GLFW to capture our mouse
		//注释了也没什么影响？
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);

		// build and compile our shader zprogram
		// ------------------------------------
		//编译、链接两类着色器
		Shader lightingShader("1.colors.vs", "1.colors.fs");
		Shader lightCubeShader("1.light_cube.vs", "1.light_cube.fs");//光源正方体着色器

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		//一份顶点供两个正方体使用
		//一个面由两个三角形构成；即6个点
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			0.5f,  0.5f, -0.5f,
			0.5f,  0.5f,  0.5f,
			0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};
		// first, configure the cube's VAO (and VBO)
		unsigned int VBO, cubeVAO;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);
	//cubeVAO start	
		glBindVertexArray(cubeVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		//声明顶点位置属性 让立方体顶点着色器能够访问到
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
    //cubeVAO end

		// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
		//设置光照顶点数组对象
		//因为使用同一份顶点缓冲对象，所以不再需要glGenBuffers生成一个顶点缓冲对象，也不需要glBufferData绑定实际数据
		unsigned int lightCubeVAO;
		glGenVertexArrays(1, &lightCubeVAO);
		//但仍要指定绑定到的顶点数组对象
		glBindVertexArray(lightCubeVAO);

		// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
		//这个注释掉也没什么影响
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		//给光照立方体指定位置属性，让光照顶点着色器能够访问到
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		// render loop
		// -----------
		while (!glfwWindowShouldClose(window))
		{
			// per-frame time logic
			// --------------------
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// input
			// -----
			lightingColors::processInput(window);

			// render
			// ------
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// be sure to activate shader when setting uniforms/drawing objects
			//在设置uniform变量之前要先激活着色器程序
			lightingShader.use();
			lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
			lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

			// view/projection transformations
			//设置模型、观察、投影矩阵
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			lightingShader.setMat4("projection", projection);
			lightingShader.setMat4("view", view);

			// world transformation
			glm::mat4 model = glm::mat4(1.0f);
			lightingShader.setMat4("model", model);

			// render the cube
			//渲染立方体
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);


			// also draw the lamp object
			lightCubeShader.use();
			lightCubeShader.setMat4("projection", projection);
			lightCubeShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
			lightCubeShader.setMat4("model", model);
			//渲染光照立方体
			glBindVertexArray(lightCubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);


			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &cubeVAO);
		glDeleteVertexArrays(1, &lightCubeVAO);
		glDeleteBuffers(1, &VBO);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
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
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera.ProcessKeyboard(DOWN, deltaTime);

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
	void lightingColors::mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
	void lightingColors::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(yoffset);
	}
}