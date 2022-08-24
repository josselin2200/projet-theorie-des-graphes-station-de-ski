#include <iostream>
#include "Station.h"
#include "Trajet.h"

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"
//#include "Remontee.h"
#include "iomanip"
//#include <allegro5/allegro.h>

void afficherArborescenceCouleur(size_t s0, const std::vector<int> &arborescence,Station &s) {
    std::cout << std::endl << "Arborescence :" << std::endl;
    float temps=0;
    for (size_t i = 0; i < arborescence.size(); ++i) {
        if (i != s0) {// tant quon arrive pas au sommet de départ
            if (arborescence[i] != -1) {// si le sommet a été découvert
                size_t j = arborescence[i];//recuperer le pred du point darrive
                std::cout << "   " << i << " <--("<<CYN<< s.getTemps(j,i)<<"s "<<NC<<RED<<s.getType(j,i)<<NC<<")--";//on commence par afficher les plus cours chemin avec le sommet le plus petit (0)point arrive
                temps+=s.getTemps(j,i);
                while (j != s0) {//et on remonte jusquà  arriver au sommet de départ
                    std::cout << j << "<--("<<CYN<<s.getTemps(arborescence[j],j)<<"s "<<NC<<RED<<s.getType(arborescence[j],j)<<NC<<")--";
                    temps+=s.getTemps(arborescence[j],j);
                    j = arborescence[j];

                }
                std::cout << j <<"      temps total trajet:  "<<GRN<<temps<<NC<<std::endl;
            }
        }
    }
}
std::vector<float> getTempstotal(size_t s0, const std::vector<int> &arborescence, Station &s) {
    float temps=0;
    std::vector<float> tempss;
    for (size_t i = 0; i < arborescence.size(); ++i) {
        if (i != s0) {
            if (arborescence[i] != -1) {
                size_t j = arborescence[i];
                temps+=s.getTemps(j,i);
                while (j != s0) {
                    temps+=s.getTemps(arborescence[j],j);
                    j = arborescence[j];
                }
                tempss.push_back(temps);
            }
        }
    }
    return tempss;

}

void afficherArborescence(size_t s0, const std::vector<int> &arborescence,Station &s) {
    std::cout << std::endl << "Arborescence :" << std::endl;
    float temps=0;
    for (size_t i = 0; i < arborescence.size(); ++i) {
        if (i != s0) {// tant quon arrive pas au sommet de départ
            if (arborescence[i] != -1) {// si le sommet a été découvert
                size_t j = arborescence[i];//recuperer le pred du point darrive
                std::cout << "   " << i << " <--("<<s.getTemps(j,i)<<"s "<<s.getType(j,i)<<")--";//on commence par afficher les plus cours chemin avec le sommet le plus petit (0)point arrive
                temps+=s.getTemps(j,i);
                while (j != s0) {//et on remonte jusquà  arriver au sommet de départ
                    std::cout << j << "<--("<<s.getTemps(arborescence[j],j)<<"s " << s.getType(arborescence[j],j) <<")--";
                    temps+=s.getTemps(arborescence[j],j);
                    j = arborescence[j];

                }
                std::cout << j <<"      temps total trajet:  "<<temps<<std::endl;
            }
        }
    }
}
void afficherArborescenceparametre(size_t s0, const std::vector<int> &arborescence,Station &s, int i) {
    std::cout << std::endl << "Arborescence :" << std::endl;
    float temps=0;
    if (i != s0) {// tant quon arrive pas au sommet de départ
        if (arborescence[i] != -1) {// si le sommet a été découvert
            size_t j = arborescence[i];//recuperer le pred du point darrive
            std::cout << "   " << i << " <--("<<s.getTemps(j,i)<<"s "<<s.getType(j,i)<<")--";//on commence par afficher les plus cours chemin avec le sommet le plus petit (0)point arrive
            temps+=s.getTemps(j,i);
            while (j != s0) {//et on remonte jusquà  arriver au sommet de départ
                std::cout << j << "<--("<<s.getTemps(arborescence[j],j)<<"s " << s.getType(arborescence[j],j) <<")--";
                temps+=s.getTemps(arborescence[j],j);
                j = arborescence[j];

            }
            std::cout << j <<"      temps total trajet:  "<<temps<<std::endl;
        }
    }

}



