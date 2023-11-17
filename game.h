#pragma once

class Game {
public:
	Game();
	void run();

	Color m_turno{ Color::B };
	bool m_jaque = false;
	bool m_move = false;
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

private:
	void render();
	void processEvents();

	sf::RenderWindow ajedrez;
};

Game::Game() : ajedrez(sf::VideoMode(825, 825), "Ajedrez")
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
	ajedrez.setPosition(sf::Vector2i(800, 100));
}

void Game::run() {
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
							else { m_move = false; }
						}
						else if (MouseEnCasilla(ajedrez, i, j) && !tablero[i][j].m_ocp)
						{
							std::cout << "\tSin entrada\n";
							m_oldpos.x = i;		m_oldpos.y = j;
							m_oldcoord.x = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().x;
							m_oldcoord.y = tablero[m_oldpos.x][m_oldpos.y].m_casilla.getGlobalBounds().getPosition().y;
							CoordenadasMouse(ajedrez);
							CoordenadasCasilla(ajedrez, i, j);
							m_move = false;
							break;
						}

					}
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (m_move)
			{
				m_newpos = EncontrarCasilla(mouse.x, mouse.y);

				switch (p[m_piece].m_tipo)
				{
				case::Tipo::Rey:
					m_move = true;
					break;
				case::Tipo::Dama:
					m_move = true;
					break;
				case::Tipo::Torre:
					m_move = MovimientosTorre(m_piece, m_newpos, m_oldpos);
					//m_move = true;
					break;
				case::Tipo::Alfil:
					m_move = MovimientosAlfil(m_piece, m_newpos, m_oldpos);
					//m_move = true;
					break;
				case::Tipo::Caballo:
					m_move = true;
					break;
				case::Tipo::Peon:
					m_move = MovimientosPeon(m_piece, m_newpos, m_oldpos);
					//m_move = true;
					break;
				default:
					break;
				}
			}

			if (m_move)
			{
				if (!MouseEnCasilla(ajedrez, m_oldpos.x, m_oldpos.y))
				{
					if (MouseEnTablero(ajedrez))
					{
						if (PiezaRival(tablero[m_newpos.x][m_newpos.y].m_pieza, tablero[m_oldpos.x][m_oldpos.y].m_pieza))
						{
							std::cout << "Movimiento\n\n";

							std::cout << "\tNUEVA UBICACION\n";
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
								std::cout << "\tPIEZA CAPTURADA\n";
								p[tablero[m_newpos.x][m_newpos.y].m_pieza].m_sprite.setPosition(1000, 1000);
								if (p[tablero[m_newpos.x][m_newpos.y].m_pieza].m_tipo == Tipo::Rey)
								{
									ajedrez.close();
								}
								VaciarCasilla(m_newpos.x, m_newpos.y);
								CargarPiezaEnCasilla(m_newpos.x, m_newpos.y, m_piece, p[m_piece].m_tipo, p[m_piece].m_color);
								VaciarCasilla(m_oldpos.x, m_oldpos.y);
							}
						}
						else if (!PiezaRival(tablero[m_newpos.x][m_newpos.y].m_pieza, tablero[m_oldpos.x][m_oldpos.y].m_pieza))
						{
							p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
							CambioDeTurno();
						}
					}
					else if (!MouseEnTablero(ajedrez))
					{
						p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
						CambioDeTurno();
					}
				}
				else if (MouseEnCasilla(ajedrez, m_oldpos.x, m_oldpos.y))
				{
					p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
					CambioDeTurno();
				}
				CambioDeTurno();
			}
			else if (!m_move)
			{
				p[m_piece].m_sprite.setPosition(m_oldcoord.x, m_oldcoord.y);
				std::cout << "\n\tMovimiento Incorrecto - Vuelva a intentar...\n";
			}
			m_piece = -1;
			break;
		}
		if (m_move) { p[m_piece].m_sprite.setPosition(mouse.x - m_movecoord.x, mouse.y - m_movecoord.y); }
	}
}

void Game::render()
{
	ajedrez.clear(sf::Color(70, 70, 70));

	sf::Texture casilla[2];

	CargarTextura(casilla[0], "CasillaB.PNG");
	CargarTextura(casilla[1], "CasillaN.PNG");

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casilla[0]);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i, distancia * j));
			}
			else if ((j % 2 == 1 && i % 2 == 0) || (j % 2 == 0 && i % 2 == 1))
			{
				tablero[i][j].setSprite(casilla[1]);
				tablero[i][j].m_casilla.setPosition(sf::Vector2f(distancia * i, distancia * j));
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

