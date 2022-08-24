#include "Station.h"
#include <fstream>
#include <queue>
#include<limits>
#include <utility>
#include <list>
#include <algorithm>
#include "Trajet.h"
//#include "Remontee.h"
//#include "Descente.h"
//#include "Navette.h"
#include "math.h"
#include "iomanip"


    /// ---------- FONCTION DE BASE ---------- ///

Station::Station(std::string cheminFichierGraphe) {
    std::ifstream ifs{cheminFichierGraphe};
    if (!ifs) {
        throw std::runtime_error("Impossible d'ouvrir " + cheminFichierGraphe);
    }
    if (ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de l'orientation du graphe.");
    }
    int ordre;
    ifs >> ordre;//nb sommets
    if (ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de l'ordre du graphe.");
    }
    std::string nomPoint;
    int altitude;
    for (int i = 0; i < ordre; ++i) {
        ifs>>nomPoint>>altitude;
        m_points.push_back(new Point(nomPoint,i,altitude));
    }
    int taille;
    ifs >> taille;
    if (ifs.fail()) {
        throw std::runtime_error("Probleme de lecture de la taille du graphe.");
    }

    std::string nom,type;
    int s2;
    int s1;
    for (int i = 0; i < taille; ++i) {
        ifs>>nom>>type>>s1>>s2;
        s1=s1-1;
        s2=s2-1;


        if (ifs.fail()) {
            throw std::runtime_error("Probleme de lecture d'un.e arc/arete.");
        }
        m_points[s1]->addSuccesseur(m_points[s2]);//ajouts des successeurs sans stocker les données qui sont dans les aretes


        ///remontée
        if(type=="TPH"){//téléphrérique
            m_trajets.push_back(new Remontee(i,nom,s1,s2,2,"TPH",4,1200));
        }
        if(type=="TC"){//téléCABINE
            m_trajets.push_back(new Remontee(i,nom,s1,s2,3,"TC",2,2200));
        }
        if(type=="TSD"){//télésiege debrayage
            m_trajets.push_back(new Remontee(i,nom,s1,s2,3,"TSD",1,2500));
        }
        if(type=="TS"){//téléphrérique
            m_trajets.push_back(new Remontee(i,nom,s1,s2,4,"TS",1,1800));
        }
        if(type=="TK"){//téléski
            m_trajets.push_back(new Remontee(i,nom,s1,s2,4,"TK",1,800));
        }

        //descente
        if(type=="V"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"V",5,70));
        }
        if(type=="B"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"B",4,60));
        }
        if(type=="R"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"R",3,50));
        }
        if(type=="N"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"N",2,40));
        }
        if(type=="KL"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"KL",0.17,30));
        }
        if(type=="SURF"){
            m_trajets.push_back(new Descente(i,nom,s1,s2,"SURF",10,20));
        }

        //navette
        if(type=="BUS"){
            if(nom=="navette1600-1800" ){
                m_trajets.push_back(new Navette(i,nom,s1,s2,"BUS",30,300));
            }
            if(nom=="navette1800-1600"){
                m_trajets.push_back(new Navette(i,nom,s1,s2,"BUS",30,300));
            }
            if(nom=="navette1600-2000"){
                m_trajets.push_back(new Navette(i,nom,s1,s2,"BUS",40,300));
            }
            if(nom=="navette2000-1600"){
                m_trajets.push_back(new Navette(i,nom,s1,s2,"BUS",40,300));
            }
        }

    }



}

Station::~Station() {
    for (auto addrSommet : m_points) {
        delete addrSommet;
    }
    for (auto addrTrajet : m_trajets){
        delete addrTrajet;
    }
}

void Station::afficher() const {
    std::cout << std::endl << "Station ";
    //std::cout << (m_estOriente ? "oriente" : "non oriente") << std::endl;
    std::cout << "Ordre : " << m_points.size() << std::endl;
    std::cout << "Liste d'adjacences : " << std::endl;
    for (auto addrSommet : m_points) {
        addrSommet->afficher();
        std::cout << std::endl;

    }
    int p=0;
    std::cout << std::endl;
    for (auto trajet:m_trajets) {
        trajet->afficher();

    }

}

