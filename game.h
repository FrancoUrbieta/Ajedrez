#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "casilla.h"
#include "pieza.h"

class Game {
	public:
		Game();
		void Run();

	private:

		//	Partida

		void setTextura(sf::Texture& t, std::string path);
		void setFuente(sf::Font& f, std::string path);
		//void setSonido(sf::SoundBuffer& s, std::string path);
		void CambioDeTurno();
		std::string getTurno();
		bool MouseEnTablero(sf::RenderWindow&);
		bool MouseEnCasilla(sf::Vector2i&, int, int);
		bool Abandonar(sf::Vector2i& mouse, sf::RectangleShape& abandonar);
		bool Tablas(sf::Vector2i& mouse, sf::RectangleShape& tablas);
		sf::Vector2i EncontrarCasilla(sf::Vector2i&);
		int SentidoDeAtaque(Pieza&, Pieza&);
		bool PiezaRival(Pieza&, Pieza&);
		int getNroPieza(sf::Vector2i mouse);
		int getReyRival(int);
		bool PeonCoronado(int k) const;
		void Notaciones();

		//	Movimientos

		bool MovimientosRey(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);
		bool MovimientosDama(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);
		bool MovimientosTorre(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);
		bool MovimientosAlfil(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);
		bool MovimientosCaballo(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);
		bool MovimientosPeon(Pieza& p, sf::Vector2i posA, sf::Vector2i posB);

		bool MovimientoPosible(int k, sf::Vector2i posk);
		bool MovimientosDisponibles(Pieza& R);

		//	Jugadas

		bool PiezaClavada(Pieza k, sf::Vector2i posA, sf::Vector2i posB, int R);
		void CapturarPieza(Pieza& k, Pieza& l, sf::Vector2i newpos);
		bool Enroque(int k, sf::Vector2i posA, sf::Vector2i posB);
		bool CapturaAlPaso(int k, sf::Vector2i posA, sf::Vector2i posB, sf::Vector2i oldpos);
		bool Coronacion(int k, sf::Vector2i posA, sf::Vector2i posB);
		bool Conversion(sf::Vector2i mouse, sf::Vector2i pos);

		//	JaqueMate

		bool PiezaEnMedio(int sentido, sf::Vector2i posA, sf::Vector2i posl, int k);
		bool CasillaEnJuego(sf::Vector2i pos, int k);
		bool Ahogado(sf::Vector2i posR, int Rey);
		bool Jaque(sf::Vector2i pos, int k);
		bool CubrirRey(int piezajaque, int piece, sf::Vector2i posA, sf::Vector2i posB);
		bool SalvarRey(int R, int Atk);

		//	Game

		void Menu();
		void PrepararJuego();
		void ProcessEvents();
		void Render();
		void ReiniciarJuego();


		sf::RenderWindow ajedrez;

		bool m_jugar = false;
		bool m_piezascolocadas = false;

		bool m_gameover = false;
		bool m_tablas = false;

		sf::RectangleShape m_tablasR;
		sf::RectangleShape m_abandonarR;

		int m_ronda = 1;
		int m_turnoB = 0;
		int m_turnoN = 0;
		Color m_turno{ Color::B };

		int m_piezasblancas = 0;
		int m_piezasnegras = 0;
		bool m_move = false;
		bool m_jugada = false;
		bool m_captura = false;
		int m_piece{ -1 };
		bool m_jaque = false;
		int m_piezajaque{ -1 };

		sf::Font m_fuente;
		sf::String m_mensaje;
		sf::String m_movimientos;
		bool m_notacion = false;
		int m_notamax = 0;
		int m_saltodelinea = 0;
		sf::String m_Njugada;
		sf::String m_Ncaptura;

		bool m_coronacion = false;

		int m_nropeon[16]{ -1 };
		bool m_peoncoronado[16]{ false };
		sf::Texture m_peonconvertido[16];

		sf::Vector2i m_lastoldpos{ -1, -1 };

		sf::Vector2i m_oldpos{ -1, -1 };
		sf::Vector2i m_newpos{ -1, -1 };

		sf::Vector2i m_oldcoord{ -1, -1 };
		sf::Vector2i m_newcoord{ -1, -1 };

		sf::Vector2f m_movecoord{ -1, -1 };
};