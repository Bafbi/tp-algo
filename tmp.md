```
void gloutonP1(DataBase db){
    int nbrObjets = db.getNbPackages(); // Le nombre de paquets à traiter
    map<int,tuple<float,float>> packages = db.getPackages();// On prend le tableau contenant la liste des paquets et leurs informations
    map<int,float> tabBsC; // Tableau dans lequel on va ranger les couples : {numéro du paquet,valeur de bénéfice/consommation de capacité}
    float capacityCar = db.getcapacity(); // Capacité de la voiture
    int i = 5;
    while(nbrObjets > 0){//Tant qu'on a des objets à traiter

        float benef = get<1>(packages[nbrObjets]);
        float consoCapa = get<0>(packages[nbrObjets]);
        float tmp = (benef/consoCapa);

        tabBsC[i] = tmp;// On range le couple : {paquet i, benef/conso du paquet} dans tabBsC
        nbrObjets -= 1;
        i-=1;
    }
    //On trie le tableau en fonction de la valeur benef/conso en mettant les valeurs de tabBsC dans un vector constitué de couples de valeurs
    vector<std::pair<int, float> > tab;
    for (const auto &item : tabBsC) {
        tab.emplace_back(item);
    }

    std::sort(tab.begin(), tab.end(),
              [] (const auto &x, const auto &y) {return x.second < y.second;});


    for(auto element : tab )
    {
        cout << element.first << " et " << element.second << endl;
    }
    tab.pop_back();//Le dernier rang du tab est juste égal à 0 et n'appartient pas aux paquets d'origine donc on l'enlève

    cout << "La voiture a une capacité de : " << capacityCar << endl;

    while (capacityCar > 0 && tab.end()->first != 0 && get<0>(packages[tab.end()->first]) != 0){

        if(capacityCar - get<0>(packages[tab.end()->first]) >= 0) { //Si assez de place dans la voiture
            cout << "On insère le paquet " << tab.end()->first << " qui consomme " << get<0>(packages[tab.end()->first]) << " places dans la voiture." << endl;
            capacityCar -= get<0>(packages[tab.end()->first]);
            cout << "Place restante dans la voiture : " << capacityCar << endl;

        }
        tab.pop_back();// Si le paquet est trop grand pour être placé dans la voiture, on passe au suivant
    }
}

```
* La `capacity` a pour but de vérifier s'il on ne dépasse pas la capacité maximale de la voiture. Pour cela, on l'initialise par sa capacité max et on décrémentera à chaque objet rajouté dans le véhicule.
* Le `benefice` calcule les entrées d'argents à chaque produit chargés
* les vecteurs `prodEmb` et `listProd` serviront à stocker les informations des produits embarqués et ceux qu'il reste à embarquer


```cpp=
class P2 {
private:
    int nbTrajets;
    int distance;

public:

    auto path(int start_index, DataBase db) {
        
        // On récupère les informations 
        auto dist = db.getDist();
        auto nbCity = db.getNbCity();
        auto nameCity = db.getNameCity();


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
            path.push_back(nameCity[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(nameCity[start_index]);

        // On met à jour les attributs de la classe
        nbTrajets = nbCity;
        distance = path_dist;

        // On renvoie un tuple contenant le chemin et la distance totale
        return make_tuple(path, path_dist);
    }

    auto path_random(int start_index, DataBase db) {

        auto& dist = db.getDist();
        auto nbCity = db.getNbCity();
        auto& nameCity = db.getNameCity();

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
            path.push_back(nameCity[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(nameCity[start_index]);

        // On met à jour les attributs de la classe
        nbTrajets = nbCity;
        distance = path_dist;

        // On renvoie un tuple contenant le chemin et la distance totale
        return make_tuple(path, path_dist);
    }

};
```

* […]




## Question 4:



Algo glouton chemin : 

Cette algoritme prend en paramètre l'indice de la ville de départ ainsi qu'un objet de la classe DataBase contenant les informations nécéssaire à l'algorithme (dist, nbCity et nameCity).

L'algorithme fonctionne de la manière suivant : 

- 1 → Il stocke dans un vecteur d'entier la liste des index des villes non visité
- 2 → Il va ensuite parcourir toutes les villes non visité afin de trouver celle la plus proche de la ville précédente
- 3 → Un fois cette ville trouvé, il l'ajoute au chemin et ajoute la distance entre cette ville et la précédente. Il supprime également l'index de la ville visité de la liste des ville non visité
- 4 → Une fois que toutes les villes ont été visité en répétant les étapes [2] et [3], il ajoute la ville de départ afin de finir le chemin ainsi que la distance qui va avec
- 5 → Enfin, il renvoie un tuple contenant le chemin trouvé et la distance totale de ce chemin.
```cpp=
auto path(int start_index, DataBase db) {
        
        // On récupère les informations 
        auto dist = db.getDist();
        auto nbCity = db.getNbCity();
        auto nameCity = db.getNameCity();


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
            path.push_back(nameCity[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(nameCity[start_index]);

        // On met à jour les attributs de la classe
        nbTrajets = nbCity;
        distance = path_dist;

        // On renvoie un tuple contenant le chemin et la distance totale
        return make_tuple(path, path_dist);
    }

```




