#include "PointGeographique.h"
#include <utility>


Point::Point(std::string nom, int num, int altitude)
        : m_nomPoint{std::move(nom)}, m_number{num}, m_altitude{altitude}
{}


int Point::getNumber() const {
    return m_number;
}

int Point::getAltitude() const {
    return m_altitude;
}

std::string Point::getNomPoint() const {
    return m_nomPoint;
}

 std::vector<const Point *> Point::getSuccesseurs() const {
    return m_successeurs;

}
void Point::addSuccesseur(const Point *succ ) {
    m_successeurs.push_back(succ);
}

void Point::afficher() const{
    std::cout << " Point numero " << m_number << ". ";
    std::cout << "Nom: "<< m_nomPoint << ", altitude: " << m_altitude << " m de hauteur" << std::endl;

    for (auto addrSommet : m_successeurs) {
        std::cout << m_number << "---->" << addrSommet->getNumber() << std::endl;
    }
}


