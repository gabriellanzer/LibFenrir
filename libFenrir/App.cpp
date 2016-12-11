#include "App.h"
#include "ResourceManager.h"
#include <fstream>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
//#include "maths_funcs.h"
#include "ClickSystem.h"
#include "TextureSynthesisSystem.h"
#include "GLError.h"
#include "PrimitiveDrawer.h"
#include "IMGReader.h"
GLFWwindow * App::window = 0;
Camera App::camera;
#pragma region Global variables
int mode = 0;
glm::mat4 mat;
float fov, near, far;

int whatIsChanging = 0; /*
0 - Object
1 - FOV
2 - NEAR
3 - FAR
*/

int widthScreen, heightScreen;

FrameBuffer *testBuffer, *hbaoBuffer, *blurBuffer;
#pragma endregion

App::App()
{

}


App::~App()
{
}

void App::init(int width, int height, string name, bool fullscreen)
{


#pragma region GLFW
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	if (width < 1 || height < 1)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
#pragma endregion
#pragma region Create window

	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0.3, 1);
	glfwSwapInterval(1);

	GLFWimage images[2];



#pragma endregion
#pragma region GLEW

	glewExperimental = GL_TRUE;
	glewInit();

#ifdef _DEBUG
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Renderer: %s\n", renderer);
	printf("OpenGL (supported version) %s\n", version);
#endif // DEBUG

#pragma endregion

#pragma region OPENGL INIT
	glFinish();
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_CULL_FACE);

	//glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//glDepthMask(true);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

#pragma endregion

#pragma region LOAD
	gRenderer->init();


	gResource->generateTriangle();
	gResource->generateQuad();


	/*gResource->readOBJ("./mesh/monkey.obj", "monkey");

	gResource->adaptMeshtoShader("monkey 0");
	gResource->generateVAOandRegister("monkey 0");

	gResource->adaptMeshtoShader("monkey 1");
	gResource->generateVAOandRegister("monkey 1");*/

	gResource->readOBJ("./mesh/table.obj", "owt");

	gResource->adaptMeshtoShader("owt 0");
	gResource->generateVAOandRegister("owt 0");

	gResource->readOBJ("./mesh/vase.obj", "vase");

	gResource->adaptMeshtoShader("vase 0");
	gResource->generateVAOandRegister("vase 0");

	gResource->readOBJ("./mesh/monkey.obj", "cube");

	{
		Image *uv = gResource->generateUVImage(32, 32, "cube 0");
		gResource->addImage("cubeUV", uv);
		gResource->createTextureOfImage("cubeUV", "vUV", false);
	}




	gResource->adaptMeshtoShader("cube 0");
	gResource->generateVAOandRegister("cube 0");



	glfwGetWindowSize(window, &widthScreen, &heightScreen);
	fov = glm::radians(66.0f);
	near = 0.01f;
	far = 100.f;
	whatIsChanging = 0;

	gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));
	updateCamera();

	gResource->readImage("./img/cube.png", "sample");
	gResource->readImage("./img/owt.png", "owt");
	gResource->readImage("./img/vase.png", "vase");

	//gResource->readImage("./img/law.png", "painted");

	{
		Image *img = new Image(128, 128);
		int n = img->getWidth() * img->getHeight();
		for (int i = 0; i < n; i++)
		{
			img->setPixel(0, 0, 0, 0, i);
		}

		gResource->addImage("blank", img);
	}
	gResource->createTextureOfImage("blank", "output");
	gResource->createTextureOfImage("blank", "painted");


	//gClick->setMesh(gResource->getMeshShader("monkey 0"));

