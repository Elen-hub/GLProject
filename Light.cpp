#include "Light.h"

Light::Light()
{
    // ���� ���̵�
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, mAmbientArr);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, mDiffuseArr);
    glLightfv(GL_LIGHT0, GL_SPECULAR, mSpecularArr);
    // ���� �ֺ���
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, new float[4]{ 1.f, 0.6f, 0.6f, 1.f });
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.7f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void Light::Enabled()
{
    // ���� Ȱ��ȭ
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