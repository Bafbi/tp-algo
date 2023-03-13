#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Génération de l'instance du problème de sac à dos 0-1
void generer_instance_P1() {
    srand(time(NULL));
    int capacite = 50;
    int nb_objets = 10;
    ofstream fichier;
    fichier.open("P1_instance.txt");
    fichier << capacite << endl;
    fichier << nb_objets << endl;
    for(int i=1; i<=nb_objets; i++) {
        int poids = rand() % 10 + 1;
        int valeur = rand() % 10 + 1;
        fichier << poids << " " << valeur << endl;
    }
    fichier.close();
    cout << "Instance P1 générée avec succès!" << endl;
}

// Génération de l'instance du problème de tournée de véhicules (VRP)
void generer_instance_P2() {
    srand(time(NULL));
    int nb_clients = 10;
    int nb_vehicules = 2;
    int capacite = 15;
    ofstream fichier;
    fichier.open("P2_instance.txt");
    fichier << nb_clients << endl;
    fichier << capacite << " " << nb_vehicules << endl;
    fichier << "0 0" << endl;
    for(int i=1; i<=nb_clients; i++) {
        int x = rand() % 10 + 1;
        int y = rand() % 10 + 1;
        int demande = rand() % 10 + 1;
        fichier << x << " " << y << " " << demande << endl;
    }
    fichier.close();
    cout << "Instance P2 générée avec succès!" << endl;
}

