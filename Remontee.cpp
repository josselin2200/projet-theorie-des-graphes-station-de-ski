#include "Remontee.h"
#include <utility>

Remontee::Remontee(int numero, std::string nomTrajet ,int depart,int arrive,int dureeParDenivele, std::string typeRemontee, int dureeFixe,int capacites)
    :Trajet(numero,std::move(nomTrajet),depart,arrive,capacites),m_dureeParDenivele{dureeParDenivele}, m_typeRemontee{std::move(typeRemontee)}, m_dureeFixe{dureeFixe}
{}


int Remontee::getDureeFixe() {
    return m_dureeFixe;
}

int Remontee::getDureeParDenivele() {
    return m_dureeParDenivele;
}

std::string Remontee::getTypeRemontee() {
    return m_typeRemontee;
}

void Remontee::afficher() {
    std::cout << "Trajet " << getNumero() << " de nom  " << getNomTrajet()
    << " est une remontee allant de " << getDepart() << " a " << getArrive()
    << " , de type: " << getTypeRemontee()
    << "  temps fixe: " << getDureeFixe()
    << "  temps denivele: " << getDureeParDenivele()
    <<"  capacite: "<<getCapacite()<< std::endl;
}