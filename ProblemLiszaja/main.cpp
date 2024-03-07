#include "Game.h"
#include <SFML/Graphics.hpp>


int main() {


    Game game;


    while (game.running())
    {
        game.update();

        game.render();

        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}