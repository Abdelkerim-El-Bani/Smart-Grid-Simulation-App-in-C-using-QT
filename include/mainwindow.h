#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Centrale.h"
#include "Gouvernerat.h"
#include "Secteur.h"
#include "Secteur_Industriel.h"
#include "Secteur_Domicile.h"
#include "CentraleGouvernorat.h"
#include <QMainWindow>
#include <QTableWidget>


enum Saison { HIVER, PRINTEMPS, ETE, AUTOMNE };
enum Meteo { ENSOLEILLE, NUAGEUX, PLUVIEUX, NEIGEUX, VENTEUX };
enum Heure { MATIN, MIDI, APRES_MIDI, SOIR, NUIT };


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //les fonctions liées à la class centra
    void ajouterCentrale();
    void afficherCentrales();
    void chercherCentrale();
    void supprimerCentrale();
    void modifierCentrale();
    void calculerProduction();
    void calculerProductionTotale();
    double calculateConsommation(int, Heure, Saison) ;
    void calculateConsommationTotale();

    //les fonction liées à la class gouvernorat

    void ajouterGouvernorat();
    void affichierGouvernorat();
    void supprimerGouvernorat();
    void chercheGouvernorat();
    void afficherCentralesParGouvernorat();

    //les fonction liées à la class laison

    void ajoutelaision();
    void affichierCentraleGouvernorat();
    void afficherGouvernorats();
    void afficherToutesLesLiaisons();
    void supprimerLiaisonParCentrale(int idCentrale);
    void supprimerLiaisonParGouvernorat(int idGouv);
    // les fonction liées à la classe secteur
    void ajouterSecteur();
    void afficherSecteurs();
    void supprimerSecteur();
    void afficherSecteursParGouvernorat();
    void modifierSecteur();
    void chercherSecteur();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_actionCredit_triggered();
private:
    Ui::MainWindow *ui;
    CentraleGouvernorat reseau;
    QList<Centrale> centrales;
    QList<Gouvernorat> gouvernorats;
    QList<Secteur> secteurs;
    QList<int> list1;

};
#endif // MAINWINDOW_H
