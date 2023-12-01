#pragma once

void CargarTextura(sf::Texture& t, std::string path)
{
	t.loadFromFile(path);
}

void PiezaEnCasilla(Pieza p)
{
	std::cout << "\n\tEntrada en " << p.getTipo() << " " << p.getColor() << "\n";
}

void CoordenadasMouse(sf::RenderWindow& ajedrez)
{
	std::cout << "MOUSE - ";
	std::cout << "(" << sf::Mouse::getPosition(ajedrez).x;
	std::cout << ", " << sf::Mouse::getPosition(ajedrez).y << ")\n";
}

void CoordenadasPieza(int k)
{
	std::cout << "PIEZA [" << k + 1 << "] - ";
	std::cout << "(" << p[k].m_sprite.getPosition().x;
	std::cout << ", " << p[k].m_sprite.getPosition().y << ")\n";
}

int ReyRival(int piece)
{
	switch (p[piece].m_color)
	{
	case::Color::B:
		return 16;		// Rey Negro (Rival)
	case::Color::N:
		return 19;		// Rey Blanco (Rival)
	default:
		return -1;
	}
}

int SentidoDeAtaque(Pieza Rey, Pieza rival)
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

bool Jaque(sf::Vector2i pos, int k)
{
	switch (p[k].m_tipo)
	{
	case::Tipo::Dama:
		for (int u = 0; u < 8; u++)
		{
			if (tablero[u][pos.y].m_ocp && u != pos.x)
			{
				if (p[tablero[u][pos.y].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[u][pos.y].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(u, pos.y);
					if (!PiezaEnMedio(1, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x][u].m_ocp && u != pos.y)
			{
				if (p[tablero[pos.x][u].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x][u].m_pieza].m_color != p[k].m_color)
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
			if (tablero[pos.x - l][pos.y - l].m_ocp && (pos.x - l >= 0 && pos.y - l >= 0))
			{
				if (p[tablero[pos.x - l][pos.y - l].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - l][pos.y - l].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(pos.x - l, pos.y - l);
					if (!PiezaEnMedio(3, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x + l][pos.y + l].m_ocp && (pos.x + l <= 7 && pos.y + l <= 7))
			{
				if (p[tablero[pos.x + l][pos.y + l].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + l][pos.y + l].m_pieza].m_color != p[k].m_color)
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
			if (tablero[pos.x - r][pos.y + r].m_ocp && (pos.x - r >= 0 && pos.y + r <= 7))
			{
				if (p[tablero[pos.x - r][pos.y + r].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - r][pos.y + r].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(pos.x - r, pos.y + r);
					if (!PiezaEnMedio(3, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x + r][pos.y - r].m_ocp && (pos.x + r <= 7 && pos.y - r >= 0))
			{
				if (p[tablero[pos.x + r][pos.y - r].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + r][pos.y - r].m_pieza].m_color != p[k].m_color)
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
			if (tablero[u][pos.y].m_ocp && u != pos.x)
			{
				if (p[tablero[u][pos.y].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[u][pos.y].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(u, pos.y);
					if (!PiezaEnMedio(1, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x][u].m_ocp && u != pos.y)
			{
				if (p[tablero[pos.x][u].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x][u].m_pieza].m_color != p[k].m_color)
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
			if (tablero[pos.x - l][pos.y - l].m_ocp && (pos.x - l >= 0 && pos.y - l >= 0))
			{
				if (p[tablero[pos.x - l][pos.y - l].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - l][pos.y - l].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(pos.x - l, pos.y - l);
					if (!PiezaEnMedio(3, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x + l][pos.y + l].m_ocp && (pos.x + l <= 7 && pos.y + l <= 7))
			{
				if (p[tablero[pos.x + l][pos.y + l].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + l][pos.y + l].m_pieza].m_color != p[k].m_color)
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
			if (tablero[pos.x - r][pos.y + r].m_ocp && (pos.x - r >= 0 && pos.y + r <= 7))
			{
				if (p[tablero[pos.x - r][pos.y + r].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - r][pos.y + r].m_pieza].m_color != p[k].m_color)
				{
					sf::Vector2i posRey(pos.x - r, pos.y + r);
					if (!PiezaEnMedio(3, pos, posRey, k))
					{
						return true;
					}
				}
			}
			if (tablero[pos.x + r][pos.y - r].m_ocp && (pos.x + r <= 7 && pos.y - r >= 0))
			{
				if (p[tablero[pos.x + r][pos.y - r].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + r][pos.y - r].m_pieza].m_color != p[k].m_color)
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
		if (tablero[pos.x - 2][pos.y - 1].m_ocp && (pos.x - 2 >= 0 && pos.y - 1 >= 0))
		{
			if (p[tablero[pos.x - 2][pos.y - 1].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x - 2][pos.y - 1].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x - 2][pos.y + 1].m_ocp && (pos.x - 2 >= 0 && pos.y + 1 <= 7))
		{
			if (p[tablero[pos.x - 2][pos.y + 1].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x - 2][pos.y + 1].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x + 2][pos.y - 1].m_ocp && (pos.x + 2 <= 7 && pos.y - 1 >= 0))
		{
			if (p[tablero[pos.x + 2][pos.y - 1].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x + 2][pos.y - 1].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x + 2][pos.y + 1].m_ocp && (pos.x + 2 <= 7 && pos.y + 1 <= 7))
		{
			if (p[tablero[pos.x + 2][pos.y + 1].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x + 2][pos.y + 1].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x - 1][pos.y - 2].m_ocp && (pos.x - 1 >= 0 && pos.y - 2 >= 0))
		{
			if (p[tablero[pos.x - 1][pos.y - 2].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x - 1][pos.y - 2].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x + 1][pos.y - 2].m_ocp && (pos.x + 1 <= 7 && pos.y - 2 >= 0))
		{
			if (p[tablero[pos.x + 1][pos.y - 2].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x + 1][pos.y - 2].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x - 1][pos.y + 2].m_ocp && (pos.x - 1 >= 0 && pos.y + 2 <= 7))
		{
			if (p[tablero[pos.x - 1][pos.y + 2].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x - 1][pos.y + 2].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		if (tablero[pos.x + 1][pos.y + 2].m_ocp && (pos.x + 1 <= 7 && pos.y + 2 <= 7))
		{
			if (p[tablero[pos.x + 1][pos.y + 2].m_pieza].m_tipo == Tipo::Rey &&
				p[tablero[pos.x + 1][pos.y + 2].m_pieza].m_color != p[k].m_color)
			{
				return true;
			}
		}
		break;
	case::Tipo::Peon:
		if (p[k].m_color == Color::N)
		{
			if (tablero[pos.x + 1][pos.y + 1].m_ocp && (pos.x + 1 <= 7 && pos.y + 1 <= 7))
			{
				if (p[tablero[pos.x + 1][pos.y + 1].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + 1][pos.y + 1].m_pieza].m_color != p[k].m_color)
				{
					return true;
				}
			}
			if (tablero[pos.x - 1][pos.y + 1].m_ocp && (pos.x - 1 >= 0 && pos.y + 1 <= 7))
			{
				if (p[tablero[pos.x - 1][pos.y + 1].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - 1][pos.y + 1].m_pieza].m_color != p[k].m_color)
				{
					return true;
				}
			}
		}
		else if (p[k].m_color == Color::B)
		{
			if (tablero[pos.x + 1][pos.y - 1].m_ocp && (pos.x + 1 <= 7 && pos.y - 1 >= 0))
			{
				if (p[tablero[pos.x + 1][pos.y - 1].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x + 1][pos.y - 1].m_pieza].m_color != p[k].m_color)
				{
					return true;
				}
			}
			if (tablero[pos.x - 1][pos.y - 1].m_ocp && (pos.x - 1 >= 0 && pos.y - 1 >= 0))
			{
				if (p[tablero[pos.x - 1][pos.y - 1].m_pieza].m_tipo == Tipo::Rey &&
					p[tablero[pos.x - 1][pos.y - 1].m_pieza].m_color != p[k].m_color)
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

bool Ahogado(sf::Vector2i posr, int r)
{
	int juego = 0, ocupado = 0, fuera = 0;

	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int x = posr.x + i;
			int y = posr.y + j;
			sf::Vector2i arear(x, y);

			if ((x >= 0 && y >= 0) && (x <= 7 && y <= 7) && arear != posr)
			{
				if (CasillaEnJuego(arear, r))
				{
					juego++;
				}
				else if (tablero[x][y].m_ocp && !PiezaRival(r, tablero[x][y].m_pieza))
				{
					ocupado++;
				}
			}
			else if (!((x >= 0 && y >= 0) && (x <= 7 && y <= 7)) && arear != posr)
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