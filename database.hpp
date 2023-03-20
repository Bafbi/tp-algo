#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include "colis.hpp"
#include "ville.hpp"

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
        vector<Trajet> &solutionsTrajet;

    public:
        DataBase(string ville_file_name, string colis_file_name) : capacityCar(0), nbPackages(0), packages(*(new map<int,tuple<int,int>>())), solutionsColis(*(new vector<Colis>())), nbCity(0), nameCity(*(new vector<string>())), dist(*(new vector<vector<int>>())), solutionsTrajet(*(new vector<Trajet>())) {
            import_ville(ville_file_name);
            import_package(colis_file_name);
        }

        /// @brief import les données des colis dans la base de données à partir d'un fichier
        /// @return A new colis with the data of the database
        Colis newColis() {
            Colis colis(capacityCar, packages);
            return colis;
        }

        /// @brief add a solved colis to the database
        /// @param colis 
        void addColis(Colis colis) {
            this->solutionsColis.push_back(colis);
        }

        /// @brief create a new trajet with the data for the resolution of the problem
        /// @return A new trajet with the data of the database
        Trajet newTrajet() {
            Trajet trajet(nameCity, dist);
            return trajet;
        }

        /// @brief add a solved trajet to the database
        /// @param trajet 
        void addTrajet(Trajet trajet) {
            this->solutionsTrajet.push_back(trajet);
        }

/// @brief import les données des villes dans la base de données à partir d'un fichier
/// @param file_name le nom du fichier
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
/// @param file_name le nom du fichier
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

/// @brief export tous les résultats dans un fichier
/// @param namefile le nom du fichier
void export_results(string namefile){
    // create file if doesn't exist then export
    ofstream file(namefile);
    for (auto &colis : solutionsColis)
    {
        file << colis << endl;
    }
    for (auto &trajet : solutionsTrajet)
    {
        file << trajet << endl;
    }
}

/// @brief export le meilleur résultat de chaque problème dans un fichier
/// @param namefile le nom du fichier
void export_best_results(string namefile){
    // create file if doesn't exist then export
    ofstream file(namefile);
    file << findBestColis() << endl;
    file << findBestTrajet() << endl;
}

/// @brief find the best colis in the solved colis list
/// @return the best colis
Colis& findBestColis() {
    Colis* bestColis = nullptr;
    int bestBenefice = 0;
    for (Colis& colis : solutionsColis) {
        if (colis.getBenefice() > bestBenefice) {
            bestBenefice = colis.getBenefice();
            bestColis = &colis;
        }
    }
    if (bestColis == nullptr) {
        throw std::logic_error("No best colis found");
    }
    return *bestColis;
}

/// @brief find the best trajet in the solved trajet list
/// @return the best trajet
Trajet& findBestTrajet() {
    int minDist = INT_MAX;
    Trajet* bestTrajet = nullptr;

    for (Trajet& trajet : solutionsTrajet) {
        if (trajet.getDistance() < minDist) {
            minDist = trajet.getDistance();
            bestTrajet = &trajet;
        }
    }

    if (bestTrajet == nullptr) {
        throw runtime_error("No solutions found");
    }

    return *bestTrajet;
}

/// @brief print the database
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