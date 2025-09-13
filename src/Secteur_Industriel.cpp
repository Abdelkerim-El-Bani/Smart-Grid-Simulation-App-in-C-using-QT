#include "/home/kerim/Documents/MiniProjet/include/Secteur_Industriel.h"

SecteurIndustriel::SecteurIndustriel(int id, float niveauTension, float puissanceConsommee, const string& horairesDemande, int priorite, const string& periodeForteConso, int NombreUsines, float puissanceReactiveConsommee , const std::string& modeFonctionnement)
    : Secteur(id, niveauTension, puissanceConsommee, horairesDemande, priorite, periodeForteConso), NombreUsines(NombreUsines), puissanceReactiveConsommee(puissanceReactiveConsommee),modeFonctionnement(modeFonctionnement) {}

int SecteurIndustriel::getNombreUsines() const {
    return NombreUsines;
}

float SecteurIndustriel::getPuissanceReactiveConsommee() const {
    return puissanceReactiveConsommee;
}


std::string SecteurIndustriel::getModeFonctionnement() const {
    return modeFonctionnement;
}

void SecteurIndustriel::setNombreUsines(int NombreUsines) {
    this->NombreUsines = NombreUsines;
}

void SecteurIndustriel::setPuissanceReactiveConsommee(float puissanceReactiveConsommee) {
    this->puissanceReactiveConsommee = puissanceReactiveConsommee;
}


void SecteurIndustriel::setModeFonctionnement(const std::string& mode) {
    this->modeFonctionnement = mode;
}
