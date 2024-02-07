#include <SFML/Graphics.hpp>
#include "game.h"

Game::Game() : ajedrez(sf::VideoMode(distancia * 15, distancia * 13), "Ajedrez")
{
	setFuente(m_fuente, "CascadiaCode.ttf");
	ajedrez.setPosition(sf::Vector2i(450, 50));
}

void Game::CambioDeTurno()
{
	switch (m_turno)
	{
		case Color::B:
			m_turno = Color::N;
			break;
		case Color::N:
			m_turno = Color::B;
			break;
		default:
			break;
	}
}

std::string Game::getTurno()
{
	switch (m_turno)
	{
		case Color::B:
			return "Blanco";
			break;
		case Color::N:
			return "Negro";
			break;
		default:
			break;
	}
}

void Game::setTextura(sf::Texture& t, std::string path) {
	t.loadFromFile(path);
	if (!t.loadFromFile(path)) {
		std::cout << "\n\tCarga Fallida... - " << path << "\n";
	}
}

void Game::setFuente(sf::Font& f, std::string path) {
	f.loadFromFile(path);
	if (!f.loadFromFile(path)) {
		std::cout << "\n\tCarga Fallida... - " << path << "\n";
	}
}

bool Game::PeonCoronado(int k) const
{
	for (int c = 0; c < 16; c++)
	{
		if (m_nropeon[c] == k && m_peoncoronado[c] == true)
		{
			return true;
		}
	}
	return false;
}

int Game::getNroPieza(sf::Vector2i mouse)
{
	for (int k = 0; k < 32; k++)
	{
		if (P(k).m_sprite.getGlobalBounds().contains(mouse.x, mouse.y))
		{
			if (P(k).m_tipo != Tipo::Peon && P(k).m_tipo != Tipo::Rey)
			{
				return P(k).m_nro;
			}
		}
	}
	return -1;
}

bool Game::MouseEnTablero(sf::RenderWindow& ajedrez)
{
	if ((sf::Mouse::getPosition(ajedrez).x > 0 && sf::Mouse::getPosition(ajedrez).x < distancia * 10) &&
		(sf::Mouse::getPosition(ajedrez).y > 0 && sf::Mouse::getPosition(ajedrez).y < distancia * 10))
	{
		return true;
	}
	else { return false; }
}

bool Game::MouseEnCasilla(sf::Vector2i& mouse, int i, int j)
{
	if (Tablero(i, j).m_casilla.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		return true;
	}
	else { return false; }
}

bool Game::Abandonar(sf::Vector2i& mouse, sf::RectangleShape& abandonar)
{
	if (abandonar.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		return true;
	}
	else { return false; }
}

bool Game::Tablas(sf::Vector2i& mouse, sf::RectangleShape& tablas)
{
	if (tablas.getGlobalBounds().contains(mouse.x, mouse.y))
	{
		return true;
	}
	else { return false; }
}

sf::Vector2i Game::EncontrarCasilla(sf::Vector2i& mouse)
{
	sf::Vector2i v(-1, -1);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Tablero(i, j).Casilla::m_casilla.getGlobalBounds().contains(mouse.x, mouse.y))
			{
				v.x = i;	v.y = j;
				break;
			}
		}
	}
	return v;
}

bool Game::PiezaRival(Pieza& k, Pieza& l)
{
	if (k.m_color == l.m_color)
	{
		return false;
	}
	else if (k.m_color != l.m_color)
	{
		return true;
	}
	else { return NULL; }
}

int Game::getReyRival(int piece)
{
	Color color{};
	switch (P(piece).m_color)
	{
		case::Color::B:
			color = Color::N;
			break;
		case::Color::N:
			color = Color::B;
			break;
		default:
			break;
	}
	return P(piece).getReyNum(color);
}

int Game::SentidoDeAtaque(Pieza& Rey, Pieza& rival)
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

void Game::PrepararJuego()
{
	int k = 0, c = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == 7 && i == 4)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Rey, Color::B);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if (j == 0 && i == 4)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Rey, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
			if (j == 7 && i == 3)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Dama, Color::B);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if (j == 0 && i == 3)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Dama, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
			if ((i == 0 && j == 7) || (i == 7 && j == 7))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Torre, Color::B);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if ((i == 0 && j == 0) || (i == 7 && j == 0))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Torre, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
			if ((i == 2 && j == 7) || (i == 5 && j == 7))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Alfil, Color::B);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if ((i == 2 && j == 0) || (i == 5 && j == 0))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Alfil, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
			if ((i == 1 && j == 7) || (i == 6 && j == 7))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Caballo, Color::B);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if ((i == 1 && j == 0) || (i == 6 && j == 0))
			{
				P(k).ColocarPieza(i, j, k, Tipo::Caballo, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
			if (j == 6)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Peon, Color::B);
				Tablero(i, j).LlenarCasilla(k);		m_piezasblancas++;
				m_nropeon[c] = k;		k++;	c++;
			}
			if (j == 1)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Peon, Color::N);
				Tablero(i, j).LlenarCasilla(k);		m_piezasnegras++;
				m_nropeon[c] = k;		k++;	c++;
			}
		}
	}
	m_piezascolocadas = true;
}

