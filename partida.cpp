#include <SFML/Graphics.hpp>
#include "casilla.h"
#include "game.h"
#include "partida.h"

bool MouseEnTablero(sf::RenderWindow& ajedrez)
{
	if ((sf::Mouse::getPosition(ajedrez).x > distancia && sf::Mouse::getPosition(ajedrez).x < distancia * 8 + distancia) &&
		(sf::Mouse::getPosition(ajedrez).y > distancia && sf::Mouse::getPosition(ajedrez).y < distancia * 8 + distancia))
	{
		return true;
	}
	else { return false; }
}

bool MouseEnCasilla(sf::Vector2i& mouse, int i, int j)
{
	if (Tablero(i, j).m_casilla.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		return true;
	}
	else { return false; }
}

sf::Vector2i EncontrarCasilla(sf::Vector2i& mouse)
{
	sf::Vector2i v(-1, -1);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Tablero(i, j).Casilla::m_casilla.getGlobalBounds().contains(mouse.x, mouse.y))
			{
				v.x = i;	v.y = j;
				break;
			}
		}
	}
	return v;
}

bool PiezaRival(Pieza& k, Pieza& l)
{
	if (k.m_color == l.m_color)
	{
		return false;
	}
	else if (k.m_color != l.m_color)
	{
		return true;
	}
	else { return NULL; }
}

int ReyRival(int piece)
{
	Color color{};
	switch (P(piece).m_color)
	{
	case::Color::B:
		color = Color::N;
		break;
	case::Color::N:
		color = Color::B;
		break;
	default:
		break;
	}
	return P(piece).getReyNum(color);
}

int SentidoDeAtaque(Pieza& Rey, Pieza& rival)
{
	if (Rey.m_pos.x != rival.m_pos.x && Rey.m_pos.y == rival.m_pos.y)
	{
		return 1;		// horizontal
	}
	else if (Rey.m_pos.x == rival.m_pos.x && Rey.m_pos.y != rival.m_pos.y)
	{
		return 2;		// vertical
	}
	else if (Rey.m_pos.x != rival.m_pos.x && Rey.m_pos.y != rival.m_pos.y)
	{
		return 3;		// diagonal
	}
	return 0;
}