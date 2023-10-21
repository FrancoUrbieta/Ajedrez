#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Tablero.h"
#include <iostream>

class Tablero
{
    public:
        sf::Sprite m_casillaI[8];
        sf::Sprite m_casillaJ[8];
        int m_posNum[8];
        char m_posLtr[8];
        bool m_ocp = false;
        Tablero() {}
};

class Pieza
{
    public:
        sf::Sprite m_imagen;
        int m_posNum[8];
        char m_posLtr[8];
};

void Window()
{
    sf::RenderWindow tablero(sf::VideoMode(900, 600), "Tablero");
    sf::Texture casillaB, casillaN;
    sf::Texture peonB, peonN, reyB, reyN, damaB, damaN;
    sf::Texture torreB, torreN, caballoB, caballoN, alfilB, alfilN;

    casillaB.loadFromFile("CasillaB.PNG");
    casillaN.loadFromFile("CasillaN.PNG");

    sf::Sprite spriteB(casillaB);
    sf::Sprite spriteN(casillaN);

    spriteB.setScale(2, 2);
    spriteN.setScale(2, 2);

    spriteB.setOrigin(-40, -20);
    spriteN.setOrigin(-40, -20);

    peonB.loadFromFile("PeonB.PNG");
    peonN.loadFromFile("PeonN.PNG");

    sf::Sprite spritePeonB(peonB);
    sf::Sprite spritePeonN(peonN);

    spritePeonB.setScale(2, 2);
    spritePeonN.setScale(2, 2);

    spritePeonB.setOrigin(-40, -20);
    spritePeonN.setOrigin(-40, -20);

    torreB.loadFromFile("TorreB.PNG");
    torreN.loadFromFile("TorreN.PNG");

    sf::Sprite spriteTorreB(torreB);
    sf::Sprite spriteTorreN(torreN);

    spriteTorreB.setScale(2, 2);
    spriteTorreN.setScale(2, 2);

    spriteTorreB.setOrigin(-40, -20);
    spriteTorreN.setOrigin(-40, -20);

    alfilB.loadFromFile("AlfilB.PNG");
    alfilN.loadFromFile("AlfilN.PNG");

    sf::Sprite spriteAlfilB(alfilB);
    sf::Sprite spriteAlfilN(alfilN);

    spriteAlfilB.setScale(2, 2);
    spriteAlfilN.setScale(2, 2);

    spriteAlfilB.setOrigin(-40, -20);
    spriteAlfilN.setOrigin(-40, -20);

    while (tablero.isOpen())
    {
        sf::Event event;

        while (tablero.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                tablero.close();
            }
        }

        tablero.clear(sf::Color(0, 0, 0));

        for (int i = 0; i < 8; i++)
        {
            float distancia = 64;
            for (int j = 0; j < 8; j++)
            {
                if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
                {
                    tablero.draw(spriteB);
                    spriteB.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
                {
                    tablero.draw(spriteN);
                    spriteN.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            float distancia = 64;
            for (int j = 0; j < 8; j++)
            {
                if (j == 1)
                {
                    tablero.draw(spritePeonN);
                    spritePeonN.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                if (j == 6)
                {
                    tablero.draw(spritePeonB);
                    spritePeonB.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                if ((i == 2 && j == 0) || (i == 5 && j == 0))
                {
                    tablero.draw(spriteAlfilN);
                    spriteAlfilN.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                if ((i == 2 && j == 7) || (i == 5 && j == 7))
                {
                    tablero.draw(spriteAlfilB);
                    spriteAlfilB.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                if ((i == 0 && j == 0) || (i == 7 && j == 0))
                {
                    tablero.draw(spriteTorreN);
                    spriteTorreN.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
                if ((i == 0 && j == 7) || (i == 7 && j == 7))
                {
                    tablero.draw(spriteTorreB);
                    spriteTorreB.setPosition(sf::Vector2f(distancia * i, distancia * j));
                }
            }
        }

        tablero.display();
    }
}

int main()
{
    Window();

    return 0;
}