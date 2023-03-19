#include <fstream>
constexpr int codeASCIIde_a=97;
constexpr int codeASCIIde_A=65;
constexpr int nombreDeLettres=26;
constexpr int tailleMinNomVille=4;
constexpr int tailleMaxNomVille=12;


// ########################### P2 ###################################

//définit le nb random de villes
int randomCityNumber(){
    int nbCities = 3 + rand()%(3); //allant de 3 à 6 villes
    return nbCities;
}

//cération random des noms des villes
vector<string> randomVecteurVille(int nombreDeVilles){
    vector<string> vect;
    for (int i = 0; i<nombreDeVilles; i++){
        string nameVille;
        int nbLettresNomVille = tailleMinNomVille + rand()%(tailleMaxNomVille-tailleMinNomVille+1);
        for(int j = 0 ; j<nbLettresNomVille; j++){
            if(j==0){
                char Majuscule = codeASCIIde_A + rand()%(nombreDeLettres);
                nameVille += Majuscule;
            }
            else{
                char Minuscule = codeASCIIde_a + rand()%(nombreDeLettres);
                nameVille += Minuscule;
            }
        }
        vect.push_back(nameVille);
    }
    return vect;
}

//création de la matrice des distances
vector<vector<int>> randomDist(int nombreDeVilles){
    vector<vector<int>> dist(nombreDeVilles, vector<int>(nombreDeVilles,0));
    for(int i=0; i<nombreDeVilles; i++){
        for(int j=0 ; j<=i ; j++){
            if(i!=j){ //la diagonale = 0
                int distance = 5 + rand()%(50);
                dist[i][j] = distance;
                dist[j][i] = distance; //car l'aller et le retour ont la même distance
            }
        }

    }
    return dist;
}

// ########################### P1 ###################################

//Définit la capacité de la voiture
int randomCarCapacity(){
    return 20+rand()%(80); //une capacité allant de jusqu'à 100
}

//Définit le nombre de colis disponibles
int randomNbPackages(int nbCity, int max){
    int addition = max + 1 - nbCity;
    return (nbCity+1)+rand()%(addition); // il y a entre nbCity+1 et 10 colis
}

//Définit les différents rapports bénéfices/capacité
map<int,tuple<int,int>> randomMapPackage(int nbPackages){
    map<int,tuple<int,int>> mapa;
    for(int i=0; i<nbPackages ; i++){
        int randomCapa = 2 + rand()%(15);
        int randomBenef = 2 + rand()%(13);
        mapa.insert(pair<int,tuple<int,int>>(i+1,tuple<int,int>(randomCapa,randomBenef)));
    }
    return mapa;
}

// ######################### Export #################################

void exportData(){
    std::ofstream outfile1 ("P1random.txt");
    std::ofstream outfile2 ("P2random.txt");

    //pour P2 - villes
    int nbCity = randomCityNumber();
    outfile2<<nbCity<<endl;
    vector<string> cityName = randomVecteurVille(nbCity);
    for(auto&elem : cityName){
        outfile2<<elem<<endl;
    }
    vector<vector<int>> dist = randomDist(nbCity);
    for(auto&elem1 : dist){
        for(auto&elem2 : elem1){
            outfile2<<elem2<<"\t";
        }
        outfile2<<endl;
    }

    //pour P1 - colis
    int place = randomCarCapacity();
    int colis = randomNbPackages(nbCity,10); //on met 10 à but indicatif, mais il est possible de modifier cette valeur à la hausse
    outfile1<<place<<"\t"<<colis<<endl;
    map<int,tuple<int,int>> packages = randomMapPackage(colis);
    for(auto&elem : packages){
        outfile1<<elem.first<<"\t"<<get<0>(elem.second)<<"\t"<<get<1>(elem.second)<<endl;
    }

    outfile1.close(); outfile2.close();
}