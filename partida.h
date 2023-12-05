#pragma once

bool MouseEnTablero(sf::RenderWindow&);

bool MouseEnCasilla(sf::Vector2i&, int, int);

sf::Vector2i EncontrarCasilla(sf::Vector2i&);

bool PiezaRival(Pieza&, Pieza&);

int ReyRival(int);

int SentidoDeAtaque(Pieza&, Pieza&);