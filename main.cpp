#include <iostream>
#include <thread>
#include "database.hpp"
#include "colis.hpp"
#include "generator.hpp"
#include "ville.hpp"

using namespace std;

int main( int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <ville_file> <colis_file> <export_file>" << endl;
        return 1;
    }

    DataBase db(argv[1], argv[2]);
    cout << db << endl;
    
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

    db.export_best_results(argv[3]);


    // Colis colis(db);
    // cout << colis << endl;
    // colis.glouton_solve(db);
    // cout << colis << endl;
    return 0;
}