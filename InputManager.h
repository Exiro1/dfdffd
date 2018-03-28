#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

#include "Player.h"
#include "Map.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <unordered_map>
#include <vector>
class Player;
struct AlwaysZero {
    size_t operator()(sf::Keyboard::Key const& ) const {
        return 0;
    }
};
class InputManager
{
public:
    InputManager();
    ~InputManager();

    void movementManager(Player &player,Map &mapManager);
    void actionManager(Player &player,Map &mapManager);
    void keyboardManager(Player &player,Map &mapManager);

protected:

private:
   // std::vector<sf::Keyboard::Key> m_keyMap;
    std::unordered_map<sf::Keyboard::Key,bool,AlwaysZero> m_keyMap;


};





#endif // INPUTMANAGER_H_INCLUDED
