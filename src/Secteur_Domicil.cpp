#include "/home/kerim/Documents/MiniProjet/include/Secteur_Domicile.h"

SecteurDomicile::SecteurDomicile(int id, float niveauTension, float puissanceConsommee, const string& horairesDemande, int priorite, const string& periodeForteConso, bool presenceEnergieRenouvelable,float n)
    : Secteur(id, niveauTension, puissanceConsommee, horairesDemande, priorite, periodeForteConso), presenceEnergieRenouvelable(presenceEnergieRenouvelable),NombreMaison(n) {}

bool SecteurDomicile::getPresenceEnergieRenouvelable() const {
    return presenceEnergieRenouvelable;
}
float SecteurDomicile::getNomberMaison() const {
	return NombreMaison;
}

void SecteurDomicile::setPresenceEnergieRenouvelable(bool presence) {
    this->presenceEnergieRenouvelable = presence;
}
void SecteurDomicile::setNombreMaison(float n)
{
	this->NombreMaison = n;
}
