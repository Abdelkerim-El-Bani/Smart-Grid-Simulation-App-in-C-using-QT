#include "/home/kerim/Documents/MiniProjet/include/Secteur.h"
#include <iostream>

Secteur::Secteur()
{
	id =0;
	niveauTension =0;
	puissanceConsommee =0;
	horairesDemande = " ";
	priorite =0;
	periodeForteConso = " ";
    id_gouv = 0;
	
}
Secteur::Secteur(int id, float niveauTension, float puissanceConsommee,
                 const string& horairesDemande, int priorite,
                 const string& periodeForteConso, int id_gouv)
    : id(id), niveauTension(niveauTension), puissanceConsommee(puissanceConsommee),
      horairesDemande(horairesDemande), priorite(priorite),
      periodeForteConso(periodeForteConso), id_gouv(id_gouv) {}
int Secteur::getId() const { return id; }
float Secteur::getNiveauTension() const { return niveauTension; }
float Secteur::getPuissanceConsommee() const { return puissanceConsommee; }
string Secteur::getHorairesDemande() const { return horairesDemande; }
int Secteur::getPriorite() const { return priorite; }
string Secteur::getPeriodeForteConso() const { return periodeForteConso; }
int Secteur::getId_gouv() const { return id_gouv; }

void Secteur::set_id (int i){ id = i;}
void Secteur::setId_gouv( int r ) {id_gouv = r ;}
void Secteur::setNiveauTension(float niveauTension) { this->niveauTension = niveauTension; }
void Secteur::setPuissanceConsommee(float puissanceConsommee) { this->puissanceConsommee = puissanceConsommee; }
void Secteur::setHorairesDemande(const string& horairesDemande) { this->horairesDemande = horairesDemande; }
void Secteur::setPriorite(int priorite) { this->priorite = priorite; }
void Secteur::setPeriodeForteConso(const string& periodeForteConso) { this->periodeForteConso = periodeForteConso; }

void Secteur::afficherInfos (){
	cout << "  id "<<id <<"  niveau de tension "<< niveauTension << "  puissance consomé"<<puissanceConsommee <<"  pic de consomation"<< horairesDemande << "  priorité "<<priorite << "  "<<periodeForteConso <<  "  id de gouvernorat "<<id_gouv << endl;
}
