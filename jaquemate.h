#pragma once

bool PiezaEnMedio(int sentido, sf::Vector2i posA, sf::Vector2i posl, int k);

bool CasillaEnJuego(sf::Vector2i pos, int k);

bool PiezaClavada(Pieza k, sf::Vector2i posA, sf::Vector2i posB, int R);

bool Ahogado(sf::Vector2i posR, int Rey);

sf::Vector2i DistanciaEntrePiezas(sf::Vector2i posA, sf::Vector2i posB);

bool Jaque(sf::Vector2i pos, int k);

bool SalvarRey(int R, int Atk);
