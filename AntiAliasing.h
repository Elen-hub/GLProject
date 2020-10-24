#pragma once
#include "GL/glaux.h"
#include "GL/glut.h"

class AntiAliasing
{
public:
	AntiAliasing();
	inline void SetAntiAilasing(bool activate)
	{
		if (activate)
		{
			glEnable(GL_BLEND);
			glEnable(GL_POINT_SMOOTH);
			glEnable(GL_LINE_SMOOTH);
			glEnable(GL_POLYGON_SMOOTH);
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		}
		else
		{
			glDisable(GL_BLEND);
			glDisable(GL_POINT_SMOOTH);
			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_POLYGON_SMOOTH);
			glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
		}
	}
};

