#ifndef TOWERDEFENSE_GAME_STATEMANAGER_H
#define TOWERDEFENSE_GAME_STATEMANAGER_H

#include <map>

#define GET_STATE_MANAGER() TGEngine::game::StateManagerInstance().getInstance()

namespace TGEngine::game {

    enum eStateType {
        MAIN_MENU,
        GAME,
        PAUSE_MENU
    };

    class StateManager {
    public:
        StateManager();
        ~StateManager();
        void registerState(eStateType, std::function<bool()>);
        void changeState(eStateType);
    private:
        std::map<eStateType, std::function<bool()>> stateMap;
    };

    class StateManagerInstance {
    public:
        static StateManager &getInstance();
    };

}//TGEngine::game


#endif //TOWERDEFENSE_GAME_STATEMANAGER_H