void Game::ReiniciarJuego()
{
	m_jugar = false;
	m_piezascolocadas = false;

	m_gameover = false;
	m_tablas = false;

	m_ronda = 1;
	m_turnoB = 0;
	m_turnoN = 0;
	m_turno = Color::B;

	m_piezasblancas = 0;	m_piezasnegras = 0;
	m_move = false;
	m_jugada = false;
	m_captura = false;
	m_piece = -1;
	m_jaque = false;
	m_piezajaque = -1;

	m_mensaje = "";
	m_movimientos = "";
	m_notacion = false;
	m_notamax = 0;
	m_saltodelinea = 0;
	m_Njugada = "";
	m_Ncaptura = "";

	m_coronacion = false;

	for (int m = 0; m < 16; m++)
	{
		m_nropeon[m] = -1;
		m_peoncoronado[m] = false;
	}

	m_lastoldpos.x = -1;	m_lastoldpos.y = -1;

	m_oldpos.x = -1;	m_oldpos.y = -1;
	m_newpos.x = -1;	m_newpos.y = -1;

	m_oldcoord.x = -1;	m_oldcoord.y = -1;
	m_newcoord.x = -1;	m_newcoord.y = -1;

	m_movecoord.x = -1;	m_movecoord.y = -1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Tablero(i, j).VaciarCasilla();
		}
	}

	for (int k = 0; k < 32; k++)
	{
		P(k).m_move = false;
	}
}

void Game::Notaciones()
{
	sf::String movimientos, moveX(char(m_newpos.x + 97)), moveY(std::to_string(m_newpos.y + 1));
	sf::String jaque = "", enroque = "", alpaso = "", conversion = "", jaquemate = "";

	if (m_captura)
	{
		if (P(Tablero(m_newpos.x, m_newpos.y).m_pieza).getTipo()[0] != 'P')
		{
			m_Ncaptura = P(Tablero(m_newpos.x, m_newpos.y).m_pieza).getTipo()[0];
		}
		else if (P(Tablero(m_newpos.x, m_newpos.y).m_pieza).getTipo()[0] == 'P')
		{
			m_Ncaptura = char(m_oldpos.x + 97);
		}
		m_Ncaptura += 'x';
		m_captura = false;
	}
	if (m_jaque)
	{
		if (m_gameover) { jaquemate = '#'; }
		else if (!m_gameover) { jaque = '+'; }
	}
	if (!m_Njugada.isEmpty())
	{
		if (m_Njugada.getSize() == 3 || m_Njugada.getSize() == 5)
		{
			enroque = m_Njugada;
		}
		else if (m_Njugada.getSize() == 4)
		{
			alpaso = m_Njugada;
		}
		else if (m_Njugada.getSize() == 1)
		{
			conversion = m_Njugada;
		}
		m_Njugada = "";
	}

	if (m_notacion && !m_coronacion)
	{
		if (m_tablas && m_gameover)
		{
			movimientos = "0.5 - 0.5";
		}
		else if (!enroque.isEmpty()) {
			movimientos = enroque + ", ";
		}
		else
		{
			if (!jaque.isEmpty())
			{
				movimientos = m_Ncaptura + moveX + moveY + conversion + alpaso + jaque + ", ";
			}
			else if (!jaquemate.isEmpty())
			{
				movimientos = m_Ncaptura + moveX + moveY + conversion + alpaso + jaquemate + ", ";
			}
			else { movimientos = m_Ncaptura + moveX + moveY + conversion + alpaso + ", "; }
		}
		m_notamax += movimientos.getSize();
		if (m_notamax > 24)
		{
			m_movimientos += "\n";
			m_notamax = movimientos.getSize();
			m_saltodelinea++;
		}
		if (m_saltodelinea > 10)
		{
			m_movimientos = movimientos;
		}
		else { m_movimientos += movimientos; }
		m_Ncaptura = "";
		m_notacion = false;
	}
}