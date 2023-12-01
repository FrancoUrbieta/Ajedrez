#pragma once
#define escala 3
#define distancia 32 * escala

class Casilla
{
public:
	sf::Sprite m_casilla;
	bool m_ocp = false;
	int m_pieza{ -1 };

	void setSprite(sf::Texture& t)
	{
		m_casilla.setTexture(t);
		m_casilla.setScale(escala, escala);
	}

	Casilla();
};

Casilla::Casilla() {}

Casilla tablero[8][8];

enum class Tipo : int { Rey = 1, Dama, Torre, Alfil, Caballo, Peon };
enum class Color : int { B = 1, N };

class Pieza
{
public:
	sf::Sprite m_sprite;
	bool m_juego = false;
	int m_nro{ -1 };
	Tipo m_tipo{};
	Color m_color{};
	sf::Vector2i m_pos{ -1, -1 };
	bool m_move = false;

	void setSprite(sf::Texture& t)
	{
		m_sprite.setTexture(t);
		m_sprite.setScale(escala, escala);
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