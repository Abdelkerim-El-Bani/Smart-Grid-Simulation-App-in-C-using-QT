#ifndef RESEAU_ELECTRIQUE_H
#define RESEAU_ELECTRIQUE_H

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include "Centrale.h"
#include "Gouvernerat.h"



using namespace std;

class CentraleGouvernorat {
private:
    
    map<int, set<int>> liaisonGouvToCentrale;

public:
     CentraleGouvernorat();
    void ajouterLiaison(int idCentrale, int idGouvernorat);
    set<int> afficherGouvernoratsParCentrale(int idCentrale) const;
    void afficherCentralesParGouvernorat(int idGouvernorat) const;

    
   
    set<int> getCentralesParGouvernorat(int idGouvernorat) const;
};

#endif

