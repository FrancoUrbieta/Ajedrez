#include <SFML/Graphics.hpp>
#include <iostream>
#include "pieza.h"
#include "casilla.h"

Pieza::Pieza() {}

void Pieza::setSprite(sf::Texture& t)
{
	m_sprite.setTexture(t);
	if (m_enjuego)
	{
		m_sprite.setScale(escala, escala);
	}
}

void Pieza::ColocarPieza(int i, int j, int k, Tipo tipo, Color color)
{
	m_enjuego = true;
	m_nro = k;
	m_tipo = tipo;
	m_color = color;
	m_pos.x = i;
	m_pos.y = j;
	Tablero(i, j).LlenarCasilla(k);
	m_sprite.setPosition(distancia * i + distancia, distancia * j + distancia);
}

void Pieza::RemoverPieza(int i, int j, int cant)
{
	m_enjuego = false;
	m_pos.x = -1;
	m_pos.y = -1;
	Tablero(i, j).VaciarCasilla();
	if (m_color == Color::B)
	{
		m_sprite.setPosition((distancia / 2), (distancia / 2) * (18 - cant));
		m_sprite.scale(0.5, 0.5);
	}
	else if (m_color == Color::N)
	{
		m_sprite.setPosition(distancia * 9, (distancia / 2) * (cant + 1));
		m_sprite.scale(0.5, 0.5);
	}
}

std::string Pieza::getTipo()
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

std::string Pieza::getColor()
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

int Pieza::getReyNum(Color color)
{
	switch (color)
	{
	case::Color::B:
		return 19;
	case::Color::N:
		return 16;
	default:
		return -1;
	}
}

Pieza p[32];

Pieza& P(int k)
{
	return p[k];
}
