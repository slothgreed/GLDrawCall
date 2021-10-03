#ifndef DRAE_CALL_TEST_H
#define	DRAE_CALL_TEST_H

class Mouse;
class MouseInput;
class ICamera;
#include "IRenderItem.h"
#include "CameraController.h"
class DrawCallTest
{
public:
	DrawCallTest() {};
	~DrawCallTest() {};

	void Execute();
	void Finalize();
	void ProcessMouseEvent(const MouseInput& input);

private:
	std::vector<std::unique_ptr<IRenderItem>> m_pRenderItems;
	std::unique_ptr<Mouse> m_pMouse;
	std::shared_ptr<ICamera> m_pCamera;
	std::unique_ptr<CameraController> m_pCameraController;
};

static DrawCallTest* TheApp();

#endif // DRAE_CALL_TEST_H