#pragma once

#include "Tauler.h"
#include "Figura.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Joc
{
public:
	Joc() { m_pos.m_y = 0; m_pos.m_x = 0; m_figuraColocada = false; m_go = false; }
	void inicialitza(const string& nomFitxerInicial);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
	void dibuixa();
	void novaFigura();
	void resetTauler();	
	void setFiguraColocada(const bool& colocada) { m_figuraColocada = colocada; }
	void setFigura(Figura figura) { m_figura = figura; }
	bool getFiguraColocada() const { return m_figuraColocada; }
	Posicio getPos() const { return m_pos; }
	bool getGo() const { return m_go; }
	void setGo(const bool& go) { m_go = go; }

private:
	Tauler m_tauler;
	Figura m_figura;
	Posicio m_pos;
	bool m_figuraColocada;
	bool m_go;

};