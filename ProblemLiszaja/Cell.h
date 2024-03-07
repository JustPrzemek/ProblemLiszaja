#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>

class Cell {
public:
    enum State { Healthy, Infected, Immune };

    Cell();

    void infect();
    void reset();
    void makeImmune(int custom_infection_time, int immunity_time);
    void updateCell(std::vector<std::vector<Cell>>& board, int i, int j, double probability,int custom_infection_time, int immunity_time, int infection_time, int grid);
    bool isInfected(int infection_time) const;

    State getState() const;
    void spreadInfection(std::vector<std::vector<Cell>>& board, int i, int j, double probability, int grid);
    

private:

    bool hasInfectedCellSpread;

    static std::mt19937& getRandomGenerator();

    State state;

    std::chrono::time_point<std::chrono::steady_clock> infectionStartTime; 
    std::chrono::time_point<std::chrono::steady_clock> immunityStartTime; 

};