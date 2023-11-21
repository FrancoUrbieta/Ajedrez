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

bool PiezaEnMedio(int s, sf::Vector2i posA, sf::Vector2i posl, int k)
{
	int sentido = s;

	if (sentido == 1)		//horizontal
	{
		int inicio = posA.x, fin = posl.x;

		if (inicio > fin) { inicio = posl.x, fin = posA.x; }

		for (int l = inicio + 1; l < fin; l++)
		{
			if (tablero[l][posA.y].m_ocp && tablero[l][posA.y].m_pieza != p[k].m_nro)
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
			if (tablero[posA.x][l].m_ocp && tablero[posA.x][l].m_pieza != p[k].m_nro)
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
			if (tablero[posA.x - l][posA.y - l].m_ocp && (posA.x - l >= 0 && posA.y - l >= 0))
			{
				if (tablero[posA.x - l][posA.y - l].m_pieza != p[k].m_nro)
				{
					return true;
				}
			}
			if (tablero[posA.x + l][posA.y - l].m_ocp && (posA.x + l <= 7 && posA.y - l >= 0))
			{
				if (tablero[posA.x + l][posA.y - l].m_pieza != p[k].m_nro)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CasillaEnJuego(sf::Vector2i pos, int k)
{
	sf::Vector2i posl;
	int pieza = 0;

	for (int i = 0; i < 8; i++)
	{
		if (i != pos.x && tablero[i][pos.y].m_ocp && p[tablero[i][pos.y].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[i][pos.y].m_pieza].m_tipo == Tipo::Torre ||
				p[tablero[i][pos.y].m_pieza].m_tipo == Tipo::Dama)
			{
				posl.x = i, posl.y = pos.y;
				if (!PiezaEnMedio(1, pos, posl, k))
				{
					pieza++;	if (pos != posl) { return true; }
				}
			}
		}
		if (i != pos.y && tablero[pos.x][i].m_ocp && p[tablero[pos.x][i].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x][i].m_pieza].m_tipo == Tipo::Torre ||
				p[tablero[pos.x][i].m_pieza].m_tipo == Tipo::Dama)
			{
				posl.x = pos.x, posl.y = i;
				if (!PiezaEnMedio(2, pos, posl, k))
				{
					pieza++;	if (pos != posl) { return true; }
				}
			}
		}
	}

	for (int i = 1; i < 9 + 1; i++)
	{
		if (tablero[pos.x - i][pos.y - i].m_ocp && (pos.x - i >= 0 && pos.y - i >= 0))
		{
			if (p[tablero[pos.x - i][pos.y - i].m_pieza].m_color != p[k].m_color)
			{
				if (p[tablero[pos.x - i][pos.y - i].m_pieza].m_tipo == Tipo::Alfil ||
					p[tablero[pos.x - i][pos.y - i].m_pieza].m_tipo == Tipo::Dama)
				{
					posl.x = pos.x - i, posl.y = pos.y - i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						pieza++;	if (pos != posl) { return true; }
					}
				}
			}
		}
		if (tablero[pos.x + i][pos.y - i].m_ocp && (pos.x + i <= 7 && pos.y - i >= 0))
		{
			if (p[tablero[pos.x + i][pos.y - i].m_pieza].m_color != p[k].m_color)
			{
				if (p[tablero[pos.x + i][pos.y - i].m_pieza].m_tipo == Tipo::Alfil ||
					p[tablero[pos.x + i][pos.y - i].m_pieza].m_tipo == Tipo::Dama)
				{
					posl.x = pos.x + i, posl.y = pos.y - i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						pieza++;	if (pos != posl) { return true; }
					}
				}
			}
		}
		if (tablero[pos.x - i][pos.y + i].m_ocp && (pos.x - i >= 0 && pos.y + i <= 7))
		{
			if (p[tablero[pos.x - i][pos.y + i].m_pieza].m_color != p[k].m_color)
			{
				if (p[tablero[pos.x - i][pos.y + i].m_pieza].m_tipo == Tipo::Alfil ||
					p[tablero[pos.x - i][pos.y + i].m_pieza].m_tipo == Tipo::Dama)
				{
					posl.x = pos.x - i, posl.y = pos.y + i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						pieza++;	if (pos != posl) { return true; }
					}
				}
			}
		}
		if (tablero[pos.x + i][pos.y + i].m_ocp && (pos.x + i <= 7 && pos.y + i <= 7))
		{
			if (p[tablero[pos.x + i][pos.y + i].m_pieza].m_color != p[k].m_color)
			{
				if (p[tablero[pos.x + i][pos.y + i].m_pieza].m_tipo == Tipo::Alfil ||
					p[tablero[pos.x + i][pos.y + i].m_pieza].m_tipo == Tipo::Dama)
				{
					posl.x = pos.x + i, posl.y = pos.y + i;
					if (!PiezaEnMedio(3, pos, posl, k))
					{
						pieza++;	if (pos != posl) { return true; }
					}
				}
			}
		}
	}

	if (tablero[pos.x - 2][pos.y - 1].m_ocp && (pos.x - 2 >= 0 && pos.y - 1 >= 0))
	{
		if (p[tablero[pos.x - 2][pos.y - 1].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x - 2][pos.y - 1].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x - 2][pos.y + 1].m_ocp && (pos.x - 2 >= 0 && pos.y + 1 <= 7))
	{
		if (p[tablero[pos.x - 2][pos.y + 1].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x - 2][pos.y + 1].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x + 2][pos.y - 1].m_ocp && (pos.x + 2 <= 7 && pos.y - 1 >= 0))
	{
		if (p[tablero[pos.x + 2][pos.y - 1].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x + 2][pos.y - 1].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x + 2][pos.y + 1].m_ocp && (pos.x + 2 <= 7 && pos.y + 1 <= 7))
	{
		if (p[tablero[pos.x + 2][pos.y + 1].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x + 2][pos.y + 1].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x - 1][pos.y - 2].m_ocp && (pos.x - 1 >= 0 && pos.y - 2 >= 0))
	{
		if (p[tablero[pos.x - 1][pos.y - 2].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x - 1][pos.y - 2].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x + 1][pos.y - 2].m_ocp && (pos.x + 1 <= 7 && pos.y - 2 >= 0))
	{
		if (p[tablero[pos.x + 1][pos.y - 2].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x + 1][pos.y - 2].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x - 1][pos.y + 2].m_ocp && (pos.x - 1 >= 0 && pos.y + 2 <= 7))
	{
		if (p[tablero[pos.x - 1][pos.y + 2].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x - 1][pos.y + 2].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}
	if (tablero[pos.x + 1][pos.y + 2].m_ocp && (pos.x + 1 <= 7 && pos.y + 2 <= 7))
	{
		if (p[tablero[pos.x + 1][pos.y + 2].m_pieza].m_color != p[k].m_color)
		{
			if (p[tablero[pos.x + 1][pos.y + 2].m_pieza].m_tipo == Tipo::Caballo)
			{
				pieza++;	if (pos != posl) { return true; }
			}
		}
	}

	if (tablero[pos.x][pos.y].m_ocp && p[tablero[pos.x][pos.y].m_pieza].m_color != p[k].m_color)
	{
		if (pieza > 1)
		{
			return true;
		}
	}

	return false;
}