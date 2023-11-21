#pragma once
#include "casilla.h"

enum class Tipo : int { Rey = 1, Dama, Torre, Alfil, Caballo, Peon };
enum class Color : int { B = 1, N };

class Pieza
{
public:
	sf::Sprite m_sprite;
	int m_nro{ -1 };
	Tipo m_tipo{};
	Color m_color{};
	sf::Vector2i m_pos{ -1, -1 };
	bool m_move = false;

	void setSprite(sf::Texture& t)
	{
		m_sprite.setTexture(t);
		m_sprite.setScale(3, 3);
	}

	std::string getTipo()
	{
		switch (m_tipo)
		{
		case::Tipo::Rey:
			return "Rey";
		case::Tipo::Dama:
			return "Dama";
		case::Tipo::Torre:
			return "Torre";
		case::Tipo::Alfil:
			return "Alfil";
		case::Tipo::Caballo:
			return "Caballo";
		case::Tipo::Peon:
			return "Peon";
		default:
			break;
		}
	}

	std::string getColor()
	{
		switch (m_color)
		{
		case Color::B:
			return "Blanco";
		case Color::N:
			return "Negro";
		default:
			break;
		}
	}

	Pieza();
};

Pieza::Pieza() {}

Pieza p[32];

void CargarTextura(sf::Texture& t, std::string path)
{
	t.loadFromFile(path);
}

void PiezaEnCasilla(Pieza p)
{
	std::cout << "\tEntrada en " << p.getTipo() << " " << p.getColor() << "\n";
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

bool PiezaRival(int k, int l)
{
	if (p[k].m_color == p[l].m_color)
	{
		return false;
	}
	else if (p[k].m_color != p[l].m_color)
	{
		return true;
	}
}