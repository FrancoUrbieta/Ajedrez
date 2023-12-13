#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"

bool Game::PiezaClavada(Pieza k, sf::Vector2i posA, sf::Vector2i posB, int R)
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
		//std::cout << "\n\tClavado";
		return true;
	}
	Tablero(posA.x, posA.y).VaciarCasilla();
	k.ColocarPieza(posB.x, posB.y, k.m_nro, k.m_tipo, k.m_color);

	if (p.m_enjuego) {
		P(p.m_nro).ColocarPieza(posA.x, posA.y, p.m_nro, p.m_tipo, p.m_color);
	}

	return false;
}

void Game::CapturarPieza(Pieza& k, Pieza& l, sf::Vector2i newpos)
{
	m_captura = true;
	if (!m_jugada)
	{
		m_mensaje = "PIEZA CAPTURADA";
	}
	//std::cout << "\n\tPIEZA CAPTURADA\n";
	if (m_turno == Color::B)
	{
		l.RemoverPieza(l.m_pos.x, l.m_pos.y, m_piezasnegras);
		m_piezasnegras--;
	}
	else if (m_turno == Color::N)
	{
		l.RemoverPieza(l.m_pos.x, l.m_pos.y, m_piezasblancas);
		m_piezasblancas--;
	}
	Tablero(k.m_pos.x, k.m_pos.y).VaciarCasilla();
	k.ColocarPieza(newpos.x, newpos.y, k.m_nro, k.m_tipo, k.m_color);
}

bool Game::Enroque(int k, sf::Vector2i posA, sf::Vector2i posB)
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
						m_mensaje = "ENROQUE CORTO";
						P(Tablero(posl.x, posl.y).m_pieza).ColocarPieza(posl.x - 2, posl.y,
							Tablero(posl.x, posl.y).m_pieza, P(Tablero(posl.x, posl.y).m_pieza).m_tipo,
							P(Tablero(posl.x, posl.y).m_pieza).m_color);
						Tablero(posl.x, posl.y).VaciarCasilla();
						m_Njugada = "O-O";
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
						m_mensaje = "ENROQUE LARGO";
						P(Tablero(posl.x, posl.y).m_pieza).ColocarPieza(posl.x + 3, posl.y,
							Tablero(posl.x, posl.y).m_pieza, P(Tablero(posl.x, posl.y).m_pieza).m_tipo,
							P(Tablero(posl.x, posl.y).m_pieza).m_color);
						Tablero(posl.x, posl.y).VaciarCasilla();
						m_Njugada = "O-O-O";
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Game::CapturaAlPaso(int k, sf::Vector2i posA, sf::Vector2i posB, sf::Vector2i oldpos)
{
	if (P(k).m_color == Color::N)
	{
		if (posB.y == 4)
		{
			if (Tablero(posB.x + 1, posB.y).m_ocp)
			{
				if (P(Tablero(posB.x + 1, posB.y).m_pieza).m_oldpos == oldpos &&
					P(Tablero(posB.x + 1, posB.y).m_pieza).m_oldpos.y == posB.y + 2)
				{
					if (P(Tablero(posB.x + 1, posB.y).m_pieza).m_color != P(k).m_color &&
						P(Tablero(posB.x + 1, posB.y).m_pieza).m_tipo == Tipo::Peon)
					{
						if (posA.x == posB.x + 1 && posA.y == posB.y + 1)
						{
							CapturarPieza(P(k), P(Tablero(posB.x + 1, posB.y).m_pieza), posA);
							return true;
						}
					}
				}
			}
			if (Tablero(posB.x - 1, posB.y).m_ocp)
			{
				if (P(Tablero(posB.x - 1, posB.y).m_pieza).m_oldpos == oldpos &&
					P(Tablero(posB.x - 1, posB.y).m_pieza).m_oldpos.y == posB.y + 2)
				{
					if (P(Tablero(posB.x - 1, posB.y).m_pieza).m_color != P(k).m_color &&
						P(Tablero(posB.x - 1, posB.y).m_pieza).m_tipo == Tipo::Peon)
					{
						if (posA.x == posB.x - 1 && posA.y == posB.y + 1)
						{
							CapturarPieza(P(k), P(Tablero(posB.x - 1, posB.y).m_pieza), posA);
							return true;
						}
					}
				}
			}
		}
	}
	else if (P(k).m_color == Color::B)
	{
		if (posB.y == 3)
		{
			if (Tablero(posB.x + 1, posB.y).m_ocp)
			{
				if (P(Tablero(posB.x + 1, posB.y).m_pieza).m_oldpos == oldpos &&
					P(Tablero(posB.x + 1, posB.y).m_pieza).m_oldpos.y == posB.y - 2)
				{
					if (P(Tablero(posB.x + 1, posB.y).m_pieza).m_color != P(k).m_color &&
						P(Tablero(posB.x + 1, posB.y).m_pieza).m_tipo == Tipo::Peon)
					{
						if (posA.x == posB.x + 1 && posA.y == posB.y - 1)
						{
							CapturarPieza(P(k), P(Tablero(posB.x + 1, posB.y).m_pieza), posA);
							return true;
						}
					}
				}
			}
			if (Tablero(posB.x - 1, posB.y).m_ocp)
			{
				if (P(Tablero(posB.x - 1, posB.y).m_pieza).m_oldpos == oldpos && 
					P(Tablero(posB.x - 1, posB.y).m_pieza).m_oldpos.y == posB.y - 2)
				{
					if (P(Tablero(posB.x - 1, posB.y).m_pieza).m_color != P(k).m_color &&
						P(Tablero(posB.x - 1, posB.y).m_pieza).m_tipo == Tipo::Peon)
					{
						if (posA.x == posB.x - 1 && posA.y == posB.y - 1)
						{
							CapturarPieza(P(k), P(Tablero(posB.x - 1, posB.y).m_pieza), posA);
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool Game::Coronacion(int k, sf::Vector2i posA, sf::Vector2i posB)
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

bool Game::Conversion(sf::Vector2i mouse, sf::Vector2i pos)
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