#pragma once
#include "GL/glaux.h"
#include "GL/glut.h"
class Culling
{
public:
	Culling();
	inline void Enabled()
	{
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
	inline void Disabled()
	{
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
};

