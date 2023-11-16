#pragma once

void MovimientosRey() {}

void MovimientosDama() {}

void MovimientosTorre() {}

void MovimientosAlfil() {}

void MovimientosCaballo() {}

void MovimientosPeon(int i, int j)
{
	if (p[tablero[i][j].m_pieza].m_color == Color::B)
	{
		if ((!tablero[i][j - 1].m_ocp && !tablero[i][j - 2].m_ocp) && (!p[tablero[i][j].m_pieza].m_move))
		{
			p[tablero[i][j].m_pieza].m_sprite.move(0, -128);
			p[tablero[i][j].m_pieza].m_move = true;
			tablero[i][j].m_ocp = false;
			tablero[i][j - 2].m_pieza = p[tablero[i][j].m_pieza].m_nro;
			tablero[i][j - 2].m_ocp = true;
		}
		else if ((!tablero[i][j - 1].m_ocp) && j > 0)
		{
			p[tablero[i][j].m_pieza].m_sprite.move(0, -64);
			tablero[i][j].m_ocp = false;
			tablero[i][j - 1].m_pieza = p[tablero[i][j].m_pieza].m_nro;
			tablero[i][j - 1].m_ocp = true;
		}
		else if (tablero[i - 1][j - 1].m_ocp && j > 0 && i > 0)
		{
			p[tablero[i][j].m_pieza].m_sprite.move(-64, -64);
			tablero[i][j].m_ocp = false;
			tablero[i - 1][j - 1].m_pieza = p[tablero[i][j].m_pieza].m_nro;
			tablero[i - 1][j - 1].m_ocp = true;
		}
	}
	else if (p[tablero[i][j].m_pieza].m_color == Color::N)
	{
		if ((!tablero[i][j + 1].m_ocp) && j < 7)
		{
			p[tablero[i][j].m_pieza].m_sprite.move(0, 64);
			tablero[i][j].m_ocp = false;
			tablero[i][j + 1].m_pieza = p[tablero[i][j].m_pieza].m_nro;
			tablero[i][j + 1].m_ocp = true;
		}
		else if (tablero[i + 1][j + 1].m_ocp && j > 0 && i > 0)
		{
			p[tablero[i][j].m_pieza].m_sprite.move(64, 64);
			tablero[i][j].m_ocp = false;
			tablero[i - 1][j - 1].m_pieza = p[tablero[i][j].m_pieza].m_nro;
			tablero[i - 1][j - 1].m_ocp = true;
		}
	}
}