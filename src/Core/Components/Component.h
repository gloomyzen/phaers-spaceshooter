#ifndef TOWERDEFENSE_GAME_COMPONENT_H
#define TOWERDEFENSE_GAME_COMPONENT_H

namespace TGEngine::core {

class IComponent
{
private:
  bool active = true;

public:

  IComponent(){};
  IComponent(const IComponent &){};

  virtual ~IComponent() = default;

  virtual void init() {}
  virtual void update() {}
  virtual void render() {}
  void destroy() { active = false; }

  bool &getActive() { return active; };
  bool isActive() const { return active; };
  void setActive(bool _active) { active = _active; };

  IComponent &operator=(const IComponent &) { return *this; }
};

class Component : public IComponent
{
public:
  Component* node{};
  void init() {}
  void update() {}
  void render() {}
  ~Component() = default;
};

}

#endif// TOWERDEFENSE_GAME_COMPONENT_H
