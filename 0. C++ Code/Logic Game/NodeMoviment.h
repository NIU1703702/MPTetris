#pragma once
#include "InfoJoc.h"

class NodeMoviment
{
public:
    void setValor(const TipusMoviment& mov) { m_valor = mov; }
    void setNext(NodeMoviment* next) { m_next = next; }
    TipusMoviment& getValor() { return m_valor; }
    NodeMoviment* getNext() { return m_next; }
private:
    TipusMoviment m_valor;
    NodeMoviment* m_next;
};