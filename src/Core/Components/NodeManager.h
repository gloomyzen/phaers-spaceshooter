#ifndef TOWERDEFENSE_GAME_NODEMANAGER_H
#define TOWERDEFENSE_GAME_NODEMANAGER_H

#include "ECS.h"

namespace TGEngine::core {

enum eNodeLayers : std::size_t { layerGround, layerUnits, layerUI };

class NodeLayers
{
public:
  //
private:
  eNodeLayers layer;
};

class NodeManager
{
public:
  void testNode(){};

private:
};

}// namespace TGEngine::core

#endif// TOWERDEFENSE_GAME_NODEMANAGER_H
