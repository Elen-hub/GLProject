#include "Camera.h"
#include "GL/glut.h"
#include <math.h>

Camera::Camera()
{

}
void Camera::Enabled(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, (GLfloat)w / (GLfloat)h, 1.0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Camera::SetCameraPos()
{
	gluLookAt(mCameraPos.x, mCameraPos.y, mCameraPos.z, mCameraView.x, mCameraView.y, mCameraView.z, mCameraUp.x, mCameraUp.y, mCameraUp.z);
}
void Camera::MoveCamera(float speed)
{
    mZoom += speed;
    mCameraPos = fVector3(0, 0, mZoom);
}
void Camera::RotateXAxis(float x, float y)
{
    x *= 0.01f;
    y *= 0.01f;
    if (x != 0)
    {
        fVector3 vec = mCameraPos - mCameraView;
        mCameraPos.z = mCameraView.z + sin(x) * vec.x + cos(x) * vec.z;
        mCameraPos.x = mCameraView.x + cos(x) * vec.x - sin(x) * vec.z;
    }
    if (y != 0)
    {
        fVector3 vec = mCameraPos - mCameraView;
        mCameraPos.z = mCameraView.z + sin(y) * vec.y + cos(y) * vec.z;
        mCameraPos.y = mCameraView.y + cos(y) * vec.y - sin(y) * vec.z;
    }
}
