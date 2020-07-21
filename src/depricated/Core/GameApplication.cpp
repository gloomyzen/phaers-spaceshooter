#include "GameApplication.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "GlError.h"
#include "moduleDefinitions.h"

USING_NAMESPACE_TGAME_CORE

GameApplication::GameApplication() : Application()
{
  GlError::glCheckError(__FILE__, __LINE__);
#ifdef __DEBUG__1
  imGuiInstance = new ImGuiLoader(getWindow(), glslVersion);
#endif
}

GameApplication::~GameApplication() {}

void GameApplication::ProcessInput(float dt) {
  // exit on window close button pressed
  if (glfwWindowShouldClose(getWindow())) {
    dt += dt;
    exit();
  }
}
void GameApplication::Update(float dt) {
  dt += dt;
#ifdef __DEBUG__1
  imGuiInstance->Update(dt);
#endif
}
void GameApplication::Render() {
#ifdef __DEBUG__1
  imGuiInstance->Render();
#endif
}

void GameApplication::PostRender() {
#ifdef __DEBUG__1
  imGuiInstance->PostRender();
#endif
}
