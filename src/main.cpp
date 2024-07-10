#include <iostream>
#include "SBwindow.h"
int main(int argc, char *argv[]){
    if (!glfwInit())
        return -1;
    sb::PTR_SBWindow sbWindow;
    try {
        sbWindow = sb::SBwindow::createWindow(700, 500, "Sandbox");
    }
    catch (std::exception& ex)
    {
        std::cerr <<"EXCEPTION: " << ex.what() << std::endl;
        return -1;
    }
   
    GLFWwindow* glfwWindow = sbWindow.get()->getGLFWwindow();
    
    while (!glfwWindowShouldClose(glfwWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255,255,0);
        glVertex2f(0.5f,0.5f);
        glVertex2f(0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
        glVertex2f(-0.5f,0.5f);
        glEnd();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    glfwTerminate();

	system("pause");
	return 0;
}

