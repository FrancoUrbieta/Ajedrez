#pragma once

bool MovimientosRey(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosDama(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosTorre(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosAlfil(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosCaballo(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosPeon(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

bool MovimientosDisponibles(Pieza& R);