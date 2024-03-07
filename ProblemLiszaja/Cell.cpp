#include "Cell.h"


Cell::Cell() : state(Healthy), hasInfectedCellSpread(false) 
{}

void Cell::infect() 
{
    if (state == Healthy) 
    {
        state = Infected;
        infectionStartTime = std::chrono::steady_clock::now();
      
    }
}

void Cell::makeImmune(int custom_infection_time, int immunity_time) 
{
    if (state == Infected) 
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - infectionStartTime).count();

        if (elapsedTime >= custom_infection_time) 
        {
            state = Immune;
            immunityStartTime = currentTime;
        }
    }
    else if (state == Immune) 
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - immunityStartTime).count();

        if (elapsedTime >= immunity_time) 
        {
            state = Healthy;
        }
    }
}

void Cell::updateCell(std::vector<std::vector<Cell>>& board, int i, int j, double probability,int custom_infection_time, int immunity_time, int infection_time, int grid) 
{

    if (state == Infected) 
    {

        if (isInfected(infection_time)) 
        {

            spreadInfection(board, i, j, probability, grid);
            
            makeImmune(custom_infection_time, immunity_time);
            
        }

        makeImmune(custom_infection_time, immunity_time);
        
    }

    else if (state == Immune)
    {
        makeImmune(custom_infection_time, immunity_time);
        board[i][j].hasInfectedCellSpread = false;
    }
}

bool Cell::isInfected(int infection_time) const 
{
    if (state == Infected) 
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = currentTime - infectionStartTime;
        return elapsedTime >= std::chrono::milliseconds(infection_time);
    }

    return false;
}


Cell::State Cell::getState() const 
{
    return state;
}

std::mt19937& Cell::getRandomGenerator() 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}


void Cell::spreadInfection(std::vector<std::vector<Cell>>& board, int i, int j, double probability, int grid)
{
    
    if (board[i][j].state == Infected && !board[i][j].hasInfectedCellSpread) 
    {
        
        for (int dx = -1; dx <= 1; ++dx) 
        {
            
            for (int dy = -1; dy <= 1; ++dy) 
            {
                int ni = i + dx;
                int nj = j + dy;

                if (ni >= 0 && ni < grid && nj >= 0 && nj < grid && (dx != 0 || dy != 0)) 
                {
                    std::uniform_real_distribution<double> dis(0.0, 1.0);
                    double randomValue = dis(getRandomGenerator());
             

                    if (randomValue < probability && board[ni][nj].state == Healthy) 
                    {
                        board[ni][nj].infect();
                    }
                }
            }
        }

        board[i][j].hasInfectedCellSpread = true;
    }
}


void Cell::reset() 
{
    state = Healthy;
    hasInfectedCellSpread = false;
}
