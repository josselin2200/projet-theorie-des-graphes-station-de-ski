#ifndef PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_STATION_H
#define PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_STATION_H

#include <iostream>
#include <vector>
#include <list>
#include "PointGeographique.h"
#include "Trajet.h"
#include "Remontee.h"
#include "Navette.h"
#include "Descente.h"

class Station{
private:
    std::vector<Point*> m_points;
    std::vector<Trajet*> m_trajets;

public:
    Station(std::string cheminFichierGraphe);
    ~Station();
    void afficher() const;
    std::vector<Trajet*> getTrajets();

    /// ---------- FONCTION DE BASE ---------- ///

    void afficherDescentes() const;
    std::vector<Descente*> getDescentes();
    std::vector<Descente*> getDescentePiste(std::string typeDescente);
    void afficherDescentesPiste(std::string typeDescente);

    void afficherRemontees() const;
    std::vector<Remontee*> getRemontees();

    void afficherNavettes() const;
    std::vector<Navette*> getNavettes();

    Trajet* getTrajet(int point1,int point2);
    void afficherToutTrajets();

    Navette* getNavette(int point1,int point2);
    int isNavette(int point1,int point2);

    Descente* getDescente(int point1,int point2);
    int isDescente(int point1,int point2);

    Remontee* getRemontee(int point1,int point2);
    int isRemontee(int point1, int point2);

    float getTemps(int point1, int point2);
    void affichagedestemps();
    void affichertemps(int point);

    std::string getType(int point1, int point2);

    /// ---------- ALGORITHME ---------- ///

    void pointToutTrajet();

    std::vector<int> BFS(int numero_s0, const std::string& type="null");
    std::vector<int> dijkstra(unsigned int s0,const std::string& type="null", const std::string& type2="null");
    std::vector<Trajet*> Kruskal();
    void afficherKruskalEntier(std::vector<Trajet*> tableauKruskal);

    void afficherToutCheminJusque(int a, int b, int chemin[], int& indexChemin);
    void afficherToutChemin();

    std::vector<std::vector<int>> creerMatriceAdj();
    void affichermatrice(std::vector<std::vector<int>> m);
    bool FF_BFS(std::vector<std::vector<int>> &resAdjMatrix, int &source, int &puit, std::vector<int> &parent);
    int fordFulkerson(std::vector< std::vector<int> > &matriceAdj, int &source, int &puit);
    void afficherFordFulkerson();
};

#endif //PROJET_THEORIE_DES_GRAPHES_STATION_DE_SKI_G_STATION_H
