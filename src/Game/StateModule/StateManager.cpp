#include "StateManager.h"
#include "Core/Debug/Logger.h"

using namespace TGEngine::game;

StateManager *currentStateManager = nullptr;

StateManager &StateManagerInstance::getInstance() {
	if (currentStateManager == nullptr) {
		currentStateManager = new StateManager();
	}
	return *currentStateManager;
}

StateManager::StateManager() {}

StateManager::~StateManager() {}

void StateManager::registerState(eStateType type, std::function<bool()> callback) {
	stateMap[type] = callback;
}

void StateManager::changeState(eStateType type) {
	if (stateMap.find(type) != stateMap.end() && stateMap[type] != nullptr) {
		stateMap[type]();
	} else {
		LOG_ERROR("StateManager::changeState: State by id '" + std::to_string(type) + "' not found.");
	}
}
