#pragma once
#include "Secteur.h"

class SecteurDomicile : public Secteur {
private:
    bool presenceEnergieRenouvelable;
    float NombreMaison;

public:
    SecteurDomicile(int id, float niveauTension, float puissanceConsommee, const string& horairesDemande, int priorite, const string& periodeForteConso, bool presenceEnergieRenouvelable,float n);

    // Getters
    bool getPresenceEnergieRenouvelable() const;
    float getNomberMaison() const;

    // Setters
    void setPresenceEnergieRenouvelable(bool presence);
    void setNombreMaison(float n);
};