## question 5:

* Algorithme glouton P1 randomisé : 

La différence avec l'algorithme glouton P1 est que la version randomisée ne va pas récupérer le paquet possédant le meilleur
rapport bénéfice/capacité puis le suivant et ainsi de suite, mais il va choisir aléatoirement :
- Soit le paquet possédant le meilleur rapport bénéfice/capacité
- Soit le paquet possédant le deuxième meilleur rapport bénéfice/capacité parmi les paquets restants.

Le tirage se fait avec la fonction "headsOrTails" suivante : 
```cpp=
int headsOrTails(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 2);
    return distrib(gen);
}
```
Et l'algorithme glouton randomisé est : 

```cpp=

void gloutonP1(DataBase db){
    int nbrObjets = db.getNbPackages(); // Le nombre de paquets à traiter
    map<int,tuple<float,float>> packages = db.getPackages();// On prend le tableau contenant la liste des paquets et leurs informations
    map<int,float> tabBsC; // Tableau dans lequel on va ranger les couples : {numéro du paquet,valeur de bénéfice/consommation de capacité}
    float capacityCar = db.getcapacity(); // Capacité de la voiture
    int i = 5;
    while(nbrObjets > 0){//Tant qu'on a des objets à traiter

        float benef = get<1>(packages[nbrObjets]);
        float consoCapa = get<0>(packages[nbrObjets]);
        float tmp = (benef/consoCapa);

        tabBsC[i] = tmp;// On range le couple : {paquet i, benef/conso du paquet} dans tabBsC
        nbrObjets -= 1;
        i-=1;
    }
    //On trie le tableau en fonction de la valeur benef/conso en mettant
    //les valeurs de tabBsC dans un vector constitué de couples de valeurs
    vector<std::pair<int, float> > tab;
    for (const auto &item : tabBsC) {
        tab.emplace_back(item);
    }

    std::sort(tab.begin(), tab.end(),
              [] (const auto &x, const auto &y) {return x.second < y.second;});

    cout << "Tableau après le tri : " << endl;
    for(auto element : tab )
    {
        cout << "    " << element.first << " et " << element.second << endl;
    }
    cout << endl;

    cout << "La voiture a une capacité de : " << capacityCar << endl;
    int flipAcoin;
    int sizeTab = tab.size();

    while (capacityCar > 0 && tab.back().first != 0 && get<0>(packages[tab.back().first]) != 0 && sizeTab > 0){//Tant qu'il y a de la place dans la voiture et que le tableau n'est pas vide

        sizeTab = tab.size();
        if(sizeTab > 1) {
            flipAcoin = headsOrTails();
        }
        else{
            flipAcoin = 1;// S'il n'y a plus qu'un paquet dans le tableau, on est obligé de le choisir
        }
        cout <<"Taille tab : " <<sizeTab<< endl;
        if(flipAcoin == 1){//heads = On prend le dernier paquet du tableau
            if(capacityCar - get<0>(packages[tab[sizeTab-1].first]) >= 0 && get<0>(packages[tab[sizeTab-1].first]) != 0) { //Si assez de place dans la voiture pour le paquet

                cout << "On insère le paquet " << tab[sizeTab-1].first << " qui consomme "
                     << get<0>(packages[tab[sizeTab-1].first]) << " places dans la voiture.(Heads !)" << endl;
                capacityCar -= get<0>(packages[tab[sizeTab-1].first]);//On enlève à la capacité de la voiture, la place consommée par le paquet
                cout << "Place restante dans la voiture : " << capacityCar << endl;

            }
            else{
                cout << "PLus de place pour ranger le paquet " << tab[sizeTab-1].first << ", (" << get<0>(packages[tab[sizeTab-1].first]) << " places requises) on l'enlève donc du tableau. (Heads !)" << endl;
            }
            cout << "Tableau avant avoir retiré le paquet : "<< endl;
            for(auto element : tab )
            {
                cout << "    " << element.first << " et " << element.second << endl;
            }
            tab.pop_back();// Si le paquet est trop grand pour être placé dans la voiture, on passe au suivant
            cout << "Tableau après avoir retiré le paquet : "<< endl;
            for(auto element : tab )
            {
                cout << "    " << element.first << " et " << element.second << endl;
            }
            cout << endl;
        }
        else if(flipAcoin == 2){//Tails = On prend l'avant dernier paquet du tableau
            if (capacityCar - get<0>(packages[tab[sizeTab-2].first]) >= 0 && get<0>(packages[tab[sizeTab-2].first]) != 0) { //Si assez de place dans la voiture pour le paquet
                cout << "On insère le paquet " << tab[sizeTab - 2].first << " qui consomme "
                     << get<0>(packages[tab[sizeTab-2].first]) << " places dans la voiture. (Tails !)" << endl;
                capacityCar -= get<0>(packages[tab[sizeTab - 2].first]);//On enlève à la capacité de la voiture, la place consommée par le paquet
                cout << "Place restante dans la voiture : " << capacityCar << endl;
            }
            else{
                cout << "PLus de place pour ranger le paquet " << tab[sizeTab-2].first << ", (" << get<0>(packages[tab[sizeTab-2].first]) << " places requises) on l'enlève donc du tableau. (Tails !)" << endl;
            }
            cout << "Tableau avant avoir retiré le paquet : "<< endl;
            for(auto element : tab )
            {
                cout << "    " << element.first << " et " << element.second << endl;
            }
            tab.erase(tab.begin() + sizeTab-2);
            cout << "Tableau après avoir retiré le paquet : "<< endl;
            for(auto element : tab )
            {
                cout << "    " << element.first << " et " << element.second << endl;
            }
            cout << endl;
        }

    }
    cout << "Fin de l'algorithme P1 !" << endl;
}
```


