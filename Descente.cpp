#include "Descente.h"

Descente::Descente(int numero, std::string nomTrajet,int depart,int arrive, std::string typeDescente, float tempsDescente,int capacites)
:Trajet(numero, nomTrajet,depart,arrive,capacites), m_typeDescente{typeDescente}, m_tempsDescente{tempsDescente}
{}

std::string Descente::getTypeDescente(){
    return m_typeDescente;
}

float Descente::getTempsDescente() {
    return m_tempsDescente;
}
void Descente::afficher() {
    std::cout << "Trajet " << getNumero() << " de nom " << getNomTrajet()
    << " est une descente allant de " << getDepart() << " a " << getArrive()
    << "  type: " << getTypeDescente() << "    temps descente " << getTempsDescente()<<"  capacite: "<<getCapacite() << std::endl;
}