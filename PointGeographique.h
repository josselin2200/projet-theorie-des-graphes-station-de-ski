#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_POINTGEOGRAPHIQUE_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_POINTGEOGRAPHIQUE_H

#include <iostream>
#include <vector>

class Point{
private:
    std::string m_nomPoint;
    int m_number, m_altitude;
    std::vector<const Point *> m_successeurs;


public:
    Point(std::string nom, int num, int altitude);

    ~Point()= default;

    int getNumber() const;
    int getAltitude() const;
    std::string getNomPoint() const;

    void addSuccesseur(const Point *succ);

    std::vector<const Point *> getSuccesseurs() const;

    void afficher() const;
};

#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_POINTGEOGRAPHIQUE_H