int main(){
    Station s{"../data_arcs1.txt"};

    ///EN CONSOLE

    std::cout <<std::endl << "/// -----****   Bienvenu dans la station de ski.   ****----- ///" << std::endl;
    int fin = 0;

    while (!fin)
    {
        std::cout << std::endl << "Que souhaitez-vous faire?" << std::endl
        << "1. S'informer sur un trajet ou sommet." << std::endl
        << "2. Chercher les chemins les plus court a partir d'un sommet initial." << std::endl
        << "3. Chercher le chemin le plus court entre deux sommets." << std::endl
        << "4. Chercher les chemins les plus court avec parametre." << std::endl
        << "5. Chercher tout les chemins entre deux sommet." << std::endl
        << "6. Chercher chemin float." << std::endl
        << "7. Chercher les plus courts chemins en parcourant le moins de sommets possible." << std::endl
        << "8. Chercher le plus court chemin en parcourant le moins de sommets possible." << std::endl
        << "9. Chemin le plus court permettant de faire le tour de la station." << std::endl
        << "10. Quitter" << std::endl;

        int choix = 0;

        std::cin >> choix;

      /*while (0 <= choix || choix >= 10)
        {
             std::cout << "Erreur. Veuillez reessayer." << std::endl;
             std::cin >> choix;
        }*/


      switch (choix){
            case 1: //S'informer sur un trajet ou sommet
            {
                std::cout << "Que cherchez-vous?" << std::endl
                << "1. Point de depart et d'arrive des trajets." << std::endl
                << "2. Tout les trajets d'un sommet (arrivant et partant)." << std::endl
                << "3. Afficher toute la station." << std::endl
                << "4. Afficher uniquement les navettes." << std::endl
                << "5. Afficher uniquement les descentes." << std::endl
                << "6. Afficher uniquement les remontees." << std::endl
                << "7. Afficher uniquement un type de descente." << std::endl;
                int choix2;
                std::cin >> choix2;
                /*while (0 < choix || choix > 2){
                    std::cout << "Erreur. Veuillez reessayer." << std::endl;
                    std::cin >> choix2;
                }*/
                switch (choix2){
                    case 1: //Point de depart et d'arrive des trajets
                    {
                        s.afficherToutTrajets();
                        break;
                    }
                    case 2: //Tout les trajets d'un sommet (arrivant et partant)
                    {
                        s.pointToutTrajet();
                        break;
                    }
                    case 3: //Afficher toute la station.
                    {
                        s.afficher();
                        break;
                    }
                    case 4: //Afficher uniquement les navettes
                    {
                        s.afficherNavettes();
                        break;
                    }
                    case 5: //Afficher uniquement les descentes
                    {
                        s.afficherDescentes();
                        break;
                    }
                    case 6: //Afficher uniquement les remontees
                    {
                        s.afficherRemontees();
                        break;
                    }
                    case 7: //Afficher uniquement un type de trajet
                    {
                        std::string descente;
                        std::cout << "Quel type voulez-vous afficher? (V, B, R, N, KL, SURF)" << std::endl;
                        std::cin >> descente;
                        std::vector<Descente*> p3=s.getDescentePiste(descente);
                        for (auto p: p3){
                            p->afficher();
                        }
                        break;
                    }
                }
                choix = 0;
                break;
            }
            case 2: //Chercher les chemins les plus court a partir d'un sommet initial
            {
                int s0;

                std::cout << "Entrez le sommet initial (Entre 0 et 36)." << std::endl;
                std::cin >> s0;
                /*while (0 < s0 || choix > 36){
                    std::cout << "Erreur. Veuillez reessayer." << std::endl;
                    std::cin >> s0;
                }*/
                afficherArborescenceCouleur(s0, s.dijkstra(s0), s);
                //afficherArborescenceCouleur(s0, s.dijkstra(s0), s); //Pour MAC
                choix = 0;
                break;
            }
            case 3: //Chercher le chemin le plus court entre deux sommets
            {
                int pt1, pt2;
                std::cout << "Entrez les deux sommets (Entre 0 et 36)." << std::endl;
                std::cin >> pt1 >> pt2;
                /*while (0 < pt1 || pt1 > 36 || 0 < pt2 || pt2 > 36){
                    std::cout << "Erreur. Veuillez reessayer." << std::endl;
                    std::cin >> pt1 >> pt2;
                }*/
                afficherArborescenceparametre(pt1, s.dijkstra(pt1), s, pt2);
                choix = 0;
                break;
            }
            case 4: //Chercher les chemins les plus court avec parametre
            {
                int choix2;
                std::cout << "Combien type de piste voulez-vous enlever?" << std::endl
                          << "1. 1." << std::endl
                          << "2. 2." << std::endl;
                std::cin >> choix2;
                switch (choix2) {
                    case 1: {
                        std::string piste;
                        int pt;
                        std::cout
                                << "Entrez le type de piste que vous souhaitez enlever (V,B,R,N,KL,SURF,TPH,TC,TSD,TS,TK,BUS)."
                                << std::endl;
                        std::cin >> piste;
                        std::cout << "Quel est votre point de depart (Entre 0 et 36)." << std::endl;
                        std::cin >> pt;
                        afficherArborescenceCouleur(pt, s.dijkstra(pt, piste), s);
                    }
                    case 2: {
                        std::string piste1;
                        std::string piste2;
                        int pt;
                        std::cout
                                << "Entrez les types de piste que vous souhaitez enlever (V,B,R,N,KL,SURF,TPH,TC,TSD,TS,TK,BUS)."
                                << std::endl;
                        std::cin >> piste1 >> piste2;
                        std::cout << "Quel est votre point de depart (Entre 0 et 36)." << std::endl;
                        std::cin >> pt;
                        afficherArborescenceCouleur(pt, s.dijkstra(pt, piste1, piste2), s);
                        break;
                    }
                }
                choix = 0;
                break;

            }
            case 5: //Chercher tout les chemins entre deux sommet
            {
                s.afficherToutChemin();
                choix = 0;
                break;
            }
            case 6: //Chercher chemin float
            {
                s.afficherFordFulkerson();
                choix = 0;
                break;
            }
            case 7: //Chercher les plus courts chemins en parcourant le moins de sommets possible
            {
                int pt;
                std::cout << "Entrez votre point de depart (Entre 0 et 36)." << std::endl;
                std::cin >> pt;
                afficherArborescenceCouleur(pt, s.BFS(pt), s);
                choix = 0;
                break;
            }
            case 8: //Chercher le plus court chemin en parcourant le moins de sommets possible
            {
                int choix2;
                std::cout << "Avec ou sans parametre? Tapez 1 ou 2." << std::endl;
                std::cin >> choix2;
                switch (choix2)
                {
                    case 1:
                    {
                        std::string type;
                        std::cout << "Par quel type de piste ne souhaitez-vous pas passer par? (V,B,R,N,KL,SURF,TPH,TC,TSD,TS,TK,BUS)" << std::endl;
                        std::cin >> type;
                        int pt1, pt2;
                        std::cout << "Entrez votre point de depart et d'arrive (Entre 0 et 36)." << std::endl;
                        std::cin >> pt1 >> pt2;
                        afficherArborescenceparametre(pt1, s.BFS(pt1, type), s, pt2);
                        break;
                    }
                    case 2:
                    {
                        int pt1, pt2;
                        std::cout << "Entrez votre point de depart et d'arrive (Entre 0 et 36)." << std::endl;
                        std::cin >> pt1 >> pt2;
                        afficherArborescenceparametre(pt1, s.BFS(pt1), s, pt2);
                        break;
                    }
                }
                choix = 0;
                break;
            }
          case 9:
          {
              s.afficherKruskalEntier(s.Kruskal());
              choix = 0;
              break;
          }
            case 10: //Sortie du programme
            {
                fin = 1;
                break;
            }
        }
    }

    /// ALLEGRO
    //affichageInterface();

    return 0;
}