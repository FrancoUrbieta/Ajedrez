#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

bool Game::MovimientosRey(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p.m_color)
	{
		case Color::B:
			pos = 1;
			break;
		case Color::N:
			pos = -1;
			break;
		default:
			break;
	}

	if (Tablero(posA.x, posA.y).m_ocp && P(Tablero(posA.x, posA.y).m_pieza).m_color == p.m_color)
	{
		return false;
	}

	if (CasillaEnJuego(posA, p.m_nro))
	{
		return false;
	}

	return (posB.x == posA.x + pos && posB.y == posA.y + pos)
		|| (posB.x == posA.x + pos && posB.y == posA.y - pos)
		|| (posB.x == posA.x - pos && posB.y == posA.y - pos)
		|| (posB.x == posA.x - pos && posB.y == posA.y + pos)
		|| (posB.x == posA.x + pos && posB.y == posA.y)
		|| (posB.x == posA.x - pos && posB.y == posA.y)
		|| (posB.x == posA.x && posB.y == posA.y + pos)
		|| (posB.x == posA.x && posB.y == posA.y - pos);
}

bool Game::MovimientosDama(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int posx = 0, posy = 0;

	switch (p.m_color)
	{
		case Color::B:
			posx = posB.x - posA.x;
			posy = posB.y - posA.y;
			break;
		case Color::N:
			posx = -posB.x + posA.x;
			posy = -posB.y + posA.y;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, difI = posx, difJ = posy;

	if (difI == 0 && difJ != 0)
	{
		if (posB.y > posA.y) { dify = -1; }

		if (difJ < 0) { difJ = -difJ; }

		int sumy = dify;

		for (int j = 0; j < difJ - 1; j++)
		{
			if (Tablero(posB.x, posB.y + dify).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			dify = dify + sumy;
		}
	}
	else if (difI != 0 && difJ == 0)
	{
		if (posB.x > posA.x) { difx = -1; }

		if (difI < 0) { difI = -difI; }

		int sumx = difx;

		for (int i = 0; i < difI - 1; i++)
		{
			if (Tablero(posB.x + difx, posB.y).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			difx = difx + sumx;
		}
	}
	else if (difI != 0 && difJ != 0)
	{
		if (posB.x > posA.x) { difx = -1; }
		if (posB.y > posA.y) { dify = -1; }

		if (difJ < 0) { difJ = -difJ; }

		int sumx = difx, sumy = dify;

		for (int i = 0; i < difJ - 1; i++)
		{
			if (Tablero(posB.x + difx, posB.y + dify).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			difx = difx + sumx;		dify = dify + sumy;
		}
	}

	if (posB.x != posA.x && posB.y != posA.y)
	{
		return (posB.x == posA.x + posy && posB.y == posA.y + posy)
			|| (posB.x == posA.x - posy && posB.y == posA.y - posy)
			|| (posB.x == posA.x + posy && posB.y == posA.y - posy)
			|| (posB.x == posA.x - posy && posB.y == posA.y + posy);
	}

	return (posB.x == posA.x + posx && posB.y == posA.y)
		|| (posB.x == posA.x - posx && posB.y == posA.y)
		|| (posB.x == posA.x && posB.y == posA.y + posy)
		|| (posB.x == posA.x && posB.y == posA.y - posy);
}

bool Game::MovimientosTorre(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int posx = 0, posy = 0;

	switch (p.m_color)
	{
		case Color::B:
			posx = posB.x - posA.x;
			posy = posB.y - posA.y;
			break;
		case Color::N:
			posx = -posB.x + posA.x;
			posy = -posB.y + posA.y;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, difI = posx, difJ = posy;

	if (posB.x > posA.x) { difx = -1; }

	if (difI < 0) { difI = -difI; }

	int sumx = difx;

	for (int i = 0; i < difI - 1; i++)
	{
		if (Tablero(posB.x + difx, posB.y).m_ocp)
		{
			return false;
		}

		difx = difx + sumx;
	}

	if (posB.y > posA.y) { dify = -1; }

	if (difJ < 0) { difJ = -difJ; }

	int sumy = dify;

	for (int j = 0; j < difJ - 1; j++)
	{
		if (Tablero(posB.x, posB.y + dify).m_ocp)
		{
			return false;
		}

		dify = dify + sumy;
	}

	return (posB.x == posA.x + posx && posB.y == posA.y)
		|| (posB.x == posA.x - posx && posB.y == posA.y)
		|| (posB.x == posA.x && posB.y == posA.y + posy)
		|| (posB.x == posA.x && posB.y == posA.y - posy);
}

bool Game::MovimientosAlfil(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p.m_color)
	{
		case Color::B:
			pos = posB.x - posA.x;
			break;
		case Color::N:
			pos = -posB.x + posA.x;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, dif = pos;

	if (posB.x > posA.x) { difx = -1; }
	if (posB.y > posA.y) { dify = -1; }

	if (dif < 0) { dif = -dif; }

	int sumx = difx, sumy = dify;

	for (int i = 0; i < dif - 1; i++)
	{
		if (Tablero(posB.x + difx, posB.y + dify).m_ocp)
		{
			return false;
		}

		difx = difx + sumx;		dify = dify + sumy;
	}

	if (posB.x == posA.x || posB.y == posA.y)
	{
		return false;
	}

	return (posB.x == posA.x + pos && posB.y == posA.y + pos)
		|| (posB.x == posA.x - pos && posB.y == posA.y - pos)
		|| (posB.x == posA.x + pos && posB.y == posA.y - pos)
		|| (posB.x == posA.x - pos && posB.y == posA.y + pos);
}

bool Game::MovimientosCaballo(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p.m_color)
	{
		case Color::B:
			pos = 1;
			break;
		case Color::N:
			pos = -1;
			break;
		default:
			break;
	}

	return (posB.x == posA.x + pos && posB.y == posA.y + pos * 2)
		|| (posB.x == posA.x + pos && posB.y == posA.y - pos * 2)
		|| (posB.x == posA.x - pos && posB.y == posA.y + pos * 2)
		|| (posB.x == posA.x - pos && posB.y == posA.y - pos * 2)
		|| (posB.x == posA.x + pos * 2 && posB.y == posA.y + pos)
		|| (posB.x == posA.x + pos * 2 && posB.y == posA.y - pos)
		|| (posB.x == posA.x - pos * 2 && posB.y == posA.y + pos)
		|| (posB.x == posA.x - pos * 2 && posB.y == posA.y - pos);
}

bool Game::MovimientosPeon(Pieza& p, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p.m_color)
	{
		case Color::B:
			pos = 1;
			break;
		case Color::N:
			pos = -1;
			break;
		default:
			break;
	}

	if (!Tablero(posA.x, posA.y).m_ocp)
	{
		if (!p.m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos * 2)
			{
				if (!Tablero(posA.x, posA.y + pos).m_ocp)
				{
					return true;
				}
			}
			else if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				return true;
			}
		}
		else if (p.m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				return true;
			}
		}
	}
	else if (Tablero(posA.x + pos, posA.y + pos).m_ocp || Tablero(posA.x - pos, posA.y + pos).m_ocp)
	{
		if (posB.x == posA.x + pos && posB.y == posA.y + pos)
		{
			return true;
		}
		else if (posB.x == posA.x - pos && posB.y == posA.y + pos)
		{
			return true;
		}
	}
	return false;
}

