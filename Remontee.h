#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_REMONTEE_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_REMONTEE_H

#include "Trajet.h"

class Remontee: public Trajet{
protected:
    int m_dureeParDenivele;
    std::string m_typeRemontee;
    int m_dureeFixe;

public:
    Remontee(int numero, std::string nomTrajet,int depart,int arrive,int dureeParDenivele, std::string typeRemontee , int dureeFixe,int capacites);

    virtual int getDureeParDenivele();

    std::string getTypeRemontee();
    int getDureeFixe();

    void afficher() override;
};


#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_REMONTEE_H