void Station::afficherRemontees() const {
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Remontee*>(m_trajets[i]);//remonte
        if(r){
            r->afficher();
        }
    }
}
std::vector<Remontee *> Station::getRemontees() {
    std::vector<Remontee*> Remontees;
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Remontee*>(m_trajets[i]);//remonte
        if(r){
            Remontees.push_back(r);
        }
    }
    return Remontees;
}
std::vector<Descente *> Station::getDescentes()  {
    std::vector<Descente*> Descentes;
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Descente*>(m_trajets[i]);//remonte
        if(r){
            Descentes.push_back(r);
        }

    }
    return Descentes;
}

void Station::afficherDescentes() const {
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Descente*>(m_trajets[i]);//remonte
        if(r){
            r->afficher();
        }
    }
}

std::vector<Trajet *> Station::getTrajets() {
    return m_trajets;
}

void Station::afficherNavettes() const {
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Navette*>(m_trajets[i]);//remonte
        if(r){
            r->afficher();
        }
    }
}
std::vector<Navette *> Station::getNavettes()  {
    std::vector<Navette*> Navettes;
    for(int i=0;i<m_trajets.size();i++) {
        auto * r= dynamic_cast<Navette*>(m_trajets[i]);//remonte
        if(r){
            Navettes.push_back(r);
        }

    }
    return Navettes;
}

std::vector<Descente *> Station::getDescentePiste(std::string typeDescente) {
    auto Descentes=getDescentes();
    std::vector<Descente*> DescentesSelectionnes;
    for(auto descente:Descentes){
        if(descente->getTypeDescente()==typeDescente){
            DescentesSelectionnes.push_back(descente);
        }
    }
    return DescentesSelectionnes;
}
void Station::afficherDescentesPiste(std::string typeDescente) {
    std::vector<Descente*> p3=getDescentePiste(std::move(typeDescente));// retourne
    for(auto pp:p3){
        pp->afficher();
    }
}

//Récupérer le trajet entre 2 points
Trajet * Station::getTrajet(int point1, int point2) {
    for(auto trajet : m_trajets){
        //int a = trajet->getDepart() ;
        //int b = trajet->getArrive();

        if((trajet->getDepart()== point1) && (trajet->getArrive() == point2)){ ///PB
            //std::cout << "le trajet existe" << std::endl;
            //trajet->afficher();
            return trajet;
        }
    }
    //std::cout << "le trajet n'existe pas" << std::endl;
    return nullptr;
}

void Station::afficherToutTrajets() {
    for(auto trajet:m_trajets){
        trajet->afficher();
    }
}

Descente * Station::getDescente(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart() == point1 && trajet->getArrive()==point2){
            return dynamic_cast<Descente *>(trajet);
        }
    }
    return nullptr;
}
Remontee * Station::getRemontee(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart()==point1 && trajet->getArrive()==point2){
            return dynamic_cast<Remontee *>(trajet);
        }
    }
    return nullptr;
}
Navette * Station::getNavette(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart()==point1 && trajet->getArrive()==point2){
            return dynamic_cast<Navette *>(trajet);
        }
    }
    return nullptr;
}
int Station::isNavette(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart()==point1 && trajet->getArrive()==point2){
            if(dynamic_cast<Navette *>(trajet)){
                return 1;
            }else{
                return 0;
            }
        }
    }
}
int Station::isDescente(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart()==point1 && trajet->getArrive()==point2){
            if(dynamic_cast<Descente *>(trajet)){
                return 1;
            }else{
                return 0;
            }
        }
    }
}
int Station::isRemontee(int point1, int point2) {
    for(auto trajet:m_trajets){
        if(trajet->getDepart()==point1 && trajet->getArrive()==point2){
            if(dynamic_cast<Remontee *>(trajet)){
                return 1;
            }else{
                return 0;
            }
        }
    }
}


