#include "pch.h"

void getError()
{
	GLenum error = glGetError(); if (error != 0) { assert(0); }
}