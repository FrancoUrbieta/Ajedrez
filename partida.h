#pragma once

bool MouseEnTablero(sf::RenderWindow&);

bool MouseEnCasilla(sf::Vector2i&, int, int);

bool Abandonar(sf::Vector2i& mouse, sf::RectangleShape& abandonar);

bool Tablas(sf::Vector2i& mouse, sf::RectangleShape& tablas);

sf::Vector2i EncontrarCasilla(sf::Vector2i&);

bool PiezaRival(Pieza&, Pieza&);

int ReyRival(int);

int SentidoDeAtaque(Pieza&, Pieza&);