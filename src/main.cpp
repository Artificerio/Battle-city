#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*Creating array to define the coordinates*/
GLfloat points[] = {
	0.0f,  0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};

/*Creating array to define the colors*/
GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

/*Writing shaders*/
const char*  vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main(){"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position,1.0);"
"}";

const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main(){"
"frag_color = vec4(color,1.0);"
"}";



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

    glClearColor(1,0,1,1);


	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);


	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	
	GLuint shader_programm = glCreateProgram();
	glAttachShader(shader_programm, vs);
	glAttachShader(shader_programm, fs);
	glLinkProgram(shader_programm);

	glDeleteShader(vs);
	glDeleteShader(fs);
	
    /*Vertex buffer objects*/
	GLuint points_vbo = 0; 
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	

	/*Vertex array object*/
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
	    
		glUseProgram(shader_programm);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

		
    }

    glfwTerminate();
    return 0;
}


