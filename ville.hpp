#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "database.hpp"

using namespace std;

/// @brief centralize all the data of the problem
class Trajet {
private:
    int distance;
    vector<string> path;
    vector<string> villes;
    vector<vector<int>>& dist;

public:
    Trajet(vector<string> villes, vector<vector<int>>& dist) : distance(0), path(*(new vector<string>())), villes(villes), dist(dist) {}

    int getDistance() {
        return distance;
    }

    Trajet& operator=(const Trajet& trajet) {
        distance = trajet.distance;
        path = trajet.path;
        villes = trajet.villes;
        dist = trajet.dist;
        return *this;
    }

    /// @brief solve the problem with a glouton algorithm
    /// @param start_index the index of the start city
    void glouton_solve(int start_index) {
        
        // On récupère les informations 
        auto nbCity = dist.size();

        // on initialise le vecteur contenant les villes non présente dans le chemin
        vector<int> index;
        // index_count représente le nombre de velles non présente dans le chemin
        int index_count = nbCity - 1;
        // path_dist représente la taille totale du chemin
        int path_dist = 0;
        // city correspond à l'index de la ville actuelle, au début elle vaut start_index
        int city = start_index;
        // On place la ville de départ
        path.push_back(villes[city]);

        // On rempli index
        for (int i = 0; i < nbCity; i++) {
            // lorsque l'on veut mettre la ville de départ, on passe le tour de boucle
            if (start_index == i) {
                continue;
            }
            index.push_back(i);
        }

        // min représente la distance minimale par rapport à la ville actuelle
        int min;
        // min_index représente l'index de cette ville
        int min_index;

        // Dans cette boucle nous allons renplir le chemin, comme nous avons déjà placer la première ville, il en reste nbCity - 1 à placer
        for (int i = 0; i < nbCity - 1; i++) {

            // Au début on défini la plus petite villes comme étant celle d'indice 0 dans index
            min = dist[city][index[0]];
            min_index = 0;

            // Pas besoin de faire de tour de boucle s'il n'y a plus qu'une ville
            if (index_count > 1) {
                // On regarde chaque ville restante
                for (int j = 1; j < index_count; j++) {
                    // Pour chaque ville on regarde la distance par rapport à celle actuelle
                    // si la distance est plus petite
                    if (dist[city][index[j]] < min) {
                        // On modifie la ville la plus proche
                        min = dist[city][index[j]];
                        min_index = j;
                    }
                }
            }

            // on augmente la taille du chemin
            path_dist += min;

            // On change la ville actuelle
            city = index[min_index];

            // On ajoute la ville au chemin
            path.push_back(villes[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(villes[start_index]);

        // On met à jour les attributs de la classe
        distance = path_dist;

    }

    /////////////////////////////////////////////////////////////////////////////////

    /// @brief solve the problem with a glouton random algorithm
    /// @param start_index the index of the start city
    /// @param seed the seed of the random number generator
    /// @return void
    auto glouton_random_solve(int start_index, unsigned int seed) {
        srand(seed);

        auto nbCity = dist.size();

        // on initialise le vecteur contenant les villes non présente dans le chemin
        vector<int> index;
        // index_count représente le nombre de velles non présente dans le chemin
        int index_count = nbCity - 1;
        // path_dist représente la taille totale du chemin
        int path_dist = 0;
        // city correspond à l'index de la ville actuelle, au début elle vaut start_index
        int city = start_index;
        // On place la ville de départ
        path.push_back(villes[city]);

        // On rempli index
        for (int i = 0; i < nbCity; i++) {
            // lorsque l'on veut mettre la ville de départ, on passe le tour de boucle
            if (start_index == i) {
                continue;
            }
            index.push_back(i);
        }

        // min représente la distance minimale par rapport à la ville actuelle
        int min;
        // min représente la deuxième distance minimale par rapport à la ville actuelle
        int min2;
        // min_index représente l'index de cette ville
        int min_index;
        // min_index2 représente l'index de cette deuxième ville
        int min_index2;

        // Dans cette boucle nous allons renplir le chemin, comme nous avons déjà placer la première ville, il en reste nbCity - 1 à placer
        for (int i = 0; i < nbCity - 1; i++) {

            // Au début on défini la plus petite villes comme étant celle d'indice 0 dans index
            min = dist[city][index[0]];
            min_index = 0;

            // S'il n'y a plus qu'une ville on la choisie forcément 
            if (index_count > 1) {
                // on sait qu'il y a plus d'une ville donc nous pouvons initialiser min2 et min_index2
                min2 = dist[city][index[1]];
                min_index2 = 1;
                // On veut que min soit la plus petite des deux ville
                if (min > min2) {
                    // Si ce n'est pas le cas, on swap les variables
                    int tmp = min;
                    min = min2;
                    min2 = tmp;
                    tmp = min_index;
                    min_index = min_index2;
                    min_index2 = tmp;
                }

                // Pas besoin de faire de tour de boucle s'il n'y a plus que deux villes
                if (index_count > 2) {
                    // On regarde chaque ville restante
                    for (int j = 1; j < index_count; j++) {

                        // Pour chaque ville on regarde la distance par rapport à celle actuelle
                        // si la distance est plus petite
                        if (dist[city][index[j]] < min) {
                            // On modifie la ville la plus proche
                            min = dist[city][index[j]];
                            min_index = j;
                        }
                        // Sinon si la distance est plus petite celle avec la deuxième ville la plus proche
                        else if (dist[city][index[j]] < min2) {
                            // on modifie la deuxième ville la plus proche
                            min2 = dist[city][index[j]];
                            min_index2 = j;
                        }
                    }
                }

                // Avec une chance sur deux on choisie la deuxième ville la plus proche
                if (rand() % 2) {
                    min_index = min_index2;
                    min = min2;
                }
            }



            // on augmente la taille du chemin
            path_dist += min;

            // On change la ville actuelle
            city = index[min_index];

            // On ajoute la ville au chemin
            path.push_back(villes[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(villes[start_index]);

        // On met à jour les attributs de la classe
        distance = path_dist;

        // On renvoie un tuple contenant le chemin et la distance totale
    }

    friend ostream& operator<<(ostream& os, const Trajet& trajet) {
        os << "Distance totale de " << trajet.distance << " km" << endl;
        for (auto& ville : trajet.path) {
            os << ville << endl;
        }
        return os;
    }

};