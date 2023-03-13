#include <iostream>
#include <thread>
#include "database.hpp"
#include "colis.hpp"
#include "generator.hpp"

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    DataBase db("../input/4villes.txt", "../input/8colis40capacite.txt");
    cout << db << endl;

    Colis colis = db.newColis();
    cout << colis << endl;
    colis.glouton_solve();
    cout << colis << endl;


    // thread t1([&db] {
    //     Colis colis = db.newColis();
    //     colis.glouton_solve(db);
    //     db.addColis(colis);
    // }, 3);

    // Colis colis(db);
    // cout << colis << endl;
    // colis.glouton_solve(db);
    // cout << colis << endl;
    return 0;
}