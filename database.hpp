#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include "colis.hpp"

using namespace std;


/// @brief centralize all the data of the problem
class DataBase {
    private:    
        // P1    
        int capacityCar;    
        int nbPackages;    
        map<int,tuple<int,int>>& packages;
        vector<Colis> &solutionsColis; 
        //P2    
        int nbCity;    
        vector<string>& nameCity;    
        vector<vector<int>>& dist;

    public:
        DataBase(string ville_file_name, string colis_file_name) : capacityCar(0), nbPackages(0), packages(*(new map<int,tuple<int,int>>())), solutionsColis(*(new vector<Colis>())), nbCity(0), nameCity(*(new vector<string>())), dist(*(new vector<vector<int>>())) {
            import_ville(ville_file_name);
            import_package(colis_file_name);
        }

        Colis newColis() {
            Colis colis(capacityCar, packages);
            return colis;
        }

        void addColis(Colis colis) {
            this->solutionsColis.push_back(colis);
        }

/// @brief import les données des villes dans la base de données à partir d'un fichier
/// @param file_name 
void import_ville(string file_name) {
    ifstream file(file_name);
    string line;
    int i = 0;
    while (getline(file, line)) {
        if (i == 0) {
            nbCity = stoi(line);
        }
        else if (i <= nbCity) {
            nameCity.push_back(line);
        }
        else {
            istringstream iss(line);
            vector<int> row;
            for (string s; iss >> s;)
                row.push_back(stoi(s));
            dist.push_back(row);
        }
        i++;
    }
}

/// @brief import les données des colis dans la base de données à partir d'un fichier
/// @param file_name
void import_package(string file_name) {
    ifstream file(file_name);
    string line;
    int i = 0;
    while (getline(file, line)) {
        if (i == 0) {
            istringstream iss(line);
            iss >> capacityCar >> nbPackages;
        }
        else {
            istringstream iss(line);
            int id, weight, volume;
            iss >> id >> weight >> volume;
            packages.insert(pair<int,tuple<int,int>>(id, make_tuple(weight, volume)));
        }
        i++;
    }
}

friend ostream &operator<<(ostream &os, const DataBase &db)
{
    os << "capacityCar: " << db.capacityCar << endl;
    os << "nbPackages: " << db.nbPackages << endl;
    for (auto &package : db.packages)
    {
        os << package.first << " " << get<0>(package.second) << " " << get<1>(package.second) << endl;
    }
    os << "nbCity: " << db.nbCity << endl;
    for (auto &ville : db.nameCity)
    {
        os << ville << endl;
    }
    for (auto &row : db.dist)
    {
        for (auto &col : row)
        {
            os << col << " ";
        }
        os << endl;
    }
    return os;
};



};