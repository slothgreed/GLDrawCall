#ifndef PCH_H
#define PCH_H
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <memory>

using namespace std;
using namespace glm;

#include "IDrawer.h"

#include "BeginEndDrawer.h"
#include "DrawElementsDrawer.h"
#include "DrawElementsIndirectDrawer.h"
#include "DrawElementsInstancedDrawer.h"
#include "MultiDrawElementsDrawer.h"

#include "IPrimitive.h"

#include "Cone.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Torus.h"
#include "Triangle.h"


enum MY_MOUSE_BUTTON : unsigned int
{
	MOUSE_BUTTON_LEFT = 1,
	MOUSE_BUTTON_RIGHT = 2,
	MOUSE_BUTTON_MIDDLE = 4
};


enum MY_MOUSE_EVENT
{
	MOUSE_EVENT_WHEEL,
	MOUSE_EVENT_DOWN,
	MOUSE_EVENT_UP,
	MOUSE_EVENT_MOVE
};


void getError();

#define OUTPUT_GLERROR getError();

#endif  PCH_H
