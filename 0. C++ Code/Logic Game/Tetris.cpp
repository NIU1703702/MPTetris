#include "Tetris.h"

int Tetris::menuTetris() //menu principal
{
	cout << "-----------------------------------------" << endl;
	cout << "		TETRIS:			" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "1.- Jugar en mode normal" << endl;
	cout << "2.- Jugar en mode test" << endl;
	cout << "3.- Veure llista de puntuacions" << endl;
	cout << "4.- Sortir" << endl;
	cout << "Selecciona una opcio de joc: ";
	int opcio;
	cin >> opcio;
    cout << endl;
	
	return opcio;
}

void Tetris::juga(Screen& pantalla, double deltaTime, int mode) //metodo para jugar una partida en modo normal o test
{
    m_partida.setEstat(false);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    m_partida.inicialitza(mode);
    pantalla.show();
    do
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();
        m_partida.actualitza(mode, deltaTime);


        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !m_partida.getEstat()); //mientras la partida no se acabe o no se pulse ESC, continua el bucle
    // Sortim del bucle si pressionem ESC
    if (mode == 1 && m_partida.getEstat()) //si la partida acaba y se juega en modo normal, se pide el nombre del jugador y se guarda su puntuacion
    {
        cout << "Nom del jugador: ";
        string nom;
        cin >> nom;
        afegeixPuntuacio(nom, m_partida.getPuntuacio());
        guardaPuntuacions();
    }
}

void Tetris::recuperaPuntuacions() //recupera los datos de un jugador de un archivo
{
    ifstream fitxer;
    fitxer.open("data/Games/puntuacions.txt");
    m_puntuacions.clear();

    if (fitxer.is_open())
    {
        DadesJugador jug;

        while (fitxer >> jug.nomJugador >> jug.puntuacioJugador)
        {
            m_puntuacions.push_back(jug); //añade los datos del jugador a la lista
        }
        fitxer.close();
    }
}

void Tetris::afegeixPuntuacio(const string& nom, int puntuacio) //añade el nombre y la puntuacion del jugador a la lista, usando el struct DadesJugador
{
    DadesJugador jugador;
    jugador.nomJugador = nom;
    jugador.puntuacioJugador = puntuacio;
    list<DadesJugador>::iterator actual = m_puntuacions.begin(), final = m_puntuacions.end();
    bool trobat = false;

    while (actual != final && !trobat)
    {
        if (puntuacio > actual->puntuacioJugador) //ordena las puntuaciones en orden ascendente
            trobat = true;
        else
            actual++;
    }
    m_puntuacions.insert(actual, jugador); //inserta la puntuacion
}

void Tetris::mostraPuntuacions() //muestra la lista de puntuaciones
{
    list<DadesJugador>::reverse_iterator actual = m_puntuacions.rbegin(), final = m_puntuacions.rend();
    int i = 1;
    cout << "-----------------------------------------" << endl;
    cout << "       Llista de puntuacions:      " << endl;
    cout << "-----------------------------------------" << endl;
    while (actual != final)
    {
        cout << i << ". " << actual->nomJugador << "  " << actual->puntuacioJugador << endl;
        actual++;
        i++;
    }
    cout << endl << endl;
}

void Tetris::guardaPuntuacions() //guarda la lista de puntuaciones en un archivo
{
    ofstream fitxer;
    fitxer.open("data/Games/puntuacions.txt");

    if (fitxer.is_open())
    {
        for (auto& jug : m_puntuacions) //iterador para recorrer la lista de puntuaciones
        {
            fitxer << jug.nomJugador << " " << jug.puntuacioJugador << endl;
        }
        fitxer.close();
    }
}