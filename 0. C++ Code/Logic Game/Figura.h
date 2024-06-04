#pragma once

#include "InfoJoc.h"

class Figura
{
public:
    Figura();

    ColorFigura getColor() const { return m_color; }
    int getSize() const { return m_size; }
    ColorFigura getFigura(const int& x, const int& y) const { return m_figura[x][y]; }
    Posicio getPosicio() const { return m_pos; }
    void setPos(const Posicio& pos) { m_pos = pos; }

    void initFigura(TipusFigura figura);
    void girarFigura(const DireccioGir& gir);
    void baixaFigura(const int& dirY);
    void desplacamentFigura(const int& dirX);
    void dibuixa();
private:
    TipusFigura m_tipus;
    ColorFigura m_color;
    Posicio m_pos;
    int m_size;
    ColorFigura m_figura[MAX_ALCADA][MAX_AMPLADA];

};
