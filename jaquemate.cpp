#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

bool Game::PiezaEnMedio(int sentido, sf::Vector2i posA, sf::Vector2i posl, int k)
{
	if (sentido == 1)		//horizontal
	{
		int inicio = posA.x, fin = posl.x;

		if (inicio > fin) { inicio = posl.x, fin = posA.x; }

		for (int l = inicio + 1; l < fin; l++)
		{
			if (Tablero(l, posA.y).m_ocp && Tablero(l, posA.y).m_pieza != P(k).m_nro)
			{
				return true;
			}
		}
	}
	else if (sentido == 2)		//vertical
	{
		int inicio = posA.y, fin = posl.y;

		if (inicio > fin) { inicio = posl.y, fin = posA.y; }

		for (int l = inicio + 1; l < fin; l++)
		{
			if (Tablero(posA.x, l).m_ocp && Tablero(posA.x, l).m_pieza != P(k).m_nro)
			{
				return true;
			}
		}
	}
	else if (sentido == 3)		//diagonal
	{
		int inicio = posA.x, fin = posl.x;

		if (inicio > fin) { inicio = posl.x, fin = posA.x; }

		int medio = fin - inicio;

		for (int l = 1; l < medio; l++)
		{
			if (posA.x > posl.x && posA.y > posl.y)
			{
				if (Tablero(posA.x - l, posA.y - l).m_ocp && (posA.x - l >= 0 && posA.y - l >= 0))
				{
					if (Tablero(posA.x - l, posA.y - l).m_pieza != P(k).m_nro)
					{
						return true;
					}
				}
			}
			if (posA.x < posl.x && posA.y > posl.y)
			{
				if (Tablero(posA.x + l, posA.y - l).m_ocp && (posA.x + l <= 7 && posA.y - l >= 0))
				{
					if (Tablero(posA.x + l, posA.y - l).m_pieza != P(k).m_nro)
					{
						return true;
					}
				}
			}
			if (posA.x > posl.x && posA.y < posl.y)
			{
				if (Tablero(posA.x - l, posA.y + l).m_ocp && (posA.x - l >= 0 && posA.y + l <= 7))
				{
					if (Tablero(posA.x - l, posA.y + l).m_pieza != P(k).m_nro)
					{
						return true;
					}
				}
			}
			if (posA.x < posl.x && posA.y < posl.y)
			{
				if (Tablero(posA.x + l, posA.y + l).m_ocp && (posA.x + l <= 7 && posA.y + l <= 7))
				{
					if (Tablero(posA.x + l, posA.y + l).m_pieza != P(k).m_nro)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::CasillaEnJuego(sf::Vector2i pos, int k)
{
	sf::Vector2i posl;

	for (int i = 0; i < 8; i++)
	{
		if (i != pos.x && Tablero(i, pos.y).m_ocp && P(Tablero(i, pos.y).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(i, pos.y).m_pieza).m_tipo == Tipo::Torre ||
				P(Tablero(i, pos.y).m_pieza).m_tipo == Tipo::Dama)
			{
				posl.x = i, posl.y = pos.y;
				if (!PiezaEnMedio(1, pos, posl, k))
				{
					if (pos != posl) { return true; }
				}
			}
		}
		if (i != pos.y && Tablero(pos.x, i).m_ocp && P(Tablero(pos.x, i).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x, i).m_pieza).m_tipo == Tipo::Torre ||
				P(Tablero(pos.x, i).m_pieza).m_tipo == Tipo::Dama)
			{
				posl.x = pos.x, posl.y = i;
				if (!PiezaEnMedio(2, pos, posl, k))
				{
					if (pos != posl) { return true; }
				}
			}
		}
	}

	for (int i = 1; i < 9 + 1; i++)
	{
		if (Tablero(pos.x - i, pos.y - i).m_ocp && (pos.x - i >= 0 && pos.y - i >= 0))
		{
			if (P(Tablero(pos.x - i, pos.y - i).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x - i, pos.y - i).m_pieza).m_tipo == Tipo::Alfil ||
					P(Tablero(pos.x - i, pos.y - i).m_pieza).m_tipo == Tipo::Dama)
				{
					posl.x = pos.x - i, posl.y = pos.y - i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						return true;
					}
				}
			}
		}
		if (Tablero(pos.x + i, pos.y - i).m_ocp && (pos.x + i <= 7 && pos.y - i >= 0))
		{
			if (P(Tablero(pos.x + i, pos.y - i).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x + i, pos.y - i).m_pieza).m_tipo == Tipo::Alfil ||
					P(Tablero(pos.x + i, pos.y - i).m_pieza).m_tipo == Tipo::Dama)
				{
					posl.x = pos.x + i, posl.y = pos.y - i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						return true;
					}
				}
			}
		}
		if (Tablero(pos.x - i, pos.y + i).m_ocp && (pos.x - i >= 0 && pos.y + i <= 7))
		{
			if (P(Tablero(pos.x - i, pos.y + i).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x - i, pos.y + i).m_pieza).m_tipo == Tipo::Alfil ||
					P(Tablero(pos.x - i, pos.y + i).m_pieza).m_tipo == Tipo::Dama)
				{
					posl.x = pos.x - i, posl.y = pos.y + i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						return true;
					}
				}
			}
		}
		if (Tablero(pos.x + i, pos.y + i).m_ocp && (pos.x + i <= 7 && pos.y + i <= 7))
		{
			if (P(Tablero(pos.x + i, pos.y + i).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x + i, pos.y + i).m_pieza).m_tipo == Tipo::Alfil ||
					P(Tablero(pos.x + i, pos.y + i).m_pieza).m_tipo == Tipo::Dama)
				{
					posl.x = pos.x + i, posl.y = pos.y + i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						return true;
					}
				}
			}
		}
	}

	if (Tablero(pos.x - 2, pos.y - 1).m_ocp && (pos.x - 2 >= 0 && pos.y - 1 >= 0))
	{
		if (P(Tablero(pos.x - 2, pos.y - 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x - 2, pos.y - 1).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x - 2, pos.y + 1).m_ocp && (pos.x - 2 >= 0 && pos.y + 1 <= 7))
	{
		if (P(Tablero(pos.x - 2, pos.y + 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x - 2, pos.y + 1).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x + 2, pos.y - 1).m_ocp && (pos.x + 2 <= 7 && pos.y - 1 >= 0))
	{
		if (P(Tablero(pos.x + 2, pos.y - 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x + 2, pos.y - 1).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x + 2, pos.y + 1).m_ocp && (pos.x + 2 <= 7 && pos.y + 1 <= 7))
	{
		if (P(Tablero(pos.x + 2, pos.y + 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x + 2, pos.y + 1).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x - 1, pos.y - 2).m_ocp && (pos.x - 1 >= 0 && pos.y - 2 >= 0))
	{
		if (P(Tablero(pos.x - 1, pos.y - 2).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x - 1, pos.y - 2).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x + 1, pos.y - 2).m_ocp && (pos.x + 1 <= 7 && pos.y - 2 >= 0))
	{
		if (P(Tablero(pos.x + 1, pos.y - 2).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x + 1, pos.y - 2).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x - 1, pos.y + 2).m_ocp && (pos.x - 1 >= 0 && pos.y + 2 <= 7))
	{
		if (P(Tablero(pos.x - 1, pos.y + 2).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x - 1, pos.y + 2).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x + 1, pos.y + 2).m_ocp && (pos.x + 1 <= 7 && pos.y + 2 <= 7))
	{
		if (P(Tablero(pos.x + 1, pos.y + 2).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x + 1, pos.y + 2).m_pieza).m_tipo == Tipo::Caballo)
			{
				return true;
			}
		}
	}

	if (P(k).m_color == Color::N)
	{
		if (Tablero(pos.x - 1, pos.y + 1).m_ocp && (pos.x - 1 >= 0 && pos.y + 1 <= 7))
		{
			if (P(Tablero(pos.x - 1, pos.y + 1).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x - 1, pos.y + 1).m_pieza).m_tipo == Tipo::Peon ||
					P(Tablero(pos.x - 1, pos.y + 1).m_pieza).m_tipo == Tipo::Rey)
				{
					return true;
				}
			}
		}
		if (Tablero(pos.x + 1, pos.y + 1).m_ocp && (pos.x + 1 <= 7 && pos.y + 1 <= 7))
		{
			if (P(Tablero(pos.x + 1, pos.y + 1).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x + 1, pos.y + 1).m_pieza).m_tipo == Tipo::Peon ||
					P(Tablero(pos.x + 1, pos.y + 1).m_pieza).m_tipo == Tipo::Rey)
				{
					return true;
				}
			}
		}
	}
	else if (P(k).m_color == Color::B)
	{
		if (Tablero(pos.x + 1, pos.y - 1).m_ocp && (pos.x + 1 <= 7 && pos.y - 1 >= 0))
		{
			if (P(Tablero(pos.x + 1, pos.y - 1).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x + 1, pos.y - 1).m_pieza).m_tipo == Tipo::Peon ||
					P(Tablero(pos.x + 1, pos.y - 1).m_pieza).m_tipo == Tipo::Rey)
				{
					return true;
				}
			}
		}
		if (Tablero(pos.x - 1, pos.y - 1).m_ocp && (pos.x - 1 >= 0 && pos.y - 1 >= 0))
		{
			if (P(Tablero(pos.x - 1, pos.y - 1).m_pieza).m_color != P(k).m_color)
			{
				if (P(Tablero(pos.x - 1, pos.y - 1).m_pieza).m_tipo == Tipo::Peon ||
					P(Tablero(pos.x - 1, pos.y - 1).m_pieza).m_tipo == Tipo::Rey)
				{
					return true;
				}
			}
		}
	}

	if (Tablero(pos.x + 1, pos.y).m_ocp && (pos.x + 1 <= 7))
	{
		if (P(Tablero(pos.x + 1, pos.y).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x + 1, pos.y).m_pieza).m_tipo == Tipo::Rey)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x, pos.y + 1).m_ocp && (pos.y + 1 <= 7))
	{
		if (P(Tablero(pos.x, pos.y + 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x, pos.y + 1).m_pieza).m_tipo == Tipo::Rey)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x - 1, pos.y).m_ocp && (pos.x - 1 >= 0))
	{
		if (P(Tablero(pos.x - 1, pos.y).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x - 1, pos.y).m_pieza).m_tipo == Tipo::Rey)
			{
				return true;
			}
		}
	}
	if (Tablero(pos.x, pos.y - 1).m_ocp && (pos.y - 1 >= 0))
	{
		if (P(Tablero(pos.x, pos.y - 1).m_pieza).m_color != P(k).m_color)
		{
			if (P(Tablero(pos.x, pos.y - 1).m_pieza).m_tipo == Tipo::Rey)
			{
				return true;
			}
		}
	}
	return false;
}

