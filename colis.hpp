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
    vector<int>&prodEmb;
    vector<int>&listProd;

public:
    Colis(DataBase db) : capacity(0), benefice(0), prodEmb(*(new vector<int>())), listProd(*(new vector<int>())) {
        capacity = db.getCapacityCar();
        for (size_t i = 1; i <= db.getNbPackages(); i++) {
            listProd.push_back(i);
        }
    }

    void glouton_solve (DataBase db) {
        while (listProd.size() > 0) {
            float bestValeur = 0;
            int bestPackage = 0;
            size_t bestIndex = 0;
            for (auto id : listProd) {
                int index = distance(listProd.begin(), find(listProd.begin(), listProd.end(), id));
                tuple<int, int> currentPackage = db.getPackages().find(id)->second;
                cout << "id: " << id << " index: " << index << endl;
                int currentWeight = get<0>(currentPackage);
                if (capacity < currentWeight) {
                    cout << "capacity: " << capacity << " currentWeight: " << currentWeight << endl;
                    listProd.erase(listProd.begin() + index);
                    if (listProd.size() == 0)
                        break;
                    continue;
                }
                int currentBenefice = get<1>(currentPackage);
                float currentValeur = static_cast<float>(currentBenefice) / static_cast<float>(currentWeight);
                cout << currentBenefice << " / " << currentWeight << " = " << currentValeur << endl;
                if (currentValeur > bestValeur) {
                    bestValeur = currentValeur;
                    bestPackage = listProd[index];
                    bestIndex = index;
                }
            }

            cout << "bestPackage: " << bestPackage << endl;
            if (bestPackage == 0) 
                return;
            auto [bestCapacity, bestBenefice] = db.getPackages().find(bestPackage)->second;
            capacity -= bestCapacity;
            benefice += bestBenefice;
            prodEmb.push_back(bestPackage);
            listProd.erase(listProd.begin() + bestIndex);
        } 
    }

    void glouton_solve_random(DataBase db) {
        while (listProd.size() > 0) {
            vector<tuple<int, int>> listProdWeightBenefice;
            int bestBenefice = 0;
            int bestPackage = 0;
            for (size_t i = 0; i < listProd.size(); i++) {
                tuple<int, int> currentPackage = db.getPackages()[listProd[i]];
                int currentWeight = get<0>(currentPackage);
                if (capacity < currentWeight) {
                    listProd.erase(listProd.begin() + i);
                    continue;
                }
                int currentBenefice = get<1>(db.getPackages()[listProd[i]]);
                if (currentBenefice > bestBenefice) {
                    bestBenefice = currentBenefice;
                    bestPackage = listProd[i];
                }
            }

            capacity -= get<0>(db.getPackages()[bestPackage]);
            benefice += get<1>(db.getPackages()[bestPackage]);
            prodEmb.push_back(bestPackage);
            listProd.erase(listProd.begin() + bestPackage - 1);
        } 
    }

    friend ostream &operator<<(ostream &os, const Colis &colis) {
        os << "Colis: " << endl;
        os << "Capacity: " << colis.capacity << endl;
        os << "Benefice: " << colis.benefice << endl;
        os << "ProdEmb: " << endl;
        for (size_t i = 0; i < colis.prodEmb.size(); i++) {
            os << colis.prodEmb[i] << " ";
        }
        os << endl;
        os << "ListProd: " << endl;
        for (size_t i = 0; i < colis.listProd.size(); i++) {
            os << colis.listProd[i] << " ";
        }
        os << endl;
        return os;
    }

};
