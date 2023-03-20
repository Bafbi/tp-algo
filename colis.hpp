#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "database.hpp"

using namespace std;

/// @brief centralize all the data of the problem
class Colis {
private:
    int capacity; 
    int benefice;
    vector<int>& solusPackages;
    map<int, tuple<int,int>>& packages;

public:
    Colis(int capacity, map<int, tuple<int,int>>& packages) : capacity(capacity), benefice(0), solusPackages(*(new vector<int>())), packages(packages) {}

    int getBenefice() const {
        return benefice;
    }

    //Colis::operator=(const Colis &)" (declared implicitly) cannot be referenced -- it is a deleted function
    Colis& operator=(const Colis &colis) {
        this->capacity = colis.capacity;
        this->benefice = colis.benefice;
        this->solusPackages = colis.solusPackages;
        this->packages = colis.packages;
        return *this;
    }

    /// @brief solve the problem with a glouton algorithm
    void glouton_solve(){
    int nbrObjets = packages.size();
    vector<tuple<int, float>> packing; // Tableau dans lequel on va ranger les couples : {numéro du paquet,valeur de bénéfice/consommation de capacité}

    for (int i = 1; i <= nbrObjets; i++) {
        int benef = get<1>(packages.find(i)->second);
        int consoCapa = get<0>(packages.find(i)->second);
        float tmp = (float)benef / (float)consoCapa;

        // cout << "benef : " << benef << " conso : " << consoCapa << " tmp : " << tmp << endl;
        packing.push_back({i, tmp});// On range le couple : {paquet i, benef/conso du paquet} dans tabBsC
    }

    //On trie le tableau en fonction de la valeur benef/conso en mettant les valeurs de tabBsC dans un vector constitué de couples de valeurs


    std::sort(packing.begin(), packing.end(),
              [] (const auto &x, const auto &y) {return get<1>(x) < get<1>(y);});

    // for (int i = 0; i < nbrObjets; i++) {
    //     cout << get<0>(packing[i]) << " " << get<1>(packing[i]) << endl;
    // }

    //On parcourt le tableau trié et on ajoute les paquets dans le colis tant que la capacité du colis n'est pas dépassée
    int i = 0;
    while (capacity > 0 && i < nbrObjets) {
        int consoCapa = get<0>(packages[get<0>(packing[i])]);
        if (capacity - consoCapa >= 0) {
            capacity -= consoCapa;
            benefice += get<1>(packages[get<0>(packing[i])]);
            solusPackages.push_back(get<0>(packing[i]));
        }
        i++;
    }
    }

    /// @brief Solve the problem with a random greedy algorithm
    /// @param seed The seed for the random number generator
    void glouton_random_solve(unsigned int seed) {
        srand(seed);
        int nbrObjets = packages.size();
        vector<tuple<int, float>> packing; // Tableau dans lequel on va ranger les couples : {numéro du paquet,valeur de bénéfice/consommation de capacité}

        for (int i = 1; i <= nbrObjets; i++) {
            int benef = get<1>(packages.find(i)->second);
            int consoCapa = get<0>(packages.find(i)->second);
            float tmp = (float)benef / (float)consoCapa;

            // cout << "benef : " << benef << " conso : " << consoCapa << " tmp : " << tmp << endl;
            packing.push_back({i, tmp});// On range le couple : {paquet i, benef/conso du paquet} dans tabBsC
        }

        //On trie le tableau en fonction de la valeur benef/conso en mettant les valeurs de tabBsC dans un vector constitué de couples de valeurs


        // sort the vector from the highest to the lowest with some randomization
        std::sort(packing.begin(), packing.end(),
                  [] (const auto &x, const auto &y) {return get<1>(x) < get<1>(y);});

        // shuffle two elements in the vector
        for (int i = 0; i < nbrObjets; i++) {
            int j = rand() % nbrObjets;
            int k = rand() % nbrObjets;
            swap(packing[j], packing[k]);
        }
        


        // for (int i = 0; i < nbrObjets; i++) {
        //     cout << get<0>(packing[i]) << " " << get<1>(packing[i]) << endl;
        // }

        //On parcourt le tableau trié et on ajoute les paquets dans le colis tant que la capacité du colis n'est pas dépassée
        int i = 0;
        while (capacity > 0 && i < nbrObjets) {
            int consoCapa = get<0>(packages[get<0>(packing[i])]);
            if (capacity - consoCapa >= 0) {
                capacity -= consoCapa;
                benefice += get<1>(packages[get<0>(packing[i])]);
                solusPackages.push_back(get<0>(packing[i]));
            }
            i++;
        }
    }



    friend ostream& operator<<(ostream& os, const Colis& colis) {
        os << "Colis : " << endl;
        os << "Capacité : " << colis.capacity << endl;
        os << "Bénéfice : " << colis.benefice << endl;
        os << "Solus Paquets : " << endl;
        for (auto& paquet : colis.solusPackages) {
            os << paquet << endl;
        }
        os << "Paquets : " << endl;
        for (auto& paquet : colis.packages) {
            os << paquet.first << " : " << get<0>(paquet.second) << " " << get<1>(paquet.second) << endl;
        }
        return os;
    }

};