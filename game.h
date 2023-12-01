#pragma once

class Game {
public:
	Game();
	void run();

	Color m_turno{ Color::B };
	int m_ronda = 0;
	bool m_move = false;
	bool m_jaque = false;
	int m_piezajaque{ -1 };
	int m_piece{ -1 };

	sf::Vector2i m_oldpos{ -1, -1 };
	sf::Vector2i m_newpos{ -1, -1 };

	sf::Vector2i m_oldcoord{ -1, -1 };
	sf::Vector2i m_newcoord{ -1, -1 };

	sf::Vector2f m_movecoord{ -1, -1 };

	void CambioDeTurno()
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

	std::string getTurno()
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

private:
	void render();
	void processEvents();

	sf::RenderWindow ajedrez;
};

Game::Game() : ajedrez(sf::VideoMode(960, 825), "Ajedrez")
{
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (j == 7 && i == 4)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Rey, Color::B);	k++;
			}
			if (j == 0 && i == 4)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Rey, Color::N);	k++;
			}
			if (j == 7 && i == 3)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Dama, Color::B);	k++;
			}
			if (j == 0 && i == 3)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Dama, Color::N);	k++;
			}
			if ((i == 0 && j == 7) || (i == 7 && j == 7))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Torre, Color::B);	k++;
			}
			if ((i == 0 && j == 0) || (i == 7 && j == 0))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Torre, Color::N);	k++;
			}
			if ((i == 2 && j == 7) || (i == 5 && j == 7))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Alfil, Color::B);	k++;
			}
			if ((i == 2 && j == 0) || (i == 5 && j == 0))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Alfil, Color::N);	k++;
			}
			if ((i == 1 && j == 7) || (i == 6 && j == 7))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Caballo, Color::B);	k++;
			}
			if ((i == 1 && j == 0) || (i == 6 && j == 0))
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Caballo, Color::N);	k++;
			}
			if (j == 6)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Peon, Color::B);	k++;
			}
			if (j == 1)
			{
				CargarPiezaEnCasilla(i, j, k, Tipo::Peon, Color::N);	k++;
			}
		}
	}
}

void Game::run()
{
	while (ajedrez.isOpen())
	{
		processEvents();
		render();
	}
}

