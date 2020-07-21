#ifndef TGAME_APPLICATION_H
#define TGAME_APPLICATION_H

#include <string>
#include "moduleDefinitions.h"

struct GLFWwindow;

/// Application class:
/// * init OpenGL
/// * provide:
///   * getWidth()
///   * getHeight()
///   * getFrameDeltaTime()
///   * getWindowRatio()
///   * windowDimensionChanged()
/// * let the user define the "loop" function.

namespace TGEngine::core {

  class Application
  {
  public:
    Application();

    virtual ~Application(){};

    virtual void ProcessInput(float){};
    virtual void Update(float){};
    virtual void Render(){};
    virtual void PostRender(){};


    static Application &getInstance();

    // get the window id
    GLFWwindow *getWindow();

    // window control
    void exit();

    // delta time between frame and time from beginning
    float getFrameDeltaTime() const;
    float getTime() const;

    // application run
    void run();

    // Application informations
    //
    int getWidth();
    int getHeight();
    float getWindowRatio();
    bool windowDimensionChanged();

  private:
    enum State { stateReady, stateRun, stateExit };

    State state;

    Application &operator=(const Application &) { return *this; }

    GLFWwindow *window;

    // Time:
    float time;
    float deltaTime;

    // Dimensions:
    int width;
    int height;
    bool dimensionChanged;
    void detectWindowDimensionChange();

  protected:
    Application(const Application &){};

    std::string title;

    const char *glslVersion;
  };

}

#endif /* end of include guard: TGAME_APPLICATION_H */
