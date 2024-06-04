#pragma once
#include "Partida.h"
#include <list>
class Tetris
{
public:
	int menuTetris();
	void juga(Screen& pantalla, double deltaTime, int mode);
	void recuperaPuntuacions();
	void afegeixPuntuacio(const string& nom, int puntuacio);
	void mostraPuntuacions();
	void guardaPuntuacions();
private:
	Partida m_partida;
	list <DadesJugador> m_puntuacions;
};

