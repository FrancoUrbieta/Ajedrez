#pragma once

void MovimientosRey() {}

void MovimientosDama() {}

bool MovimientosTorre(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	if (p[k].m_color == Color::B) { pos = posB.x - posA.x; }
	else if (p[k].m_color == Color::N) { pos = -posB.x + posA.x; }

	if (posB.x == posA.x + pos && posB.y == posA.y)
	{
		return true;
	}
	else if (posB.x == posA.x - pos && posB.y == posA.y)
	{
		return true;
	}
	else if (posB.x == posA.x && posB.y == posA.y + pos)
	{
		return true;
	}
	else if (posB.x == posA.x && posB.y == posA.y - pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MovimientosAlfil(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	if (p[k].m_color == Color::B) { pos = posB.x - posA.x; }
	else if (p[k].m_color == Color::N) { pos = -posB.x + posA.x; }

	if (posB.x == posA.x + pos && posB.y == posA.y + pos)
	{
		return true;
	}
	else if (posB.x == posA.x + pos && posB.y == posA.y - pos)
	{
		return true;
	}
	else if (posB.x == posA.x - pos && posB.y == posA.y - pos)
	{
		return true;
	}
	else if (posB.x == posA.x - pos && posB.y == posA.y + pos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MovimientosCaballo() {}

bool MovimientosPeon(int k, sf::Vector2i posA, sf::Vector2i posB)
{
	int pos = 0;

	if (p[k].m_color == Color::B) { pos = 1; }
	else if (p[k].m_color == Color::N) { pos = -1; }

	if (!tablero[posA.x][posA.y].m_ocp)
	{
		if (!p[k].m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos * 2)
			{
				p[k].m_move = true;
				return true;
			}
			else if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				p[k].m_move = true;
				return true;
			}
			else { return false; }
		}
		else if (p[k].m_move)
		{
			if (posB.x == posA.x && posB.y == posA.y + pos)
			{
				p[k].m_move = true;
				return true;
			}
			else { return false; }
		}
	}
	else if (tablero[posA.x + pos][posA.y + pos].m_ocp)
	{
		if (posB.x == posA.x + pos && posB.y == posA.y + pos)
		{
			p[k].m_move = true;
			return true;
		}
		else { return false; }
	}
	else if (tablero[posA.x - pos][posA.y + pos].m_ocp)
	{
		if (posB.x == posA.x - pos && posB.y == posA.y + pos)
		{
			p[k].m_move = true;
			return true;
		}
		else { return false; }
	}
	else { return false; }
}