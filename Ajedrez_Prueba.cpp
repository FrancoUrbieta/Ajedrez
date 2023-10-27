#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "game.h"

struct Casilla
{
	sf::Sprite m_casilla;
	bool m_ocp = false;
};

class Pieza
{
	public:
		sf::Sprite m_pieza;
		
};

void Window()
{
	sf::RenderWindow tablero(sf::VideoMode(1000, 700), "Tablero");
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

	tablero.setPosition(sf::Vector2i(250, 100));

	while (tablero.isOpen())
	{
		sf::Event event;

		while (tablero.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				tablero.close();
			}
			sf::Vector2f pos = spriteB.getPosition();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i vecI = sf::Vector2i(spriteB.getPosition()), vecsum(1, 1);
					sf::Vector2f vecF = sf::Vector2f(sf::Mouse::getPosition(tablero));
					if (sf::Mouse::getPosition(tablero) == vecI)
					{
						spriteB.setPosition(vecF);
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				spriteB.setPosition(pos);
			}
		}
		tablero.clear(sf::Color(70, 70, 70));

		Casilla casilla[8][8];

		for (int i = 0; i < 8; i++)
		{
			float distancia = 64;
			for (int j = 0; j < 8; j++)
			{
				int I = i;
				if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
				{
					tablero.draw(spriteB);
					spriteB.setPosition(sf::Vector2f(distancia * i, distancia * j));
					casilla[i][j].m_casilla = spriteB;
					
				}
				else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
				{
					tablero.draw(spriteN);
					spriteN.setPosition(sf::Vector2f(distancia * i, distancia * j));
					casilla[i][j].m_casilla = spriteN;
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
					casilla[i][j].m_ocp = true;
					spritePeonN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 6)
				{
					tablero.draw(spritePeonB);
					casilla[i][j].m_ocp = true;
					spritePeonB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 0 && i == 3)
				{
					
				}
				if (j == 7 && i == 3)
				{
					
				}
				if (j == 0 && i == 4)
				{

				}
				if (j == 7 && i == 4)
				{
					
				}
				if ((i == 2 && j == 0) || (i == 5 && j == 0))
				{
					tablero.draw(spriteAlfilN);
					casilla[i][j].m_ocp = true;
					spriteAlfilN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 2 && j == 7) || (i == 5 && j == 7))
				{
					tablero.draw(spriteAlfilB);
					casilla[i][j].m_ocp = true;
					spriteAlfilB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 1 && j == 0) || (i == 6 && j == 0))
				{

				}
				if ((i == 1 && j == 7) || (i == 6 && j == 7))
				{

				}
				if ((i == 0 && j == 0) || (i == 7 && j == 0))
				{
					tablero.draw(spriteTorreN);
					casilla[i][j].m_ocp = true;
					spriteTorreN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 0 && j == 7) || (i == 7 && j == 7))
				{
					tablero.draw(spriteTorreB);
					casilla[i][j].m_ocp = true;
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
	/*
	Game game;
	game.run();
	*/
	return 0;
}