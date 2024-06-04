#pragma once

#include "Figura.h"

class NodeFigura
{
public:
    void setValor(const Figura& fig) { m_valor = fig; }
    void setNext(NodeFigura* next) { m_next = next; }
    Figura& getValor() { return m_valor; }
    NodeFigura* getNext() { return m_next; }
private:
    Figura m_valor;
    NodeFigura* m_next;
};