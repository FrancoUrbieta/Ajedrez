#pragma once
#include "pieza.h"
#define distancia 96

class Casilla
{
public:
	sf::Sprite m_casilla;
	bool m_ocp = false;
	int m_pieza{ -1 };

	void setSprite(sf::Texture& t)
	{
		m_casilla.setTexture(t);
		m_casilla.setScale(3, 3);

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

bool MouseEnTablero(sf::RenderWindow& ajedrez)
{
	if ((sf::Mouse::getPosition(ajedrez).x > 0 && sf::Mouse::getPosition(ajedrez).x < 768) &&
		(sf::Mouse::getPosition(ajedrez).y > 0 && sf::Mouse::getPosition(ajedrez).y < 768))
	{
		return true;
	}
	else { return false; }
}

sf::Vector2i EncontrarCasilla(int x, int y)
{
	sf::Vector2i v(-1, -1);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (tablero[i][j].m_casilla.getGlobalBounds().contains(x, y))
			{
				v.x = i;	v.y = j;
				break;
			}
		}
	}
	return v;
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
	p[k].m_pos.x = i;
	p[k].m_pos.y = j;
	tablero[i][j].m_pieza = k;
	p[k].m_sprite.setPosition(distancia * i, distancia * j);
}

void VaciarCasilla(int i, int j)
{
	tablero[i][j].m_ocp = false;
	tablero[i][j].m_pieza = -1;
}

