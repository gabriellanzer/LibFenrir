#ifndef APP_H
#define APP_H
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include "RendererSystem.h"
#include "Camera.h"

using namespace std;

class App
{
public:
	App();
	~App();

	static void init(int window, int height, string name, bool fullscreen);
	static void init(string config = "config.txt.");
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void resize_callback(GLFWwindow* window, int width, int height);

	static void run();
	static void end();

	static void display();
	static void updateMouse();
	static void updateKeyboard();
	static void updateInputCamera();
	static void updateCamera();

private:
	static Camera camera;
	static GLFWwindow *window;
};


#endif

