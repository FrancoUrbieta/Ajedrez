#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

static void PiezaEnCasilla(Pieza k)
{
	std::cout << "\n\tEntrada en " << k.getTipo() << " " << k.getColor() << "\n";
}

static void CoordenadasMouse(sf::RenderWindow& ajedrez)
{
	std::cout << "MOUSE - ";
	std::cout << "(" << sf::Mouse::getPosition(ajedrez).x;
	std::cout << ", " << sf::Mouse::getPosition(ajedrez).y << ")\n";
}

static void CoordenadasPieza(int k)
{
	std::cout << "PIEZA [" << k + 1 << "] - ";
	std::cout << "(" << P(k).m_sprite.getPosition().x;
	std::cout << ", " << P(k).m_sprite.getPosition().y << ")\n";
}

static void CoordenadasCasilla(int i, int j)
{
	std::cout << "CASILLA[" << i + 1 << "][" << j + 1 << "] - ";
	std::cout << "(" << Tablero(i, j).m_casilla.getGlobalBounds().getPosition().x;
	std::cout << ", " << Tablero(i, j).m_casilla.getGlobalBounds().getPosition().y << ")\n";
}