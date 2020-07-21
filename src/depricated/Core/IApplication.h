#ifndef TGAME_IAPPLICATION_H
#define TGAME_IAPPLICATION_H

namespace TGEngine::core {

class IApplication
{
public:
  IApplication() = default;
  virtual ~IApplication() = 0;

  virtual void ProcessInput(float) = 0;
  virtual void Update(float) = 0;
  virtual void Render() = 0;
};

}

#endif// TGAME_IAPPLICATION_H
