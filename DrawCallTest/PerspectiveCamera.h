#ifndef PERSPECTIVE_CAMERA_H
#define	PERSPECTIVE_CAMERA_H
#include "ICamera.h"
class PerspectiveCamera : public ICamera
{
public:
	PerspectiveCamera();
	~PerspectiveCamera() {};

	CAMERA_TYPE Type() override { return CAMERA_TYPE::CAMERA_TYPE_PERSPECTIVE; };
	void Perspective(float fov, float aspect, float _near, float _far);
	void MoveWithSpherical(const vec2& move);
	const float Phi() const { return m_phi; }
	const float Theta() const { return m_theta; }
	virtual void FitToBDB(const BDB& bdb) override;

private:
	void SphericalToCartesian(float radius, float x, float y, vec3& result);
	void SetTheta(float value);
	void SetPhi(float value);

	float m_fov;
	float m_aspect;
	float m_near;
	float m_far;

	float m_theta;
	float m_phi;
};
#endif // PERSPECTIVE_CAMERA_H