float Station::getTemps(int point1,int point2) {
    int pt1=getTrajet(point1,point2)->getDepart();
    int pt2=getTrajet(point1,point2)->getArrive();
    //float distance=abs(m_points[pt1-1]->getAltitude()-m_points[pt2-1]->getAltitude());
    float distance=abs(m_points[pt1]->getAltitude()-m_points[pt2]->getAltitude());
    if(isRemontee(point1,point2)==1){
        float tps=getRemontee(point1,point2)->getDureeFixe()+((getRemontee(point1,point2)->getDureeParDenivele()*distance)/100);
        return tps;
    }
    else if(isDescente(point1,point2)==1){
        float tps=(getDescente(point1,point2)->getTempsDescente()*distance)/100;
        return tps;
    }
    else if(isNavette(point1,point2)==1){
        return getNavette(point1,point2)->getDureeBus();
    }
}
std::string Station::getType(int point1, int point2) {
    if(isRemontee(point1,point2)==1){
        return getRemontee(point1,point2)->getTypeRemontee();
    }
    if(isDescente(point1,point2)==1){
        return getDescente(point1,point2)->getTypeDescente();
    }
    if(isNavette(point1,point2)==1){
        return getNavette(point1,point2)->getTypeNavette();
    }
    else{
        return "null ";
    }
}

void Station::affichagedestemps() {
    for(auto trajet:m_trajets){
        int arrive=trajet->getArrive();
        int depart=trajet->getDepart();
        std::cout<<arrive<<"<--("<<getTemps(depart,arrive)<<")--"<<depart<<std::endl;
    }
}
void Station::affichertemps(int point) {
    for(auto trajet:m_trajets){
        int arrive=trajet->getArrive();
        int depart=trajet->getDepart();
        if(depart==point){
            std::cout<<arrive<<"<--("<<getTemps(depart,arrive)<<")--"<<depart<<std::endl;
        }
    }
}


    /// ---------- ALGORITHME ---------- ///


    std::vector<int> Station::BFS(int numero_s0, const std::string& type) {
        std::vector<int> predecesseurs((int) m_points.size(), -1);//(-1) equivalent a ?//stocke les predeceseur
        std::vector<int> couleurs((int) m_points.size(), 0);//(-1) equivalent a ?
        std::queue<const Point*> file;//qui stock les sommets a visiter
        file.push(m_points[numero_s0]);
        couleurs[numero_s0]=1;
        predecesseurs[numero_s0]=-2;
        const Point* s= nullptr;
        while (!file.empty()){//voudra dire qy el'on a plus de sommets a visiter
            s=file.front();//stock sommet numero_s0
            file.pop();//comme on va visiter c sommets on peut supprimer le(sommet numero_s0) de la file
            if(type=="null"){
                for(auto ptrvoisin:s->getSuccesseurs()){
                    if(couleurs[ptrvoisin->getNumber()]==0){// si ce voisin à pour couleur 0
                        file.push(ptrvoisin);//on a decouvert un nouveau voisin donc il faudra le visiter après donc on le rajoute à la file
                        couleurs[ptrvoisin->getNumber()]=1;//si on l'a découvert il devient gris(1)
                        predecesseurs[ptrvoisin->getNumber()]=s->getNumber();//stock celui qui la découvert
                    }
                }// si on sort de la boucle on a visite tous les voisins de s donc il peut etre noir (2)
            } else{
                for(auto ptrvoisin:s->getSuccesseurs() ){
                    if(couleurs[ptrvoisin->getNumber()]==0 && type!=getType(s->getNumber(),ptrvoisin->getNumber()) ){// si ce voisin à pour couleur 0
                        file.push(ptrvoisin);//on a decouvert un nouveau voisin donc il faudra le visiter après donc on le rajoute à la file
                        couleurs[ptrvoisin->getNumber()]=1;//si on l'a découvert il devient gris(1)
                        predecesseurs[ptrvoisin->getNumber()]=s->getNumber();//stock celui qui la découvert
                    }
                }// si on sort de la boucle on a visite tous les voisins de s donc il peut etre noir (2)
            }
            couleurs[s->getNumber()]=2;
        }
        return predecesseurs;

    }

