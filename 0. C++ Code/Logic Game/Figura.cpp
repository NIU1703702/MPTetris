#include "Figura.h"

Figura::Figura() //constructor por defecto 
{
	m_size = 0;
	m_color = NO_COLOR;
	m_tipus = NO_FIGURA;
	m_pos.m_y = 0;
	m_pos.m_x = 0;

	for (int i = 0; i < MAX_ALCADA; i++)
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_figura[i][j] = NO_COLOR;

}

void Figura::initFigura(TipusFigura tipusFigura) //inicializa la figura segun la figura de entrada
{
	m_size = 0;
	m_tipus = tipusFigura;
	m_pos.m_y = 0;
	m_pos.m_x = 0;

	for (int i = 0; i < MAX_ALCADA; i++)
		for (int j = 0; j < MAX_AMPLADA; j++)
			m_figura[i][j] = NO_COLOR;

	switch (m_tipus)
	{
	case FIGURA_O:
		m_figura[0][0] = COLOR_GROC;
		m_figura[0][1] = COLOR_GROC;
		m_figura[1][0] = COLOR_GROC;
		m_figura[1][1] = COLOR_GROC;
		m_color = COLOR_GROC;
		m_size = 2;
		break;
	case FIGURA_I:
		m_figura[1][0] = COLOR_BLAUCEL;
		m_figura[1][1] = COLOR_BLAUCEL;
		m_figura[1][2] = COLOR_BLAUCEL;
		m_figura[1][3] = COLOR_BLAUCEL;
		m_color = COLOR_BLAUCEL;
		m_size = 4;
		break;
	case FIGURA_T:
		m_figura[0][1] = COLOR_MAGENTA;
		m_figura[1][0] = COLOR_MAGENTA;
		m_figura[1][1] = COLOR_MAGENTA;
		m_figura[1][2] = COLOR_MAGENTA;
		m_color = COLOR_MAGENTA;
		m_size = 3;
		break;
	case FIGURA_L:
		m_figura[0][2] = COLOR_TARONJA;
		m_figura[1][0] = COLOR_TARONJA;
		m_figura[1][1] = COLOR_TARONJA;
		m_figura[1][2] = COLOR_TARONJA;
		m_color = COLOR_TARONJA;
		m_size = 3;
		break;
	case FIGURA_J:
		m_figura[0][0] = COLOR_BLAUFOSC;
		m_figura[1][0] = COLOR_BLAUFOSC;
		m_figura[1][1] = COLOR_BLAUFOSC;
		m_figura[1][2] = COLOR_BLAUFOSC;
		m_color = COLOR_BLAUFOSC;
		m_size = 3;
		break;
	case FIGURA_Z:
		m_figura[0][0] = COLOR_VERMELL;
		m_figura[0][1] = COLOR_VERMELL;
		m_figura[1][1] = COLOR_VERMELL;
		m_figura[1][2] = COLOR_VERMELL;
		m_color = COLOR_VERMELL;
		m_size = 3;
		break;
	case FIGURA_S:
		m_figura[0][1] = COLOR_VERD;
		m_figura[0][2] = COLOR_VERD;
		m_figura[1][0] = COLOR_VERD;
		m_figura[1][1] = COLOR_VERD;
		m_color = COLOR_VERD;
		m_size = 3;
		break;
	}
}

void Figura::girarFigura(const DireccioGir& gir)
{
	// intercambia los elementos de la matriz en packs de cuatro
	// pilla las esquinas y va avanzando hacia el centro

	for (int i = 0; i < m_size / 2; ++i) {
		for (int j = i; j < m_size - i - 1; ++j) {

			ColorFigura temp = m_figura[i][j]; // matriz de colores temporal para las figuras

			if (gir == GIR_HORARI) {
				m_figura[i][j] = m_figura[m_size - 1 - j][i];
				m_figura[m_size - 1 - j][i] = m_figura[m_size - 1 - i][m_size - 1 - j];
				m_figura[m_size - 1 - i][m_size - 1 - j] = m_figura[j][m_size - 1 - i];
				m_figura[j][m_size - 1 - i] = temp;
			}
			else {
				m_figura[i][j] = m_figura[j][m_size - 1 - i];
				m_figura[j][m_size - 1 - i] = m_figura[m_size - 1 - i][m_size - 1 - j];
				m_figura[m_size - 1 - i][m_size - 1 - j] = m_figura[m_size - 1 - j][i];
				m_figura[m_size - 1 - j][i] = temp;
			}
		}
	}
}

void Figura::desplacamentFigura(const int& dirX) // mueve hacia izquierda si es -1 y derecha si es1 
{
	if (dirX == -1)
		m_pos.m_x--;
	else
		m_pos.m_x++;
}


void Figura::baixaFigura(const int& dirY) // mueve para abajo 
{
	if (dirY == -1) // esto es porque movemos antes de comprobar y si vemos que no se puede lo devolvemos a su posicion inicial
		m_pos.m_y--;
	else
		m_pos.m_y++;
}

void Figura::dibuixa() //dibuja las figuras en formato grafico
{
	for (int i = 0; i < m_size; i++)
		for (int j = 0; j < m_size; j++)
		{
			switch (m_figura[i][j])
			{
				case COLOR_GROC:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GROC, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_BLAUCEL:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUCEL, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_BLAUFOSC:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_BLAUFOSC, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_MAGENTA:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_MAGENTA, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_TARONJA:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_TARONJA, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_VERD:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERD, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				case COLOR_VERMELL:
					GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_VERMELL, POS_X_TAULER + (m_pos.m_x + 1 + j) * MIDA_QUADRAT, POS_Y_TAULER + ((m_pos.m_y + i) * MIDA_QUADRAT), false);
					break;
				default:
					break;
			}
		}
}