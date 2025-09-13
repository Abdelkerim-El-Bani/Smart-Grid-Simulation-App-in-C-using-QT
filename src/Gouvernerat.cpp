#include "/home/kerim/Documents/MiniProjet/include/Gouvernerat.h"


#include <iostream>

Gouvernorat::Gouvernorat(const string& nom, const int i)
    : Nom_gouv(nom), id(i) {}

string Gouvernorat::getNom_gouv() const { return Nom_gouv; }
int Gouvernorat::getId() const { return id; }

void Gouvernorat::setNom_gouv(const string& nom) { Nom_gouv = nom; }
void Gouvernorat::setId(const int  i) { id = i; }



void Gouvernorat::afficherInfos() const {
    cout << "Gouvernorat: " << Nom_gouv << " identifient : " << id<< ")\n";
}
