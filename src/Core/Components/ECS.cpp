#include "ECS.h"

using namespace TGEngine::core;

void Entity::addGroup(Group mGroup) {
  groupBitSet[mGroup] = true;
  manager.addToGroup(this, mGroup);
}