#include <iostream>
#include <thread>
#include "database.hpp"
#include "colis.hpp"
#include "generator.hpp"
#include "ville.hpp"

using namespace std;

int main() {
    DataBase db("../input/4villes.txt", "../input/8colis40capacite.txt");
    cout << db << endl;

    // generate multiple colis
    // solve them in parallel
    // add them to the database
    
    vector<thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.push_back(thread([&db, i] {
            Colis colis = db.newColis();
            colis.glouton_random_solve(i);
            db.addColis(colis);
        }));
    }

    for (int i = 0; i < 10; i++) {
        threads.push_back(thread([&db, i] {
            Trajet ville = db.newTrajet();
            ville.glouton_random_solve(0, i);
            db.addTrajet(ville);
        }));
    }

    for (auto& t : threads) {
        t.join();
    }
    // cout << db.getBestColis() << endl;

    db.export_best_results("../output/result.txt");


    // Colis colis(db);
    // cout << colis << endl;
    // colis.glouton_solve(db);
    // cout << colis << endl;
    return 0;
}