#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "game.h"
#include "debugging.h";

void Game::Run()
{
	while (ajedrez.isOpen())
	{
		if (!m_jugar)
		{
			Menu();
		}
		else if (m_jugar)
		{
			if (!m_piezascolocadas)
			{
				PrepararJuego();
			}
			ProcessEvents();
			Render();
		}
	}
}

void Game::Menu()
{
	sf::Texture T_fondo;
	T_fondo.loadFromFile("FondoMenu.PNG");

	sf::Sprite S_fondo(T_fondo);
	S_fondo.setScale(0.944, 0.82);

	sf::RectangleShape R_jugar(sf::Vector2f(distancia * 4 + 10, distancia * 1.25 + 10));
	R_jugar.setPosition((distancia * 16.5) / 3, (distancia * 14) / 2);
	R_jugar.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_jugar(sf::Vector2f(distancia * 4, distancia * 1.25));
	SubR_jugar.setPosition((distancia * 16.5) / 3 + 5, (distancia * 14) / 2 + 5);
	SubR_jugar.setFillColor(sf::Color::Black);

	sf::Text T_jugar("Jugar", m_fuente, 64);
	T_jugar.setPosition((distancia * 18.25) / 3, (distancia * 14) / 2);

	sf::RectangleShape R_salir(sf::Vector2f(distancia * 4 + 10, distancia * 1.25 + 10));
	R_salir.setPosition((distancia * 16.5) / 3, (distancia * 17.25) / 2);
	R_salir.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_salir(sf::Vector2f(distancia * 4, distancia * 1.25));
	SubR_salir.setPosition((distancia * 16.5) / 3 + 5, (distancia * 17.25) / 2 + 5);
	SubR_salir.setFillColor(sf::Color::Black);

	sf::Text T_salir("Salir", m_fuente, 64);
	T_salir.setPosition((distancia * 18.25) / 3, (distancia * 17.25) / 2);

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
				if (SubR_jugar.getGlobalBounds().contains(mouse.x, mouse.y)) {
					m_jugar = true;
				}
				if (SubR_salir.getGlobalBounds().contains(mouse.x, mouse.y)) {
					ajedrez.close();
				}
				break;
		}
	}

	ajedrez.setSize(sf::Vector2u(distancia * 15, distancia * 13));
	ajedrez.clear();

	ajedrez.draw(S_fondo);

	ajedrez.draw(R_jugar);
	ajedrez.draw(SubR_jugar);
	ajedrez.draw(T_jugar);

	ajedrez.draw(R_salir);
	ajedrez.draw(SubR_salir);
	ajedrez.draw(T_salir);

	ajedrez.display();
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
						m_notacion = true;
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
					{
						m_mensaje = "TABLAS RECHAZADAS - La partida continua...";
						m_tablas = false;
						CambioDeTurno();
					}
				}
				if (m_gameover)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						ajedrez.close();
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						ReiniciarJuego();
					}
				}
				break;
			default:
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left && !m_tablas && !m_gameover)
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
									m_move = false;
								}
							}
							else if (MouseEnCasilla(mouse, i, j) && !Tablero(i, j).m_ocp)
							{
								m_mensaje = "Entrada en Casilla Vacia - [ ";
								m_mensaje += char(i + 97);
								m_mensaje += " ][ " + std::to_string(j + 1) + " ]";
								m_oldpos.x = i;		m_oldpos.y = j;
								m_oldcoord.x = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().x;
								m_oldcoord.y = Tablero(m_oldpos.x, m_oldpos.y).m_casilla.getGlobalBounds().getPosition().y;
								break;
							}
						}
						if (!MouseEnTablero(ajedrez))
						{
							m_mensaje = "Sin entrada - Fuera del Tablero";
							break;
						}
					}
					if (Abandonar(mouse, m_abandonarR))
					{
						m_mensaje = "ABANDONO - El equipo " + getTurno() + " se ha retirado, ";

						CambioDeTurno();

						m_mensaje += "gana \nel equipo " + getTurno() + "!";
						m_gameover = true;
					}
					if (Tablas(mouse, m_tablasR))
					{
						m_mensaje = "El equipo " + getTurno() + " ofrece tablas.\n";

						CambioDeTurno();

						m_mensaje += "\n\n\tAceptar: [ Y ]\t\tRechazar: [ N ]";
						m_tablas = true;
					}
					if (m_coronacion)
					{
						if (Conversion(mouse, m_newpos))
						{
							int k = 0;

							if (m_piece < 0) { k = P(getNroPieza(mouse)).m_nro; }
							else if (m_piece >= 0) { k = P(m_piece).m_nro; }

							sf::Texture textura;
							setTextura(textura, P(k).getTipo() +
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

							P(Tablero(m_newpos.x, m_newpos.y).m_pieza).ConvertirPieza(P(k).m_tipo);
							m_mensaje = "CONVERSION EXITOSA - El Peon se convirtio \n";
							m_mensaje += "en " + P(k).getTipo() + "!";

							if (CasillaEnJuego(P(P(k).getReyNum(P(k).m_color)).m_pos, P(k).getReyNum(P(k).m_color)))
							{
								m_mensaje += " JAQUE realizado en consecuencia.";
								m_jaque = true;
							}

							m_Njugada = P(k).getTipo()[0];
							m_coronacion = false;
							m_move = false;
						}
						else if (!Conversion(mouse, m_newpos))
						{
							m_mensaje = "CONVERSION INVALIDA - Vuelva a intentar...";
							m_move = false;
						}
					}
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left && !m_coronacion && !m_gameover)
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
							if (CubrirRey(m_piezajaque, m_piece, m_newpos, m_oldpos) &&
								MovimientoPosible(m_piece, m_newpos))
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
							if (m_move) 
							{
								m_move = !PiezaClavada(P(m_piece), m_newpos, m_oldpos, 
									P(m_piece).getReyNum(P(m_piece).m_color));
							}
							if (CapturaAlPaso(m_piece, m_newpos, m_oldpos, m_lastoldpos))
							{
								m_mensaje = "CAPTURA AL PASO";
								m_Njugada = "a.p.";
								m_jugada = true;
								m_move = true;
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
								}

								if (m_piece > -1) { P(m_piece).m_move = true; }
								
								m_newcoord.x = Tablero(m_newpos.x, m_newpos.y).m_casilla.getGlobalBounds().getPosition().x;
								m_newcoord.y = Tablero(m_newpos.x, m_newpos.y).m_casilla.getGlobalBounds().getPosition().y;

								if (!Tablero(m_newpos.x, m_newpos.y).m_ocp)
								{
									P(m_piece).ColocarPieza(m_newpos.x, m_newpos.y, m_piece, P(m_piece).m_tipo, P(m_piece).m_color);
									Tablero(m_oldpos.x, m_oldpos.y).VaciarCasilla();
									m_lastoldpos = m_oldpos;
								}
								else if (Tablero(m_newpos.x, m_newpos.y).m_ocp)
								{
									if (PiezaRival(P(Tablero(m_newpos.x, m_newpos.y).m_pieza), P(Tablero(m_oldpos.x, m_oldpos.y).m_pieza)))
									{									
										CapturarPieza(P(m_piece), P(Tablero(m_newpos.x, m_newpos.y).m_pieza),
												m_newpos);
										m_lastoldpos = m_oldpos;
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
								m_move = false;		break;
							}
						}
						if (m_turno == Color::B)
						{
							m_turnoB++;
							CambioDeTurno();
						}
						else if (m_turno == Color::N)
						{
							m_turnoN++;
							CambioDeTurno();
						}
						if (m_turnoB == m_turnoN)
						{
							m_ronda++;
						}
						m_jugada = false;
						m_notacion = true;
					}
					else if (!m_move && !m_coronacion)
					{
						P(m_piece).m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
						m_mensaje = "Movimiento Incorrecto - Vuelva a intentar...";
					}
					
					if (m_jaque || CasillaEnJuego(P(getReyRival(m_piece)).m_pos, getReyRival(m_piece)))
					{
						m_mensaje = "JAQUE - Mueva, cubra o salve al Rey...";
						m_jaque = true;
					}

					if (Ahogado(P(getReyRival(m_piece)).m_pos, getReyRival(m_piece)) &&
						CasillaEnJuego(P(getReyRival(m_piece)).m_pos, getReyRival(m_piece)) &&
						!SalvarRey(getReyRival(m_piece), m_piezajaque))
					{
						m_mensaje = "JAQUE MATE - Gana el equipo " + P(m_piece).getColor() + "!\n";
						m_gameover = true;
					}
					else if (!MovimientosDisponibles(P(getReyRival(m_piece))) &&
						Ahogado(P(getReyRival(m_piece)).m_pos, getReyRival(m_piece)) &&
						!CasillaEnJuego(P(getReyRival(m_piece)).m_pos, getReyRival(m_piece)))
					{
						m_mensaje = "TABLAS POR AHOGADO - No hay movimientos \ndisponibles.";
						m_gameover = true;
					}
					else if (m_piezasblancas == 1 && m_piezasnegras == 1)
					{
						m_mensaje = "TABLAS POR MATERIAL INSUFICIENTE - Un Rey no puede \ndar JaqueMate a otro Rey.";
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

	if (m_gameover && m_mensaje.getSize() < 150) {
		m_mensaje += "\n\n Volver al Menu: [ Enter ]  Cerrar Juego: [ Esc ]";
	}

	sf::Text T_mensaje(m_mensaje, m_fuente, 32);
	T_mensaje.setPosition(42, distancia * 10 + 20);

	ajedrez.draw(R_mensaje);
	ajedrez.draw(SubR_mensaje);
	ajedrez.draw(T_mensaje);

	sf::RectangleShape R_ronda(sf::Vector2f(distancia * 4.6 + 10, distancia + 10));
	R_ronda.setPosition(distancia * 10 + 10, 10);
	R_ronda.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_numero(sf::Vector2f(distancia * 2.65, distancia));
	SubR_numero.setPosition(distancia * 10 + 15, 15);
	SubR_numero.setFillColor(sf::Color::Black);

	sf::Text T_numero("Ronda " + std::to_string(m_ronda), m_fuente, 32);
	T_numero.setPosition(distancia * 10 + 20, distancia / 3);

	sf::RectangleShape SubR_turno(sf::Vector2f(distancia * 1.95 - 5, distancia));
	SubR_turno.setPosition(distancia * 12.65 + 20, 15);
	SubR_turno.setFillColor(sf::Color::Black);

	sf::Text T_turno(getTurno(), m_fuente, 32);
	T_turno.setPosition(distancia * 13 + 5, distancia / 3);

	ajedrez.draw(R_ronda);
	ajedrez.draw(SubR_numero);
	ajedrez.draw(T_numero);
	ajedrez.draw(SubR_turno);
	ajedrez.draw(T_turno);

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

	sf::RectangleShape R_notaciones(sf::Vector2f(distancia * 4.6 + 10, distancia * 5.5 + 10));
	R_notaciones.setPosition(distancia * 10 + 10, distancia * 4.25 + 5);
	R_notaciones.setFillColor(sf::Color::White);

	sf::RectangleShape SubR_jugada(sf::Vector2f(distancia * 4.6, distancia * 1));
	SubR_jugada.setPosition(distancia * 10 + 15, distancia * 4.25 + 10);
	SubR_jugada.setFillColor(sf::Color::Black);

	sf::Text T_jugada("Jugadas Previas", m_fuente, 32);
	T_jugada.setPosition(distancia * 10.4, distancia * 4.25 + distancia / 4);

	sf::RectangleShape SubR_movimientos(sf::Vector2f(distancia * 4.6, distancia * 4.5 - 5));
	SubR_movimientos.setPosition(distancia * 10 + 15, distancia * 5.25 + 15);
	SubR_movimientos.setFillColor(sf::Color::Black);

	Notaciones();

	sf::Text T_movimientos(m_movimientos, m_fuente, 22);
	T_movimientos.setPosition(distancia * 10.4, distancia * 5.3 + distancia / 4);

	ajedrez.draw(R_notaciones);
	ajedrez.draw(SubR_jugada);
	ajedrez.draw(T_jugada);
	ajedrez.draw(SubR_movimientos);
	ajedrez.draw(T_movimientos);

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
	Columna[0].setString("1\n\n2\n\n3\n\n4\n\n5\n\n6\n\n7\n\n8");
	Columna[0].setPosition(distancia - 14 * escala, distancia + 6 * escala);

	Columna[1].setFont(m_fuente);
	Columna[1].setCharacterSize(28);
	Columna[1].setFillColor(sf::Color(65, 40, 30));
	Columna[1].setString("1\n\n2\n\n3\n\n4\n\n5\n\n6\n\n7\n\n8");
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
				Tablero(i, j).setSprite(casilla[0]);
				Tablero(i, j).m_casilla.setPosition(sf::Vector2f(distancia * i + distancia,
					distancia * j + distancia));
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				Tablero(i, j).setSprite(casilla[1]);
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