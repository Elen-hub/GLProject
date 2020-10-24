#pragma once

#include "GL/glut.h"

class Light
{
public:
    Light();
    void Enabled();
    void Disabled();
    void SetPosition(GLfloat* pos);
private:
    const GLfloat mAmbientArr[4] = { 1, 1, 1, 1.0f };
    const GLfloat mDiffuseArr[4] = { 1, 1, 1, 1.0f };
    const GLfloat mSpecularArr[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};

