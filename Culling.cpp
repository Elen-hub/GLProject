#include "Culling.h"

Culling::Culling()
{
	glCullFace(GL_CW);
	glFrontFace(GL_CCW);
}