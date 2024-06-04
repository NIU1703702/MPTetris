#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "Joc.h"
#include "NodeFigura.h"
#include "NodeMoviment.h"

using namespace std;

class Partida 
{
public:
    Partida();
    void inicialitza(int mode);
    void actualitza(int mode, double deltaTime);
    int sumarPuntuacio(int nFilesCompletades);
    void setEstat(const bool& estat) { m_acabada = estat; }
    bool getEstat() const { return m_acabada; }
    int getPuntuacio() const { return m_puntuacio; }
    int getNivell() const { return m_nivell; }

private:
    Joc m_joc;
    double m_temps;
    double m_velocitat;
    int m_nivell;
    int m_puntuacio;
    bool m_acabada;

    NodeMoviment* m_moviment;
    NodeMoviment* m_movAux;
    NodeFigura* m_figuras;
    NodeFigura* m_figAux;
    
    
};

#endif 