bool Game::MovimientoPosible(int k, sf::Vector2i posk)
{
	switch (P(k).m_tipo)
	{
		case::Tipo::Dama:
			if (MovimientosDama(P(k), posk, P(k).m_pos))
			{
				if (!PiezaClavada(P(k), posk, P(k).m_pos, P(k).getReyNum(P(k).m_color)))
				{
					if (Tablero(posk.x, posk.y).m_ocp)
					{
						if (PiezaRival(P(k), P(Tablero(posk.x, posk.y).m_pieza)))
						{
							return true;
						}
					}
					else if (!Tablero(posk.x, posk.y).m_ocp)
					{
						return true;
					}
				}
			}
			break;
		case::Tipo::Torre:
			if (MovimientosTorre(P(k), posk, P(k).m_pos))
			{
				if (!PiezaClavada(P(k), posk, P(k).m_pos, P(k).getReyNum(P(k).m_color)))
				{
					if (Tablero(posk.x, posk.y).m_ocp)
					{
						if (PiezaRival(P(k), P(Tablero(posk.x, posk.y).m_pieza)))
						{
							return true;
						}
					}
					else if (!Tablero(posk.x, posk.y).m_ocp)
					{
						return true;
					}
				}
			}
			break;
		case::Tipo::Alfil:
			if (MovimientosAlfil(P(k), posk, P(k).m_pos))
			{
				if (!PiezaClavada(P(k), posk, P(k).m_pos, P(k).getReyNum(P(k).m_color)))
				{
					if (Tablero(posk.x, posk.y).m_ocp)
					{
						if (PiezaRival(P(k), P(Tablero(posk.x, posk.y).m_pieza)))
						{
							return true;
						}
					}
					else if (!Tablero(posk.x, posk.y).m_ocp)
					{
						return true;
					}
				}
			}
			break;
		case::Tipo::Caballo:
			if (MovimientosCaballo(P(k), posk, P(k).m_pos))
			{
				if (!PiezaClavada(P(k), posk, P(k).m_pos, P(k).getReyNum(P(k).m_color)))
				{
					if (Tablero(posk.x, posk.y).m_ocp)
					{
						if (PiezaRival(P(k), P(Tablero(posk.x, posk.y).m_pieza)))
						{
							return true;
						}
					}
					else if (!Tablero(posk.x, posk.y).m_ocp)
					{
						return true;
					}
				}
			}
			break;
		case::Tipo::Peon:
			if (MovimientosPeon(P(k), posk, P(k).m_pos))
			{
				if (!PiezaClavada(P(k), posk, P(k).m_pos, P(k).getReyNum(P(k).m_color)))
				{
					if (Tablero(posk.x, posk.y).m_ocp)
					{
						if (PiezaRival(P(k), P(Tablero(posk.x, posk.y).m_pieza)))
						{
							return true;
						}
					}
					else if (!Tablero(posk.x, posk.y).m_ocp)
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

bool Game::MovimientosDisponibles(Pieza& R)
{
	for (int k = 0; k < 32; k++)
	{
		if (R.m_color == P(k).m_color && P(k).m_enjuego)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sf::Vector2i posk(i, j);
					if (MovimientoPosible(k, posk))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}