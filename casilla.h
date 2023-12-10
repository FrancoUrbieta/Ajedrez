#pragma once
#include <SFML/Graphics.hpp>
#define escala 2.125
#define distancia 32 * escala

class Casilla
{
public:
	sf::Sprite m_casilla;
	bool m_ocp = false;
	int m_pieza{ -1 };

	Casilla();

	void setSprite(Casilla&, sf::Texture&);

	void VaciarCasilla();
	void LlenarCasilla(int);
};

Casilla& Tablero(int, int);