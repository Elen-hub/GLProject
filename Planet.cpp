#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <cmath>
#include "Planet.h"

// 행성 이름, 텍스쳐 이름, 행성 크기, 자전 주기, 자전 축
Planet::Planet(char* name, char* textureName, const float size, const float rotationSpeed, float rotationAxis)
{
	mName = name;
	mSphere = gluNewQuadric();
	gluQuadricDrawStyle(mSphere, GL_FILL);
	gluQuadricDrawStyle(mSphere, GL_TRUE);
	gluQuadricTexture(mSphere, GL_TRUE);

	FILE* pFile = NULL;
	pFile = fopen(textureName, "r");
	if (pFile)
	{
		if (mTexture = auxDIBImageLoad(textureName))
		{
			glGenTextures(1, &mTextureObject);
			glBindTexture(GL_TEXTURE_2D, mTextureObject);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, 3, mTexture->sizeX, mTexture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, mTexture->data);
		}
		fclose(pFile);
	}
	mSize = size;
	mRotationSpeed = rotationSpeed;
	mRotationAxis = rotationAxis;
	mRotationTime = 0;

	mPosition = new float[3] { 0.f, 0.f, 0.f };
	mRotation = 0;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);

}
// 공전타겟, 공전주기, 공전 축, 장축의 길이, 이심률
void Planet::SetRevolution(Planet* parent, const float revolutionSpeed, const float revolutionAxis, const float majorAxis, float eccentricity)
{
	mParent = parent;
	mRevolutionSpeed = revolutionSpeed * 24;
	mRevolutionAxis = revolutionAxis;
	mRevolutionTime = 0;
	mMajorAxis = majorAxis;
	mEccentricity = eccentricity;
	// 단축
	mMinorAxis = majorAxis * sqrtf(1 - eccentricity * eccentricity);
}
float* Planet::GetPosition()
{
	return mPosition;
}
void Planet::GetCalculateRevolutionMatrix()
{
	float t = mRevolutionTime / mRevolutionSpeed * 2 * M_PI;
	mPosition[0] = mMajorAxis * cos(t);
	mPosition[1] = mMinorAxis * sin(t);
}
void Planet::Draw(bool drawLine)
{
	GetParameterArr();
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glRotatef(90, 1, 0, 0);
		// 공전 연산
		if (mParent)
		{
			glRotatef(mRevolutionAxis, 1, 1, 0);
			glTranslatef(mParent->GetPosition()[0], mParent->GetPosition()[1], mParent->GetPosition()[2]);
			GetCalculateRevolutionMatrix();
			if (drawLine)
			{
				glPushMatrix();
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; ++i)
				{
					float t = i * M_PI / 180.f;
					glVertex3f(mMajorAxis * cos(t)+ mMinorAxis * 0.5f, mMinorAxis * sin(t), 0);
				}
				glEnd();
				glPopMatrix();
			}
			glTranslatef(mPosition[0] + mMinorAxis*0.5f, mPosition[1], mPosition[2]);
		}
		// 자전 연산
		glRotatef(360*mRotationTime / mRotationSpeed, 0, 0, 0.01f * mRotationAxis);
		glBindTexture(GL_TEXTURE_2D, mTextureObject);
		gluSphere(mSphere, mSize, 200, 200);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void Planet::SetAmbient(float* ambientArr)
{
	mAmbient = ambientArr;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbient);
}
void Planet::SetDiffuse(float* diffuseArr)
{
	mDiffuse = diffuseArr;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
}
void Planet::SetSpecular(float* specularArr)
{
	mSpecular = specularArr;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
}
void Planet::SetShininess(float* shininess)
{
	mShininess = shininess;
	glMaterialfv(GL_FRONT, GL_SHININESS, mShininess);
}
// 0.01초 = 1시간 , 1초 = 100시간 (4.16일) 87.7초 = 365일
void Planet::NextFrame(float deltaTime)
{
	// 자전속도는 원래 속도의 1/10으로 적용 (지구 기준 240시간, 프로그램 2.4초)
	mRotationTime += deltaTime*0.1;
	if (mRotationTime >= mRotationSpeed)
	{
		mRotationTime -= mRotationSpeed;
		mRotationCount += 10;
	}
	// 종속된 행성이 있다면 공전
	if (mParent)
	{
		mRevolutionTime += deltaTime;
		if (mRevolutionTime >= mRevolutionSpeed)
		{
			mRevolutionTime -= mRevolutionSpeed;
			mRevolutionCount += 1;
		}
	}
}