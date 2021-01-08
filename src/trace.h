#pragma once

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"

#include<time.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define MAXFRAME 300.0

void makebox(double width, double height, double length, GLenum type=GL_LINE_LOOP);
