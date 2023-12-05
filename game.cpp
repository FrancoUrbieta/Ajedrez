#include <SFML/Graphics.hpp>
#include <iostream>
#include "casilla.h"
#include "game.h"
#include "partida.h"
#include "movimientos.h"
#include "jaquemate.h"
#include "debugging.h"

Game::Game() : ajedrez(sf::VideoMode(960, 825), "Ajedrez")
{
	int k = 0;
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
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasblancas++;
			}
			if (j == 1)
			{
				P(k).ColocarPieza(i, j, k, Tipo::Peon, Color::N);
				Tablero(i, j).LlenarCasilla(k);		k++;	m_piezasnegras++;
			}
		}
	}
	ajedrez.setPosition(sf::Vector2i(700, 100));
}

void Game::Run()
{
	while (ajedrez.isOpen())
	{
		ProcessEvents();
		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;

	while (ajedrez.pollEvent(event))
	{
		sf::Vector2i mouse = sf::Mouse::getPosition(ajedrez);

		switch (event.type)
		{
		case sf::Event::Closed:
			ajedrez.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				m_movecoord.x = -1;		m_movecoord.y = -1;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (MouseEnCasilla(mouse, i, j) && Tablero(i, j).m_ocp)
						{
							if (P(Tablero(i, j).m_pieza).m_color == m_turno && P(Tablero(i, j).m_pieza).m_enjuego)
							{
								PiezaEnCasilla(P(Tablero(i, j).m_pieza));
								CoordenadasMouse(ajedrez);
								CoordenadasPieza(Tablero(i, j).m_pieza);
								CoordenadasCasilla(i, j);

								m_piece = Tablero(i, j).m_pieza;
								m_oldpos.x = i;		m_oldpos.y = j;
								m_oldcoord.x = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().x;
								m_oldcoord.y = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().y;
								m_movecoord.x = mouse.x - P(m_piece).m_sprite.getPosition().x;
								m_movecoord.y = mouse.y - P(m_piece).m_sprite.getPosition().y;
								m_move = true;
								break;
							}
							else
							{
								std::cout << "\n\tPieza Equivocada - Turno del Equipo " << getTurno() << "...\n";
							}
						}
						else if (MouseEnCasilla(mouse, i, j) && !Tablero(i, j).m_ocp)
						{
							std::cout << "\n\Entrada en Casilla Vacia\n";
							m_oldpos.x = i;		m_oldpos.y = j;
							m_oldcoord.x = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().x;
							m_oldcoord.y = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().y;
							CoordenadasMouse(ajedrez);
							CoordenadasCasilla(i, j);
							break;
						}
					}
					if (!MouseEnTablero(ajedrez))
					{
						std::cout << "\n\tSin entrada - Fuera del Tablero\n";
						break;
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (MouseEnCasilla(mouse, i, j) && Tablero(i, j).m_ocp)
						{
							if (P(Tablero(i, j).m_pieza).m_tipo == Tipo::Rey &&
								P(Tablero(i, j).m_pieza).m_color == m_turno)
							{
								std::cout << "\n\n\t\tABANDONO - El equipo " << getTurno() << " se ha retirado, ";
								CambioDeTurno();
								std::cout << "gana el equipo " << getTurno() << "!\n\n";
								ajedrez.close();
							}
						}
					}
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_movecoord.x == -1 && m_movecoord.y == -1) { break; }

				m_newpos = EncontrarCasilla(mouse);

				if (m_oldpos == m_newpos)
				{
					P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					m_move = false;		break;
				}
				if (m_jaque)
				{
					if (P(m_piece).m_tipo != Tipo::Rey)
					{
						int Rey = ReyRival(m_piezajaque);
						if (m_newpos == P(m_piezajaque).m_pos)
						{
							Tablero(m_oldpos.x, m_oldpos.y).VaciarCasilla();
							Tablero(P(m_piezajaque).m_pos.x, P(m_piezajaque).m_pos.y).VaciarCasilla();
							if (CasillaEnJuego(P(Rey).m_pos, Rey))
							{
								std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
								P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
								P(m_piece).ColocarPieza(m_oldpos.x, m_oldpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
								P(m_piezajaque).ColocarPieza(P(m_piezajaque).m_pos.x, P(m_piezajaque).m_pos.y,
									m_piezajaque, P(m_piezajaque).m_tipo, P(m_piezajaque).m_color);
								m_move = false;		break;
							}
							else if (!CasillaEnJuego(P(Rey).m_pos, Rey))
							{
								m_jaque = false;
							}
							P(m_piece).ColocarPieza(m_oldpos.x, m_oldpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
							P(m_piezajaque).ColocarPieza(P(m_piezajaque).m_pos.x, P(m_piezajaque).m_pos.y,
								m_piezajaque, P(m_piezajaque).m_tipo, P(m_piezajaque).m_color);
						}
						else if (m_newpos != P(m_piezajaque).m_pos && !Tablero(m_newpos.x, m_newpos.y).m_ocp)
						{
							int angulo = SentidoDeAtaque(P(Rey), P(m_piezajaque));
							P(m_piece).ColocarPieza(m_newpos.x, m_newpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
							if (!PiezaEnMedio(angulo, P(Rey).m_pos, P(m_piezajaque).m_pos, Rey))
							{
								std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
								P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
								Tablero(m_newpos.x, m_newpos.y).VaciarCasilla();
								m_move = false;		break;
							}
							else if (PiezaEnMedio(angulo, P(Rey).m_pos, P(m_piezajaque).m_pos, Rey))
							{
								m_jaque = false;
							}
							Tablero(m_newpos.x, m_newpos.y).VaciarCasilla();
						}
						else
						{
							std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
							P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							m_move = false;		break;
						}
					}
				}

				switch (P(m_piece).m_tipo)
				{
				case::Tipo::Rey:
					m_move = MovimientosRey(P(m_piece), m_newpos, m_oldpos);
					if (m_jaque && m_move) { m_jaque = false; }
					break;
				case::Tipo::Dama:
					m_move = MovimientosDama(P(m_piece), m_newpos, m_oldpos);
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Torre:
					m_move = MovimientosTorre(P(m_piece), m_newpos, m_oldpos);
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Alfil:
					m_move = MovimientosAlfil(P(m_piece), m_newpos, m_oldpos);
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Caballo:
					m_move = MovimientosCaballo(P(m_piece), m_newpos, m_oldpos);
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Peon:
					m_move = MovimientosPeon(P(m_piece), m_newpos, m_oldpos);
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				default:
					break;
				}

				if (m_jaque) { std::cout << "\n\tJAQUE\n"; }

				if (m_move)
				{
					if (!MouseEnCasilla(mouse, m_oldpos.x, m_oldpos.y))
					{
						if (MouseEnTablero(ajedrez))
						{
							if (m_piece > -1) { P(m_piece).m_move = true; }
							std::cout << "\n\tNUEVA UBICACION\n";
							CoordenadasPieza(m_piece);
							CoordenadasCasilla(m_newpos.x, m_newpos.y);

							m_newcoord.x = Tablero(m_newpos.x, m_newpos.y).m_casilla.getGlobalBounds().getPosition().x;
							m_newcoord.y = Tablero(m_newpos.x, m_newpos.y).m_casilla.getGlobalBounds().getPosition().y;

							if (!Tablero(m_newpos.x, m_newpos.y).m_ocp)
							{
								P(m_piece).ColocarPieza(m_newpos.x, m_newpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
								Tablero(m_oldpos.x, m_oldpos.y).VaciarCasilla();
							}
							else if (Tablero(m_newpos.x, m_newpos.y).m_ocp)
							{
								if (PiezaRival(P(Tablero(m_newpos.x, m_newpos.y).m_pieza), P(Tablero(m_oldpos.x, m_oldpos.y).m_pieza)))
								{
									std::cout << "\n\tPIEZA CAPTURADA\n";
									if (P(Tablero(m_newpos.x, m_newpos.y).m_pieza).m_tipo == Tipo::Rey)
									{
										ajedrez.close();
									}
									if (m_turno == Color::B)
									{
										P(Tablero(m_newpos.x, m_newpos.y).m_pieza).RemoverPieza(m_newpos.x, m_newpos.y, m_piezasnegras);
										m_piezasnegras--;
									}
									else if (m_turno == Color::N)
									{
										P(Tablero(m_newpos.x, m_newpos.y).m_pieza).RemoverPieza(m_newpos.x, m_newpos.y, m_piezasblancas);
										m_piezasblancas--;
									}
									P(m_piece).ColocarPieza(m_newpos.x, m_newpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
									Tablero(m_oldpos.x, m_oldpos.y).VaciarCasilla();
								}
								else if (!PiezaRival(P(Tablero(m_newpos.x, m_newpos.y).m_pieza), P(Tablero(m_oldpos.x, m_oldpos.y).m_pieza)))
								{
									P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
									CambioDeTurno();
								}
							}
						}
						else if (!MouseEnTablero(ajedrez))
						{
							P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
							m_move = false;		break;
						}
					}
					CambioDeTurno();
					m_ronda++;
					if (Ahogado(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)) &&
						CasillaEnJuego(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)))
					{
						std::cout << "\n\n\t\tJAQUE MATE - Gana el equipo " << P(m_piece).getColor() << "!\n\n";
						ajedrez.close();
					}
					else if (!MovimientosDisponibles(P(ReyRival(m_piece))) &&
						Ahogado(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)) &&
						!CasillaEnJuego(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)))
					{
						std::cout << "\n\n\t\tTABLAS POR AHOGADO - No hay movimientos disponibles.\n\n";
						ajedrez.close();
					}
					else if (m_piezasblancas == 1 && m_piezasnegras == 1)
					{
						std::cout << "\n\n\t\tTABLAS POR MATERIAL INSUFICIENTE - Un Rey no puede dar JaqueMate a otro.\n\n";
						ajedrez.close();
					}
				}
				else if (!m_move)
				{
					P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
				}
				m_piece = -1;
			}
			break;
		}
		if (m_move) { P(m_piece).m_sprite.setPosition(mouse.x - m_movecoord.x, mouse.y - m_movecoord.y); }
	}
}

