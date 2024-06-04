#include "Partida.h"

Partida::Partida() //constructor por defecto
{
    m_temps = 0;
	m_nivell = 1;
	m_velocitat = 1;
	m_puntuacio = 0;
	m_acabada = false;

	m_moviment = nullptr;
	m_figuras = nullptr;
	m_movAux = m_moviment;
	m_figAux = m_figuras;
}


void Partida::inicialitza(int mode) 
{
	m_joc.setFiguraColocada(false);
	m_temps = 0;
	m_nivell = 1;
	m_velocitat = 1; //valores por defecto
	m_puntuacio = 0;
	m_joc.setGo(false);
	m_joc.resetTauler();
	if (mode == 1) //si es modo normal, crea una figura nueva
	{
		m_joc.novaFigura();
	}
	else if (mode == 2) //si es modo test, se inicializa en funcion de los archivos
	{
		m_figuras = nullptr;
		m_moviment = nullptr;
		cout << "Nom del fitxer amb l'estat inicial del tauler: ";
		string fitxerInicial;
		cin >> fitxerInicial;
		cout << "Nom del fitxer amb la sequencia de figures: ";
		string fitxerFigures;
		cin >> fitxerFigures;
		cout << "Nom del fitxer amb la sequencia de moviments: ";
		string fitxerMoviments;
		cin >> fitxerMoviments;
		m_joc.inicialitza(fitxerInicial); //inicializa tablero y figura inicial

		ifstream fitxer;
		fitxer.open("data/Games/" + fitxerMoviments); //inicializa movimientos
		if (fitxer.is_open())
		{
			bool trobat = false;
			int input;
			TipusMoviment mov;

			fitxer >> input;
			while (!fitxer.eof())
			{
				trobat = false;
				switch (input)
				{
				case 0:
					mov = MOVIMENT_ESQUERRA;
					break;
				case 1: 
					mov = MOVIMENT_DRETA;
					break;
				case 2:
					mov = MOVIMENT_GIR_HORARI;
					break;
				case 3:
					mov = MOVIMENT_GIR_ANTI_HORARI;
					break;
				case 4:
					mov = MOVIMENT_BAIXA;
					break;
				case 5:
					mov = MOVIMENT_BAIXA_FINAL;
					break;
				}
				NodeMoviment* moviment = new NodeMoviment; //se genera un nodo que coge los valores de movimiento
				moviment->setValor(mov);
				moviment->setNext(nullptr);

				if (m_moviment == nullptr) //si la lista esta vacia
					m_moviment = moviment; //recibe el valor del nodo temporal
				else
				{
					NodeMoviment* seguent = m_moviment; //se crea un nodo que mantiene el siguiente valor
					while (!trobat) //se hace un recorrido hasta llegar al final de la lista
					{
						if (seguent->getNext() == nullptr)
						{
							trobat = true;
							seguent->setNext(moviment); //se añade el movimiento al final de la lista
						}
						else
							seguent = seguent->getNext();
					}
				}
				fitxer >> input;
			}
			m_movAux = m_moviment; //se da el valor del nodo principal al nodo auxiliar
			fitxer.close();
		}

		fitxer.open("data/Games/" + fitxerFigures); //se sigue el mismo proceso que en los movimientos, en este caso con las figuras
		if (fitxer.is_open())
		{
			Posicio pos;
			int tipus, gir;
			fitxer >> tipus >> pos.m_y >> pos.m_x >> gir;
			bool trobat = false;
			while (!fitxer.eof())
			{
				NodeFigura* figura = new NodeFigura;
				trobat = false;
				Figura fig;

				fig.initFigura(TipusFigura(tipus));

				pos.m_x--;
				pos.m_y--;
				fig.setPos(pos);

				for (int i = 0; i < gir; i++)
					fig.girarFigura(GIR_HORARI);
				
				figura->setValor(fig);
				figura->setNext(nullptr);

				if (m_figuras == nullptr) //si la lista esta vacia, recibe el valor del nodo temporal
					m_figuras = figura;
				else
				{
					NodeFigura* seguent = m_figuras;
					while (!trobat) //recorre la lista hasta llegar al final
					{
						if (seguent->getNext() == nullptr)
						{
							trobat = true;
							seguent->setNext(figura); //se añade la figura al final de la lista
						}
						else
							seguent = seguent->getNext();
					}
				}
				fitxer >> tipus >> pos.m_y >> pos.m_x >> gir;
			}
			m_figAux = m_figuras; //el nodo auxiliar toma el mismo valor que el principal
			fitxer.close();
		}
	}
}

