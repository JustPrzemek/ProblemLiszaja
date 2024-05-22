#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Button.h"
#include "Cell.h"


class Game {
public:
    Game();
    ~Game();

    void initializeBoard();
    void initWindow();
    void update();
    void updateBoard();
    void drawBoard();
    void restartGame();
    void pauseCells();
    void resumeCells();

    void pollEvents();
    void render();
    void resetHealthyCell();
    void initButton();
    void drawButtons();
    void fontInit();
    void initText();

    const bool running() const;

    void handleMouseMoved();

private:
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Font arial;
    sf::Text TimeOfInfection;
    sf::Text Probability;
    sf::Text Immunity;
    sf::Text InfectionTime;
    Button restartButton;
    Button startButton;
    Button stopButton;
    
    std::vector<Button> buttons;
    
    bool isPaused;
    int GRID_SIZE;
    int WINDOW_SIZE;
    int GRID_WINDOW_SIZE;
    int INFECTION_TIME; // czas zara¿ania
    int IMMUNITY_TIME; // cas odpornoœci
    int CUSTOMINFECTION_TIME;//czas trwania zara¿enia
    double PROBABILITY_OF_INFECTION;
    bool simulationStarted;
    bool simulationRunning;

    std::vector<std::vector<Cell>> board;
    std::pair<int, int> selectedCell = { -1, -1 };
    std::chrono::steady_clock::time_point simulationStartTime;
};