#include "Game.h"


Game::Game() :  WINDOW_SIZE(1000), GRID_WINDOW_SIZE(800), INFECTION_TIME(1000),
IMMUNITY_TIME(4000), CUSTOMINFECTION_TIME(6000), PROBABILITY_OF_INFECTION(0.5)
{
    std::string input;

    while (true) {
        std::cout << "Podaj wielkosc siatki (GRID_SIZE): ";
        std::getline(std::cin, input);

        bool isNumeric = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric) {
            GRID_SIZE = std::stoi(input);
            break;
        }
        else {
            std::cerr << "Bledne dane. Wprowadz liczbe calkowita." << std::endl;
        }
    }

    initWindow();
    initializeBoard();
    initButton();
    
}

Game::~Game()
{
    delete window;
}

void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, GRID_WINDOW_SIZE), "Problem Liszaja");
}

void Game::initializeBoard() {
    board.resize(GRID_SIZE, std::vector<Cell>(GRID_SIZE));
    board[GRID_SIZE / 2][GRID_SIZE / 2].infect();
}

void Game::resetHealthyCell()
{
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            board[i][j].reset();
        }
    }
}

void Game::updateBoard() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            board[i][j].updateCell(board,i,j, PROBABILITY_OF_INFECTION, CUSTOMINFECTION_TIME, IMMUNITY_TIME, INFECTION_TIME, GRID_SIZE);
        }
    }
}

void Game::restartGame()
{
    resetHealthyCell();
    initializeBoard();
}

void Game::update()
{

    pollEvents();
    updateBoard();

}

void Game::render()
{
    window->clear();
    drawBoard();
    drawButtons();
    initText();
    window->display();
}

void Game::drawBoard() {

    float cellSize = static_cast <float>(GRID_WINDOW_SIZE) / GRID_SIZE;

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);

            switch (board[i][j].getState()) {
            case Cell::Healthy:
                cell.setFillColor(sf::Color::Green);
                break;
            case Cell::Infected:
                cell.setFillColor(sf::Color::Red);
                break;
            case Cell::Immune:
                cell.setFillColor(sf::Color::White);
                break;
            }

            window->draw(cell);
        }
    }
}


void Game::pollEvents()
{

    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;

        case sf::Event::MouseMoved:
            handleMouseMoved();
            break;
        case sf::Event::MouseButtonPressed:
            if (buttons[0].isMouseOver(*window)) {
                INFECTION_TIME += 100;
            }
            else if (buttons[1].isMouseOver(*window)) {
                INFECTION_TIME -= 100;

                if (INFECTION_TIME < 0) {
                    INFECTION_TIME = 0;
                }
            }
            else if (buttons[2].isMouseOver(*window)) {
                PROBABILITY_OF_INFECTION += 0.01;

                if (PROBABILITY_OF_INFECTION > 1.0) {
                    PROBABILITY_OF_INFECTION = 1.0;
                }
            }
            else if (buttons[3].isMouseOver(*window)) {
                PROBABILITY_OF_INFECTION -= 0.01;

                if (PROBABILITY_OF_INFECTION < 0.0) {
                    PROBABILITY_OF_INFECTION = 0.0;
                }
            }
            else if (buttons[4].isMouseOver(*window)) {
                IMMUNITY_TIME += 100;
            }
            else if (buttons[5].isMouseOver(*window)) {
                IMMUNITY_TIME -= 100;

                if (IMMUNITY_TIME < 0) {
                    IMMUNITY_TIME = 0;
                }
            }
            else if (buttons[6].isMouseOver(*window)) {
                CUSTOMINFECTION_TIME += 100;
            }
            else if (buttons[7].isMouseOver(*window)) {
                CUSTOMINFECTION_TIME -= 100;

                if (CUSTOMINFECTION_TIME < 0) {
                    CUSTOMINFECTION_TIME = 0;
                }
            }
            else if (restartButton.isMouseOver(*window)) {
                restartGame();
            }
            break;
           
        }
    }
}

