#include "Tauler.h"

using namespace std;

Tauler::Tauler() //constructor por defecto
{
	for (int i = 0; i < MAX_COL; i++)
		for (int j = 0; j < MAX_FILA; j++)
			m_tauler[i][j] = COLOR_NEGRE;
}

Tauler::Tauler(ColorFigura tauler[MAX_COL][MAX_FILA]) //constructor de copia de la matriz
{
	for (int i = 0; i < MAX_COL; i++)
		for (int j = 0; j < MAX_FILA; j++)
			m_tauler[i][j] = tauler[i][j];
}


bool Tauler::validMoviments(const Figura& figura, const Posicio& pos) const
{
    bool valid = true;

    // Verificar si alguna parte de la figura excede el límite superior del tablero
    for (int i = 0; i < figura.getSize() && valid; ++i)
    {
        for (int j = 0; j < figura.getSize() && valid; ++j)
        {
            if (figura.getFigura(i, j) != NO_COLOR)
            {
                Posicio pos_tmp{ pos.m_y + i, pos.m_x + j };
                valid = posicioValida(pos_tmp) && pos_tmp.m_y >= 0; // Verificar si la posición está dentro del límite superior
            }
        }
    }

    return valid;
}


bool Tauler::posicioValida(const Posicio& pos) const //complemento de validMoviments que comprueba posiciones
{
	bool valid = true;

	if (0 > pos.m_x || pos.m_x >= MAX_FILA || pos.m_y >= MAX_COL) //Comprobar limite
		valid = false;
	else
	{
		if (m_tauler[pos.m_y][pos.m_x] != COLOR_NEGRE) //Comprobar vacio
			valid = false;
	}

	return valid;
}


int Tauler::eliminaFila() //elimina las filas llenas
{
	int completades = 0;

	for (int i = 0; i < MAX_COL; ++i)
	{
		bool completa = true;
		int j = 0;

		while (j < MAX_FILA && completa)
		{
			if (m_tauler[i][j] == COLOR_NEGRE) {
				completa = false;
			}
			j++;
		}
		if (completa)
		{
			completades++;
			resetLinia(i); //Ponemos toda la fila en color negro

			for (int fila = i; fila > 0; fila--)
				for (int col = 0; col < MAX_FILA; col++)
					m_tauler[fila][col] = m_tauler[fila - 1][col];

			resetLinia(0);
		}
	}
	return completades;
}

void Tauler::resetLinia(int fila) //resetea la fila a 0 despues de eliminarla
{
	for (int j = 0; j < MAX_FILA; j++)
		m_tauler[fila][j] = COLOR_NEGRE;
	//Rellena toda la fila en color negro, desde el principio a fin de fila
}


void Tauler::colocarFigura(Figura figura, const Posicio& pos) //mete la figura en el tablero 
{
	for (int i = 0; i < figura.getSize(); i++)
		for (int j = 0; j < figura.getSize(); j++)
			if (figura.getFigura(i, j) != NO_COLOR)
				m_tauler[pos.m_y + i][pos.m_x + j] = figura.getColor(); //va posicion por posicion metiendolo al tablero, solo si es parte de la figura

	figura.setPos(pos);
}

void Tauler::dibuixa()
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false); //dibuja el tablero vacío
	for (int i = 0; i < MAX_COL; i++)
		for (int j = 0; j < MAX_FILA; j++)
		{ //comprueba si hay figuras ya colocadas y las dibuja
			switch (m_tauler[i][j])
			{
			case COLOR_GROC:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GROC, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_BLAUCEL:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUCEL, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_BLAUFOSC:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUFOSC, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_MAGENTA:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_MAGENTA, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_TARONJA:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_TARONJA, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_VERD:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			case COLOR_VERMELL:
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERMELL, POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false);
				break;
			default:
				break;
			}
		}
}

