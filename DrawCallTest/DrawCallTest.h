#ifndef DRAE_CALL_TEST_H
#define	DRAE_CALL_TEST_H

#include "CameraController.h"

enum DRAWER_TYPE
{
	DRAWER_BEGIN_END,
	DRAWER_DRAW_ELEMENT,
	DRAWER_MULTI_DRAW_ELEMENT,
	DRAWER_MULTI_DRAW_ELEMENT_BASE_VERTEX,
	DRAWER_DRAW_ELEMENTS_INSTANCED,
	DRAWER_DRAW_ELEMENTS_INDIRECT,
	DRAWER_MULTI_DRAW_ELEMENTS_INDIRECT,
};

class TestArgs
{
public:
	TestArgs(DRAWER_TYPE type, int range)
		: m_type(type)
		, m_range(range)
	{
		assert(range % 5 == 0);
	}

	DRAWER_TYPE Type() const { return m_type; }
	int Range() const { return m_range;}
private:
	DRAWER_TYPE m_type;
	int m_range;
};


class DrawCallTest
{
public:
	DrawCallTest() {};
	~DrawCallTest() {};

	void Execute(const TestArgs& args);
	void Finalize();
	void ProcessMouseEvent(const MouseInput& input);

private:
	std::unique_ptr<Mouse> m_pMouse;
	std::shared_ptr<PerspectiveCamera> m_pCamera;
	std::unique_ptr<CameraController> m_pCameraController;
};

static DrawCallTest* Application();

#endif // DRAE_CALL_TEST_H