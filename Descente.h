#include "Trajet.h"

#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_DESCENTE_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_DESCENTE_H

#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_DESCENTE_H

class Descente: public Trajet{
protected :
    std::string m_typeDescente;
    float m_tempsDescente;

public:
    Descente(int numero, std::string nomTrajet,int depart,int arrive, std::string m_typeDescente, float m_tempsDescente,int capacites);

    std::string getTypeDescente();
    float getTempsDescente();

    void afficher() override;
};