void Game::Render()
{
	ajedrez.setSize(sf::Vector2u(960, 825));
	ajedrez.clear(sf::Color(70, 70, 70));

	sf::Texture casilla[2];

	setTextura(casilla[0], "CasillaB.PNG");
	setTextura(casilla[1], "CasillaN.PNG");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
			{
				Tablero(i, j).setSprite(Tablero(i, j), casilla[0]);
				Tablero(i, j).m_casilla.setPosition(sf::Vector2f(distancia * i + distancia, distancia * j + distancia));
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				Tablero(i, j).setSprite(Tablero(i, j), casilla[1]);
				Tablero(i, j).m_casilla.setPosition(sf::Vector2f(distancia * i + distancia, distancia * j + distancia));
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ajedrez.draw(Tablero(i, j).m_casilla);
		}
	}

	sf::Texture pieza[12];

	setTextura(pieza[0], "ReyB.PNG");
	setTextura(pieza[1], "ReyN.PNG");

	setTextura(pieza[2], "DamaB.PNG");
	setTextura(pieza[3], "DamaN.PNG");

	setTextura(pieza[4], "TorreB.PNG");
	setTextura(pieza[5], "TorreN.PNG");

	setTextura(pieza[6], "AlfilB.PNG");
	setTextura(pieza[7], "AlfilN.PNG");

	setTextura(pieza[8], "CaballoB.PNG");
	setTextura(pieza[9], "CaballoN.PNG");

	setTextura(pieza[10], "PeonB.PNG");
	setTextura(pieza[11], "PeonN.PNG");

	for (int k = 0; k < 32; k++)
	{
		switch (P(k).m_tipo)
		{
		case Tipo::Peon:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[11]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[10]); }
			break;
		case::Tipo::Caballo:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[9]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[8]); }
			break;
		case::Tipo::Alfil:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[7]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[6]); }
			break;
		case::Tipo::Torre:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[5]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[4]); }
			break;
		case::Tipo::Dama:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[3]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[2]); }
			break;
		case::Tipo::Rey:
			if (P(k).m_color == Color::N) { P(k).setSprite(pieza[1]); }
			else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[0]); }
			break;
		default:
			break;
		}
	}

	for (int k = 0; k < 32; k++)
	{
		ajedrez.draw(P(k).m_sprite);
	}

	ajedrez.display();
}
