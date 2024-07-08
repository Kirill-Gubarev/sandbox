#pragma comment (lib, "opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char *argv[]){
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glClearColor(1, 1, 0, 1);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	system("pause");
	return 0;
}