bool Game::Ahogado(sf::Vector2i posR, int Rey)
{
	int juego = 0, ocupado = 0, fuera = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int x = posR.x + i;
			int y = posR.y + j;
			sf::Vector2i areaR(x, y);

			if ((x >= 0 && y >= 0) && (x <= 7 && y <= 7) && areaR != posR)
			{
				if (CasillaEnJuego(areaR, Rey))
				{
					juego++;
				}
				else if (Tablero(x, y).m_ocp)
				{
					if (!PiezaRival(P(Rey), P(Tablero(x, y).m_pieza)))
					{
						ocupado++;
					}
					else if (PiezaRival(P(Rey), P(Tablero(x, y).m_pieza)))
					{
						if (CasillaEnJuego(areaR, Rey))
						{
							juego++;
						}
					}
				}
			}
			else if ((x < 0 || y < 0) || (x > 7 || y > 7))
			{
				fuera++;
			}
		}
	}
	if (juego + ocupado + fuera == 8)
	{
		return true;
	}
	return false;
}

bool Game::Jaque(sf::Vector2i pos, int k)
{
	switch (P(k).m_tipo)
	{
		case::Tipo::Dama:
			for (int u = 0; u < 8; u++)
			{
				if (Tablero(u, pos.y).m_ocp && u != pos.x)
				{
					if (P(Tablero(u, pos.y).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(u, pos.y).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(u, pos.y);
						if (!PiezaEnMedio(1, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x, u).m_ocp && u != pos.y)
				{
					if (P(Tablero(pos.x, u).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x, u).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x, u);
						if (!PiezaEnMedio(2, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			for (int l = 1; l < 9; l++)
			{
				if (Tablero(pos.x - l, pos.y - l).m_ocp && (pos.x - l >= 0 && pos.y - l >= 0))
				{
					if (P(Tablero(pos.x - l, pos.y - l).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - l, pos.y - l).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x - l, pos.y - l);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x + l, pos.y + l).m_ocp && (pos.x + l <= 7 && pos.y + l <= 7))
				{
					if (P(Tablero(pos.x + l, pos.y + l).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + l, pos.y + l).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x + l, pos.y + l);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			for (int r = 1; r < 9; r++)
			{
				if (Tablero(pos.x - r, pos.y + r).m_ocp && (pos.x - r >= 0 && pos.y + r <= 7))
				{
					if (P(Tablero(pos.x - r, pos.y + r).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - r, pos.y + r).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x - r, pos.y + r);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x + r, pos.y - r).m_ocp && (pos.x + r <= 7 && pos.y - r >= 0))
				{
					if (P(Tablero(pos.x + r, pos.y - r).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + r, pos.y - r).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x + r, pos.y - r);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			break;
		case::Tipo::Torre:
			for (int u = 0; u < 8; u++)
			{
				if (Tablero(u, pos.y).m_ocp && u != pos.x)
				{
					if (P(Tablero(u, pos.y).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(u, pos.y).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(u, pos.y);
						if (!PiezaEnMedio(1, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x, u).m_ocp && u != pos.y)
				{
					if (P(Tablero(pos.x, u).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x, u).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x, u);
						if (!PiezaEnMedio(2, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			break;
		case::Tipo::Alfil:
			for (int l = 1; l < 9; l++)
			{
				if (Tablero(pos.x - l, pos.y - l).m_ocp && (pos.x - l >= 0 && pos.y - l >= 0))
				{
					if (P(Tablero(pos.x - l, pos.y - l).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - l, pos.y - l).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x - l, pos.y - l);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x + l, pos.y + l).m_ocp && (pos.x + l <= 7 && pos.y + l <= 7))
				{
					if (P(Tablero(pos.x + l, pos.y + l).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + l, pos.y + l).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x + l, pos.y + l);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			for (int r = 1; r < 9; r++)
			{
				if (Tablero(pos.x - r, pos.y + r).m_ocp && (pos.x - r >= 0 && pos.y + r <= 7))
				{
					if (P(Tablero(pos.x - r, pos.y + r).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - r, pos.y + r).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x - r, pos.y + r);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
				if (Tablero(pos.x + r, pos.y - r).m_ocp && (pos.x + r <= 7 && pos.y - r >= 0))
				{
					if (P(Tablero(pos.x + r, pos.y - r).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + r, pos.y - r).m_pieza).m_color != P(k).m_color)
					{
						sf::Vector2i posRey(pos.x + r, pos.y - r);
						if (!PiezaEnMedio(3, pos, posRey, k))
						{
							return true;
						}
					}
				}
			}
			break;
		case::Tipo::Caballo:
			if (Tablero(pos.x - 2, pos.y - 1).m_ocp && (pos.x - 2 >= 0 && pos.y - 1 >= 0))
			{
				if (P(Tablero(pos.x - 2, pos.y - 1).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x - 2, pos.y - 1).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x - 2, pos.y + 1).m_ocp && (pos.x - 2 >= 0 && pos.y + 1 <= 7))
			{
				if (P(Tablero(pos.x - 2, pos.y + 1).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x - 2, pos.y + 1).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x + 2, pos.y - 1).m_ocp && (pos.x + 2 <= 7 && pos.y - 1 >= 0))
			{
				if (P(Tablero(pos.x + 2, pos.y - 1).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x + 2, pos.y - 1).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x + 2, pos.y + 1).m_ocp && (pos.x + 2 <= 7 && pos.y + 1 <= 7))
			{
				if (P(Tablero(pos.x + 2, pos.y + 1).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x + 2, pos.y + 1).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x - 1, pos.y - 2).m_ocp && (pos.x - 1 >= 0 && pos.y - 2 >= 0))
			{
				if (P(Tablero(pos.x - 1, pos.y - 2).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x - 1, pos.y - 2).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x + 1, pos.y - 2).m_ocp && (pos.x + 1 <= 7 && pos.y - 2 >= 0))
			{
				if (P(Tablero(pos.x + 1, pos.y - 2).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x + 1, pos.y - 2).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x - 1, pos.y + 2).m_ocp && (pos.x - 1 >= 0 && pos.y + 2 <= 7))
			{
				if (P(Tablero(pos.x - 1, pos.y + 2).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x - 1, pos.y + 2).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			if (Tablero(pos.x + 1, pos.y + 2).m_ocp && (pos.x + 1 <= 7 && pos.y + 2 <= 7))
			{
				if (P(Tablero(pos.x + 1, pos.y + 2).m_pieza).m_tipo == Tipo::Rey &&
					P(Tablero(pos.x + 1, pos.y + 2).m_pieza).m_color != P(k).m_color)
				{
					return true;
				}
			}
			break;
		case::Tipo::Peon:
			if (P(k).m_color == Color::N)
			{
				if (Tablero(pos.x + 1, pos.y + 1).m_ocp && (pos.x + 1 <= 7 && pos.y + 1 <= 7))
				{
					if (P(Tablero(pos.x + 1, pos.y + 1).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + 1, pos.y + 1).m_pieza).m_color != P(k).m_color)
					{
						return true;
					}
				}
				if (Tablero(pos.x - 1, pos.y + 1).m_ocp && (pos.x - 1 >= 0 && pos.y + 1 <= 7))
				{
					if (P(Tablero(pos.x - 1, pos.y + 1).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - 1, pos.y + 1).m_pieza).m_color != P(k).m_color)
					{
						return true;
					}
				}
			}
			else if (P(k).m_color == Color::B)
			{
				if (Tablero(pos.x + 1, pos.y - 1).m_ocp && (pos.x + 1 <= 7 && pos.y - 1 >= 0))
				{
					if (P(Tablero(pos.x + 1, pos.y - 1).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x + 1, pos.y - 1).m_pieza).m_color != P(k).m_color)
					{
						return true;
					}
				}
				if (Tablero(pos.x - 1, pos.y - 1).m_ocp && (pos.x - 1 >= 0 && pos.y - 1 >= 0))
				{
					if (P(Tablero(pos.x - 1, pos.y - 1).m_pieza).m_tipo == Tipo::Rey &&
						P(Tablero(pos.x - 1, pos.y - 1).m_pieza).m_color != P(k).m_color)
					{
						return true;
					}
				}
			}
			break;
		default:
			break;
	}
	return false;
}

bool Game::CubrirRey(int piezajaque, int piece, sf::Vector2i posA, sf::Vector2i posB)
{
	int Rey = getReyRival(piezajaque);
	if (posA == P(piezajaque).m_pos)
	{
		Tablero(posB.x, posB.y).VaciarCasilla();
		Tablero(P(piezajaque).m_pos.x, P(piezajaque).m_pos.y).VaciarCasilla();
		if (CasillaEnJuego(P(Rey).m_pos, Rey))
		{
			P(piece).ColocarPieza(posB.x, posB.y, piece, P(piece).m_tipo, P(piece).m_color);
			P(piezajaque).ColocarPieza(P(piezajaque).m_pos.x, P(piezajaque).m_pos.y,
				piezajaque, P(piezajaque).m_tipo, P(piezajaque).m_color);
		}
		else if (!CasillaEnJuego(P(Rey).m_pos, Rey))
		{
			P(piece).ColocarPieza(posB.x, posB.y, piece, P(piece).m_tipo, P(piece).m_color);
			P(piezajaque).ColocarPieza(P(piezajaque).m_pos.x, P(piezajaque).m_pos.y,
				piezajaque, P(piezajaque).m_tipo, P(piezajaque).m_color);
			return true;
		}
	}
	else if (posA != P(piezajaque).m_pos && !Tablero(posA.x, posA.y).m_ocp)
	{
		int angulo = SentidoDeAtaque(P(Rey), P(piezajaque));
		P(piece).ColocarPieza(posA.x, posA.y, piece, P(piece).m_tipo, P(piece).m_color);
		if (!PiezaEnMedio(angulo, P(Rey).m_pos, P(piezajaque).m_pos, Rey))
		{
			Tablero(posA.x, posA.y).VaciarCasilla();
			P(piece).ColocarPieza(posB.x, posB.y, piece, P(piece).m_tipo, P(piece).m_color);
		}
		else if (PiezaEnMedio(angulo, P(Rey).m_pos, P(piezajaque).m_pos, Rey))
		{
			Tablero(posA.x, posA.y).VaciarCasilla();
			P(piece).ColocarPieza(posB.x, posB.y, piece, P(piece).m_tipo, P(piece).m_color);
			return true;
		}
	}
	return false;
}

bool Game::SalvarRey(int R, int Atk)
{
	for (int k = 0; k < 32; k++)
	{
		if (P(R).m_color == P(k).m_color && P(k).m_enjuego)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sf::Vector2i posk(i, j);
					if (CubrirRey(Atk, k, posk, P(k).m_pos))
					{
						if (MovimientoPosible(k, posk))
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}