void Station::pointToutTrajet(){ //Affiche les trajets qui partent ou arrivent au sommet choisit
    int so;
    std::cout << "Pour quel sommet souhaitez-vous voir les trajets qui en partent et qui permettent d'y arriver?" << std::endl;
    std::cin >> so;
    std::cout << "Les trajets qui partent du sommet " << so << " sont:" << std::endl;
    for (int i = 0; i < m_points.size(); i++){
        for(auto trajet:m_trajets){
            if(trajet->getDepart() == so && trajet->getArrive() == i){
                //std::cout << i << std::endl;
                trajet->afficher();
            }
        }
    }
    std::cout << std::endl;
    std::cout << "Les trajets suivants permettent d'acceder au sommet " << so <<":" << std::endl;
    for (int i = 0; i < m_points.size(); i++){
        for(auto trajet:m_trajets){
            if(trajet->getDepart() == i && trajet->getArrive() == so){
                //std::cout << i << std::endl;
                trajet->afficher();
            }
        }
    }
}


std::vector<int> Station::dijkstra(unsigned int s0,const std::string& type,const std::string& type2)  {
    std::cout << std::endl << std::endl << "LANCEMENT DE DIJKSTRA TEMPS :" << std::endl;
    // INITIALISATION
    int nbMarques = 0;
    std::vector<int> couleurs(m_points.size(), 0); // tous les sommets sont non marqués
    std::vector<int> distances(m_points.size(),std::numeric_limits<int>::max()); // tous les sommets sont supposés à une distance infinie de s0;
    distances[s0] = 0; // s0 est à une distance de 0 de lui même.
    std::vector<int> predecesseurs(m_points.size(), -1); // nous ne connaissons pas encore les prédécesseurs , celui qui la decouvert
    predecesseurs[s0] = 0; // on pourrait laisser -1, s0 n'a pas vraiment de prédécesseur car il s'agit du sommet initial

    do {
        int s = 0;//sommet sélectionné
        float distanceMini = std::numeric_limits<float >::max();
        std::cout << std::endl << std::endl;
        for (size_t i = 0; i < distances.size(); i++) {
            std::cout << couleurs[i] << " "
                      << ((distances[i] == std::numeric_limits<int>::max()) ? "Inf" : std::to_string(
                              distances[i])) << " "
                      << (predecesseurs[i] == -1 ? "?" : std::to_string(//si le pred est a -1 on le connait pas donc ? sinon on l'écrit
                              predecesseurs[i])) << "    ";
            if (couleurs[i] == 0 && distances[i] < distanceMini) {//parcourt chaque sommet si il est non marqué et inférieur a toutes les autres distance
                distanceMini = distances[i];
                s = i;
            }
        }
        std::cout << std::endl << std::endl;

        couleurs[s] = 1;
        nbMarques++;
        std::cout << "Sommet choisi : " << s << " (plus petite distance depuis le sommet " << s0 << " (" << distanceMini
                  << ")"
                  << "). Ses successeurs non marques sont :" << std::endl;
        for (auto successeur: m_points[s]->getSuccesseurs()) {
            float temps;
            temps = getTemps(m_points[s]->getNumber(),m_points[successeur->getNumber()]->getNumber());// temps entre le sommet s et son successeur
            if (couleurs[successeur->getNumber()] == 0 && type!=getType(m_points[s]->getNumber(),successeur->getNumber()) && type2!=getType(m_points[s]->getNumber(),successeur->getNumber())) {//succeseur non marqué
                std::cout << "    - " << successeur->getNumber() << " : "
                          << "Si considere, la distance deviendrait " << distances[s] << " + "
                          << temps << " = " << distances[s] + temps
                          << ". Ce qui est "
                          << ((distances[s] + temps < distances[successeur->getNumber()]) ? "inferieur"
                                                                                          : "superieur")
                          << " a sa distance actuelle de "
                          << distances[successeur->getNumber()] << ". Donc : "
                          << ((distances[s] + temps < distances[successeur->getNumber()]) ? "MAJ"
                                                                                          : "NON MAJ")
                          << std::endl;
                if (distances[s] + temps < distances[successeur->getNumber()]) {//si la distance depuis le sommet découvert + temps pour aller à son succeseur est inférieur
                    distances[successeur->getNumber()] = distances[s] + temps;// au temps du succeseur actuel on met a jour
                    predecesseurs[successeur->getNumber()] = s;//et on note son predecesseur
                }
            }

        }
    } while (nbMarques < m_points.size());

    std::cout << std::endl << "FIN DE DIJKSTRA." << std::endl;
    return predecesseurs;//pred[x]=y// le sommet x a pour prédecesseur y
}

