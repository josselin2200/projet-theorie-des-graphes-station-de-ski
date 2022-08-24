#include "Trajet.h"

Trajet::Trajet(int numero, std::string nomTrajet,int depart,int arrive,int capacites)
        : m_numero{numero}, m_nomTrajet{nomTrajet},m_depart{depart},m_arrive{arrive},m_capacites{capacites}
{}

std::string Trajet::getNomTrajet() {
    return m_nomTrajet;
}

int Trajet::getNumero() {
    return m_numero;
}

double Trajet::getTempsTrajet() {
    return m_tempsTrajet;
}

int Trajet::getArrive() {
    return m_arrive;
}
int Trajet::getDepart() {
    return m_depart;
}

void Trajet::afficher() {
    std::cout<<"Trajet ";
}

int Trajet::getCapacite() {
    return m_capacites;
}