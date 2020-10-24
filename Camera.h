#pragma once
#include "fVector3.h"

class Camera
{
public:
	Camera();
	void Enabled(int w ,int h);
	float mZoom = 10.f;
	void SetCameraPos();
	void MoveCamera(float speed);
	void RotateXAxis(float x, float y);
public:
	fVector3 mCameraPos = fVector3(0, 0, 10);
	fVector3 mCameraView = fVector3(0, 0, 0);
	fVector3 mCameraUp = fVector3(0, 1, 0);
};

