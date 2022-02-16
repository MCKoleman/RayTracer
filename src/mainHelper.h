#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include "scene.h"
#include "sphere.h"
#include "tetrahedron.h"
#include "plane.h"
#pragma once

// Image settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const float MOVE_MOD = 0.05f;
const float LOOK_MOD = 15.0f;
const int WIDTH = 512;
const int HEIGHT = 512; // Width and height must be powers of 2

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
bool processInput(GLFWwindow* window, Scene* scene);
void RaytraceScene(Scene* scene);
glm::vec3 RaytracePixel(Scene* scene, Ray viewRay, unsigned int depth);
Scene* InitScene();