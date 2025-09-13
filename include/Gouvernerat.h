#pragma once
#include <string>
#include <vector>
#include <memory> 

using namespace std;

class Gouvernorat {
private:
     string Nom_gouv;
    int id ;
   

public:
    Gouvernorat(const string& nom, const int i);

    string getNom_gouv() const;
    int  getId() const;

    void setNom_gouv(const string& nom);
    void setId (const int  id);

    void afficherInfos() const;
};

