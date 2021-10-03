#ifndef ORTHO_CAMERA_H
#define	ORTHO_CAMERA_H
#include "ICamera.h"

class OrthoCamera : public ICamera
{
public:

	struct OrthoParameter
	{
		float m_left;
		float m_right;
		float m_bottom;
		float m_top;
		float m_near;
		float m_far;
	};

	OrthoCamera();
	~OrthoCamera();
	CAMERA_TYPE Type() override { return CAMERA_TYPE::CAMERA_TYPE_ORTHO; };
	void Ortho(float left, float right, float bottom, float top, float _near, float _far);
	void Ortho(const OrthoParameter& ortho);
	virtual void FitToBDB(const BDB& bdb) override;

	void GetOrtho(OrthoParameter* _far);
	float GetWidth();
	float GetHeight();
	float GetDepth();
	vec3 GetCenter();
private:
	OrthoParameter m_ortho;

};

#endif // ORTHO_CAMERA_H