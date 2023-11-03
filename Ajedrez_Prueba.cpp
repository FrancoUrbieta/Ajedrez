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

	caballoB.loadFromFile("CaballoB.PNG");
	caballoN.loadFromFile("CaballoN.PNG");

	sf::Sprite spriteCaballoB(caballoB);
	sf::Sprite spriteCaballoN(caballoN);

	spriteCaballoB.setScale(2, 2);
	spriteCaballoN.setScale(2, 2);

	spriteCaballoB.setOrigin(-40, -20);
	spriteCaballoN.setOrigin(-40, -20);

	alfilB.loadFromFile("AlfilB.PNG");
	alfilN.loadFromFile("AlfilN.PNG");

	sf::Sprite spriteAlfilB(alfilB);
	sf::Sprite spriteAlfilN(alfilN);

	spriteAlfilB.setScale(2, 2);
	spriteAlfilN.setScale(2, 2);

	spriteAlfilB.setOrigin(-40, -20);
	spriteAlfilN.setOrigin(-40, -20);

	damaB.loadFromFile("DamaB.PNG");
	damaN.loadFromFile("DamaN.PNG");

	sf::Sprite spriteDamaB(damaB);
	sf::Sprite spriteDamaN(damaN);

	spriteDamaB.setScale(2, 2);
	spriteDamaN.setScale(2, 2);

	spriteDamaB.setOrigin(-40, -20);
	spriteDamaN.setOrigin(-40, -20);

	reyB.loadFromFile("ReyB.PNG");
	reyN.loadFromFile("ReyN.PNG");

	sf::Sprite spriteReyB(reyB);
	sf::Sprite spriteReyN(reyN);

	spriteReyB.setScale(2, 2);
	spriteReyN.setScale(2, 2);

	spriteReyB.setOrigin(-40, -20);
	spriteReyN.setOrigin(-40, -20);

	Casilla casilla[8][8];

	tablero.setPosition(sf::Vector2i(800, 200));

	while (tablero.isOpen())
	{
		sf::Event event;

		while (tablero.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				tablero.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (casilla[i][j].m_casilla.getGlobalBounds().contains(sf::Mouse::getPosition(tablero).x, sf::Mouse::getPosition(tablero).y))
							{
								std::cout << "\tEntrada\n";
								std::cout << "MOUSE - ";
								std::cout << "(" << sf::Mouse::getPosition(tablero).x;
								std::cout << ", " << sf::Mouse::getPosition(tablero).y << ")\n";
								std::cout << "CASILLA[" << i + 1 << "][" << j + 1 << "] - ";
								std::cout << "(" << casilla[i][j].m_casilla.getGlobalBounds().getPosition().x;
								std::cout << ", " << casilla[i][j].m_casilla.getGlobalBounds().getPosition().y << ")\n\n";
							}
						}
					}
				}
			}
		}
		tablero.clear(sf::Color(70, 70, 70));

		for (int i = 0; i < 8; i++)
		{
			float distancia = 64;
			for (int j = 0; j < 8; j++)
			{
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

		Pieza reyB, reyN;
		Pieza damaB, damaN;
		Pieza alfilB[2], alfilN[2];
		Pieza caballoB[2], caballoN[2];
		Pieza torreB[2], torreN[2];
		Pieza peonB[8], peonN[8];

		for (int i = 0; i < 8; i++)
		{
			float distancia = 64;
			for (int j = 0; j < 8; j++)
			{
				if (j == 1)
				{
					tablero.draw(spritePeonN);
					casilla[i][j].m_ocp = true;
					peonN[i].m_pieza = spritePeonN;
					spritePeonN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 6)
				{
					tablero.draw(spritePeonB);
					casilla[i][j].m_ocp = true;
					peonB[i].m_pieza = spritePeonB;
					spritePeonB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 0 && i == 3)
				{
					tablero.draw(spriteDamaN);
					casilla[i][j].m_ocp = true;
					damaN.m_pieza = spriteDamaN;
					spriteDamaN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 7 && i == 3)
				{
					tablero.draw(spriteDamaB);
					casilla[i][j].m_ocp = true;
					damaB.m_pieza = spriteDamaB;
					spriteDamaB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 0 && i == 4)
				{
					tablero.draw(spriteReyN);
					casilla[i][j].m_ocp = true;
					reyN.m_pieza = spriteReyN;
					spriteReyN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if (j == 7 && i == 4)
				{
					tablero.draw(spriteReyB);
					casilla[i][j].m_ocp = true;
					reyB.m_pieza = spriteReyB;
					spriteReyB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 2 && j == 0) || (i == 5 && j == 0))
				{
					int k = 0;
					tablero.draw(spriteAlfilN);
					casilla[i][j].m_ocp = true;
					alfilN[k].m_pieza = spriteAlfilN;	k++;
					spriteAlfilN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 2 && j == 7) || (i == 5 && j == 7))
				{
					int k = 0;
					tablero.draw(spriteAlfilB);
					casilla[i][j].m_ocp = true;
					alfilB[k].m_pieza = spriteAlfilB;	k++;
					spriteAlfilB.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 1 && j == 0) || (i == 6 && j == 0))
				{
					int k = 0;
					tablero.draw(spriteCaballoN);
					casilla[i][j].m_ocp = true;
					caballoN[k].m_pieza = spriteCaballoN;	k++;
					spriteCaballoN.setPosition(sf::Vector2f(distancia* i, distancia* j));
				}
				if ((i == 1 && j == 7) || (i == 6 && j == 7))
				{
					int k = 0;
					tablero.draw(spriteCaballoB);
					casilla[i][j].m_ocp = true;
					caballoB[k].m_pieza = spriteCaballoB;	k++;
					spriteCaballoB.setPosition(sf::Vector2f(distancia* i, distancia* j));
				}
				if ((i == 0 && j == 0) || (i == 7 && j == 0))
				{
					int k = 0;
					tablero.draw(spriteTorreN);
					casilla[i][j].m_ocp = true;
					torreN[k].m_pieza = spriteTorreN;	k++;
					spriteTorreN.setPosition(sf::Vector2f(distancia * i, distancia * j));
				}
				if ((i == 0 && j == 7) || (i == 7 && j == 7))
				{
					int k = 0;
					tablero.draw(spriteTorreB);
					casilla[i][j].m_ocp = true;
					torreB[k].m_pieza = spriteTorreB;	k++;
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