///Passer par tous les trajets en prenant le moins de temps possible
std::vector<Trajet*> Station::Kruskal(){
    //Création de l'arbre
    std::vector<Trajet*> kruskal;

    int nb_aretes = 0;

    //Initialisation des numeros des composantes connexes
    std::vector<int> composanteConnexe;
    for(int c = 0; c < m_points.size(); c++){
        composanteConnexe.push_back(c);
    }

    //Trier les arêtes par ordre croissant
    std::sort(m_trajets.begin(), m_trajets.end(), [](Trajet* a, Trajet* b){
        return a->getTempsTrajet() < b->getTempsTrajet();
    });

    while(nb_aretes <= m_points.size()-1){
        for(int i = 0; i < m_trajets.size(); i++) { //on parcourt toutes les aretes du graphe, qui ont été trié

            if(composanteConnexe[m_trajets[i]->getDepart()] != composanteConnexe[m_trajets[i]->getArrive()]){

                //On ajoute l'arete a l'arbre
                kruskal.push_back(m_trajets[i]);

                //On change le numero de CC des sommets qui ont le meme que notre extrémité 2
                for (int j = 0; j < m_points.size(); j++){
                    if (composanteConnexe[j]==composanteConnexe[m_trajets[i]->getArrive()]){
                        composanteConnexe[j]=composanteConnexe[m_trajets[i]->getDepart()];
                    }
                }
                //On change le numero de CC pour que les deux extremites aient le meme
                composanteConnexe[m_trajets[i]->getArrive()] = composanteConnexe[m_trajets[i]->getDepart()];
                nb_aretes++;
            }
        }
    }
    return kruskal;
}

