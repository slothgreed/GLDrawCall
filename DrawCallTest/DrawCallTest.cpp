// DrawCallTest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//


#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
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
	input.SetEvent(KI_MOUSE_EVENT::MOUSE_EVENT_WHEEL);
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
	input.SetEvent(KI_MOUSE_EVENT::MOUSE_EVENT_MOVE);

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_LEFT);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_MIDDLE);
	}

	if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPress(KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}
	else
	{
		input.SetRelease(KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT);
	}

	Application()->ProcessMouseEvent(input);
}

void MouseButtonCallBack(GLFWwindow* window, int button, int action, int mods)
{
	KI_MOUSE_BUTTON mouseButton;
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

void DrawCallTest::Execute()
{
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Can't initilize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x アンチエイリアス
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL3.3を使います。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS用:必ずしも必要ではありません。
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 古いOpenGLは使いません。


	GLFWwindow* window; // (ソースコードではこの変数はグローバルです。)
	window = glfwCreateWindow(1024, 768, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "GLFWウィンドウのオープンに失敗しました。 もしIntelのGPUならば, 3.3に対応していません。チュートリアルのバージョン2.1を試してください。n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window); // GLEWを初期化する
	glewExperimental = true; // コアプロファイルで必要となります。
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "GLEWの初期化に失敗しました。n");
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
	glfwSetScrollCallback(window, ScrollCallBack);	// mouse wheel;
	glfwSetWindowSizeCallback(window, WindowSizeCallBack);
	glfwSwapInterval(0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	int range = 60;
	//auto primitive = std::make_shared<Sphere>(glm::vec3(0), 0.1, 16, 16);
	auto primitive = std::make_shared<Sphere>(glm::vec3(0), 0.1, 16, 16);
	//auto primitive = std::make_shared<Triangle>();
	//primitive->Convert(IPrimitive::StoreType::Interleave);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	//DrawElementsDrawer drawer;
	//MultiDrawElementsDrawer drawer;
	//DrawElementsInstancedDrawer drawer;
	DrawElementsIndirectDrawer drawer;
	drawer.BuildRenderItem(primitive, range);
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

		drawer.Draw(m_pCamera->Projection(),m_pCamera->ViewMatrix());

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
// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
