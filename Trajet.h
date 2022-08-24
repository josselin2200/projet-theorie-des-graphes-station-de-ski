#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_TRAJET_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_TRAJET_H

#include <iostream>
#include "PointGeographique.h"
#include <vector>

class Trajet {
private:
    int m_numero;
    int m_depart,m_arrive;
    std::string m_nomTrajet;
    double m_tempsTrajet;
    int m_capacites;

public:
    Trajet(int numero, std::string nomTrajet,int depart,int arrive,int capacites);

    int getNumero();
    double getTempsTrajet();

    std::string getNomTrajet();

    int getDepart();
    int getArrive();
    int getCapacite();

    virtual void afficher();
};

#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_TRAJET_H
