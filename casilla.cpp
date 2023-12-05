#include <SFML/Graphics.hpp>
#include "casilla.h"

Casilla::Casilla() {}

void Casilla::setSprite(Casilla& casilla, sf::Texture& t)
{
	casilla.m_casilla.setTexture(t);
	casilla.m_casilla.setScale(escala, escala);
}

void Casilla::VaciarCasilla()
{
	m_ocp = false;
	m_pieza = -1;
}

void Casilla::LlenarCasilla(int k)
{
	m_ocp = true;
	m_pieza = k;
}

Casilla tablero[8][8];

Casilla& Tablero(int i, int j)
{
	return tablero[i][j];
}


