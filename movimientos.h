#pragma once

bool Enroque(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	if (!p[k].m_move)
	{
		if (posB.x == posA.x - 2 && posB.y == posA.y)
		{
			if (tablero[7][posA.y].m_ocp)
			{
				if (p[tablero[7][posA.y].m_pieza].m_tipo == Tipo::Torre && !p[tablero[7][posA.y].m_pieza].m_move)
				{
					sf::Vector2i posl{ 7, posA.y };

					if (!PiezaEnMedio(1, posB, posl, k) && !CasillaEnJuego(posA, k))
					{
						std::cout << "\n\tENROQUE CORTO\n";
						CargarPiezaEnCasilla(posl.x - 2, posl.y, tablero[posl.x][posl.y].m_pieza,
							p[tablero[posl.x][posl.y].m_pieza].m_tipo,
							p[tablero[posl.x][posl.y].m_pieza].m_color);
						VaciarCasilla(posl.x, posl.y);
						return true;
					}
				}
			}
		}
		else if (posB.x == posA.x + 2 && posB.y == posA.y)
		{
			if (tablero[0][posA.y].m_ocp)
			{
				if (p[tablero[0][posA.y].m_pieza].m_tipo == Tipo::Torre && !p[tablero[0][posA.y].m_pieza].m_move)
				{
					sf::Vector2i posl{ 0, posA.y };

					if (!PiezaEnMedio(1, posB, posl, k) && !CasillaEnJuego(posA, k))
					{
						std::cout << "\n\tENROQUE LARGO\n";
						CargarPiezaEnCasilla(posl.x + 3, posl.y, tablero[posl.x][posl.y].m_pieza,
							p[tablero[posl.x][posl.y].m_pieza].m_tipo,
							p[tablero[posl.x][posl.y].m_pieza].m_color);
						VaciarCasilla(posl.x, posl.y);
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MovimientosRey(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p[k].m_color)
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

	if (tablero[posA.x][posA.y].m_ocp && p[tablero[posA.x][posA.y].m_pieza].m_color == p[k].m_color)
	{
		return false;
	}

	if (CasillaEnJuego(posA, k))
	{
		return false;
	}

	if (Enroque(k, posA, posB))
	{
		return true;
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

bool MovimientosDama(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int posx = 0, posy = 0;

	switch (p[k].m_color)
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
			if (tablero[posB.x][posB.y + dify].m_ocp)
			{
				std::cout << "\nOCUPADO\n";
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
			if (tablero[posB.x + difx][posB.y].m_ocp)
			{
				std::cout << "\nOCUPADO\n";
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
			if (tablero[posB.x + difx][posB.y + dify].m_ocp)
			{
				std::cout << "\nOCUPADO\n";
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

bool MovimientosTorre(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int posx = 0, posy = 0;

	switch (p[k].m_color)
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
		if (tablero[posB.x + difx][posB.y].m_ocp)
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
		if (tablero[posB.x][posB.y + dify].m_ocp)
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

// Este metodo calcula los movimientos posibles del alfil
bool MovimientosAlfil(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p[k].m_color)
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
		if (tablero[posB.x + difx][posB.y + dify].m_ocp)
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

bool MovimientosCaballo(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p[k].m_color)
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

bool MovimientosPeon(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	switch (p[k].m_color)
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

	if (!tablero[posA.x][posA.y].m_ocp)
	{
		if (!p[k].m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos * 2)
			{
				if (!tablero[posA.x][posA.y + pos].m_ocp)
				{
					return true;
				}
			}
			else if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				return true;
			}
		}
		else if (p[k].m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				return true;
			}
		}
	}
	else if (tablero[posA.x + pos][posA.y + pos].m_ocp || tablero[posA.x - pos][posA.y + pos].m_ocp)
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

bool MovimientosPosibles(int R)
{
	for (int k = 0; k < 32; k++)
	{
		if (p[R].m_color == p[k].m_color)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sf::Vector2i posk(i, j);
					switch (p[k].m_tipo)
					{
					case::Tipo::Rey:
						if (MovimientosRey(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					case::Tipo::Dama:
						if (MovimientosDama(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					case::Tipo::Torre:
						if (MovimientosTorre(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					case::Tipo::Alfil:
						if (MovimientosAlfil(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					case::Tipo::Caballo:
						if (MovimientosCaballo(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					case::Tipo::Peon:
						if (MovimientosPeon(k, posk, p[k].m_pos))
						{
							if (PiezaRival(k, tablero[i][j].m_pieza))
							{
								return true;
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
	}

	return false;
}