void Game::handleMouseMoved() {
    for (auto& button : buttons) {
        if (button.isMouseOver(*window)) {
            button.setBackColor(sf::Color::Yellow);
        }
        else {
            button.setBackColor(sf::Color::White);
        }
    }

    if (restartButton.isMouseOver(*window)) {
        restartButton.setBackColor(sf::Color::Yellow);
    }
    else {
        restartButton.setBackColor(sf::Color::White);
    }
}

const bool Game::running() const
{
    return window->isOpen();
}

void Game::fontInit()
{
    if (!arial.loadFromFile("Arial.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
    }
}

void Game::initText()
{
    std::ostringstream stream;

    stream << std::fixed << std::setprecision(2) << PROBABILITY_OF_INFECTION;
    std::string formattedProbability = stream.str();

    Probability.setFont(arial);
    Probability.setCharacterSize(15);
    Probability.setFillColor(sf::Color::White);

    Probability.setString("PRAWDOPODOBIENSTWO\n ZARAZENIA: " + formattedProbability);
    Probability.setPosition(810, 250);
    window->draw(Probability);
    

    double infectionTimeInSeconds = static_cast<double>(INFECTION_TIME) / 1000.0;

    stream.str("");
    stream << std::fixed << std::setprecision(1) << infectionTimeInSeconds;
    std::string formattedInfectionTime = stream.str();

    TimeOfInfection.setFont(arial);
    TimeOfInfection.setCharacterSize(15);
    TimeOfInfection.setFillColor(sf::Color::White);
    TimeOfInfection.setString("CZAS ZARAZANIA: \n" + formattedInfectionTime + " s");
    TimeOfInfection.setPosition(820, 100);
    window->draw(TimeOfInfection);

    
    double immunityTimeInSeconds = static_cast<double>(IMMUNITY_TIME) / 1000.0;

    stream.str("");
    stream << std::fixed << std::setprecision(1) << immunityTimeInSeconds;
    std::string formattedImmunityTime = stream.str();

    Immunity.setFont(arial);
    Immunity.setCharacterSize(15);
    Immunity.setFillColor(sf::Color::White);
    Immunity.setString("CZAS ODPORNOSCI: \n" + formattedImmunityTime + " s");
    Immunity.setPosition(820, 380);
    window->draw(Immunity);

    double custominfectionTimeInSeconds = static_cast<double>(CUSTOMINFECTION_TIME) / 1000.0;

    stream.str("");
    stream << std::fixed << std::setprecision(1) << custominfectionTimeInSeconds;
    std::string formattedCustomTime = stream.str();

    InfectionTime.setFont(arial);
    InfectionTime.setCharacterSize(15);
    InfectionTime.setFillColor(sf::Color::White);
    InfectionTime.setString("CZAS TRWANIA \nZARAZENIA: \n" + formattedCustomTime + " s");
    InfectionTime.setPosition(820, 500);
    window->draw(InfectionTime);
}

void Game::initButton()
{
   
    buttons.push_back(Button("+", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));
    buttons.push_back(Button("-", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));

    buttons.push_back(Button("+", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));
    buttons.push_back(Button("-", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));

    buttons.push_back(Button("+", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));
    buttons.push_back(Button("-", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));

    buttons.push_back(Button("+", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));
    buttons.push_back(Button("-", sf::Vector2f(50, 50), 30, sf::Color::White, sf::Color::Black));
    
    fontInit();

    for (auto& button : buttons) {
        button.setFont(arial);
    }
   
    for (size_t i = 0; i < buttons.size(); i=i+2) {
        buttons[i].setPosition(sf::Vector2f(825, static_cast<float>(150 + i * 70)));
        buttons[i+1].setPosition(sf::Vector2f(900, static_cast<float>(150 + i * 70)));
    }

    restartButton = Button("Restart", sf::Vector2f(100, 50), 17, sf::Color::White, sf::Color::Black);
    restartButton.setPosition(sf::Vector2f(850, 700));
    restartButton.setFont(arial);
}


void Game::drawButtons() {
    for (auto& button : buttons) {
        button.drawTo(*window);
    }
    restartButton.drawTo(*window);
}
