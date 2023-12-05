#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Tipo : int { Rey = 1, Dama, Torre, Alfil, Caballo, Peon };
enum class Color : int { B = 1, N };

class Pieza
{
public:
	sf::Sprite m_sprite;
	bool m_enjuego = false;
	int m_nro{ -1 };
	Tipo m_tipo{};
	Color m_color{};
	sf::Vector2i m_pos{ -1, -1 };
	bool m_move = false;

	Pieza();

	void setSprite(sf::Texture& t);
	void ColocarPieza(int i, int j, int k, Tipo tipo, Color color);
	void RemoverPieza(int i, int j, int cant);
	std::string getTipo();
	std::string getColor();
	int getReyNum(Color);
};

Pieza& P(int);