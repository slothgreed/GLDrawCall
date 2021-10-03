#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "ICamera.h"
#include "Mouse.h"
class CameraController
{
public:
	CameraController(std::shared_ptr<ICamera> pCamera) :m_pCamera(pCamera),m_ZoomRatio(0.1f) {};
	~CameraController() {};
	bool Move(const Mouse& mouse);
	bool Wheel(const Mouse&  mouse);
private:
	void Zoom(float ratio);
	void Rotate(const vec2& move);
	void Translate(const vec2& move);
	float m_ZoomRatio;

	std::shared_ptr<ICamera> m_pCamera;

};

#endif CAMERA_CONTROLLER_H