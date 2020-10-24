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
		printf("%s	:: ����: %5dȸ ����: %5dȸ �����ֱ�: %5.1fh �����ֱ�: %8.1fd �̽ɷ�: %.3f ����: %6.3f ������: %5.1f�� ������: %.2f��\n", 
			mName, mRotationCount + (int)(mRotationTime*10/mRotationSpeed), mRevolutionCount, mRotationSpeed, mRevolutionSpeed/24.f,
			mEccentricity, mMajorAxis, mRotationAxis, mRevolutionAxis
			);
	}
private:
	void GetCalculateRevolutionMatrix();
private:
	char* mName;
	// ���� �༺
	Planet* mParent;
	// ���� �Ķ����
	float mRotationAxis;
	float mRotationSpeed;
	float mRotationTime;
	int mRotationCount;

	// ���� �Ķ����
	float mRevolutionAxis;
	float mRevolutionSpeed;
	float mRevolutionTime;
	int mRevolutionCount;

	// ����
	float mMajorAxis;
	// ����
	float mMinorAxis;
	// �̽ɷ�
	float mEccentricity;

	float mSize;
	float* mPosition;
	float* mRotation;

	// �ؽ���
	GLUquadric* mSphere;
	unsigned int mTextureObject;
	AUX_RGBImageRec* mTexture;

	// ��ü ���׸���
	GLfloat* mAmbient = new GLfloat[4]{ 0.08f, 0.08f, 0.08f, 1.0f };
	GLfloat* mDiffuse = new GLfloat[4]{ 1, 1, 1, 1.0f };
	GLfloat* mSpecular = new GLfloat[4]{ 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat* mShininess = new GLfloat[1]{ 25.0f };
};

