#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "game.h"

enum Tipo { Rey = 1, Dama, Torre, Alfil, Caballo, Peon }; 
enum Color { B = 1, N };

class Pieza
{
public:
	sf::Sprite m_sprite;
	int m_nro;
	Tipo m_tipo;
	Color m_color;
	int m_posX;
	char m_posY;

	void setSprite(sf::Texture& t)
	{
		m_sprite.setTexture(t);
		m_sprite.setScale(2, 2);
		m_sprite.setOrigin(-40, -20);
	}

	std::string getTipo()
	{
		switch (m_tipo)
		{
		case::Rey:
			return "Rey";
		case::Dama:
			return "Dama";
		case::Torre:
			return "Torre";
		case::Alfil:
			return "Alfil";
		case::Caballo:
			return "Caballo";
		case::Peon:
			return "Peon";
		default:
			break;
		}
	}
	std::string getColor()
	{
		switch (m_color)
		{
		case Color::B:
			return "Blanco";
		case Color::N:
			return "Negro";
		default:
			break;
		}
	}
};

class Casilla
{
public:
	sf::Sprite m_casilla;
	bool m_ocp = false;
	Pieza m_pieza;

	void setSprite(sf::Texture& t)
	{
		m_casilla.setTexture(t);
		m_casilla.setScale(2, 2);
		m_casilla.setOrigin(-40, -20);
	}

	void setPieza(Pieza p) {
		m_pieza = p;
	}
};

void Window()
{
	sf::RenderWindow ajedrez(sf::VideoMode(1000, 700), "Ajedrez");
	sf::Texture casillaB, casillaN;
	sf::Texture peonB, peonN, reyB, reyN, damaB, damaN;
	sf::Texture torreB, torreN, caballoB, caballoN, alfilB, alfilN;

	casillaB.loadFromFile("CasillaB.PNG");
	casillaN.loadFromFile("CasillaN.PNG");

	peonB.loadFromFile("PeonB.PNG");
	peonN.loadFromFile("PeonN.PNG");

	torreB.loadFromFile("TorreB.PNG");
	torreN.loadFromFile("TorreN.PNG");

	caballoB.loadFromFile("CaballoB.PNG");
	caballoN.loadFromFile("CaballoN.PNG");

	alfilB.loadFromFile("AlfilB.PNG");
	alfilN.loadFromFile("AlfilN.PNG");

	damaB.loadFromFile("DamaB.PNG");
	damaN.loadFromFile("DamaN.PNG");

	reyB.loadFromFile("ReyB.PNG");
	reyN.loadFromFile("ReyN.PNG");

	Casilla tablero[8][8];
	Pieza p[32], P;

	float distancia = 64;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casillaB);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(tablero[i][j].m_casilla);
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casillaN);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(tablero[i][j].m_casilla);
			}
		}
	}

	int k = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == 1)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(peonN);
				p[k].m_nro = k;
				p[k].m_tipo = Peon;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if (j == 6)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(peonB);
				p[k].m_nro = k;
				p[k].m_tipo = Peon;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if (j == 0 && i == 3)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(damaN);
				p[k].m_nro = k;
				p[k].m_tipo = Dama;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if (j == 7 && i == 3)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(damaB);
				p[k].m_nro = k;
				p[k].m_tipo = Dama;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if (j == 0 && i == 4)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(reyN);
				p[k].m_nro = k;
				p[k].m_tipo = Rey;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if (j == 7 && i == 4)
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(reyB);
				p[k].m_nro = k;
				p[k].m_tipo = Rey;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 2 && j == 0) || (i == 5 && j == 0))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(alfilN);
				p[k].m_nro = k;
				p[k].m_tipo = Alfil;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 2 && j == 7) || (i == 5 && j == 7))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(alfilB);
				p[k].m_nro = k;
				p[k].m_tipo = Alfil;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 1 && j == 0) || (i == 6 && j == 0))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(caballoN);
				p[k].m_nro = k;
				p[k].m_tipo = Caballo;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 1 && j == 7) || (i == 6 && j == 7))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(caballoB);
				p[k].m_nro = k;
				p[k].m_tipo = Caballo;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 0 && j == 0) || (i == 7 && j == 0))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(torreN);
				p[k].m_nro = k;
				p[k].m_tipo = Torre;
				p[k].m_color = N;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
			if ((i == 0 && j == 7) || (i == 7 && j == 7))
			{
				tablero[i][j].m_ocp = true;
				p[k].setSprite(torreB);
				p[k].m_nro = k;
				p[k].m_tipo = Torre;
				p[k].m_color = B;
				p[k].m_posX = i + 1;
				p[k].m_posY = char(j + 97);
				tablero[i][j].setPieza(p[k]);
				p[k].m_sprite.setPosition(sf::Vector2f(distancia * i, distancia * j));
				ajedrez.draw(p[k].m_sprite);	k++;
			}
		}
	}

	ajedrez.setPosition(sf::Vector2i(800, 200));

	while (ajedrez.isOpen())
	{
		sf::Event event;

		while (ajedrez.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) { ajedrez.close(); }
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (tablero[i][j].m_casilla.getGlobalBounds().contains(sf::Mouse::getPosition(ajedrez).x, sf::Mouse::getPosition(ajedrez).y))
							{
								if (tablero[i][j].m_ocp == true)
								{
									std::cout << "\tEntrada en " << tablero[i][j].m_pieza.getTipo() << " " << tablero[i][j].m_pieza.getColor() << "\n";
									std::cout << "MOUSE - ";
									std::cout << "(" << sf::Mouse::getPosition(ajedrez).x;
									std::cout << ", " << sf::Mouse::getPosition(ajedrez).y << ")\n";
									std::cout << "CASILLA[" << i + 1 << "][" << j + 1 << "] - ";
									std::cout << "(" << tablero[i][j].m_casilla.getGlobalBounds().getPosition().x;
									std::cout << ", " << tablero[i][j].m_casilla.getGlobalBounds().getPosition().y << ")\n\n";

									switch (tablero[i][j].m_pieza.m_tipo)
									{
									case::Peon:
										if (tablero[i][j].m_pieza.m_color == B)
										{
											if (tablero[i][j - 1].m_ocp == false)
											{
												p[tablero[i][j].m_pieza.m_nro].m_sprite.move(0, -64);
												tablero[i][j].m_ocp = false;
												tablero[i][j - 1].setPieza(p[tablero[i][j].m_pieza.m_nro]);
												tablero[i][j - 1].m_ocp = true;
											}
										}
										else if (tablero[i][j].m_pieza.m_color == N)
										{
											if (tablero[i][j + 1].m_ocp == false)
											{
												p[tablero[i][j].m_pieza.m_nro].m_sprite.move(0, 64);
												tablero[i][j].m_ocp = false;
												tablero[i][j + 1].setPieza(p[tablero[i][j].m_pieza.m_nro]);
												tablero[i][j + 1].m_ocp = true;
											}
										}
										break;
									case::Caballo:
										break;
									case::Alfil:
										break;
									case::Torre:
										break;
									case::Dama:
										break;
									case::Rey:
										break;
									default:
										break;
									}
									break;
								}
							}
						}
					}
				}
			}
		}
		ajedrez.clear(sf::Color(70, 70, 70));

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				ajedrez.draw(tablero[i][j].m_casilla);
			}
		}
		for (int k = 0; k < 32; k++)
		{
			ajedrez.draw(p[k].m_sprite);
		}

		ajedrez.display();
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