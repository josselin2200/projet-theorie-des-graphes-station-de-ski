#include "Navette.h"
#include <utility>

Navette::Navette(int numero, std::string nomTrajet, int depart, int arrive,std::string typeNavette, int dureeBus,int capacites)
    :Trajet(numero,std::move(nomTrajet),depart,arrive,capacites),m_typeNavette{std::move(typeNavette)},m_dureeBus{dureeBus}
{}

int Navette::getDureeBus() {
    return m_dureeBus;
}
void Navette::afficher() {
    std::cout << "Trajet numero "<< getNumero() << ", de nom  "<< getNomTrajet()
    <<". C'est une Navette allant de  "<< getDepart() << " a " << getArrive()
    <<". Le trajet dure " << getDureeBus() << ". Capacite: " << getCapacite() << " personnes." << std::endl;
}
std::string Navette::getTypeNavette() {
    return m_typeNavette;
}