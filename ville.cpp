#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "database.hpp"

using namespace std;

class P2{
private:
    int nbTrajets;
    int distance;
    vector<int>&villesVisit;
    vector<int>&listVilles;
};

auto path(int start_index) {

    // On initialise path qui contiendra le chemin final
    vector<string> path;
    // on initialise le vecteur contenant les villes non présente dans le chemin
    vector<int> index;
    // index_count représente le nombre de velles non présente dans le chemin
    int index_count = nbCity - 1;
    // path_dist représente la taille totale du chemin
    int path_dist = 0;
    // city correspond à l'index de la ville actuelle, au début elle vaut start_index
    int city = start_index;
    // On place la ville de départ
    path.push_back(nameCity[city]);

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
    for (int i = 0; i < nbCity-1; i++) {
               
        // Au début on défini la plus petite villes comme étant celle d'indice 0 dans index
        min = dist[city][index[0]];
        min_index = 0;
            
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

        // on augmente la taille du chemin
        path_dist += min;

        // On change la ville actuelle
        city = index[min_index];
            
        // On ajoute la ville au chemin
        path.push_back(nameCity[city]);

        //  on supprime la ville de la liste des villes à traiter
        index.erase(index.begin() + min_index);
        index_count--;
            

    }
        
    // on ajoute la distance entre la ville finale et celle de début
    path_dist += dist[city][start_index];
    // on finit le chemin en retournant à la ville de départ
    path.push_back(nameCity[start_index]);

    // On renvoie un tuple contenant le chemin et la distance totale
    return make_tuple(path, path_dist);
}