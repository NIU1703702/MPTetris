#pragma once
#include "Figura.h"

class Tauler
{
public:
	Tauler();
	Tauler(ColorFigura tauler[MAX_COL][MAX_FILA]);

	ColorFigura getTauler(const int& x, const int& y) const { return m_tauler[x][y]; }
	void setTauler(ColorFigura color, int posX, int posY) { m_tauler[posX][posY] = color; }

	bool validMoviments(const Figura& figura, const Posicio& pos) const;
	int eliminaFila();
	void colocarFigura(Figura figura, const Posicio& pos);
	void resetLinia(int fila);
	void dibuixa();
private:

	bool posicioValida(const Posicio& pos) const;
	ColorFigura m_tauler[MAX_COL][MAX_FILA];
};

