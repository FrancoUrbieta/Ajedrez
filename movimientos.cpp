#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

bool Game::MovimientosRey(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
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

	if (Tablero(posP.x, posP.y).m_ocp && P(Tablero(posP.x, posP.y).m_pieza).m_color == p.m_color)
	{
		return false;
	}

	if (CasillaEnJuego(posP, p.m_nro))
	{
		return false;
	}

	return (posA.x == posP.x + pos && posA.y == posP.y + pos)
		|| (posA.x == posP.x + pos && posA.y == posP.y - pos)
		|| (posA.x == posP.x - pos && posA.y == posP.y - pos)
		|| (posA.x == posP.x - pos && posA.y == posP.y + pos)
		|| (posA.x == posP.x + pos && posA.y == posP.y)
		|| (posA.x == posP.x - pos && posA.y == posP.y)
		|| (posA.x == posP.x && posA.y == posP.y + pos)
		|| (posA.x == posP.x && posA.y == posP.y - pos);
}

bool Game::MovimientosDama(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
{
	int posx = 0, posy = 0;

	switch (p.m_color)
	{
		case Color::B:
			posx = posA.x - posP.x;
			posy = posA.y - posP.y;
			break;
		case Color::N:
			posx = -posA.x + posP.x;
			posy = -posA.y + posP.y;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, difI = posx, difJ = posy;

	if (difI == 0 && difJ != 0)
	{
		if (posA.y > posP.y) { dify = -1; }

		if (difJ < 0) { difJ = -difJ; }

		int sumy = dify;

		for (int j = 0; j < difJ - 1; j++)
		{
			if (Tablero(posA.x, posA.y + dify).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			dify = dify + sumy;
		}
	}
	else if (difI != 0 && difJ == 0)
	{
		if (posA.x > posP.x) { difx = -1; }

		if (difI < 0) { difI = -difI; }

		int sumx = difx;

		for (int i = 0; i < difI - 1; i++)
		{
			if (Tablero(posA.x + difx, posA.y).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			difx = difx + sumx;
		}
	}
	else if (difI != 0 && difJ != 0)
	{
		if (posA.x > posP.x) { difx = -1; }
		if (posA.y > posP.y) { dify = -1; }

		if (difJ < 0) { difJ = -difJ; }

		int sumx = difx, sumy = dify;

		for (int i = 0; i < difJ - 1; i++)
		{
			if (Tablero(posA.x + difx, posA.y + dify).m_ocp)
			{
				//std::cout << "\nOCUPADO\n";
				return false;
			}
			difx = difx + sumx;		dify = dify + sumy;
		}
	}

	if (posA.x != posP.x && posA.y != posP.y)
	{
		return (posA.x == posP.x + posy && posA.y == posP.y + posy)
			|| (posA.x == posP.x - posy && posA.y == posP.y - posy)
			|| (posA.x == posP.x + posy && posA.y == posP.y - posy)
			|| (posA.x == posP.x - posy && posA.y == posP.y + posy);
	}

	return (posA.x == posP.x + posx && posA.y == posP.y)
		|| (posA.x == posP.x - posx && posA.y == posP.y)
		|| (posA.x == posP.x && posA.y == posP.y + posy)
		|| (posA.x == posP.x && posA.y == posP.y - posy);
}

bool Game::MovimientosTorre(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
{
	int posx = 0, posy = 0;

	switch (p.m_color)
	{
		case Color::B:
			posx = posA.x - posP.x;
			posy = posA.y - posP.y;
			break;
		case Color::N:
			posx = -posA.x + posP.x;
			posy = -posA.y + posP.y;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, difI = posx, difJ = posy;

	if (posA.x > posP.x) { difx = -1; }

	if (difI < 0) { difI = -difI; }

	int sumx = difx;

	for (int i = 0; i < difI - 1; i++)
	{
		if (Tablero(posA.x + difx, posA.y).m_ocp)
		{
			return false;
		}

		difx = difx + sumx;
	}

	if (posA.y > posP.y) { dify = -1; }

	if (difJ < 0) { difJ = -difJ; }

	int sumy = dify;

	for (int j = 0; j < difJ - 1; j++)
	{
		if (Tablero(posA.x, posA.y + dify).m_ocp)
		{
			return false;
		}

		dify = dify + sumy;
	}

	return (posA.x == posP.x + posx && posA.y == posP.y)
		|| (posA.x == posP.x - posx && posA.y == posP.y)
		|| (posA.x == posP.x && posA.y == posP.y + posy)
		|| (posA.x == posP.x && posA.y == posP.y - posy);
}

bool Game::MovimientosAlfil(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
{
	int pos = 0;

	switch (p.m_color)
	{
		case Color::B:
			pos = posA.x - posP.x;
			break;
		case Color::N:
			pos = -posA.x + posP.x;
			break;
		default:
			break;
	}

	int difx = 1, dify = 1, dif = pos;

	if (posA.x > posP.x) { difx = -1; }
	if (posA.y > posP.y) { dify = -1; }

	if (dif < 0) { dif = -dif; }

	int sumx = difx, sumy = dify;

	for (int i = 0; i < dif - 1; i++)
	{
		if (Tablero(posA.x + difx, posA.y + dify).m_ocp)
		{
			return false;
		}

		difx = difx + sumx;		dify = dify + sumy;
	}

	if (posA.x == posP.x || posA.y == posP.y)
	{
		return false;
	}

	return (posA.x == posP.x + pos && posA.y == posP.y + pos)
		|| (posA.x == posP.x - pos && posA.y == posP.y - pos)
		|| (posA.x == posP.x + pos && posA.y == posP.y - pos)
		|| (posA.x == posP.x - pos && posA.y == posP.y + pos);
}

bool Game::MovimientosCaballo(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
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

	return (posA.x == posP.x + pos && posA.y == posP.y + pos * 2)
		|| (posA.x == posP.x + pos && posA.y == posP.y - pos * 2)
		|| (posA.x == posP.x - pos && posA.y == posP.y + pos * 2)
		|| (posA.x == posP.x - pos && posA.y == posP.y - pos * 2)
		|| (posA.x == posP.x + pos * 2 && posA.y == posP.y + pos)
		|| (posA.x == posP.x + pos * 2 && posA.y == posP.y - pos)
		|| (posA.x == posP.x - pos * 2 && posA.y == posP.y + pos)
		|| (posA.x == posP.x - pos * 2 && posA.y == posP.y - pos);
}

bool Game::MovimientosPeon(Pieza& p, sf::Vector2i posP, sf::Vector2i posA)
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

	if (!Tablero(posP.x, posP.y).m_ocp)
	{
		if (!p.m_move)
		{
			if (posA.x == posP.x && posA.y == posP.y + pos * 2)
			{
				if (!Tablero(posP.x, posP.y + pos).m_ocp)
				{
					return true;
				}
			}
			else if (posA.x == posP.x && posA.y == posP.y + pos)
			{
				return true;
			}
		}
		else if (p.m_move)
		{
			if (posA.x == posP.x && posA.y == posP.y + pos)
			{
				return true;
			}
		}
	}
	else if (Tablero(posP.x + pos, posP.y + pos).m_ocp || Tablero(posP.x - pos, posP.y + pos).m_ocp)
	{
		if (posA.x == posP.x + pos && posA.y == posP.y + pos)
		{
			return true;
		}
		else if (posA.x == posP.x - pos && posA.y == posP.y + pos)
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