void Partida::actualitza(int mode, double deltaTime)
{
	m_joc.dibuixa(); //se dibuja el tablero y la figura
	string msg = "SCORE: " + to_string(m_puntuacio);
	string msg2 = " LEVEL: " + to_string(m_nivell); //se escribe la puntuacion y el nivel en pantalla
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 40, 30, 0.8, msg);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 445, 30, 0.8, msg2); //se dibuja graficamente

	int filesCompletes = 0;
		if (mode == 1) //modo normal
		{
			if (!m_joc.getFiguraColocada()) //si no se ha colocado la figura
			{
				m_temps += deltaTime;
				if (m_temps > m_velocitat) //si el tiempo es menor que la velocidad
				{
					filesCompletes = m_joc.baixaFigura();//la figura baja
					m_temps = 0.0;
				}
				//asignacion de los controles del juego
				if (Keyboard_GetKeyTrg(KEYBOARD_UP))
					m_joc.giraFigura(GIR_HORARI);
				else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
					m_joc.mouFigura(1);
				else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
					m_joc.giraFigura(GIR_ANTI_HORARI);
				else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
					m_joc.mouFigura(-1);
				else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
					while (!m_joc.getFiguraColocada())
						filesCompletes = m_joc.baixaFigura();
				m_puntuacio += sumarPuntuacio(filesCompletes); //suma la puntuacion despues de cada movimiento
			}
			else //si la figura esta colocada
			{
				if (m_joc.getGo() == true) //comprueba si hay Game Over
					m_acabada = true; //la partida acaba

				if (!m_acabada) //si la partida no esta acabada
				{
					m_joc.novaFigura(); //se crea una nueva figura
					m_puntuacio += 10; //suma 10 a la puntuacion, al haberse colocado una figura
					m_velocitat = 1; 
					if (m_puntuacio > 1000)
						m_nivell = (m_puntuacio / 1000) + 1; //se calcula el nivel actual
					for (int i = 0; i < m_nivell; i++) //y la velocidad
						m_velocitat *= 0.9;

				}
				else  //si la partida acaba
				{
					m_puntuacio -= sumarPuntuacio(filesCompletes); //se resta todo lo que se haya podido sumar con la ultima figura antes del Game Over
					m_puntuacio -= 10;							   //debido a la implementacion del Game Over
					GraphicManager::getInstance()->drawSprite(GRAFIC_GAME_OVER, 0, 0, false);
				}
			}
		}
		else if (mode == 2) //modo test
		{
			filesCompletes = 0;
			m_temps += deltaTime;
			if (m_temps > m_velocitat)
			{
				m_temps = 0.0;

				if (m_movAux != nullptr && m_figAux != nullptr) //la partida continua hasta que no hayan mas movimientos
				{
					TipusMoviment mov = m_movAux->getValor();
					m_movAux = m_movAux->getNext();
					switch (mov)
					{
					case MOVIMENT_ESQUERRA:
						m_joc.mouFigura(-1);
						break;
					case MOVIMENT_DRETA:
						m_joc.mouFigura(1);
						break;
					case MOVIMENT_GIR_HORARI:
						m_joc.giraFigura(GIR_HORARI);
						break;
					case MOVIMENT_GIR_ANTI_HORARI:
						m_joc.giraFigura(GIR_ANTI_HORARI);
						break;
					case MOVIMENT_BAIXA:
						filesCompletes = m_joc.baixaFigura();
						break;
					case MOVIMENT_BAIXA_FINAL:
						while (!m_joc.getFiguraColocada())
							filesCompletes = m_joc.baixaFigura();
						break;
						m_puntuacio += sumarPuntuacio(filesCompletes);
					}
					if (m_joc.getFiguraColocada()) //si la figura se coloca, pasa a la siguiente
					{
						m_joc.setFigura(m_figAux->getValor());
						m_figAux = m_figAux->getNext();
						m_joc.setFiguraColocada(false);
						m_puntuacio += 10;
					}
				}
				else
				{
					m_acabada = true; //game over
					GraphicManager::getInstance()->drawSprite(GRAFIC_GAME_OVER, 0, 0, false);
				}
			}
		}
	}


int Partida::sumarPuntuacio(int nFilesCompletades) //suma de puntuacion en funcion de la cantidad de filas completadas a la vez
{
	int puntuacio = 0;

	switch (nFilesCompletades)
	{
	case 1:
		puntuacio += 100;
		break;
	case 2:
		puntuacio += 150;
		break;
	case 3:
		puntuacio += 175;
		break;
	case 4:
		puntuacio += 200;
		break;
	default:
		break;
	}
	return puntuacio;
}
