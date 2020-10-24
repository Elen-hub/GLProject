#include "Light.h"

Light::Light()
{
    // 구로 셰이딩
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, mAmbientArr);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mDiffuseArr);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mSpecularArr);
    // 전역 주변광
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, new float[4]{ 1.f, 0.6f, 0.6f, 1.f });
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.7f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void Light::Enabled()
{
    // 광원 활성화
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}
void Light::Disabled()
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, new float[4] {0,0,0,0});
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}
void Light::SetPosition(GLfloat* pos)
{
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}