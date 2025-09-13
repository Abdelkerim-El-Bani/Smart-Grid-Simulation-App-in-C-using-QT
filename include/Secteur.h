#pragma once
#include <string>
using namespace std;

class Secteur {
private:
    int id;
    float niveauTension;
    float puissanceConsommee;
    string horairesDemande;
    int priorite;
    string periodeForteConso;
    int id_gouv;

public:
    Secteur();
    Secteur(int id = 0, float niveauTension = 0, float puissanceConsommee = 0,
            const string& horairesDemande = " ", int priorite = 0,
            const string& periodeForteConso = " ", int id_gouv = 0);

    int getId() const;
    float getNiveauTension() const;
    float getPuissanceConsommee() const;
    string getHorairesDemande() const;
    int getPriorite() const;
    string getPeriodeForteConso() const;
    int getId_gouv() const;

    void set_id(int i);
    void setId_gouv(int r);
    void setNiveauTension(float niveauTension);
    void setPuissanceConsommee(float puissanceConsommee);
    void setHorairesDemande(const string& horairesDemande);
    void setPriorite(int priorite);
    void setPeriodeForteConso(const string& periodeForteConso);
    
     void afficherInfos ();
};

