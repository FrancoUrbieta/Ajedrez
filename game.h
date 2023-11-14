#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Game {
public:
    Game();
    void run();

private:
    void render();
    void processEvents();

    sf::RenderWindow mWindow; // ventana del juego
};

Game::Game() : mWindow(sf::VideoMode(1200, 600), "Titulo del juego") {}

void Game::run()        // ejecuta el juego
{
    while (mWindow.isOpen())
    {
        processEvents();
        render();
    }
}

void Game::processEvents()      // eventos (Teclado, joystick, mouse, etc.)
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::render()     // se encarga de dibujar las cosas
{
    mWindow.clear();

    //mWindow.draw(objectToDraw) ....

    mWindow.display();
}

/*if (sf::Mouse::getPosition(tablero).x < casilla[5][5].m_casilla.getGlobalBounds().getPosition().x &&
    sf::Mouse::getPosition(tablero).y < casilla[5][5].m_casilla.getGlobalBounds().getPosition().y) &&
    (sf::Mouse::getPosition(tablero).x > casilla[5][5].m_casilla.getGlobalBounds().getPosition().x - 64 &&
        sf::Mouse::getPosition(tablero).y > casilla[5][5].m_casilla.getGlobalBounds().getPosition().y - 64)) { }*/