* Algo glouton randomisé chemin : 

Cette algoritme prend en paramètre l'indice de la ville de départ ainsi qu'un objet de la classe DataBase contenant les informations nécéssaire à l'algorithme (dist, nbCity et nameCity).

L'algorithme fonctionne de la manière suivant : 

- 1)Il stocke dans un vecteur d'entier la liste des index des villes non visité
- 2)Il va ensuite parcourir toutes les villes non visité afin de trouver les deux villes les plus proche de la ville précédente
- 3)Un fois ces villes trouvés, il choisie l'une des deux villes de manière aléatoire.
- 4)Il ajoute la ville choisie au chemin et ajoute la distance entre cette ville et la précédente. Il supprime également l'index de la ville visité de la liste des ville non visité
- 4)Une fois que toutes les villes ont été visité en répétant les étapes 2), 3) et 4), il ajoute la ville de départ afin de finir le chemin ainsi que la distance qui va avec
- 5)Enfin, il renvoie un tuple contenant le chemin trouvé et la distance totale de ce chemin.
```cpp=
auto path_random(int start_index, DataBase db) {

        auto& dist = db.getDist();
        auto nbCity = db.getNbCity();
        auto& nameCity = db.getNameCity();

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
            path.push_back(nameCity[city]);

            //  on supprime la ville de la liste des villes à traiter
            index.erase(index.begin() + min_index);
            index_count--;


        }

        // on ajoute la distance entre la ville finale et celle de début
        path_dist += dist[city][start_index];
        // on finit le chemin en retournant à la ville de départ
        path.push_back(nameCity[start_index]);

        // On met à jour les attributs de la classe
        nbTrajets = nbCity;
        distance = path_dist;

        // On renvoie un tuple contenant le chemin et la distance totale
        return make_tuple(path, path_dist);
    }
```

Pour insérer les données traitées dans un fichier texte, nous avons créé deux fonctions : 
* La première, `addP1P2()` permet d'insérer à chaque réplication les valeurs trouvées par l'algorithme glouton de P1 et P2. Les données sont enregistrées sous forme de paire dans un vecteur mis dans l'argument de la fonction. Cette fonction prend également la classe `P1`, `P2` et `DataBase` (pour réupérer les infos générales initiales).
* La deuxième est la fonction`exportFile()` qui va réellement insérer les données dans le fichier. Ces données proviennent du vecteur évoqué juste au dessus. Cette fonction va prendre chaque couple et faire une opération en fonction du poids que l'on stock dans une map avec l'opération en clé et le couple en valeur. Cela nous permettra après de récupéré le couple avec le plus gros calcul pondéré. Cette fonction prend en argument le nom du fichier, le vecteur et les deux poids qui sont automatiquement associés à une valeur si ils ne sont pas donnés.

```cpp

void addP1P2(P1& pack, P2& ville, DataBase& general, vector<pair<float,int>>& P1P2){
    float rapport1 = (float)(general.getCapacityCar() - pack.getCapacity())/pack.getBenefice();
    float rapport2 = ville.getDistance();

    P1P2.push_back(pair<float,int>(rapport1,rapport2));
}

void exportFile(string namefile,vector<pair<float,int>>& P1P2, float poids1 = 0.8, float poids2 = 0.2){
    ofstream file;
    file.open(namefile);

    map<float, pair<float,int>> comparation;
    float max=0;
    for(auto&elem : P1P2){
        float operation = poids1 * get<0>(elem) + poids2 * get<1>(elem);
        if(max<operation) max = operation;
        comparation.insert(pair<float, pair<float,int>>(operation, elem));
    }
    float solP1 = get<0>(comparation[max]);
    float solP2 = get<1>(comparation[max]);

    file<<"Best Solution => P1 : "<< solP1 << " , P2 : "<< solP2 <<"\n";

    file.close();

}
```