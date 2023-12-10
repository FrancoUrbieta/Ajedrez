#include <SFML/Graphics.hpp>
#include <iostream>
#include "casilla.h"
#include "pieza.h"
#include "jaquemate.h"
#include "jugadas.h"

bool Enroque(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	if (!P(k).m_move)
	{
		if (posB.x == posA.x - 2 && posB.y == posA.y)
		{
			if (Tablero(7, posA.y).m_ocp)
			{
				if (P(Tablero(7, posA.y).m_pieza).m_tipo == Tipo::Torre && !P(Tablero(7, posA.y).m_pieza).m_move)
				{
					sf::Vector2i posl{ 7, posA.y };

					if (!PiezaEnMedio(1, posB, posl, k) && !CasillaEnJuego(posA, k))
					{
						std::cout << "\n\tENROQUE CORTO\n";
						P(Tablero(posl.x, posl.y).m_pieza).ColocarPieza(posl.x - 2, posl.y,
							Tablero(posl.x, posl.y).m_pieza, P(Tablero(posl.x, posl.y).m_pieza).m_tipo,
							P(Tablero(posl.x, posl.y).m_pieza).m_color);
						Tablero(posl.x, posl.y).VaciarCasilla();
						return true;
					}
				}
			}
		}
		else if (posB.x == posA.x + 2 && posB.y == posA.y)
		{
			if (Tablero(0, posA.y).m_ocp)
			{
				if (P(Tablero(0, posA.y).m_pieza).m_tipo == Tipo::Torre && !P(Tablero(0, posA.y).m_pieza).m_move)
				{
					sf::Vector2i posl{ 0, posA.y };

					if (!PiezaEnMedio(1, posB, posl, k) && !CasillaEnJuego(posA, k))
					{
						std::cout << "\n\tENROQUE LARGO\n";
						P(Tablero(posl.x, posl.y).m_pieza).ColocarPieza(posl.x + 3, posl.y,
							Tablero(posl.x, posl.y).m_pieza, P(Tablero(posl.x, posl.y).m_pieza).m_tipo,
							P(Tablero(posl.x, posl.y).m_pieza).m_color);
						Tablero(posl.x, posl.y).VaciarCasilla();
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool CapturaAlPaso(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	return false;
}

bool Coronacion(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	if (posA != posB)
	{
		if (P(k).m_color == Color::N)
		{
			if (posA.y == 7)
			{
				return true;
			}
		}
		else if (P(k).m_color == Color::B)
		{
			if (posA.y == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool Conversion(sf::Vector2i mouse, Pieza& p, sf::Vector2i pos)
{
	for (int k = 0; k < 32; k++)
	{
		if (P(k).m_sprite.getGlobalBounds().contains(mouse.x, mouse.y))
		{
			if (P(k).m_tipo != Tipo::Peon && P(k).m_tipo != Tipo::Rey)
			{
				return true;
			}
		}
	}
	return false;
}