void Station::afficherKruskalEntier(std::vector<Trajet*> tableauKruskal) {
    //On affiche les aretes de l'arbre couvrant
    for(auto p : tableauKruskal){
        p->afficher();
        std::cout << std::endl;
    }
    //On calcule le temps total
    double tempsTotal = 0;
    for(auto p : tableauKruskal){
        tempsTotal = tempsTotal + getTemps(p->getDepart(), p->getArrive());; //c'est bien getTempsTrajet() qu'il faut utiliser?

    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Le temps total pour parcourir toute la station est de " << tempsTotal << " minutes." <<std::endl;
}


void Station::afficherToutChemin() {

    ///----------INITIALISATION----------///

    int pointDepart, pointArrivee;
    std::cout << "De quel point souhaitez-vous partir?" <<std::endl;
    std::cin >> pointDepart;

    std::cout << "Vous avez choisi comme point de depart: " << pointDepart << std::endl;

    std::cout << "A quel point souhaitez-vous arriver?" <<std::endl;
    std::cin >> pointArrivee;
    std::cout << "Vous avez choisi comme point d'arrivee: " << pointArrivee << std::endl;

    //On crée un chemin qui pourrait contenir tous les points de la station
    int* chemin = new int[m_points.size()];
    int chemin_index = 0;

    afficherToutCheminJusque(pointDepart, pointArrivee, chemin, chemin_index);
}

void Station::afficherToutCheminJusque(int depart, int arrivee, int chemin[], int& index_chemin) {

    //Initialisation des points visités : aucun
    std::vector<bool> visite(m_points.size(), false);

    visite[depart] = true;
    chemin[index_chemin] = depart; //u est le premier sommet du chemin
    index_chemin++; // On passe au sommet suivant du chemin


    if (depart == arrivee) {// si départ = arrivée
        std::cout << "Voici un chemin pour aller de" << depart << "a " << arrivee << ": " << std::endl;
        for (int i = 0; i < index_chemin; i++) { //On affiche tous les sommets du chemin
            m_points[chemin[i]]->afficher();
        }
        ///AMELIORATION: afficher les trajets entre les points avec leur types et temps ect
    } else // si on a pas atteint l'arrivée
    {
        for (int i = 0; i <= m_points.size() ; i++){ //parcours du vecteur points
            //si un trajet existe entre u et i et que i n'a pas encore été visité
            ///AMELIORATION: garder le trajet pour l'afficher plus tard
            if((getTrajet(depart, i) != nullptr) && !visite[i]){ ///PB : access violation
                std::cout << "rentre dans le if" << std::endl;
                afficherToutCheminJusque(i, arrivee, chemin, index_chemin); ///récursivité infinie
            }else if(visite[i] == true){
                std::cout << "point deja visite" << std::endl;
            }
        }
    }
    index_chemin--;
    visite[depart] = false;
}


///ford fulkerson
std::vector<std::vector<int> > Station::creerMatriceAdj() {
    std::vector<std::vector<int>> matAdj/*(m_points.size(), std::vector< int >( m_points.size() ))*/ ;
    for(int i=0; i< m_points.size();i++){
        std::vector<int> lignes;
        matAdj.push_back(lignes);//vecteur de lignes (matrice)
        for(int j=0;j<m_points.size();j++){
            matAdj[i].push_back(0);

        }
    }
    for(auto trajet:m_trajets){
        if( matAdj[trajet->getDepart()][trajet->getArrive()]==0 || matAdj[trajet->getDepart()][trajet->getArrive()]<trajet->getCapacite())//si il ya plusieurs chemins...
        matAdj[trajet->getDepart()][trajet->getArrive()]=trajet->getCapacite();//... entre le depart et larrive on chosit celui qui a la capacite max

    }
    return matAdj;
}
void Station::affichermatrice(std::vector<std::vector<int> > m) {
    int p = 0;
    std::cout<<"lire le numero de la ligne pour avoir le sommet de depart depart et le numero de la colonne pour le sommet d'arrive"<<std::endl;
    std::cout<<"depart | arrive:"<<std::endl<<"       | ";
    for (int k = 0; k < m_points.size(); ++k) {
        if(k<10){
            std::cout<<k<<"    ";
        }else{
            std::cout<<k<<"   ";
        }
    }
    std::cout<<std::endl<<"_______ ";
    for (int k = 0; k < m_points.size(); ++k) {
        std::cout<<"____ ";
    }
    std::cout<<std::endl;
    for(int i=0;i<m_points.size();i++){//lignes
        if(i<10){
            std::cout<<i<<"      | ";
        }else{
            std::cout<<i<<"     | ";
        }
        for(int j=0;j<m_points.size();j++){
            if( m[i][j]<10){
                std::cout<<m[i][j]<<"    ";//affiche la ligne
            }
            if(m[i][j]>=10 && m[i][j]<100){
                std::cout<<m[i][j]<<"   ";//affiche la ligne
            }
            if(m[i][j]>=100 && m[i][j]<1000){
                std::cout<<m[i][j]<<"  ";//affiche la ligne
            }
            if(m[i][j]>=1000){
                std::cout<<m[i][j]<<" ";//affiche la ligne
            }
            if(m[i][j]!=0){
                p++;
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl<<"il y a "<<p<<" trajets reliant chaque sommets en elevant les trajets supplementaires entre 2 points"<<std::endl;
}

bool Station::FF_BFS(std::vector< std::vector<int> > &resAdjMatrice, int &source, int &puit, std::vector<int> &parent){
    // retourne si il y a un chemin ou non pour aller d'une source a un puit
    int n = resAdjMatrice.size();// taille du vecteur qui stocke des vecteur , sa taille == nombre de lignes de la matrice
    std::vector<bool> visite(n, false);//personne a ete visite
    std::queue<int> q;//stocke les sommets a visite
    q.push(source);//source stocke pour etre visite apres
    visite[source] = true;//noté comme visité
    parent[source] = -1;// decouvert par personne comme c'est une source
    while(!q.empty())//tant qu'il reste des sommets a decouvrir
    {

        int u = q.front();//recupere le premier de la file(pour quon decouvre ses voisin)...
        q.pop();//pour le supprimer juste apres car on va le visite par la suite
        for(int i = 0; i < n; i++)
        {
            int v = i;
            int capacite = resAdjMatrice[u][v];//u point de depart quon veut visiter(lignes), on parcourt toutes les colonnes (v) (tous les points darrive possible)

            if(!visite[v] && capacite > 0)// si le sommet darrive(v) est un voisin de u => il a donc une capacite >0, et si il na pas deja ete visite
            {
                q.push(v);//alors on lajoute a la liste pour le visiter apres
                parent[v] = u;//donc on peut aller de u a v, celui qui a decouvert v est u
                visite[v] = true;
            }
        }
    }
    /*if(visite[puit]==true){
        return true;//si le puit a ete visite on retourne vrai cad quil existe un chemin pour aller de la source au puit
    }
    return false;*/
    return visite[puit];//equivalent
}

int Station::fordFulkerson(std::vector< std::vector<int> > &matriceAdj, int &source, int &puit)//FF retourne le flot max entre une source et un puit(entre 2 pts)
{
    int flotMax = 0;
    std::vector< std::vector<int> > resAdjMatrice;//graphe residuel, matrice vide ,
    int n = matriceAdj.size();//recupere le nombre de lignes de la matrice
    for(int i = 0; i < n; i++)
    {
        std::vector<int> lignes;
        resAdjMatrice.push_back(lignes);
        for(int j = 0; j < matriceAdj[i].size(); j++)
        {
            resAdjMatrice[i].push_back(matriceAdj[i][j]);// recree le graphe de base que l'on va modifier
        }
    }
    std::vector<int> parent;
    parent.reserve(n);
    for(int i = 0; i < n; i++)
    {
        parent.push_back(-1);//pour linstant chaque sommet na pas de parent cad quils nont pas ete decouvert
    }
    while(FF_BFS(resAdjMatrice, source, puit, parent))// tant qu'il y a des chemins a augmenter on continue
    {
        int flotChemin = 100000;
        int v = puit;
        while(v != source)//tant que le puit nest pas la source ca veut dire que l'on est pas arrive
        {
            int u = parent[v];// on parcourt du puit pour remonter a la source
            int capacite = resAdjMatrice[u][v];
            flotChemin = std::min(flotChemin, capacite);//en recuperant le flot minimal qui sera augmente apres
            v = u;
        }
        v = puit;
        while(v != source)
        {
            int u = parent[v];//modif du chemin avec laugmentztion en plus , on ajoute cette augmentation a chaque arete du chemin
            resAdjMatrice[u][v] -= flotChemin;
            resAdjMatrice[v][u] += flotChemin;
            v = u;
        }
        flotMax += flotChemin;
    }

    return flotMax;
}
void Station::afficherFordFulkerson() {
    std::vector< std::vector<int> > adjMatrix(m_points.size(), std::vector< int >(m_points.size() ));
    adjMatrix = creerMatriceAdj();
    affichermatrice(adjMatrix);
    std::vector<int> parent(37,0);
    for(int i = 0; i < m_points.size(); i++){
        for(int j = 0; j < m_points.size(); j++){
            int source = i;
            int sink = j;
            if(i == j) { continue; }

            if(getTrajet(source,sink)!= nullptr){
                std::cout <<" le flot maximal de " << source << " a " << sink << " est: ";
                std::cout << fordFulkerson(adjMatrix, source, sink) ;
                std::cout<<"    flot initial: "<<getTrajet(source,sink)->getCapacite();
                std::cout<<"    on peut donc augmenter le trajet de :"<<fordFulkerson(adjMatrix, source, sink)-getTrajet(source,sink)->getCapacite()<<std::endl;
            }
        }

    }
}