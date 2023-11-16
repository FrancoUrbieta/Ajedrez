#pragma once
#include "pieza.h"

class Casilla
{
public:
	sf::Sprite m_casilla;
	bool m_ocp = false;
	int m_pieza{ -1 };

	void setSprite(sf::Texture& t)
	{
		m_casilla.setTexture(t);
		m_casilla.setScale(2, 2);

	}
};

Casilla tablero[8][8];

bool MouseEnCasilla(sf::RenderWindow& ajedrez, int i, int j)
{
	if (tablero[i][j].m_casilla.getGlobalBounds().contains(sf::Mouse::getPosition(ajedrez).x, sf::Mouse::getPosition(ajedrez).y))
	{
		return true;
	}
	else { return false; }
}

sf::Vector2i EncontrarCasilla(int x, int y)
{
	sf::Vector2i v;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tablero[i][j].m_casilla.getGlobalBounds().contains(x, y))
			{
				//std::cout << i << " - " << j << "\n";
				v.x = i;	v.y = j;
				return v;
			}
		}
	}
}

void CoordenadasMouse(sf::RenderWindow& ajedrez)
{
	std::cout << "MOUSE - ";
	std::cout << "(" << sf::Mouse::getPosition(ajedrez).x;
	std::cout << ", " << sf::Mouse::getPosition(ajedrez).y << ")\n";
}

void CoordenadasPieza(int k)
{
	std::cout << "PIEZA [" << k << "] - ";
	std::cout << "(" << p[k].m_sprite.getPosition().x;
	std::cout << ", " << p[k].m_sprite.getPosition().y << ")\n";
}

void CoordenadasCasilla(sf::RenderWindow& ajedrez, int i, int j)
{
	std::cout << "CASILLA[" << i + 1 << "][" << j + 1 << "] - ";
	std::cout << "(" << tablero[i][j].m_casilla.getGlobalBounds().getPosition().x;
	std::cout << ", " << tablero[i][j].m_casilla.getGlobalBounds().getPosition().y << ")\n\n";
}

void CargarPiezaEnCasilla(int i, int j, int k, Tipo tipo, Color color)
{
	tablero[i][j].m_ocp = true;
	p[k].m_nro = k;
	p[k].m_tipo = tipo;
	p[k].m_color = color;
	p[k].m_posX = i + 1;
	p[k].m_posY = char(j + 97);
	tablero[i][j].m_pieza = k;
	p[k].m_sprite.setPosition(sf::Vector2f(64 * i, 64 * j));
}

void MovimientosPosibles(sf::Event event, int i, int j)
{
	sf::Color color = tablero[i][j].m_casilla.getColor();

	while (sf::Event::MouseButtonPressed)
	{
		tablero[i][j].m_casilla.setColor(sf::Color::Green);

		if (sf::Event::MouseButtonReleased)
		{


			break;
		}
	}

	tablero[i][j].m_casilla.setColor(color);
}