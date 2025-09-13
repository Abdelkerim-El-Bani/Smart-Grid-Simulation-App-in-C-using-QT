#pragma once
#include "Secteur.h"

class SecteurIndustriel : public Secteur {
private:
    int NombreUsines;
    float puissanceReactiveConsommee;
    string  modeFonctionnement;
 
public:
    SecteurIndustriel(int id, float niveauTension, float puissanceConsommee, const string& horairesDemande, int priorite, const string& periodeForteConso, const    int NombreUsines, float puissanceReactiveConsommee  ,const string& modeFonctionnement = "24/24");

    // Getters
    int getNombreUsines() const;
    float getPuissanceReactiveConsommee() const;
    string getModeFonctionnement() const;

    // Setters
    void setNombreUsines(const int NombreUsines);
    void setPuissanceReactiveConsommee(float puissanceReactiveConsommee);
    void setModeFonctionnement(const string& mode);
};

