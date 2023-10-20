#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Tablero.h"
#include <iostream>

class Tablero
{
    public:
        sf::Sprite m_casillaB[8];
        sf::Sprite m_casillaN[8];
        int m_posNum[8];
        char m_posLtr[8];
        bool m_ocp = false;
        Tablero(sf::Image imagenN, sf::Image imagenB) {}
};

void Window()
{
    sf::RenderWindow tablero(sf::VideoMode(900, 600), "Tablero");
    sf::Texture casillaB, casillaN;

    casillaB.loadFromFile("CasillaB.PNG");
    casillaN.loadFromFile("CasillaN.PNG");

    sf::Sprite spriteB(casillaB);
    sf::Sprite spriteN(casillaN);

    spriteB.setScale(2, 2);
    spriteN.setScale(2, 2);

    spriteB.setOrigin(-40, -20);
    spriteN.setOrigin(-40, -20);

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

        tablero.display();
    }
}

int main()
{
    Window();

    return 0;
}