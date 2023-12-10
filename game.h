#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "pieza.h"

class Game {
public:
	Game();
	void Run();

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

	void setTextura(sf::Texture& t, std::string path) {
		t.loadFromFile(path);
		if (!t.loadFromFile(path))
		{
			std::cout << "\n\tCarga Fallida... - " << path << "\n";
		}
	}

	void setFuente(sf::Font& f, std::string path) {
		f.loadFromFile(path);
		if (!f.loadFromFile(path))
		{
			std::cout << "\n\tCarga Fallida... - " << path << "\n";
		}
	}

	bool PeonCoronado(int k) const
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

	int m_ronda = 1;
	Color m_turno{ Color::B };
	int m_piezasblancas = 0;
	int m_piezasnegras = 0;
	bool m_jaque = false;
	int m_piezajaque{ -1 };
	bool m_move = false;
	bool m_jugada = false;
	int m_piece{ -1 };

	sf::Font m_fuente;
	sf::String m_mensaje;
	sf::String m_movimiento;

	sf::RectangleShape m_abandonarR;
	sf::RectangleShape m_tablasR;

	bool m_tablas = false;
	bool m_coronacion = false;
	bool m_gameover = false;

	int m_nropeon[16]{ -1 };
	bool m_peoncoronado[16]{ false };
	sf::Texture m_peonconvertido[16];

	sf::Vector2i m_oldpos{ -1, -1 };
	sf::Vector2i m_newpos{ -1, -1 };

	sf::Vector2i m_oldcoord{ -1, -1 };
	sf::Vector2i m_newcoord{ -1, -1 };

	sf::Vector2f m_movecoord{ -1, -1 };

private:
	void ProcessEvents();
	void Render();

	sf::RenderWindow ajedrez;
};