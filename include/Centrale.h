#pragma once

#include <string>
using namespace std;

class Centrale {
protected:
    int id;
    string nom;
    float puissance;
    float rendement;
    int id_gouv;
    string source;

public:
    // Constructeur par défaut
    Centrale();

    // Constructeur avec paramètres
    Centrale(int id, const string& nom, float puissance, float rendement, int id_gouv, const string& source);

    // Getters
    int getId() const;
    string getNom() const;
    float getPuissance() const;
    float getRendement() const;
    int getIdGouv() const;
    string getSource() const;

    // Setters
    void setId(int id);
    void setNom(const string& nom);
    void setPuissance(float puissance);
    void setRendement(float rendement);
    void setIdGouv(int id_gouv);
    void setSource(const string& source);

    // Affichage
    void afficherInfos() const;
};

