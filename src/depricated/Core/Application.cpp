#include "Application.h"
#include "moduleDefinitions.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <stdexcept>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <cmath>
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

USING_NAMESPACE_TGAME_CORE

std::function<void()> registered_loop;
void loop_iteration() { registered_loop(); }

Application *currentApplication = NULL;

Application &Application::getInstance()
{
  if (currentApplication)
    return *currentApplication;
  else
    throw std::runtime_error("There is no current Application");
}

Application::Application() : state(stateReady), width(TGAME_WINDOW_WIDTH), height(TGAME_WINDOW_HEIGHT), title(TGAME_WINDOW_TITLE)
{
  currentApplication = this;

  std::cout << "[Info] GLFW initialisation" << std::endl;

  // initialize the GLFW library
  if (!glfwInit()) { throw std::runtime_error("Couldn't init GLFW"); }

  // setting the opengl version
#ifdef __EMSCRIPTEN__
  // GL 3.0 + GLSL 130
  glslVersion = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#else
  // GL 3.2 + GLSL 150
  glslVersion = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef APPLE
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
#endif

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // create the window
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Couldn't create a window");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();

  if (err != GLEW_OK) {
    glfwTerminate();
    throw std::runtime_error(
      std::string("Could initialize GLEW, error = ") + reinterpret_cast<const char *>(glewGetErrorString(err)));
  }

  // get version info
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported " << version << std::endl;

  // opengl configuration
  glEnable(GL_DEPTH_TEST);// enable depth-testing
  glDepthFunc(GL_LESS);// depth-testing interprets a smaller value as "closer"
}

GLFWwindow *Application::getWindow() { return window; }

void Application::exit() { state = stateExit; }

float Application::getFrameDeltaTime() const { return deltaTime; }

float Application::getTime() const { return time; }

void Application::run()
{
  state = stateRun;

  // Make the window's context current
  glfwMakeContextCurrent(window);

  time = static_cast<float>(glfwGetTime());

  registered_loop = [&]() {
    // compute new time and delta time
    auto t = static_cast<float>(glfwGetTime());
    deltaTime = t - time;
    time = t;

    // Detect window related changes
    detectWindowDimensionChange();

    // ------- execute the frame code -------

    // 1. manage user input
    // -----------------
    glfwPollEvents();
    ProcessInput(deltaTime);

    // update game state
    // -----------------
    Update(deltaTime);

    // render
    // ------
    Render();
    // может вызывать проблемы с определением соотношения экрана
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    PostRender();

    // Swap Front and Back buffers (double buffering)
    glfwSwapBuffers(window);
  };

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop_iteration, 0, 1);
#else
  while (state == stateRun) { loop_iteration(); }
  glfwTerminate();
#endif
}

void Application::detectWindowDimensionChange()
{
  int w, h;
#ifdef __EMSCRIPTEN__
  emscripten_get_canvas_element_size("canvas", &w, &h);
#else
  glfwGetWindowSize(getWindow(), &w, &h);
#endif

  dimensionChanged = (w != width or h != height);
  if (dimensionChanged) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
  }
}

//Application::~Application() {}

int Application::getWidth() { return width; }

int Application::getHeight() { return height; }

float Application::getWindowRatio() { return float(width) / float(height); }

bool Application::windowDimensionChanged() { return dimensionChanged; }
