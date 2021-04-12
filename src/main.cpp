#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int g_windowSizeX = 640;
int g_windowSizeY = 480;

//Making the window resizable
void glfwSizeCallback(GLFWwindow* pwindow, int width, int height)
{
	g_windowSizeX = width;
	g_windowSizeY = height;
	glViewport(0, 0, g_windowSizeX, g_windowSizeY);

}

//Closing the window with ESC
void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_windowSizeX,g_windowSizeX, "Battle-City", NULL, NULL);
    if (!window)
    {
		std::cout << "glfwCreateWindow failed !" << std::endl;
        glfwTerminate();
        return -1;
    }

	/*CallBack functions*/
	glfwSetWindowSizeCallback(window, glfwSizeCallback);
	glfwSetKeyCallback(window, glfwKeyCallBack);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	/*Initialize GLAD library*/
	if(!gladLoadGL())
	{
		std::cout<<"Cant load GLAD!" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "GLAD has been loaded successfully!" << std::endl;
	}

	std::cout << "Render :" << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "OpenGL : " << GLVersion.major << "." << GLVersion.major << std::endl;

    glClearColor(0,1,0,1);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


