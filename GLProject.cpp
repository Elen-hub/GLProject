#pragma once

#include <iostream>
#include "Light.h"
#include <vector>
#include "Planet.h"
#include "GL/glut.h"
#include "fVector3.h"
#include "Camera.h"
#include "AntiAliasing.h"
#include "Culling.h"

Culling* mCulling;
Light* mLight;
Camera* mCamera;
AntiAliasing* mAntiAliasing;
std::vector<Planet*> mPlanetVector;
fVector3 mClickPos = fVector3(0, 0, 0);
float mTimeSpeed = 1;
float mTime = 0;
bool mbUseAntiAliasing = true;
bool mbUseCulling = true;
bool mbUseLight = true;
bool mbUseCameraMove;
bool mbUseRevolutionLine;

void Display()
{
    char* a;
    char* c;
    char* l;
    mAntiAliasing ? a = new char[] {"활성화"} : a = new char[] {"비활성화"};
    mbUseCulling ? c = new char[] {"활성화"} : c = new char[] {"비활성화"};
    mbUseLight ? l = new char[] {"활성화"} : l = new char[] {"비활성화"};
    system("cls");
    printf("진행시간: %d시간(%d일), 속도: 1초당 %d시간 \n\n", (int)mTime, (int)(mTime/24.f), (int)mTimeSpeed*24);
    printf("안티엘리어싱: %s\n은면,후면제거: %s\n라이팅: %s\n", a, c, l);
    mAntiAliasing->SetAntiAilasing(mbUseAntiAliasing);
    // 0번 광원 위치
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);

    mCamera->SetCameraPos();

    GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, -5.0f };
    mLight->SetPosition(lightPosition);
    mLight->Disabled();

    mPlanetVector[0]->Draw(false);
    if(mbUseLight)
        mLight->Enabled();
    for (int i = 1; i < mPlanetVector.size(); ++i)
        mPlanetVector[i]->Draw(mbUseRevolutionLine);

    glPopMatrix();
    glFlush();
}
void Reshape(int w, int h)
{
    mCamera->Enabled(w, h);
}
void OnTimerAnimation(int value)
{
    for (int i = 0; i < mPlanetVector.size(); ++i)
        mPlanetVector[i]->NextFrame(mTimeSpeed);

    mTime += mTimeSpeed;
    glutPostRedisplay();
    glutTimerFunc(10, OnTimerAnimation, 1);
}
void OnMouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        mbUseCameraMove = state == GLUT_DOWN;
        mClickPos.x = x;
        mClickPos.y = y;
    }
}
void OnMouseDrag(int x, int y)
{
    if (!mbUseCameraMove)
        return;

    mCamera->RotateXAxis(x- mClickPos.x, y - mClickPos.y);
    mClickPos.x = x;
    mClickPos.y = y;
    glutPostRedisplay();
}
void OnKeyboardEvent(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        mCamera->MoveCamera(-1.f);
        break;
    case 's':
    case 'S':
        mCamera->MoveCamera(1.f);
        break;
    case 't':
    case 'T':
        ++mTimeSpeed;
        break;
    case 'r':
    case 'R':
        mTimeSpeed = 1;
    }
    glutPostRedisplay();
}
void OnMainMenu(int entryID)
{
    switch (entryID)
    {
    case 1:
        mbUseCulling = !mbUseCulling;
        mbUseCulling ? mCulling->Enabled() : mCulling->Disabled();
        break;
    case 2:
        mbUseAntiAliasing = !mbUseAntiAliasing;
        break;
    case 3:
        mbUseRevolutionLine = !mbUseRevolutionLine;
    default:;
    }
}
void OnLightMenu(int entryID)
{
    mbUseLight = entryID;
    entryID ? mLight->Enabled() : mLight->Disabled();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Example");

    mLight = new Light();
    mLight->Enabled();
    mCamera = new Camera();
    mCamera->Enabled(500, 500);
    mAntiAliasing = new AntiAliasing();
    mCulling = new Culling();
    mCulling->Enabled();

    Planet* sun = new Planet(new char[] {"Sun"}, new char[] {"sunmap.BMP"}, .2f, 200, 20);
    mPlanetVector.push_back(sun);
    sun->SetAmbient(new float[4]{ 1.f, 1.f, 1.f, 1.f });
    Planet* earth = new Planet(new char[] {"Earth"}, new char[] {"earthmap.bmp"}, .1f, 24.f, 23.4f);
    earth->SetRevolution(sun, 365.f,0, 1.496f, 0.0167f);
    mPlanetVector.push_back(earth);
    Planet* mercury = new Planet(new char[] {"Mercury"}, new char[] {"mercurymap.bmp"}, .0382f, 58, 0.05f);
    mercury->SetRevolution(sun, 87.965f, 7, 0.579f, 0.2506f);
    mPlanetVector.push_back(mercury);
    Planet* venus = new Planet(new char[] {"Venus"}, new char[] {"venusmap.bmp"}, .09488f, 243, 177.35f);
    venus->SetRevolution(sun, 137.97f, 3.39f, 1.082f, 0.0067f);
    mPlanetVector.push_back(venus);
    Planet* mars = new Planet(new char[] {"Mars"}, new char[] {"marsmap.bmp"}, .05315f, 24.6f, 25.19f);
    mars->SetRevolution(sun, 686.565f, 1.85f, 2.279f, 0.0935f);
    mPlanetVector.push_back(mars);
    Planet* jupiter = new Planet(new char[] {"Jupiter"}, new char[] {"jupitermap.bmp"}, 1.096f, 9.8f, 3.13f);
    jupiter->SetRevolution(sun, 4328.9f,1.31f, 7.786f, 0.0489f);
    mPlanetVector.push_back(jupiter);
    Planet* saturn = new Planet(new char[] {"Saturn"}, new char[] {"saturnmap.bmp"}, 0.913f, 10.25f, 26.73f);
    saturn->SetRevolution(sun, 10752.9f, 2.49f, 14.33f, 0.0565f);
    mPlanetVector.push_back(saturn);
    Planet* uranus = new Planet(new char[] {"Uranus"}, new char[] {"uranusmap.bmp"}, 0.39764f, 17.25f,97.77f);
    uranus->SetRevolution(sun, 30663.65f, 0.77f, 28.72f, 0.0457f);
    mPlanetVector.push_back(uranus);
    Planet* neptune = new Planet(new char[] {"Neptune"}, new char[] {"neptunemap.bmp"}, 0.38604f, 16.1f, 28.32f);
    neptune->SetRevolution(sun, 60148.35f, 1.77f, 44.95f, 0.0113f);
    mPlanetVector.push_back(neptune);

    GLint lightMenu = glutCreateMenu(OnLightMenu);
    glutAddMenuEntry("LightOn", 1);
    glutAddMenuEntry("LightOff", 0);
    GLint mainMenu = glutCreateMenu(OnMainMenu);
    glutAddMenuEntry("Culling", 1);
    glutAddMenuEntry("AntiAliasing", 2);
    glutAddMenuEntry("DrawRevolutionLine", 3);
    glutAddSubMenu("Lighting", lightMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutTimerFunc(10, OnTimerAnimation, 1);
    glutMouseFunc(OnMouseEvent);
    glutMotionFunc(OnMouseDrag);
    glutKeyboardFunc(OnKeyboardEvent);

    glutMainLoop();
    return 0;
}