#pragma endregion

	//FrameBuffer Test
	testBuffer = gResource->createDefaultFrameBuffer(widthScreen, heightScreen, "testFBO", true, true);

	//HBAO FrameBuffer setup
	hbaoBuffer = new FrameBuffer();
	
	//Define HBAOTexture
	{
		// The texture we're going to render to
		GLuint renderTexture;
		glGenTextures(1, &renderTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, renderTexture);

		// Give an empty image to OpenGL ( the last "NULL" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthScreen, heightScreen, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//Attach to FrameBuffer on layout 0
		hbaoBuffer->Attach(Color_Attachment, renderTexture, 0);

		//Register on map
		gResource->addTexture("HBAO_texture", renderTexture);

		//Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	blurBuffer = new FrameBuffer();

	//Define BlurTexture
	{
		// The texture we're going to render to
		GLuint blurTexture;
		glGenTextures(1, &blurTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, blurTexture);

		// Give an empty image to OpenGL ( the last "NULL" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthScreen, heightScreen, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//Attach to FrameBuffer on layout 0
		blurBuffer->Attach(Color_Attachment, blurTexture, 0);

		//Register on map
		gResource->addTexture("Blur_texture", blurTexture);

		//Unbind Texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//Screen Pass Object
	gResource->generateQuad();
}

void App::init(string config)
{
	ifstream arq(config);

}

void _update_fps_counter(GLFWwindow* window) {
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf_s(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void App::error_callback(int error, const char * description)
{

	std::cout << description;
	getchar();

}

void App::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// state of the keys can be obtnaied by calling glfwGetKey(window, GLFW_KEY_E)
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void App::resize_callback(GLFWwindow * window, int width, int height)
{


}

void App::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_update_fps_counter(window);

		updateMouse();
		updateKeyboard();
		display();



		glfwSwapBuffers(window);
		glfwPollEvents();
		check_gl_error();

	}
}

void App::end()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void App::display()
{
#pragma region FIRST_PASS
	//Bind testBuffer
	testBuffer->Bind();

	//Clear testBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reference Shader Object
	Shader *FBOShader = gRenderer->getShader("FBO_RGB_NOR_DEPTH");

	//Use program
	glUseProgram(FBOShader->getIndexProgram());

	GLint loc = FBOShader->getAtt("basic_texture");
	glUniform1i(loc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gResource->getTexture("sample"));

	//Draw the Scene to get RGB, Normals and Depth textures

	//gResource->getMeshShader("vase 0")->bindVBO(e_face);

	glBindTexture(GL_TEXTURE_2D, gResource->getTexture("owt"));
	FBOShader->render3D(gResource->getMeshShader("owt 0"), glm::translate(mat, glm::vec3(0, -3.5, 0)));

	//gResource->getMeshShader("vase 0")->bindVBO(e_texture);
	glBindTexture(GL_TEXTURE_2D, gResource->getTexture("vase"));
	FBOShader->render3D(gResource->getMeshShader("vase 0"), glm::translate(glm::scale(mat, glm::vec3(0.25, 0.25, 0.25)), glm::vec3(0, 3.26, 0)));

	glBindTexture(GL_TEXTURE_2D, gResource->getTexture("sample"));


	/*gResource->getMeshShader("monkey 0")->bindVBO(e_face);
	FBOShader->render3D(gResource->getMeshShader("monkey 0"), mat);
	gResource->getMeshShader("monkey 0")->bindVBO(e_texture);

	gResource->getMeshShader("monkey 1")->bindVBO(e_face);
	FBOShader->render3D(gResource->getMeshShader("monkey 1"), glm::translate(glm::mat4x4(), glm::vec3(5, 0, 1)));
	gResource->getMeshShader("monkey 1")->bindVBO(e_texture);*/

	FBOShader->render3D(gResource->getMeshShader("cube 0"), glm::translate(glm::mat4x4(), glm::vec3(-3, 1.2, 0)));

	//Unbind and bind default buffer instead
	testBuffer->Unbind();
#pragma endregion


	//-------------------------------//

#pragma region HBAO Pass
	{
		//Bind testBuffer
		hbaoBuffer->Bind();

		//Clear defaultBuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Reference Shader Object
		Shader *hbaoPass = gRenderer->getShader("HBAO");

		//Use program
		glUseProgram(hbaoPass->getIndexProgram());

		//Reference for Texture Location Index
		GLint uniformLocation;

		//Bind RenderTexture with uniform location 0
		uniformLocation = hbaoPass->getAtt("noise_texture");
		glUniform1i(uniformLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		check_gl_error();
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_renderTexture"));

		//Bind NormalsTexture with uniform location 1
		uniformLocation = hbaoPass->getAtt("normals_texture");
		glUniform1i(uniformLocation, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_normalsTexture"));

		//Bind DepthTexture with uniform location 2
		uniformLocation = hbaoPass->getAtt("depth_texture");
		glUniform1i(uniformLocation, 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_depthTexture"));

		//Update zNear and zFar
		uniformLocation = hbaoPass->getAtt("zNear");
		glUniform1f(uniformLocation, near);
		uniformLocation = hbaoPass->getAtt("zFar");
		glUniform1f(uniformLocation, far);

		//Set Aspect Ratio
		uniformLocation = hbaoPass->getAtt("aspectRatio");
		glUniform1f(uniformLocation, widthScreen / heightScreen);

		//Set Screen Height
		uniformLocation = hbaoPass->getAtt("screenHeight");
		glUniform1f(uniformLocation, heightScreen);

		//Set FOV
		uniformLocation = hbaoPass->getAtt("FOV");
		glUniform1f(uniformLocation, fov);

		//Do the actual drawing process
		hbaoPass->render(gResource->getVAO("quadTexture"), 6, 0);

		//Unbind and bind default buffer instead
		hbaoBuffer->Unbind();
	}

#pragma endregion

#pragma region BLUR_PASS
	//Bind testBuffer
	blurBuffer->Bind();

	//Clear defaultBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reference Shader Object
	Shader *blurPass = gRenderer->getShader("BLUR");

	//Use program
	glUseProgram(blurPass->getIndexProgram());

	//Reference for Texture Location Index
	GLint uniformLocation;

	//Bind RenderTexture with uniform location 0
	uniformLocation = blurPass->getAtt("hbao_texture");
	glUniform1i(uniformLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	check_gl_error();
	glBindTexture(GL_TEXTURE_2D, gResource->getTexture("HBAO_texture"));

	//Do the actual drawing process
	blurPass->render(gResource->getVAO("quadTexture"), 6, 0);

	//Unbind and bind default buffer instead
	blurBuffer->Unbind();


#pragma endregion


	//-------------------------------//

#pragma region SCREEN_PASS
	{
		//Clear defaultBuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Reference Shader Object
		Shader *sPass = gRenderer->getShader("SCREEN_PASS");

		//Use program
		glUseProgram(sPass->getIndexProgram());

		//Reference for Texture Location Index
		GLint uniformLocation;

		//Bind RenderTexture with uniform location 0
		uniformLocation = sPass->getAtt("rgb_texture");
		glUniform1i(uniformLocation, 0);
		glActiveTexture(GL_TEXTURE0);
		check_gl_error();
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_renderTexture"));

		//Bind NormalsTexture with uniform location 1
		uniformLocation = sPass->getAtt("normals_texture");
		glUniform1i(uniformLocation, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_normalsTexture"));

		//Bind DepthTexture with uniform location 2
		uniformLocation = sPass->getAtt("depth_texture");
		glUniform1i(uniformLocation, 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("testFBO_depthTexture"));

		//Bind HBAOTexture with uniform location 3
		uniformLocation = sPass->getAtt("hbao_texture");
		glUniform1i(uniformLocation, 3);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("HBAO_texture"));

		//Bind HBAOTexture with uniform location 3
		uniformLocation = sPass->getAtt("blur_texture");
		glUniform1i(uniformLocation, 4);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, gResource->getTexture("Blur_texture"));

		//Update zNear and zFar
		uniformLocation = sPass->getAtt("zNear");
		glUniform1f(uniformLocation, near);
		uniformLocation = sPass->getAtt("zFar");
		glUniform1f(uniformLocation, far);

		//Change Mode
		uniformLocation = sPass->getAtt("mode");
		glUniform1i(uniformLocation, mode);

		//Do the actual drawing process
		sPass->render(gResource->getVAO("quadTexture"), 6, 0);
	}

#pragma endregion

}

void App::updateMouse()
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		double x, y;
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glfwGetCursorPos(window, &x, &y);

		//cout << "x: " << x << "\ty: " << y << endl;


	}
}

void App::updateKeyboard()
{
	updateInputCamera();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		mode = 0;

	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		mode = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		mode = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		mode = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		mode = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		mode = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		mode = 6;
	}

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		whatIsChanging = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		whatIsChanging = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		whatIsChanging = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		whatIsChanging = 3;
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		switch (whatIsChanging)
		{
		case 0:
			mat = glm::translate(mat, glm::vec3(0.1, 0, 0));
			break;
		case 1:
			fov += 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 2:
			near += 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 3:
			far += 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		switch (whatIsChanging)
		{
		case 0:
			mat = glm::translate(mat, glm::vec3(-0.1, 0, 0));
			break;
		case 1:
			fov -= 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 2:
			near -= 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 3:
			far -= 0.283;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		switch (whatIsChanging)
		{
		case 0:
			mat = glm::translate(mat, glm::vec3(0, 0.1, 0));
			break;
		case 1:
			fov += 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 2:
			near += 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 3:
			far += 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		default:
			break;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		switch (whatIsChanging)
		{
		case 0:
			mat = glm::translate(mat, glm::vec3(0, -0.1, 0));
			break;
		case 1:
			fov -= 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 2:
			near -= 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		case 3:
			far -= 0.1;
			gRenderer->updateAllShadersProj(glm::perspective<float>(fov, widthScreen / (float)heightScreen, near, far));

			break;
		default:
			break;
		}
	}


	static bool doProjection = true;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && doProjection)
	{
		doProjection = false;
		cout << "Projection Matrix: \n";
		cout << "FOV -> " << fov << endl;
		cout << "Near -> " << near << endl;
		cout << "Far -> " << far << endl;


	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
	{
		doProjection = true;
	}

	static bool doHelp = true;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && doHelp)
	{
		doHelp = false;
		cout << "Commands: \n";
		cout << "'W', 'A', 'S', 'D', 'E', 'Q', '+', '-' -> move the camera.\n";
		cout << "Right and left arrow -> increase or decrease the value that is changing.\n";
		cout << "To change what is changing:\n";
		cout << "	C -> translate of model;\n";
		cout << "	F -> FOV;\n";
		cout << "	N -> near plane;\n";
		cout << "	M -> far plane.\n";
		cout << "P -> write the current variables of the projection matrix\n";

	}
	else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
	{
		doHelp = true;
	}



}

void App::updateInputCamera()
{

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.translate(0.1);
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.translate(-0.1);
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SlideRight();
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SlideLeft();
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.addAngle(-5);
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.addAngle(5);
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	{
		camera.addEyeY(0.1);
		updateCamera();
		gClick->changeFrameBuffer();

	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		camera.addEyeY(-0.1);
		updateCamera();
		gClick->changeFrameBuffer();

	}
}

void App::updateCamera()
{
	float dx, dy, dz;
	camera.getDirection(dx, dy, dz);
	gRenderer->updateAllShadersView(glm::lookAt(glm::vec3(camera.eyeX(), camera.eyeY(), camera.eyeZ()), glm::vec3(dx, dy, dz), glm::vec3(0, 1, 0)));
}

