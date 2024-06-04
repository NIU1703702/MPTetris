#include "Joc.h"
#include <cstdlib>


void Joc::inicialitza(const string& nomFitxerInicial) //incializa el tablero y la primera figura del modo test
{
	ifstream fitxer;
	Posicio pos;
	int gir, input;
	m_figuraColocada = false;

		fitxer.open("data/Games/" + nomFitxerInicial);
		if (fitxer.is_open())
		{
			fitxer >> input >> pos.m_y >> pos.m_x >> gir;
			pos.m_x--;
			pos.m_y--;
			m_figura.initFigura(TipusFigura(input));
			m_figura.setPos(pos);
			m_pos = pos;
			for (int i = 0; i < gir; i++)
				m_figura.girarFigura(GIR_HORARI);

			for (int i = 0; i < MAX_COL; i++)
			{
				for (int j = 0; j < MAX_FILA; j++)
				{
					int color;
					fitxer >> color;

					m_tauler.setTauler(ColorFigura(color), i, j);
				}
			}
			fitxer.close();
		}	
}

bool Joc::giraFigura(DireccioGir direccio) //devuelve un bool en funcion de si puede girar o no
{
	bool potGirar = true;
	m_figura.girarFigura(direccio);

	if (!m_tauler.validMoviments(m_figura, m_pos))
	{
		if (direccio == GIR_HORARI)
			m_figura.girarFigura(GIR_ANTI_HORARI);
		else
			m_figura.girarFigura(GIR_HORARI);
		potGirar = false;
	}
	return potGirar;
}

bool Joc::mouFigura(int dirX)
{
	bool moviment = true;
	m_figura.desplacamentFigura(dirX); //lo mueve y despues comprueba si es correcto

	if (!m_tauler.validMoviments(m_figura, m_figura.getPosicio())) //si no es correcto
	{
		if (dirX == -1)
			m_figura.desplacamentFigura(1); //retrocede
		else
			m_figura.desplacamentFigura(-1); //retrocede
		moviment = false;
	}
	else
		m_pos = m_figura.getPosicio(); //se puede mover por lo tanto se coloca (ya se habia movido)

	return moviment;
}

int Joc::baixaFigura()
{
	int eliminades = 0;
	m_figura.baixaFigura(1); //baja la figura y despues comprueba si es correcto

	if (!m_tauler.validMoviments(m_figura, m_figura.getPosicio())) //si no es correcto
	{
		m_figura.baixaFigura(-1); //retrocede
		m_tauler.colocarFigura(m_figura, m_figura.getPosicio()); //lo coloca porque ya no puede bajar mas
		m_figuraColocada = true;
		eliminades = m_tauler.eliminaFila(); //comprobamos y eliminamos, si hay, las filas completas
	}
	else
		m_pos = m_figura.getPosicio();  //si ha podido bajar, recupera esa posicion y la guarda

	return eliminades; //devuelve el numero de filas eliminadas
}

void Joc::escriuTauler(const string& nomFitxer) //funcion utilizada en la primera entrega
{
	int i, j;
	ofstream fitxer;

	fitxer.open(nomFitxer); //escribe el tablero en un archivo

	if (fitxer.is_open())
	{
		if (!m_figuraColocada)
			m_tauler.colocarFigura(m_figura, m_pos);

		for (int i = 0; i < MAX_COL; i++)
		{
			for (int j = 0; j < MAX_FILA; j++)
				fitxer << int(m_tauler.getTauler(i, j)) << " ";
			fitxer << endl;
		}
		fitxer.close();
	}
}

void Joc::dibuixa() //llama a los metodos de dibuixa de figura y tablero
{
	m_tauler.dibuixa();
	m_figura.dibuixa();
}

void Joc::novaFigura()
{
	Posicio pos;
	int count = 0;

	do
	{
		int tipus = (rand() % 7) + 1; //genera un numero aleatorio entre el 1-7 para el tipo de figura
		m_figura.initFigura(TipusFigura(tipus)); 
		pos.m_y = 0; 
		pos.m_x = rand() % MAX_FILA; //genera una posicion aleatoria en el eje X
		m_figura.setPos(pos);

		if (count < 30) //contador que tiene en cuenta las veces que se repite el do-while
			count++;
		else //si se repite el codigo 30 veces y la figura no se genera en una posicion valida, el juego acaba (Game Over)
			m_go = true;			
	} while (!m_tauler.validMoviments(m_figura, pos) && !m_go); //hacemos do-while ya que al generar una figura, podria generarse fuera de los límites del juego
		//si la figura no tiene espacio para moverse la partida acaba
	m_figuraColocada = false; //se reinicia figuraColocada
}

void Joc::resetTauler() //vacia el tablero
{
	for (int i = 0; i < MAX_COL; i++)
		for (int j = 0; j < MAX_FILA; j++)
			m_tauler.setTauler(COLOR_NEGRE, i, j);
}
