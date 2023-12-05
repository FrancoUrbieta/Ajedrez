#include <SFML/Graphics.hpp>
#include <iostream>
#include "casilla.h"
#include "pieza.h"
#include "jaquemate.h"
#include "partida.h"
#include "movimientos.h"

bool PiezaEnMedio(int sentido, sf::Vector2i posA, sf::Vector2i posl, int k)
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

bool CasillaEnJuego(sf::Vector2i pos, int k)
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

bool PiezaClavada(Pieza k, sf::Vector2i posA, sf::Vector2i posB, int R)
{
	Pieza p;
	Tablero(posB.x, posB.y).VaciarCasilla();
	if (Tablero(posA.x, posA.y).m_ocp) {
		p = P(Tablero(posA.x, posA.y).m_pieza);
	}
	k.ColocarPieza(posA.x, posA.y, k.m_nro, k.m_tipo, k.m_color);
	if (CasillaEnJuego(P(R).m_pos, R))
	{
		Tablero(posA.x, posA.y).VaciarCasilla();
		k.ColocarPieza(posB.x, posB.y, k.m_nro, k.m_tipo, k.m_color);
		if (p.m_enjuego) {
			P(p.m_nro).ColocarPieza(posA.x, posA.y, p.m_nro, p.m_tipo, p.m_color);
		}
		if (CasillaEnJuego(P(R).m_pos, R))
		{
			return false;
		}
		std::cout << "\n\tClavado";
		return true;
	}
	Tablero(posA.x, posA.y).VaciarCasilla();
	k.ColocarPieza(posB.x, posB.y, k.m_nro, k.m_tipo, k.m_color);
	if (p.m_enjuego) {
		P(p.m_nro).ColocarPieza(posA.x, posA.y, p.m_nro, p.m_tipo, p.m_color);
	}
	return false;
}

bool Ahogado(sf::Vector2i posR, int Rey)
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

sf::Vector2i DistanciaEntrePiezas(sf::Vector2i posA, sf::Vector2i posB)
{
	int disx = posA.x - posB.x, disy = posA.y - posB.y;

	if (disx < 0) { disx = -disx; }
	if (disy < 0) { disy = -disy; }

	sf::Vector2i dis(disx, disy);

	return dis;
}

bool Jaque(sf::Vector2i pos, int k)
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

bool SalvarRey(int R, int Atk)
{
	sf::Vector2i dis = DistanciaEntrePiezas(P(R).m_pos, P(Atk).m_pos), posR;
	int posx = 0, posy = 0;

	if (P(R).m_pos.x < P(Atk).m_pos.x) { posx = 1; }
	else if (P(R).m_pos.x > P(Atk).m_pos.x) { posx = -1; }

	if (P(R).m_pos.y < P(Atk).m_pos.y) { posy = 1; }
	else if (P(R).m_pos.y > P(Atk).m_pos.y) { posy = -1; }

	if (dis.x != 0 && dis.y == 0)
	{
		for (int i = 1; i < dis.x + 1; i++)
		{
			posR.x = P(R).m_pos.x + posx * i; posR.y = P(R).m_pos.y;
			if (CasillaEnJuego(posR, Atk))
			{
				if (MovimientosDisponibles(P(R)))
				{
					return true;
				}
			}
		}
	}
	else if (dis.x == 0 && dis.y != 0)
	{
		for (int j = 1; j < dis.y + 1; j++)
		{
			posR.x = P(R).m_pos.x;	posR.y = P(R).m_pos.y + posx * j;
			if (CasillaEnJuego(posR, Atk))
			{
				if (MovimientosDisponibles(P(R)))
				{
					return true;
				}
			}
		}
	}
	else if (dis.x != 0 && dis.y != 0)
	{

	}

	return false;
}
