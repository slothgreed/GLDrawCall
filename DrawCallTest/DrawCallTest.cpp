// DrawCallTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#include <iostream>

#include "Mouse.h"
#include "MouseInput.h"
#include "DrawCallTest.h"
#include "CameraController.h"
#include "PerspectiveCamera.h"
#include "Profiler.h"

DrawCallTest* m_instance;
DrawCallTest* Application()
{
	return m_instance;
}
void ScrollCallBack(GLFWwindow* window, double x, double y)
{
	MouseInput input;
	input.SetWheel((int)y);
	input.SetEvent(MY_MOUSE_EVENT::MOUSE_EVENT_WHEEL);
	Application()->ProcessMouseEvent(input);
}

void WindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	MouseInput input;
	input.SetPosition((float)xpos, (float)ypos);
	input.SetEvent(MY_MOUSE_EVENT::MOUSE_EVENT_MOVE);

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		input.SetPress(MY_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}
	else
	{
		input.SetRelease(MY_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		input.SetPress(MY_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}
	else
	{
		input.SetRelease(MY_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPress(MY_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}
	else
	{
		input.SetRelease(MY_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}

	Application()->ProcessMouseEvent(input);
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	MY_MOUSE_BUTTON mouseButton;
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		mouseButton = MOUSE_BUTTON_LEFT;
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		mouseButton = MOUSE_BUTTON_MIDDLE;
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		mouseButton = MOUSE_BUTTON_RIGHT;
		break;
	default:
		break;
	}

	double posX;
	double posY;
	glfwGetCursorPos(window, &posX, &posY);

	MouseInput input;
	input.SetPosition((float)posX, (float)posY);
	if (action == GLFW_PRESS)
	{
		input.SetEvent(MOUSE_EVENT_DOWN);
		input.SetPress(mouseButton);
	}
	else
	{
		input.SetEvent(MOUSE_EVENT_UP);
		input.SetRelease(mouseButton);
	}

	Application()->ProcessMouseEvent(input);
}

void DrawCallTest::ProcessMouseEvent(const MouseInput& input)
{
	m_pMouse->ApplyMouseInput(input);

	if (input.Event() == MOUSE_EVENT_WHEEL)
	{
		m_pCameraController->Wheel(*m_pMouse.get());
	}
	else if (input.Event() == MOUSE_EVENT_MOVE)
	{
		m_pCameraController->Move(*m_pMouse.get());
	}
}

void CreateMatrix(int range, std::vector<mat4x4>& matrices)
{
	matrices.resize(range * range * range);
	for (int x = 0; x < range; x++)
	{
		for (int y = 0; y < range; y++)
		{
			for (int z = 0; z < range; z++)
			{
				int index = x * range * range + y * range + z;
				matrices[index] = glm::translate(mat4x4(1), vec3(x, y, z));
			}
		}
	}
}

void DrawCallTest::Execute(const TestArgs& args)
{
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Can't initilize GLFW" << std::endl;
		return;
	}

	GLFWwindow* window = glfwCreateWindow(1024, 768, "DrawCallTest", NULL, NULL);
	if (window == NULL) {
		return;
	}
	glfwMakeContextCurrent(window); 
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		return;
	}

	m_instance = this;
	m_pMouse = std::make_unique<Mouse>();
	auto pCamera = std::make_shared<PerspectiveCamera>();
	pCamera->Perspective(45, 1, 0.1, 100);
	pCamera->LookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera = pCamera;

	m_pCameraController = std::make_unique<CameraController>(m_pCamera);
	glfwSetCursorPosCallback(window, CursorPosCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallBack);
	glfwSetScrollCallback(window, ScrollCallBack);	
	glfwSetWindowSizeCallback(window, WindowSizeCallBack);
	glfwSwapInterval(0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	int range = args.Range();
	Primitives primitives;
	primitives.push_back(std::make_unique<Cone>(0.1f, 0.1f, 16));
	primitives.push_back(std::make_unique<Cube>(glm::vec3(-0.1f), vec3(0.1f)));
	primitives.push_back(std::make_unique<Cylinder>(0.1f, 0.1f, 0.1f, 16));
	primitives.push_back(std::make_unique<Sphere>(0.1f, 16, 16));
	primitives.push_back(std::make_unique<Torus>(0.05f, 0.1f, 16, 16));

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	std::unique_ptr<IDrawer> drawer;
	switch (args.Type())
	{
	case DRAWER_BEGIN_END:
		drawer = std::make_unique<BeginEndDrawer>();
		break;
	case DRAWER_DRAW_ELEMENT:
		drawer = std::make_unique<DrawElementsDrawer>();
		break;
	case DRAWER_MULTI_DRAW_ELEMENT:
		drawer = std::make_unique<MultiDrawElementsDrawer>();
		break;
	case DRAWER_DRAW_ELEMENTS_INSTANCED:
		drawer = std::make_unique<DrawElementsInstancedDrawer>();
		break;
	case DRAWER_DRAW_ELEMENTS_INDIRECT:
		drawer = std::make_unique<DrawElementsIndirectDrawer>();
		break;
	default:
		assert(0);
		break;
	}

	std::vector<glm::mat4x4> matrices;
	CreateMatrix(range, matrices);
	drawer->BuildRenderItem(primitives, std::move(matrices));
	pCamera->FitToBDB(BDB(vec3(0), vec3(range, range, range)));
	
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);	// GLenum mode
	Profile profiler;
	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		profiler.Start();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawer->Draw(m_pCamera->Projection(),m_pCamera->ViewMatrix());

		profiler.Stop();
		profiler.Output();
		glfwSwapBuffers(window);

		glfwWaitEvents();
		OUTPUT_GLERROR;
	}


}

void DrawCallTest::Finalize()
{
	glfwTerminate();
}
