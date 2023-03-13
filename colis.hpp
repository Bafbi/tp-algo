#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "database.hpp"

using namespace std;

class Colis {
private:
    int capacity; 
    int benefice;
    vector<int>& solusPackages;
    map<int, tuple<int,int>>& packages;

public:
    Colis(int capacity, map<int, tuple<int,int>>& packages) : capacity(capacity), benefice(0), solusPackages(*(new vector<int>())), packages(packages) {}

    void glouton_solve(){
    int nbrObjets = packages.size();
    map<int,float> tabBsC; // Tableau dans lequel on va ranger les couples : {numéro du paquet,valeur de bénéfice/consommation de capacité}
    int i = 5;
    while(nbrObjets > 0){//Tant qu'on a des objets à traiter

        float benef = get<1>(packages[nbrObjets]);
        float consoCapa = get<0>(packages[nbrObjets]);
        float tmp = (benef/consoCapa);

        tabBsC[i] = tmp;// On range le couple : {paquet i, benef/conso du paquet} dans tabBsC
        nbrObjets -= 1;
        i-=1;
    }
    //On trie le tableau en fonction de la valeur benef/conso en mettant les valeurs de tabBsC dans un vector constitué de couples de valeurs
    vector<pair<int, float> > tab;
    for (const auto &item : tabBsC) {
        tab.emplace_back(item);
    }

    std::sort(tab.begin(), tab.end(),
              [] (const auto &x, const auto &y) {return x.second < y.second;});


    for(auto element : tab )
    {
        cout << element.first << " et " << element.second << endl;
    }
    tab.pop_back();//Le dernier rang du tab est juste égal à 0 et n'appartient pas aux paquets d'origine donc on l'enlève

    cout << "La voiture a une capacité de : " << capacity << endl;

    while (capacity > 0 && tab.end()->first != 0 && get<0>(packages[tab.end()->first]) != 0){

        if(capacity - get<0>(packages[tab.end()->first]) >= 0) { //Si assez de place dans la voiture
            cout << "On insère le paquet " << tab.end()->first << " qui consomme " << get<0>(packages[tab.end()->first]) << " places dans la voiture." << endl;
            solusPackages.push_back(tab.end()->first);
            capacity -= get<0>(packages[tab.end()->first]);
            cout << "Place restante dans la voiture : " << capacity << endl;

        }
        tab.pop_back();// Si le paquet est trop grand pour être placé dans la voiture, on passe au suivant
    }
}

    friend ostream& operator<<(ostream& os, const Colis& colis) {
        os << "Colis : " << endl;
        os << "Capacité : " << colis.capacity << endl;
        os << "Bénéfice : " << colis.benefice << endl;
        os << "Paquets : " << endl;
        for (auto& paquet : colis.solusPackages) {
            os << paquet << endl;
        }
        return os;
    }

};