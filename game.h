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

	Color m_turno{ Color::B };
	int m_piezasblancas = 0;
	int m_piezasnegras = 0;
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

private:
	void Render();
	void ProcessEvents();

	sf::RenderWindow ajedrez;
};