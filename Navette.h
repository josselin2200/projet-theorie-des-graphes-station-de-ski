#include "Trajet.h"

#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_NAVETTE_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_NAVETTE_H

#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_NAVETTE_H

class Navette: public Trajet{
protected :
    int m_dureeBus;
    std::string m_typeNavette;
public:
    Navette(int numero, std::string nomTrajet,int depart, int arrive,std::string typeNavette, int dureeBus, int capacites);

    int getDureeBus();
    std::string getTypeNavette();

    void afficher() override ;
};