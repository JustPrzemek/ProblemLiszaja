#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>

class Cell {
public:
    enum State { Healthy, Infected, Immune, Dead };

    Cell();

    void infect();
    void reset();
    void pause();
    void resume();
    void makeImmune(int custom_infection_time, int immunity_time);
    void updateCell(std::vector<std::vector<Cell>>& board, int i, int j, double probability,int custom_infection_time, int immunity_time, int infection_time, int grid);
    bool isInfected(int infection_time) const;

    State getState() const;
    void spreadInfection(std::vector<std::vector<Cell>>& board, int i, int j, double probability, int grid);
    
    static void setSimulationRunning(bool running);

private:

    bool hasInfectedCellSpread;

    static std::mt19937& getRandomGenerator();

    State state;

    std::chrono::time_point<std::chrono::steady_clock> infectionStartTime; 
    std::chrono::time_point<std::chrono::steady_clock> immunityStartTime; 
    std::chrono::steady_clock::time_point pauseTime;
    bool isPaused;

    static bool simulationRunning;
};