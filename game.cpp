#include <SFML/Graphics.hpp>
#include <iostream>
#include "casilla.h"
#include "game.h"
#include "partida.h"
#include "movimientos.h"
#include "jaquemate.h"
#include "debugging.h"
#include "jugadas.h"

Game::Game() : ajedrez(sf::VideoMode(distancia * 15, distancia * 13), "Ajedrez")
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
	setFuente(m_fuente, "CascadiaCode.ttf");
	ajedrez.setPosition(sf::Vector2i(700, 80));
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
		case sf::Event::KeyPressed:
			if (m_tablas)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
				{
					m_mensaje = "TABLAS POR MUTUO ACUERDO - Ambos equipos aceptan \nel empate.";
					m_gameover = true;
					m_tablas = false;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
				{
					m_mensaje = "TABLAS RECHAZADAS - La partida continua...";
					m_tablas = false;
				}
			}
			break;
		default:
			break;
		case sf::Event::MouseButtonPressed:
			if (m_gameover)
			{
				ajedrez.close();
			}
			if (event.mouseButton.button == sf::Mouse::Left && !m_tablas)
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
								m_piece = Tablero(i, j).m_pieza;
								m_mensaje = "Entrada en " + P(m_piece).getTipo() + " " + P(m_piece).getColor();

								PiezaEnCasilla(P(Tablero(i, j).m_pieza));
								CoordenadasMouse(ajedrez);
								CoordenadasPieza(Tablero(i, j).m_pieza);
								CoordenadasCasilla(i, j);

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
								m_piece = Tablero(i, j).m_pieza;
								m_mensaje = "Pieza Equivocada - Turno del Equipo " + getTurno() + "...";
								std::cout << "\n\tPieza Equivocada - Turno del Equipo " << getTurno() << "...\n";
							}
						}
						else if (MouseEnCasilla(mouse, i, j) && !Tablero(i, j).m_ocp)
						{
							m_mensaje = "Entrada en Casilla Vacia";
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
						m_mensaje = "Sin entrada - Fuera del Tablero";
						std::cout << "\n\tSin entrada - Fuera del Tablero\n";
						break;
					}
				}
				if (Abandonar(mouse, m_abandonarR))
				{
					m_mensaje = "ABANDONO - El equipo " + getTurno() + " se ha retirado, ";
					std::cout << "\n\n\t\tABANDONO - El equipo " << getTurno() << " se ha retirado, ";

					CambioDeTurno();

					m_mensaje += "\ngana el equipo " + getTurno() + "!";
					std::cout << "gana el equipo " << getTurno() << "!\n\n";
					m_gameover = true;
				}
				if (Tablas(mouse, m_tablasR))
				{
					m_mensaje = "El equipo " + getTurno() + " ofrece tablas.\n";
					m_mensaje += "\n\n\tAceptar: [ Y ]\t\tRechazar: [ N ]";
					m_tablas = true;
				}
				if (m_coronacion)
				{
					if (Conversion(mouse, P(m_piece), m_newpos))
					{
						sf::Texture textura;
						setTextura(textura, P(m_piece).getTipo() +
							P(Tablero(m_newpos.x, m_newpos.y).m_pieza).getColor()[0] + ".PNG");

						for (int c = 0; c < 16; c++)
						{
							if (m_nropeon[c] == Tablero(m_newpos.x, m_newpos.y).m_pieza)
							{
								m_peonconvertido[c] = textura;
								m_peoncoronado[c] = true;
								break;
							}
						}
						P(Tablero(m_newpos.x, m_newpos.y).m_pieza).ConvertirPieza(P(m_piece).m_tipo);
						m_mensaje = "CONVERSION EXITOSA - El Peon se convirtio \n";
						m_mensaje += "en " + P(m_piece).getTipo() + "!";
						m_coronacion = false;
						m_jugada = false;
						m_move = false;
					}
					else if (!Conversion(mouse, P(m_piece), m_newpos))
					{
						m_mensaje = "CONVERSION INVALIDA - Vuelva a intentar...";
						m_move = false;
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
						if (CubrirRey(m_piezajaque, m_piece, m_newpos, m_oldpos))
						{
							m_jaque = false;
						}
						else if (!CubrirRey(m_piezajaque, m_piece, m_newpos, m_oldpos))
						{
							m_mensaje = "Rey en Jaque - Vuelva a intentar...";
							P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							m_move = false;		 break;
						}
					}
				}

				switch (P(m_piece).m_tipo)
				{
				case::Tipo::Rey:
					m_move = MovimientosRey(P(m_piece), m_newpos, m_oldpos);
					if (Enroque(m_piece, m_newpos, m_oldpos))
					{
						m_mensaje = "ENROQUE";
						m_jugada = true;
						m_move = true;
					}
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
					if (CapturaAlPaso(m_piece, m_newpos, m_oldpos))
					{
						m_mensaje = "CAPTURA AL PASO";
						m_jugada = true;
						m_move = true;
					}
					if (m_move) {
						m_move = !PiezaClavada(P(m_piece), m_newpos,
							m_oldpos, P(m_piece).getReyNum(P(m_piece).m_color));
					}
					if (Coronacion(m_piece, m_newpos, m_oldpos) && m_move)
					{
						m_mensaje = "CORONACION - El Peon atraveso el tablero, \n";
						m_mensaje += "elija la pieza en la que quiera convertirlo...";

						m_coronacion = true;
						m_jugada = true;
						m_move = true;
					}
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				default:
					break;
				}

				if (m_move)
				{
					if (!MouseEnCasilla(mouse, m_oldpos.x, m_oldpos.y))
					{
						if (MouseEnTablero(ajedrez))
						{
							if (!m_jugada)
							{
								m_mensaje = "NUEVA UBICACION";
								std::cout << "\n\tNUEVA UBICACION\n";
							}

							if (m_piece > -1) { P(m_piece).m_move = true; }
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
									if (!m_jugada)
									{
										m_mensaje = "PIEZA CAPTURADA";
										std::cout << "\n\tPIEZA CAPTURADA\n";
									}
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
							m_mensaje = "Movimiento Incorrecto - Vuelva a intentar...";
							std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
							m_move = false;		break;
						}
					}
					CambioDeTurno();
					m_ronda++;
				}
				else if (!m_move && !m_coronacion)
				{
					P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					m_mensaje = "Movimiento Incorrecto - Vuelva a intentar...";
					std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
				}

				if (m_jaque)
				{
					std::cout << "\n\tJAQUE\n";	m_mensaje = "JAQUE - Mueva, cubra o salve al Rey...";
				}

				if (Ahogado(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)) &&
					CasillaEnJuego(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)) &&
					!SalvarRey(ReyRival(m_piece), m_piezajaque))
				{
					m_mensaje = "JAQUE MATE - Gana el equipo " + P(m_piece).getColor() + "!";
					std::cout << "\n\n\t\tJAQUE MATE - Gana el equipo " << P(m_piece).getColor() << "!\n\n";
					m_gameover = true;
				}
				else if (!MovimientosDisponibles(P(ReyRival(m_piece))) &&
					Ahogado(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)) &&
					!CasillaEnJuego(P(ReyRival(m_piece)).m_pos, ReyRival(m_piece)))
				{
					m_mensaje = "TABLAS POR AHOGADO - No hay movimientos \ndisponibles.";
					std::cout << "\n\n\t\tTABLAS POR AHOGADO - No hay movimientos disponibles.\n\n";
					m_gameover = true;
				}
				else if (m_piezasblancas == 1 && m_piezasnegras == 1)
				{
					m_mensaje = "TABLAS POR MATERIAL INSUFICIENTE - Un Rey no \npuede dar JaqueMate a otro Rey.";
					std::cout << "\n\n\t\tTABLAS POR MATERIAL INSUFICIENTE - Un Rey no puede dar JaqueMate a otro.\n\n";
					m_gameover = true;
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
	ajedrez.setSize(sf::Vector2u(distancia * 15, distancia * 13));
	ajedrez.clear(sf::Color(70, 70, 70));

	sf::RectangleShape R_mensaje(sf::Vector2f(distancia * 14.6 + 10, distancia * 2.5 + 10));
	R_mensaje.setPosition(10, distancia * 10 + 10);
	R_mensaje.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_mensaje(sf::Vector2f(distancia * 14.6, distancia * 2.5));
	SubR_mensaje.setPosition(15, distancia * 10 + 15);
	SubR_mensaje.setFillColor(sf::Color::Black);

	sf::Text T_mensaje(m_mensaje, m_fuente, 32);
	T_mensaje.setPosition(42, distancia * 10 + 20);

	ajedrez.draw(R_mensaje);
	ajedrez.draw(SubR_mensaje);
	ajedrez.draw(T_mensaje);

	sf::RectangleShape R_ronda(sf::Vector2f(distancia * 4 + 10, distancia + 10));
	R_ronda.setPosition(distancia * 10.5, 10);
	R_ronda.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_ronda(sf::Vector2f(distancia * 4, distancia));
	SubR_ronda.setPosition(distancia * 10.5 + 5, 15);
	SubR_ronda.setFillColor(sf::Color::Black);

	sf::Text T_ronda("Ronda " + std::to_string(m_ronda), m_fuente, 32);
	T_ronda.setPosition(distancia * 10.5 + 35, distancia / 3);

	ajedrez.draw(R_ronda);
	ajedrez.draw(SubR_ronda);
	ajedrez.draw(T_ronda);

	sf::RectangleShape R_tablas(sf::Vector2f(distancia * 4.6 + 10, distancia + 10));
	R_tablas.setPosition(distancia * 10 + 10, distancia * 1.5 + 5);
	R_tablas.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_tablas(sf::Vector2f(distancia * 4.6, distancia));
	SubR_tablas.setPosition(distancia * 10 + 15, distancia * 1.5 + 10);
	SubR_tablas.setFillColor(sf::Color::Black);

	sf::Text T_tablas("Ofrecer Tablas", m_fuente, 32);
	T_tablas.setPosition(distancia * 10.5, distancia * 1.5 + distancia / 4);

	m_tablasR = SubR_tablas;

	ajedrez.draw(R_tablas);
	ajedrez.draw(SubR_tablas);
	ajedrez.draw(T_tablas);

	sf::RectangleShape R_abandonar(sf::Vector2f(distancia * 4.6 + 10, distancia + 10));
	R_abandonar.setPosition(distancia * 10 + 10, distancia * 2.75 + 5);
	R_abandonar.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_abandonar(sf::Vector2f(distancia * 4.6, distancia));
	SubR_abandonar.setPosition(distancia * 10 + 15, distancia * 2.75 + 10);
	SubR_abandonar.setFillColor(sf::Color::Black);

	sf::Text T_abandonar("Abandonar Juego", m_fuente, 32);
	T_abandonar.setPosition(distancia * 10.4, distancia * 2.75 + distancia / 4);

	m_abandonarR = SubR_abandonar;

	ajedrez.draw(R_abandonar);
	ajedrez.draw(SubR_abandonar);
	ajedrez.draw(T_abandonar);

	sf::RectangleShape R_Movimientos(sf::Vector2f(distancia * 4.6 + 10, distancia * 5.5 + 10));
	R_Movimientos.setPosition(distancia * 10 + 10, distancia * 4.25 + 5);
	R_Movimientos.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_Movimientos(sf::Vector2f(distancia * 4.6, distancia * 5.5));
	SubR_Movimientos.setPosition(distancia * 10 + 15, distancia * 4.25 + 10);
	SubR_Movimientos.setFillColor(sf::Color::Black);

	sf::Text T_Movimientos("Jugadas Previas", m_fuente, 32);
	T_Movimientos.setPosition(distancia * 10.4, distancia * 4.25 + distancia / 4);

	ajedrez.draw(R_Movimientos);
	ajedrez.draw(SubR_Movimientos);
	ajedrez.draw(T_Movimientos);

	sf::RectangleShape Borde1, Borde2, Borde3;

	Borde1.setPosition(distancia - 3 * escala, distancia - 3 * escala);
	Borde1.setSize(sf::Vector2f(distancia * 8 + (3 * 2) * escala, distancia * 8 + (3 * 2) * escala));
	Borde1.setFillColor(sf::Color(65, 40, 30));

	Borde2.setPosition(distancia - 17 * escala, distancia - 17 * escala);
	Borde2.setSize(sf::Vector2f(distancia * 8 + (17 * 2) * escala, distancia * 8 + (17 * 2) * escala));
	Borde2.setFillColor(sf::Color(200, 180, 140));

	Borde3.setSize(sf::Vector2f(distancia * 8 + (32 * 2) * escala, distancia * 8 + (32 * 2) * escala));
	Borde3.setFillColor(sf::Color(65, 40, 30));

	ajedrez.draw(Borde3);
	ajedrez.draw(Borde2);
	ajedrez.draw(Borde1);

	sf::Text Fila[2], Columna[2];

	Fila[0].setFont(m_fuente);
	Fila[0].setCharacterSize(24);
	Fila[0].setFillColor(sf::Color(65, 40, 30));
	Fila[0].setString("A\tB\tC\tD\tE\tF\tG\tH");
	Fila[0].setPosition(distancia * 1.3, distancia - 17 * escala);

	Fila[1].setFont(m_fuente);
	Fila[1].setCharacterSize(24);
	Fila[1].setFillColor(sf::Color(65, 40, 30));
	Fila[1].setString("A\tB\tC\tD\tE\tF\tG\tH");
	Fila[1].setPosition(distancia * 1.3, distancia * 9 + 6);

	ajedrez.draw(Fila[0]);
	ajedrez.draw(Fila[1]);

	Columna[0].setFont(m_fuente);
	Columna[0].setCharacterSize(28);
	Columna[0].setFillColor(sf::Color(65, 40, 30));
	Columna[0].setString("8\n\n7\n\n6\n\n5\n\n4\n\n3\n\n2\n\n1");
	Columna[0].setPosition(distancia - 14 * escala, distancia + 6 * escala);

	Columna[1].setFont(m_fuente);
	Columna[1].setCharacterSize(28);
	Columna[1].setFillColor(sf::Color(65, 40, 30));
	Columna[1].setString("8\n\n7\n\n6\n\n5\n\n4\n\n3\n\n2\n\n1");
	Columna[1].setPosition(distancia * 9 + 12, distancia + 6 * escala);

	ajedrez.draw(Columna[0]);
	ajedrez.draw(Columna[1]);

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
				Tablero(i, j).m_casilla.setPosition(sf::Vector2f(distancia * i + distancia,
					distancia * j + distancia));
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				Tablero(i, j).setSprite(Tablero(i, j), casilla[1]);
				Tablero(i, j).m_casilla.setPosition(sf::Vector2f(distancia * i + distancia,
					distancia * j + distancia));
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
			if (!PeonCoronado(k))
			{
				if (P(k).m_color == Color::N) { P(k).setSprite(pieza[11]); }
				else if (P(k).m_color == Color::B) { P(k).setSprite(pieza[10]); }
			}
			else if (PeonCoronado(k))
			{
				int peonC = 0;
				for (int c = 0; c < 16; c++) {
					if (m_nropeon[c] == k) { peonC = c; }
				}
				if (P(k).m_color == Color::N) { P(k).setSprite(m_peonconvertido[peonC]); }
				else if (P(k).m_color == Color::B) { P(k).setSprite(m_peonconvertido[peonC]); }
			}
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
