#pragma once

#include "GL/glaux.h"
#include "GL/glut.h"

class Planet
{
public:
	Planet(char* name, char* textureName, const float size, const float rotationSpeed, float rotationAxis);
	void SetRevolution(Planet* parent, const float revolutionSpeed, const float revolutionAxis, const float majorAxis, float eccentricity);
	void NextFrame(float deltaTime);
	float* GetPosition();
	void Draw(bool drawLine);
	void SetAmbient(float* ambientArr);
	void SetDiffuse(float* diffuseArr);
	void SetSpecular(float* specularArr);
	void SetShininess(float* shininess);
	inline void GetParameterArr()
	{
		printf("%s	:: 자전: %5d회 공전: %5d회 자전주기: %5.1fh 공전주기: %8.1fd 이심률: %.3f 장축: %6.3f 자전축: %5.1f도 공전축: %.2f도\n", 
			mName, mRotationCount + (int)(mRotationTime*10/mRotationSpeed), mRevolutionCount, mRotationSpeed, mRevolutionSpeed/24.f,
			mEccentricity, mMajorAxis, mRotationAxis, mRevolutionAxis
			);
	}
private:
	void GetCalculateRevolutionMatrix();
private:
	char* mName;
	// 공전 행성
	Planet* mParent;
	// 자전 파라메터
	float mRotationAxis;
	float mRotationSpeed;
	float mRotationTime;
	int mRotationCount;

	// 공전 파라메터
	float mRevolutionAxis;
	float mRevolutionSpeed;
	float mRevolutionTime;
	int mRevolutionCount;

	// 장축
	float mMajorAxis;
	// 단축
	float mMinorAxis;
	// 이심률
	float mEccentricity;

	float mSize;
	float* mPosition;
	float* mRotation;

	// 텍스쳐
	GLUquadric* mSphere;
	unsigned int mTextureObject;
	AUX_RGBImageRec* mTexture;

	// 물체 메테리얼
	GLfloat* mAmbient = new GLfloat[4]{ 0.08f, 0.08f, 0.08f, 1.0f };
	GLfloat* mDiffuse = new GLfloat[4]{ 1, 1, 1, 1.0f };
	GLfloat* mSpecular = new GLfloat[4]{ 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat* mShininess = new GLfloat[1]{ 25.0f };
};

