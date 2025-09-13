
#include "/home/kerim/Documents/MiniProjet_1/include/Centrale.h"
#include <iostream>

using namespace std;

// Constructeur par défaut
Centrale::Centrale() : id(0), nom(""), puissance(0.0f), rendement(0.0f), id_gouv(0), source("") {}

// Constructeur avec paramètres
Centrale::Centrale(int id, const string& nom, float puissance, float rendement, int id_gouv, const string& source)
    : id(id), nom(nom), puissance(puissance), rendement(rendement), id_gouv(id_gouv), source(source) {}

// Getters
int Centrale::getId() const {
    return id;
}

string Centrale::getNom() const {
    return nom;
}

float Centrale::getPuissance() const {
    return puissance;
}

float Centrale::getRendement() const {
    return rendement;
}

int Centrale::getIdGouv() const {
    return id_gouv;
}

string Centrale::getSource() const {
    return source;
}

// Setters
void Centrale::setId(int id) {
    this->id = id;
}

void Centrale::setNom(const string& nom) {
    this->nom = nom;
}

void Centrale::setPuissance(float puissance) {
    this->puissance = puissance;
}

void Centrale::setRendement(float rendement) {
    this->rendement = rendement;
}

void Centrale::setIdGouv(int id_gouv) {
    this->id_gouv = id_gouv;
}

void Centrale::setSource(const string& source) {
    this->source = source;
}

// Affichage
void Centrale::afficherInfos() const {
    cout << "ID: " << id << endl;
    cout << "Nom: " << nom << endl;
    cout << "Puissance: " << puissance << " MW" << endl;
    cout << "Rendement: " << rendement * 100 << " %" << endl;
    cout << "ID Gouvernorat: " << id_gouv << endl;
    cout << "Source d'energie: " << source << endl;
}