void Game::processEvents()
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
						if (MouseEnCasilla(ajedrez, i, j) && tablero[i][j].m_ocp)
						{
							if (p[tablero[i][j].m_pieza].m_color == m_turno)
							{
								PiezaEnCasilla(p[tablero[i][j].m_pieza]);
								CoordenadasMouse(ajedrez);
								CoordenadasPieza(tablero[i][j].m_pieza);
								CoordenadasCasilla(ajedrez, i, j);

								m_piece = tablero[i][j].m_pieza;
								m_oldpos.x = i;		m_oldpos.y = j;
								m_oldcoord.x = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().x;
								m_oldcoord.y = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().y;
								m_movecoord.x = mouse.x - p[m_piece].m_sprite.getPosition().x;
								m_movecoord.y = mouse.y - p[m_piece].m_sprite.getPosition().y;
								m_move = true;
								break;
							}
							else
							{
								std::cout << "\n\tPieza Equivocada - Turno del Equipo " << getTurno() << "...\n";
							}
						}
						else if (MouseEnCasilla(ajedrez, i, j) && !tablero[i][j].m_ocp)
						{
							std::cout << "\n\tSin entrada\n";
							m_oldpos.x = i;		m_oldpos.y = j;
							m_oldcoord.x = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().x;
							m_oldcoord.y = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().y;
							CoordenadasMouse(ajedrez);
							CoordenadasCasilla(ajedrez, i, j);
							break;
						}
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						if (MouseEnCasilla(ajedrez, i, j) && tablero[i][j].m_ocp)
						{
							if (p[tablero[i][j].m_pieza].m_tipo == Tipo::Rey)
							{
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
				//std::cout << "j";

				m_newpos = EncontrarCasilla(mouse.x, mouse.y);

				if (m_oldpos == m_newpos)
				{
					p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					m_move = false;		break;
				}
				if (m_jaque)
				{
					if (p[m_piece].m_tipo != Tipo::Rey)
					{
						int Rey = ReyRival(m_piezajaque);
						if (m_newpos == p[m_piezajaque].m_pos)
						{
							VaciarCasilla(m_oldpos.x, m_oldpos.y);
							VaciarCasilla(p[m_piezajaque].m_pos.x, p[m_piezajaque].m_pos.y);
							if (CasillaEnJuego(p[Rey].m_pos, Rey))
							{
								std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
								p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
								CargarPiezaEnCasilla(m_oldpos.x, m_oldpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
								CargarPiezaEnCasilla(p[m_piezajaque].m_pos.x, p[m_piezajaque].m_pos.y,
									m_piezajaque, p[m_piezajaque].m_tipo, p[m_piezajaque].m_color);
								m_move = false;		break;
							}
							else if (!CasillaEnJuego(p[Rey].m_pos, Rey))
							{
								m_jaque = false;
							}
							CargarPiezaEnCasilla(m_oldpos.x, m_oldpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
							CargarPiezaEnCasilla(p[m_piezajaque].m_pos.x, p[m_piezajaque].m_pos.y,
								m_piezajaque, p[m_piezajaque].m_tipo, p[m_piezajaque].m_color);
						}
						else if (m_newpos != p[m_piezajaque].m_pos && !tablero[m_newpos.x][m_newpos.y].m_ocp)
						{
							int angulo = SentidoDeAtaque(p[Rey], p[m_piezajaque]);
							CargarPiezaEnCasilla(m_newpos.x, m_newpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
							if (!PiezaEnMedio(angulo, p[Rey].m_pos, p[m_piezajaque].m_pos, Rey))
							{
								std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
								p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
								VaciarCasilla(m_newpos.x, m_newpos.y);
								m_move = false;		break;
							}
							else if (PiezaEnMedio(angulo, p[Rey].m_pos, p[m_piezajaque].m_pos, Rey))
							{
								m_jaque = false;
							}
							VaciarCasilla(m_newpos.x, m_newpos.y);
						}
						else
						{
							std::cout << "\n\tRey en Jaque - Vuelva a intentar...\n";
							p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							m_move = false;		break;
						}
					}
				}

				switch (p[m_piece].m_tipo)
				{
				case::Tipo::Rey:
					m_move = MovimientosRey(m_piece, m_newpos, m_oldpos);
					if (m_jaque && m_move) { m_jaque = false; }
					break;
				case::Tipo::Dama:
					m_move = MovimientosDama(m_piece, m_newpos, m_oldpos);
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Torre:
					m_move = MovimientosTorre(m_piece, m_newpos, m_oldpos);
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Alfil:
					m_move = MovimientosAlfil(m_piece, m_newpos, m_oldpos);
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Caballo:
					m_move = MovimientosCaballo(m_piece, m_newpos, m_oldpos);
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				case::Tipo::Peon:
					m_move = MovimientosPeon(m_piece, m_newpos, m_oldpos);
					if (m_move) { m_jaque = Jaque(m_newpos, m_piece); m_piezajaque = m_piece; }
					break;
				default:
					break;
				}

				if (m_jaque) { std::cout << "\n\tJAQUE\n"; }

				if (m_move)
				{
					if (!MouseEnCasilla(ajedrez, m_oldpos.x, m_oldpos.y))
					{
						if (MouseEnTablero(ajedrez))
						{
							p[m_piece].m_move = true;
							std::cout << "\n\tNUEVA UBICACION\n";
							CoordenadasPieza(m_piece);
							CoordenadasCasilla(ajedrez, m_newpos.x, m_newpos.y);

							m_newcoord.x = tablero[m_newpos.x][m_newpos.y].m_casilla.getGlobalBounds().getPosition().x;
							m_newcoord.y = tablero[m_newpos.x][m_newpos.y].m_casilla.getGlobalBounds().getPosition().y;

							if (!tablero[m_newpos.x][m_newpos.y].m_ocp)
							{
								CargarPiezaEnCasilla(m_newpos.x, m_newpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
								VaciarCasilla(m_oldpos.x, m_oldpos.y);
							}
							else if (tablero[m_newpos.x][m_newpos.y].m_ocp)
							{
								if (PiezaRival(tablero[m_newpos.x][m_newpos.y].m_pieza, tablero[m_oldpos.x][m_oldpos.y].m_pieza))
								{
									std::cout << "\n\tPIEZA CAPTURADA\n";
									p[tablero[m_newpos.x][m_newpos.y].m_pieza].m_juego = false;
									p[tablero[m_newpos.x][m_newpos.y].m_pieza].m_sprite.setPosition(1000, 1000);
									if (p[tablero[m_newpos.x][m_newpos.y].m_pieza].m_tipo == Tipo::Rey)
									{
										ajedrez.close();
									}
									VaciarCasilla(m_newpos.x, m_newpos.y);
									CargarPiezaEnCasilla(m_newpos.x, m_newpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
									VaciarCasilla(m_oldpos.x, m_oldpos.y);
								}
								else if (!PiezaRival(tablero[m_newpos.x][m_newpos.y].m_pieza, tablero[m_oldpos.x][m_oldpos.y].m_pieza))
								{
									p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
									CambioDeTurno();
								}
							}
						}
						else if (!MouseEnTablero(ajedrez))
						{
							p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
							m_move = false;		break;
						}
					}
					CambioDeTurno();
					m_ronda++;
				}
				else if (!m_move)
				{
					p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
				}
				//!MovimientosPosibles(ReyRival(m_piece))
				if (Ahogado(p[ReyRival(m_piece)].m_pos, ReyRival(m_piece)) && CasillaEnJuego(p[ReyRival(m_piece)].m_pos, ReyRival(m_piece)))
				{
					std::cout << "\n\n\t\tJAQUE MATE - Gana el equipo " << p[m_piece].getColor() << "!\n\n";
					ajedrez.close();
				}

				m_piece = -1;
			}
			break;
		}
		if (m_move) { p[m_piece].m_sprite.setPosition(mouse.x - m_movecoord.x, mouse.y - m_movecoord.y); }
	}
}

void Game::render()
{
	ajedrez.setPosition(sf::Vector2i(700, 100));
	ajedrez.setSize(sf::Vector2u(960, 825));
	ajedrez.clear(sf::Color(70, 70, 70));

	sf::Texture casilla[2];

	CargarTextura(casilla[0], "CasillaB.PNG");
	CargarTextura(casilla[1], "CasillaN.PNG");

	for (int i = 0; i < 8; i++)
	{
		int dis = distancia;
		for (int j = 0; j < 8; j++)
		{
			if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casilla[0]);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i + dis, distancia * j));
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casilla[1]);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i + dis, distancia * j));
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ajedrez.draw(tablero[i][j].m_casilla);
		}
	}

	sf::Texture pieza[12];

	CargarTextura(pieza[0], "ReyB.PNG");
	CargarTextura(pieza[1], "ReyN.PNG");

	CargarTextura(pieza[2], "DamaB.PNG");
	CargarTextura(pieza[3], "DamaN.PNG");

	CargarTextura(pieza[4], "TorreB.PNG");
	CargarTextura(pieza[5], "TorreN.PNG");

	CargarTextura(pieza[6], "AlfilB.PNG");
	CargarTextura(pieza[7], "AlfilN.PNG");

	CargarTextura(pieza[8], "CaballoB.PNG");
	CargarTextura(pieza[9], "CaballoN.PNG");

	CargarTextura(pieza[10], "PeonB.PNG");
	CargarTextura(pieza[11], "PeonN.PNG");

	for (int k = 0; k < 32; k++)
	{
		switch (p[k].m_tipo)
		{
		case Tipo::Peon:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[11]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[10]); }
			break;
		case::Tipo::Caballo:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[9]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[8]); }
			break;
		case::Tipo::Alfil:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[7]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[6]); }
			break;
		case::Tipo::Torre:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[5]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[4]); }
			break;
		case::Tipo::Dama:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[3]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[2]); }
			break;
		case::Tipo::Rey:
			if (p[k].m_color == Color::N) { p[k].setSprite(pieza[1]); }
			else if (p[k].m_color == Color::B) { p[k].setSprite(pieza[0]); }
			break;
		default:
			break;
		}
	}

	for (int k = 0; k < 32; k++)
	{
		ajedrez.draw(p[k].m_sprite);
	}

	ajedrez.display();
}