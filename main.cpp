#include <iostream>
#include "database.hpp"
#include "colis.hpp"

using namespace std;

int main() {
    DataBase db("../input/4villes.txt", "../input/8colis40capacite.txt");
    cout << db << endl;

    Colis colis(db);
    cout << colis << endl;
    colis.glouton_solve(db);
    cout << colis << endl;
    return 0;
}