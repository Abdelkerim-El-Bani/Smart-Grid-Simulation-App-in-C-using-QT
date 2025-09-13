#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "Centrale.cpp"
#include "Gouvernerat.cpp"
#include "Secteur.cpp"
#include "Secteur_Industriel.cpp"
#include "Secteur_Domicil.cpp"
#include "CentraleGouvernorat.cpp"
#include "QTextStream"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
// Les fonctions liées à la classe centrale.
void MainWindow::ajouterCentrale() {
    bool ok;

    int id = QInputDialog::getInt(this, "Ajout", "ID de la centrale :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Vérifier dans le fichier centrale.txt si l'ID existe déjà
    QFile fichier("centrale.txt");
    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichier);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() > 0 && champs[0].toInt() == id) {
                QMessageBox::warning(this, "Erreur", "L'ID de la centrale existe déjà dans le fichier.");
                fichier.close();
                return;
            }
        }
        fichier.close();
    }

    // Collecte les autres informations
    QString nom = QInputDialog::getText(this, "Ajout", "Nom de la centrale :", QLineEdit::Normal, "", &ok);
    if (!ok || nom.isEmpty()) return;

    float puissance = QInputDialog::getDouble(this, "Ajout", "Puissance (MW) :", 0, 0, 10000, 2, &ok);
    if (!ok) return;

    int id_gouv;
    do {
        id_gouv = QInputDialog::getInt(this, "Ajout", "ID du gouvernorat (1-24) :", 1, 1, 24, 1, &ok);
        if (!ok) return;
        if (id_gouv < 1 || id_gouv > 24) {
            QMessageBox::warning(this, "Erreur", "L'ID du gouvernorat doit être entre 1 et 24.");
            continue;
        }
        break;
    } while (true);

    QString source;
    std::map<QString, float> source_rendement = {
        {"gaz", 0.90},
        {"charbon", 0.80},
        {"solaire", 0.60},
        {"hydrolique", 0.70},
        {"eolienne", 0.50}
    };

    while (true) {
        source = QInputDialog::getText(this, "Ajout", "La source d'énergie de la centrale :", QLineEdit::Normal, "", &ok);
        if (!ok) return;

        source = source.toLower().trimmed();

        if (source_rendement.find(source) != source_rendement.end()) {
            break;
        } else {
            QMessageBox::warning(this, "Erreur", "Source invalide. Veuillez entrer : gaz, charbon, solaire, hydrolique, eolienne.");
        }
    }

    float rendement = source_rendement[source];
    // Ajouter au fichier
    if (fichier.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&fichier);
        out << id << ";" << nom << ";" << puissance << ";" << rendement << ";" << id_gouv << ";" << source << "\n";
        fichier.close();
        QMessageBox::information(this, "Ajout", "Centrale ajoutée avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour écrire.");
    }
}

void MainWindow::supprimerCentrale() {
    bool ok;
    int idSupp = QInputDialog::getInt(this, "Suppression", "ID de la centrale à supprimer :", 0, 0, 999999, 1, &ok);
    if (!ok) return;
    supprimerLiaisonParCentrale(idSupp);
    QFile fichier("centrale.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier centrale.txt.");
        return;
    }

    QTextStream in(&fichier);
    QStringList lignes;
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 1 && champs[0].toInt() == idSupp) {
            trouve = true; // On ne garde pas cette ligne
        } else {
            lignes.append(ligne);
        }
    }
    fichier.close();

    if (!trouve) {
        QMessageBox::information(this, "Suppression", "Aucune centrale trouvée avec cet ID.");
        return;
    }

    // Réécrire le fichier sans la ligne supprimée
    if (fichier.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&fichier);
        for (const QString& ligne : lignes) {
            out << ligne << "\n";
        }
        fichier.close();
        QMessageBox::information(this, "Suppression", "Centrale supprimée avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de réécrire le fichier.");
    }
}

void MainWindow::chercherCentrale() {
    bool ok;
    int idRecherche = QInputDialog::getInt(this, "Recherche", "ID de la centrale à chercher :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QFile fichier("centrale.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier centrale.txt.");
        return;
    }

    QTextStream in(&fichier);
    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 6) {
            int id = champs[0].toInt();
            if (id == idRecherche) {
                QString info = "Centrale trouvée :\n";
                info += "ID : " + champs[0] + "\n";
                info += "Nom : " + champs[1] + "\n";
                info += "Puissance : " + champs[2] + " MW\n";
                info += "Rendement : " + champs[3] + " %\n";
                info += "ID Gouvernorat : " + champs[4] + "\n";
                info += "Source : " + champs[5];

                QMessageBox::information(this, "Résultat de la recherche", info);
                fichier.close();
                return;
            }
        }
    }

    fichier.close();
    QMessageBox::warning(this, "Résultat", "Aucune centrale trouvée avec cet ID.");
}

void MainWindow::afficherCentrales()
{
    QFile file("centrale.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier des centrales.");
        return;
    }

    QTextStream in(&file);
    QVector<QString> centralesList;

    std::map<int, QString> gouvernorats = {
        {1, "Ariana"},
        {2, "Béja"},
        {3, "Ben Arous"},
        {4, "Bizerte"},
        {5, "Gabès"},
        {6, "Gafsa"},
        {7, "Jendouba"},
        {8, "Kairouan"},
        {9, "Kasserine"},
        {10, "Kébili"},
        {11, "Kef"},
        {12, "Mahdia"},
        {13, "Manouba"},
        {14, "Médenine"},
        {15, "Monastir"},
        {16, "Nabeul"},
        {17, "Sfax"},
        {18, "Sidi Bouzid"},
        {19, "Siliana"},
        {20, "Sousse"},
        {21, "Tataouine"},
        {22, "Tozeur"},
        {23, "Tunis"},
        {24, "Zaghouan"}
    };

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(';', Qt::SkipEmptyParts);

        if (parts.size() >= 6) {
            QString id = parts[0].trimmed();
            QString nom = parts[1].trimmed();
            QString puissance = parts[2].trimmed();
            QString rendement = parts[3].trimmed();
            QString id_gouv = parts[4].trimmed();
            QString source = parts[5].trimmed();

            if (id.isEmpty() || nom.isEmpty()) continue;

            QString gouv_name = gouvernorats.count(id_gouv.toInt()) ? gouvernorats[id_gouv.toInt()] : "Unknown";

            QString centrale = "ID: " + id +
                               "\nNom: " + nom +
                               "\nPuissance: " + puissance + " MW" +
                               "\nRendement: " + rendement + "%" +
                               "\nID Gouvernorat: " + id_gouv + " (" + gouv_name + ")" +
                               "\nSource: " + source +
                               "\n--------------------------\n";
            centralesList.append(centrale);
        }
    }

    file.close();

    if (centralesList.isEmpty()) {
        QMessageBox::information(this, "Centrales", "Aucune centrale trouvée dans le fichier.");
        return;
    }

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Centrales existantes");
    dialog->resize(600, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(dialog);

    QTextEdit *textEdit = new QTextEdit(dialog);
    textEdit->setReadOnly(true);
    mainLayout->addWidget(textEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *prevButton = new QPushButton("Précédent", dialog);
    QPushButton *nextButton = new QPushButton("Suivant", dialog);
    QPushButton *closeButton = new QPushButton("Fermer", dialog);
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);

    const int itemsPerPage = 3;
    int currentPage = 0;
    int totalPages = (centralesList.size() + itemsPerPage - 1) / itemsPerPage;

    auto updateDisplay = [textEdit, centralesList, itemsPerPage, totalPages, &currentPage, prevButton, nextButton]() {
        QString message = "Liste des centrales (Page " + QString::number(currentPage + 1) + "/" + QString::number(totalPages) + "):\n\n";
        int startIndex = currentPage * itemsPerPage;
        int endIndex = qMin(startIndex + itemsPerPage, centralesList.size());
        for (int i = startIndex; i < endIndex; ++i) {
            message += centralesList[i];
        }
        textEdit->setText(message);
        prevButton->setEnabled(currentPage > 0);
        nextButton->setEnabled(currentPage < totalPages - 1);
    };

    updateDisplay();

    connect(prevButton, &QPushButton::clicked, [&currentPage, updateDisplay]() {
        if (currentPage > 0) {
            --currentPage;
            updateDisplay();
        }
    });
    connect(nextButton, &QPushButton::clicked, [&currentPage, &totalPages, updateDisplay]() {
        if (currentPage < totalPages - 1) {
            ++currentPage;
            updateDisplay();
        }
    });
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    dialog->setLayout(mainLayout);
    dialog->exec();
    delete dialog;
}

void MainWindow::modifierCentrale()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Modifier Centrale", "Entrez l'ID de la centrale à modifier :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QFile file("centrale.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier centrale.txt");
        return;
    }

    QStringList lignes;
    QTextStream in(&file);
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(";");
        if (champs.size() < 6) continue;

        if (champs[0].toInt() == id) {
            trouve = true;

            QStringList options = {
                "Nom", "Puissance (MW)", "Rendement (%)", "ID Gouvernorat", "Source d'énergie"
            };

            QString choix = QInputDialog::getItem(this, "Choix d'attribut",
                                                  "Quel attribut souhaitez-vous modifier ?", options, 0, false, &ok);
            if (!ok) return;

            QString nouvelleValeur = QInputDialog::getText(this, "Nouvelle valeur", "Entrez la nouvelle valeur :", QLineEdit::Normal, "", &ok);
            if (!ok || nouvelleValeur.isEmpty()) return;

            int index = options.indexOf(choix);
            champs[index + 1] = nouvelleValeur;  // +1 car l'ID est en position 0

            ligne = champs.join(";");
        }

        lignes.append(ligne);
    }

    file.close();

    if (!trouve) {
        QMessageBox::warning(this, "Erreur", "Aucune centrale trouvée avec cet ID.");
        return;
    }

    // Réécriture du fichier avec la ligne modifiée
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const QString& l : lignes)
            out << l << "\n";
        file.close();
        QMessageBox::information(this, "Succès", "Centrale modifiée avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de réécrire dans le fichier.");
    }
}

void MainWindow::calculerProduction() {
    bool ok;
    int id = QInputDialog::getInt(this, "Production", "Entrez l'ID de la centrale :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Lire la centrale depuis le fichier
    QFile fichier("centrale.txt");
    QString nom, source;
    double puissance = 0;
    double rendement = 0;
    bool idTrouve = false;

    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichier);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 6 && champs[0].toInt() == id) {
                nom = champs[1];
                puissance = champs[2].toDouble();
                rendement = champs[3].toDouble();
                source = champs[5].trimmed().toLower();
                idTrouve = true;
                break;
            }
        }
        fichier.close();
    }

    if (!idTrouve) {
        QMessageBox::warning(this, "Erreur", "L'ID de la centrale est introuvable dans le fichier.");
        return;
    }

    // Choix via combo box (drop-downs)
    QStringList saisons = {"HIVER", "PRINTEMPS", "ETE", "AUTOMNE"};
    QStringList heures = {"NUIT", "MATIN", "MIDI", "APRES_MIDI", "SOIR"};
    QStringList meteoOptions = {"ENSOLEILLE", "NUAGEUX", "PLUVIEUX", "NEIGEUX", "VENTEUX"};

    QString saisonStr = QInputDialog::getItem(this, "Saison", "Choisissez la saison :", saisons, 0, false, &ok);
    if (!ok) return;

    QString heureStr = QInputDialog::getItem(this, "Heure", "Choisissez l'heure :", heures, 0, false, &ok);
    if (!ok) return;

    QString meteoStr = QInputDialog::getItem(this, "Météo", "Choisissez la météo :", meteoOptions, 0, false, &ok);
    if (!ok) return;

    // Conversion des strings en enums
    Saison saison;
    if (saisonStr == "HIVER") saison = HIVER;
    else if (saisonStr == "PRINTEMPS") saison = PRINTEMPS;
    else if (saisonStr == "ETE") saison = ETE;
    else saison = AUTOMNE;

    Heure heure;
    if (heureStr == "NUIT") heure = NUIT;
    else if (heureStr == "MATIN") heure = MATIN;
    else if (heureStr == "MIDI") heure = MIDI;
    else if (heureStr == "APRES_MIDI") heure = APRES_MIDI;
    else heure = SOIR;

    Meteo meteo;
    if (meteoStr == "ENSOLEILLE") meteo = ENSOLEILLE;
    else if (meteoStr == "NUAGEUX") meteo = NUAGEUX;
    else if (meteoStr == "PLUVIEUX") meteo = PLUVIEUX;
    else if (meteoStr == "NEIGEUX") meteo = NEIGEUX;
    else meteo = VENTEUX;

    // Calcul des coefficients
    double coeffSaison = 1.0;
    double coeffHeure = 1.0;
    double coeffMeteo = 1.0;

    if (source == "gaz" || source == "charbon") {
        // Pas d'effet des conditions
    } else if (source == "solaire") {
        if (saison == ETE) coeffSaison = 1.0;
        else if (saison == PRINTEMPS || saison == AUTOMNE) coeffSaison = 0.8;
        else coeffSaison = 0.6;

        if (heure == MIDI) coeffHeure = 1.0;
        else if (heure == MATIN || heure == APRES_MIDI) coeffHeure = 0.7;
        else if (heure == SOIR) coeffHeure = 0.3;
        else coeffHeure = 0.0;

        if (meteo == ENSOLEILLE) coeffMeteo = 1.0;
        else if (meteo == NUAGEUX) coeffMeteo = 0.5;
        else if (meteo == PLUVIEUX || meteo == NEIGEUX) coeffMeteo = 0.1;
        else coeffMeteo = 0.8;

    } else if (source == "hydraulique") {
        if (saison == HIVER || saison == PRINTEMPS) coeffSaison = 1.0;
        else if (saison == AUTOMNE) coeffSaison = 0.9;
        else coeffSaison = 0.7;

        coeffHeure = 1.0;

        if (meteo == PLUVIEUX || meteo == NEIGEUX) coeffMeteo = 1.2;
        else coeffMeteo = 1.0;

    } else if (source == "eolienne") {
        if (saison == AUTOMNE || saison == HIVER) coeffSaison = 1.0;
        else if (saison == PRINTEMPS) coeffSaison = 0.8;
        else coeffSaison = 0.7;

        coeffHeure = 1.0;

        if (meteo == VENTEUX) coeffMeteo = 1.5;
        else if (meteo == ENSOLEILLE || meteo == NUAGEUX) coeffMeteo = 0.8;
        else if (meteo == PLUVIEUX) coeffMeteo = 1.0;
        else coeffMeteo = 0.6;

    } else {
        QMessageBox::warning(this, "Erreur", "Type de source non reconnu : " + source);
        return;
    }

    // Calcul final
    double production = puissance * rendement * coeffSaison * coeffHeure * coeffMeteo;

    QMessageBox::information(
        this,
        "Résultat",
        "Production estimée pour la centrale \"" + nom + "\": " + QString::number(production, 'f', 2) + " MW"
        );
}

double MainWindow::calculateConsommation(int id_gouv, Heure heure, Saison saison) {
    double consommationTotale = 0.0;

    // Open and read the "domicile.txt" file
    QFile fileDomicile("domicile.txt");
    if (!fileDomicile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur de fichier", "Impossible d'ouvrir le fichier : domicile.txt");
        return 0.0;
    }

    QTextStream inDomicile(&fileDomicile);
    while (!inDomicile.atEnd()) {
        QString line = inDomicile.readLine();
        QStringList sectorData = line.split(";");

        if (sectorData.size() < 5) continue;  // Skip malformed lines

        int sectorIdGouv = sectorData[0].toInt();
        double puissanceConsommee = sectorData[1].toDouble();
        QString horairesDemande = sectorData[2];
        QString periodeForteConso = sectorData[3];
        int nbHousesOrIndustries = sectorData[4].toInt();

        // Check if this sector belongs to the given governorate
        if (sectorIdGouv != id_gouv) continue;

        double coeffHeure = 1.0;
        double coeffSaison = 1.0;

        // Calculer coefficient de saison
        if ((saison == ETE && periodeForteConso.contains("ETE")) ||
            (saison == HIVER && periodeForteConso.contains("HIVER")) ||
            (saison == PRINTEMPS && periodeForteConso.contains("PRINTEMPS")) ||
            (saison == AUTOMNE && periodeForteConso.contains("AUTOMNE"))) {
            coeffSaison = 1.5; // Higher consumption in peak season
        }

        // Calculer coefficient d'heure
        if ((heure == MATIN && horairesDemande.contains("MATIN")) ||
            (heure == MIDI && horairesDemande.contains("MIDI")) ||
            (heure == APRES_MIDI && horairesDemande.contains("APRES_MIDI")) ||
            (heure == SOIR && horairesDemande.contains("SOIR")) ||
            (heure == NUIT && horairesDemande.contains("NUIT"))) {
            coeffHeure = 1.5; // Higher consumption during peak hours
        }

        double consommationSecteur = 0.0;

        // Calculating consumption for Domicile sectors
        double coeffEnergieRenouvelable = 1.0;
        if (sectorData.size() > 5 && sectorData[5] == "oui") {
            coeffEnergieRenouvelable = 0.7; // Reduced consumption if renewable energy is present
        }

        consommationSecteur = puissanceConsommee * nbHousesOrIndustries * coeffHeure * coeffSaison * coeffEnergieRenouvelable;
        consommationTotale += consommationSecteur;
    }

    fileDomicile.close();  // Close the file after reading

    // Open and read the "industriel.txt" file
    QFile fileIndustriel("industriel.txt");
    if (!fileIndustriel.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur de fichier", "Impossible d'ouvrir le fichier : industriel.txt");
        return 0.0;
    }

    QTextStream inIndustriel(&fileIndustriel);
    while (!inIndustriel.atEnd()) {
        QString line = inIndustriel.readLine();
        QStringList sectorData = line.split(";");

        if (sectorData.size() < 5) continue;  // Skip malformed lines

        int sectorIdGouv = sectorData[0].toInt();
        double puissanceConsommee = sectorData[1].toDouble();
        QString horairesDemande = sectorData[2];
        QString periodeForteConso = sectorData[3];
        int nbHousesOrIndustries = sectorData[4].toInt();

        // Check if this sector belongs to the given governorate
        if (sectorIdGouv != id_gouv) continue;

        double coeffHeure = 1.0;
        double coeffSaison = 1.0;

        // Calculer coefficient de saison
        if ((saison == ETE && periodeForteConso.contains("ETE")) ||
            (saison == HIVER && periodeForteConso.contains("HIVER")) ||
            (saison == PRINTEMPS && periodeForteConso.contains("PRINTEMPS")) ||
            (saison == AUTOMNE && periodeForteConso.contains("AUTOMNE"))) {
            coeffSaison = 1.5; // Higher consumption in peak season
        }

        // Calculer coefficient d'heure
        if ((heure == MATIN && horairesDemande.contains("MATIN")) ||
            (heure == MIDI && horairesDemande.contains("MIDI")) ||
            (heure == APRES_MIDI && horairesDemande.contains("APRES_MIDI")) ||
            (heure == SOIR && horairesDemande.contains("SOIR")) ||
            (heure == NUIT && horairesDemande.contains("NUIT"))) {
            coeffHeure = 1.5; // Higher consumption during peak hours
        }

        double consommationSecteur = 0.0;

        // Calculating consumption for Industriel sectors
        double coeffFonctionnement = 1.0;
        if (sectorData.size() > 6 && sectorData[6] == "24/7") {
            coeffFonctionnement = 1.8; // Higher consumption for 24/7 industries
        }

        consommationSecteur = puissanceConsommee * nbHousesOrIndustries * coeffHeure * coeffSaison * coeffFonctionnement;
        consommationTotale += consommationSecteur;
    }

    fileIndustriel.close();  // Close the file after reading

    return consommationTotale;
}


// Les fonctions liées à la classe gouvernorate

void MainWindow::ajouterGouvernorat() {
    bool ok;

    int id = QInputDialog::getInt(this, "Ajout", "ID du gouvernorat :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Vérifie si l'ID existe déjà dans le fichier
    QFile fichier("gouvernorats.txt");
    if (fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichier);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() > 0 && champs[0].toInt() == id) {
                QMessageBox::warning(this, "Erreur", "L'ID du gouvernorat existe déjà dans le fichier.");
                fichier.close();
                return;
            }
        }
        fichier.close();
    }

    QString nom = QInputDialog::getText(this, "Ajout", "Nom du gouvernorat :", QLineEdit::Normal, "", &ok);
    if (!ok || nom.isEmpty()) return;

    // Ajouter au fichier
    if (fichier.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&fichier);
        out << id << ";" << nom << "\n";
        fichier.close();
        QMessageBox::information(this, "Ajout", "Gouvernorat ajouté avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier pour écrire.");
    }
}

void MainWindow::afficherCentralesParGouvernorat()
{
    bool ok;
    int idGouv = QInputDialog::getInt(this, "Recherche", "ID du gouvernorat :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QFile fichier("centrale.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier centrale.txt.");
        return;
    }

    QTextStream in(&fichier);
    QString message = "Centrales du gouvernorat ID " + QString::number(idGouv) + ":\n";
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 6) {
            int idGouvCentrale = champs[4].toInt(); // 5e champ = id_gouv
            if (idGouvCentrale == idGouv) {
                trouve = true;
                message += "- ID: " + champs[0] + ", Nom: " + champs[1] +
                           ", Puissance: " + champs[2] + " MW, Rendement: " +
                           champs[3] + "%, Source: " + champs[5] + "\n";
            }
        }
    }

    fichier.close();

    if (!trouve) {
        QMessageBox::information(this, "Résultat", "Aucune centrale trouvée pour ce gouvernorat.");
    } else {
        QMessageBox::information(this, "Centrales trouvées", message);
    }
}

void MainWindow::supprimerGouvernorat() {
    bool ok;
    int idSupp = QInputDialog::getInt(this, "Suppression", "ID du gouvernorat à supprimer :", 0, 0, 999999, 1, &ok);
    if (!ok) return;
    supprimerLiaisonParGouvernorat( idSupp);
    QFile fichier("gouvernorats.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier gouvernorats.txt.");
        return;
    }

    QTextStream in(&fichier);
    QStringList lignes;
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2 && champs[0].toInt() == idSupp) {
            trouve = true; // On ne garde pas cette ligne
        } else {
            lignes.append(ligne);
        }
    }
    fichier.close();

    if (!trouve) {
        QMessageBox::information(this, "Suppression", "Aucun gouvernorat trouvé avec cet ID.");
        return;
    }

    // Réécrire le fichier sans la ligne supprimée
    if (fichier.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&fichier);
        for (const QString& ligne : lignes) {
            out << ligne << "\n";
        }
        fichier.close();
        QMessageBox::information(this, "Suppression", "Gouvernorat supprimé avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de réécrire le fichier.");
    }
}

void MainWindow::affichierGouvernorat() {
    QFile fichier("gouvernorats.txt");

    if (!fichier.exists() || !fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Aucun gouvernorat", "Aucun gouvernorat n'est enregistré.");
        return;
    }

    QTextStream in(&fichier);
    QString message = "Liste des gouvernorats disponibles :\n";
    bool vide = true;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2) {
            vide = false;
            QString id = champs[0];
            QString nom = champs[1];
            message += "- ID: " + id + ", Nom: " + nom + "\n";
        }
    }

    fichier.close();

    if (vide) {
        QMessageBox::information(this, "Aucun gouvernorat", "Le fichier est vide.");
    } else {
        QMessageBox::information(this, "Gouvernorats existants", message);
    }
}

void MainWindow::chercheGouvernorat() {
    bool ok;
    int idRecherche = QInputDialog::getInt(this, "Recherche", "ID du gouvernorat à chercher :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QFile fichier("gouvernorats.txt");
    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier gouvernorats.txt.");
        return;
    }

    QTextStream in(&fichier);
    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2) {
            int id = champs[0].toInt();
            QString nom = champs[1];

            if (id == idRecherche) {
                QString info = "Gouvernorat trouvé :\n";
                info += "ID : " + QString::number(id) + "\n";
                info += "Nom : " + nom;
                QMessageBox::information(this, "Résultat de la recherche", info);
                fichier.close();
                return;
            }
        }
    }

    fichier.close();
    QMessageBox::warning(this, "Résultat", "Aucun gouvernorat trouvé avec cet ID.");
}

// Les fonctions liées à la classe  laison

void MainWindow::ajoutelaision() {
    bool ok;
    int idCentrale = QInputDialog::getInt(this, "Liaison", "ID de la centrale :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    int idGouv = QInputDialog::getInt(this, "Liaison", "ID du gouvernorat :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Vérification dans le fichier centrale.txt
    bool centraleExiste = false;
    QFile fichierC("centrale.txt");
    if (fichierC.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierC);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 1 && champs[0].toInt() == idCentrale) {
                centraleExiste = true;
                break;
            }
        }
        fichierC.close();
    }

    // Vérification dans le fichier gouvernorats.txt
    bool gouvernoratExiste = false;
    QFile fichierG("gouvernorats.txt");
    if (fichierG.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierG);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 1 && champs[0].toInt() == idGouv) {
                gouvernoratExiste = true;
                break;
            }
        }
        fichierG.close();
    }

    if (!centraleExiste) {
        QMessageBox::warning(this, "Erreur", "L'ID de la centrale n'existe pas dans le fichier.");
        return;
    }

    if (!gouvernoratExiste) {
        QMessageBox::warning(this, "Erreur", "L'ID du gouvernorat n'existe pas dans le fichier.");
        return;
    }

    // Demander la distance
    float distance = QInputDialog::getDouble(this, "Liaison", "Distance (km) :", 0, 0, 10000, 2, &ok);
    if (!ok) return;

    // Ajout dans le fichier liaisons.txt
    QFile fichierL("liaisons.txt");
    if (fichierL.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&fichierL);
        out << idCentrale << ";" << idGouv << ";" << distance << "\n";
        fichierL.close();
        QMessageBox::information(this, "Succès", "Liaison ajoutée avec succès !");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ajouter la liaison au fichier.");
    }
}

void MainWindow::afficherGouvernorats() {
    bool ok;
    int idCentrale = QInputDialog::getInt(this, "Recherche", "ID de la centrale à chercher :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Lire les liaisons depuis le fichier
    QSet<int> idGouvernorats;
    QFile fichierL("liaisons.txt");
    if (fichierL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierL);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2 && champs[0].toInt() == idCentrale) {
                idGouvernorats.insert(champs[1].toInt());
            }
        }
        fichierL.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier liaisons.txt.");
        return;
    }

    if (idGouvernorats.isEmpty()) {
        QMessageBox::information(this, "Aucun gouvernorat", "Aucun gouvernorat trouvé pour cette centrale.");
        return;
    }

    // Lire les noms des gouvernorats depuis gouvernorats.txt
    QMap<int, QString> mapGouv;
    QFile fichierG("gouvernorats.txt");
    if (fichierG.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierG);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2) {
                int id = champs[0].toInt();
                QString nom = champs[1];
                mapGouv[id] = nom;
            }
        }
        fichierG.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier gouvernorats.txt.");
        return;
    }

    // Construire le message d'affichage
    QString message = "Gouvernorats pour la centrale " + QString::number(idCentrale) + ":\n";
    for (int id : idGouvernorats) {
        QString nom = mapGouv.contains(id) ? mapGouv[id] : "(Nom inconnu)";
        message += "- Gouvernorat ID: " + QString::number(id) + ", Nom: " + nom + "\n";
    }

    QMessageBox::information(this, "Gouvernorats liés", message);
}

void MainWindow::affichierCentraleGouvernorat()
{
    bool ok;
    int idGou = QInputDialog::getInt(this, "Recherche", "ID du gouvernorat à chercher :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Lire les liaisons depuis le fichier
    QSet<int> idCentrales;
    QFile fichierL("liaisons.txt");
    if (fichierL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierL);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2 && champs[1].toInt() == idGou) {
                idCentrales.insert(champs[0].toInt());
            }
        }
        fichierL.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier liaisons.txt.");
        return;
    }

    if (idCentrales.isEmpty()) {
        QMessageBox::information(this, "Aucune centrale", "Aucune centrale trouvée pour ce gouvernorat.");
        return;
    }

    // Lire les noms des centrales depuis centrale.txt
    QMap<int, QString> mapCentrales;
    QFile fichierC("centrale.txt");
    if (fichierC.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierC);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2) {
                int id = champs[0].toInt();
                QString nom = champs[1];
                mapCentrales[id] = nom;
            }
        }
        fichierC.close();
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier centrale.txt.");
        return;
    }

    // Construire le message d'affichage
    QString message = "Centrales pour le gouvernorat " + QString::number(idGou) + ":\n";
    for (int id : idCentrales) {
        QString nom = mapCentrales.contains(id) ? mapCentrales[id] : "(Nom inconnu)";
        message += "- Centrale ID: " + QString::number(id) + ", Nom: " + nom + "\n";
    }

    QMessageBox::information(this, "Centrales liées", message);
}

void MainWindow::afficherToutesLesLiaisons()
{
    QFile fichierL("liaisons.txt");
    if (!fichierL.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier liaisons.txt.");
        return;
    }

    // Charger les centrales depuis centrale.txt
    QMap<int, QString> nomsCentrales;
    QFile fichierC("centrale.txt");
    if (fichierC.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierC);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2) {
                int id = champs[0].toInt();
                QString nom = champs[1];
                nomsCentrales[id] = nom;
            }
        }
        fichierC.close();
    }

    // Charger les gouvernorats depuis gouvernorat.txt
    QMap<int, QString> nomsGouvs;
    QFile fichierG("gouvernorat.txt");
    if (fichierG.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fichierG);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(';');
            if (champs.size() >= 2) {
                int id = champs[1].toInt(); // selon le format: nom;id
                QString nom = champs[0];
                nomsGouvs[id] = nom;
            }
        }
        fichierG.close();
    }

    QTextStream in(&fichierL);
    QString message = "Liste des liaisons :\n";
    bool hasLiaisons = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2) {
            int idC = champs[0].toInt();
            int idG = champs[1].toInt();
            QString nomC = nomsCentrales.contains(idC) ? nomsCentrales[idC] : "(Inconnu)";
            QString nomG = nomsGouvs.contains(idG) ? nomsGouvs[idG] : "(Inconnu)";
            message += "Centrale: " + nomC + " (ID: " + QString::number(idC) + ") <--> Gouvernorat: " + nomG + " (ID: " + QString::number(idG) + ")\n";
            hasLiaisons = true;
        }
    }

    fichierL.close();

    if (!hasLiaisons) {
        QMessageBox::information(this, "Liaisons", "Aucune liaison enregistrée.");
    } else {
        QMessageBox::information(this, "Liaisons", message);
    }
}

void MainWindow::supprimerLiaisonParCentrale(int idCentrale)
{
    QFile fichier("liaisons.txt");
    QFile tempFichier("liaisons_temp.txt");

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !tempFichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir les fichiers.");
        return;
    }

    QTextStream in(&fichier);
    QTextStream out(&tempFichier);
    bool supprime = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2 && champs[0].toInt() == idCentrale) {
            supprime = true;
            continue; // ne pas copier cette ligne
        }
        out << ligne << "\n";
    }

    fichier.close();
    tempFichier.close();

    fichier.remove();
    tempFichier.rename("liaisons.txt");

    if (supprime)
        QMessageBox::information(this, "Suppression", "Liaison(s) supprimée(s) avec succès.");
    else
        QMessageBox::information(this, "Suppression", "Aucune liaison trouvée pour cet ID de centrale.");
}

void MainWindow::supprimerLiaisonParGouvernorat(int idGouv)
{
    QFile fichier("liaisons.txt");
    QFile tempFichier("liaisons_temp.txt");

    if (!fichier.open(QIODevice::ReadOnly | QIODevice::Text) ||
        !tempFichier.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir les fichiers.");
        return;
    }

    QTextStream in(&fichier);
    QTextStream out(&tempFichier);
    bool supprime = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(';');
        if (champs.size() >= 2 && champs[1].toInt() == idGouv) {
            supprime = true;
            continue; // ne pas copier cette ligne
        }
        out << ligne << "\n";
    }

    fichier.close();
    tempFichier.close();

    fichier.remove();
    tempFichier.rename("liaisons.txt");

    if (supprime)
        QMessageBox::information(this, "Suppression", "Liaison(s) supprimée(s) avec succès.");
    else
        QMessageBox::information(this, "Suppression", "Aucune liaison trouvée pour cet ID de gouvernorat.");
}

// Les fonctions liées à la classe secteur

void MainWindow::ajouterSecteur()
{
    bool ok;
    QString type = QInputDialog::getItem(this, "Type de secteur",
                                         "Choisissez le type de secteur :", {"Domicile", "Industriel"}, 0, false, &ok);
    if (!ok) return;

    // Demander les données communes
    int id = QInputDialog::getInt(this, "Ajout", "ID du secteur :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Vérifier si l'ID existe déjà dans le fichier
    bool idExiste = false;
    QFile file;
    if (type == "Domicile") {
        file.setFileName("domicile.txt");
    } else if (type == "Industriel") {
        file.setFileName("industriel.txt");
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(";");
            int existingId = fields[0].toInt(); // ID est la première colonne

            if (existingId == id) {
                idExiste = true;
                break;
            }
        }
        file.close();
    }

    if (idExiste) {
        QMessageBox::warning(this, "Erreur", "L'ID du secteur existe déjà dans le fichier.");
        return;
    }

    // Demander les autres informations communes
    float tension = QInputDialog::getDouble(this, "Ajout", "Niveau de tension :", 0, 0, 100000, 2, &ok);
    if (!ok) return;

    float puissance = QInputDialog::getDouble(this, "Ajout", "Puissance consommée :", 0, 0, 100000, 2, &ok);
    if (!ok) return;

    QString horaires = QInputDialog::getText(this, "Ajout", "Horaires de demande :", QLineEdit::Normal, "", &ok);
    if (!ok || horaires.isEmpty()) return;

    int priorite = QInputDialog::getInt(this, "Ajout", "Priorité :", 0, 0, 10, 1, &ok);
    if (!ok) return;

    QString periode = QInputDialog::getText(this, "Ajout", "Période de forte consommation :", QLineEdit::Normal, "", &ok);
    if (!ok || periode.isEmpty()) return;

    int id_gouv = QInputDialog::getInt(this, "Ajout", "ID du gouvernorat :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    // Type spécifique
    if (type == "Domicile") {
        int presence = QMessageBox::question(this, "Énergie renouvelable", "Présence d'énergie renouvelable ?", QMessageBox::Yes | QMessageBox::No);
        bool energieRenouvelable = (presence == QMessageBox::Yes);

        float nbMaisons = QInputDialog::getDouble(this, "Ajout", "Nombre de maisons :", 0, 0, 100000, 2, &ok);
        if (!ok) return;

        // Créer secteur domicile
        SecteurDomicile secteur(id, tension, puissance, horaires.toStdString(), priorite, periode.toStdString(), energieRenouvelable, nbMaisons);

        QFile file("domicile.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << id << ";" << tension << ";" << puissance << ";" << QString::fromStdString(horaires.toStdString()) << ";" << priorite
                << ";" << QString::fromStdString(periode.toStdString()) << ";" << id_gouv << ";" << (energieRenouvelable ? "1" : "0")
                << ";" << nbMaisons << "\n";
            file.close();
        }

    } else if (type == "Industriel") {
        // Get the NombreUsine as a QString
        QString NombreUsineStr = QInputDialog::getText(this, "Ajout", "Nombre d'usines :", QLineEdit::Normal, "", &ok);
        if (!ok || NombreUsineStr.isEmpty()) return;

        // Convert NombreUsine from QString to int
        bool okConversion;
        int NombreUsine = NombreUsineStr.toInt(&okConversion);
        if (!okConversion) {
            QMessageBox::warning(this, "Erreur", "Veuillez entrer un nombre valide pour le nombre d'usines.");
            return;
        }

        // Get the puissance reactive
        float puissanceReactive = QInputDialog::getDouble(this, "Ajout", "Puissance réactive consommée :", 0, 0, 100000, 2, &ok);
        if (!ok) return;

        // Demander le mode de fonctionnement uniquement pour secteur industriel
        QStringList modesFonctionnement = {"Jour", "Jour+Nuit"};
        QString mode = QInputDialog::getItem(this, "Mode de fonctionnement", "Choisissez le mode :", modesFonctionnement, 0, false, &ok);
        if (!ok) return;

        // Créer secteur industriel
        SecteurIndustriel secteur(
            id,
            tension,
            puissance,
            horaires.toStdString(),
            priorite,
            periode.toStdString(),
            NombreUsine,          // Now it's passed as an int
            puissanceReactive,
            mode.toStdString()    // Convert QString to std::string
            );

        QFile file("industriel.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << id << ";" << tension << ";" << puissance << ";" << horaires << ";" << priorite
                << ";" << periode << ";" << id_gouv << ";" << NombreUsine
                << ";" << puissanceReactive << ";" << mode<< "\n";
            file.close();
        }
    }

    QMessageBox::information(this, "Ajout", "Secteur ajouté avec succès !");
}

void MainWindow::afficherSecteurs()
{
    QString message;

    // === Lecture des secteurs DOMICILES ===
    QFile fileDomicile("domicile.txt");
    if (fileDomicile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileDomicile);
        message += "Secteurs Domicile :\n";

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() >= 9) {
                message += "- ID: " + parts[0] +
                           ", Tension: " + parts[1] +
                           "V, Puissance: " + parts[2] +
                           "kW, Horaires: " + parts[3] +
                           ", Priorité: " + parts[4] +
                           ", Période: " + parts[5] +
                           ", ID Gouv: " + parts[6] +
                           ", Énergie Renouvelable: " + (parts[7] == "1" ? "Oui" : "Non") +
                           ", Maisons: " + parts[8] + "\n";
            }
        }
        fileDomicile.close();
    } else {
        message += "Erreur d'accès à domicile.txt\n";
    }

    // === Lecture des secteurs INDUSTRIELS ===
    QFile fileIndustriel("industriel.txt");
    if (fileIndustriel.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileIndustriel);
        message += "\nSecteurs Industriels :\n";

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() >= 10) {  // Ajout de la taille 10 pour prendre en compte le mode
                message += "- ID: " + parts[0] +
                           ", Tension: " + parts[1] +
                           "V, Puissance: " + parts[2] +
                           "kW, Horaires: " + parts[3] +
                           ", Priorité: " + parts[4] +
                           ", Période: " + parts[5] +
                           ", ID Gouv: " + parts[6] +
                           ", Industrie: " + parts[7] +
                           ", Puissance Réactive: " + parts[8] + "kVAR" +
                           ", Mode: " + parts[9] + "\n";  // Affichage du mode de fonctionnement
            }
        }
        fileIndustriel.close();
    } else {
        message += "Erreur d'accès à industriel.txt\n";
    }

    // Affichage
    if (message.isEmpty()) {
        message = "Aucun secteur trouvé.";
    }

    QMessageBox::information(this, "Liste des secteurs", message);
}

void MainWindow::supprimerSecteur()
{
    bool ok;
    QString type = QInputDialog::getItem(this, "Type de secteur",
                                         "Choisissez le type de secteur :", {"Domicile", "Industriel"}, 0, false, &ok);
    if (!ok) return;

    int id = QInputDialog::getInt(this, "Suppression", "ID du secteur à supprimer :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QString nomFichier = (type == "domicile") ? "domicile.txt" : "industriel.txt";
    QFile file(nomFichier);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier " + nomFichier);
        return;
    }

    QStringList lignes;
    QTextStream in(&file);

    bool trouve = false;
    while (!in.atEnd()) {
        QString ligne = in.readLine();
        if (!ligne.isEmpty() && ligne.split(";").value(0).toInt() != id) {
            lignes.append(ligne);
        } else {
            trouve = true;
        }
    }

    file.close();

    if (!trouve) {
        QMessageBox::information(this, "Résultat", "Aucun secteur avec l'ID donné.");
        return;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le fichier " + nomFichier);
        return;
    }

    QTextStream out(&file);
    for (const QString& ligne : lignes) {
        out << ligne << "\n";
    }

    file.close();

    QMessageBox::information(this, "Suppression", "Secteur supprimé avec succès.");
}

void MainWindow::afficherSecteursParGouvernorat()
{
    bool ok;
    int idGouv = QInputDialog::getInt(this, "Recherche", "ID du gouvernorat :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QString message = "Secteurs avec ID gouvernorat " + QString::number(idGouv) + " :\n\n";
    bool trouve = false;

    // ---- Lire domicile.txt ----
    QFile fileD("domicile.txt");
    if (fileD.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileD);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(";");
            if (champs.size() >= 8 && champs[6].toInt() == idGouv) {
                message += "[Domicile] ID: " + champs[0] +
                           ", Puissance: " + champs[2] +
                           ", Maisons: " + champs[8] +
                           ", Energie Renouvelable: " + champs[7] + "\n";
                trouve = true;
            }
        }
        fileD.close();
    }

    // ---- Lire industriel.txt ----
    QFile fileI("industriel.txt");
    if (fileI.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileI);
        while (!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList champs = ligne.split(";");
            if (champs.size() >= 8 && champs[6].toInt() == idGouv) {
                message += "[Industriel] ID: " + champs[0] +
                           ", Type: " + champs[7] +
                           ", Puissance Réactive: " + champs[8] + "\n";
                trouve = true;
            }
        }
        fileI.close();
    }

    if (!trouve) {
        QMessageBox::information(this, "Résultat", "Aucun secteur trouvé pour cet ID gouvernorat.");
    } else {
        QMessageBox::information(this, "Secteurs trouvés", message);
    }
}

void MainWindow::modifierSecteur()
{
    bool ok;
    QString type = QInputDialog::getItem(this, "Type de secteur",
                                         "Choisissez le type de secteur :", {"Domicile", "Industriel"}, 0, false, &ok);
    if (!ok) return;

    QString fichier = (type == "Domicile") ? "domicile.txt" : "industriel.txt";

    int id = QInputDialog::getInt(this, "ID", "Entrez l'ID du secteur à modifier :", 0, 0, 999999, 1, &ok);
    if (!ok) return;

    QFile file(fichier);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier.");
        return;
    }

    QStringList lignes;
    QTextStream in(&file);
    bool trouve = false;

    while (!in.atEnd()) {
        QString ligne = in.readLine();
        QStringList champs = ligne.split(";");
        if (champs.size() < 9) continue;

        if (champs[0].toInt() == id) {
            trouve = true;

            QStringList options;
            if (type == "Domicile") {
                options << "Niveau tension" << "Puissance consommée" << "Horaires demande"
                        << "Priorité" << "Période forte consommation"
                        << "Présence énergie renouvelable" << "Nombre de maisons" << "ID Gouvernorat";
            } else {
                options << "Niveau tension" << "Puissance consommée" << "Horaires demande"
                        << "Priorité" << "Période forte consommation" << "ID Gouvernorat"
                        << "Type d'industrie" << "Puissance réactive" << "Mode de fonctionnement" ; // Ajout de l'ID Gouvernorat
            }

            QString choix = QInputDialog::getItem(this, "Attribut à modifier",
                                                  "Quel attribut souhaitez-vous modifier ?", options, 0, false, &ok);
            if (!ok) return;

            QString nouvelleValeur = QInputDialog::getText(this, "Nouvelle valeur", "Entrez la nouvelle valeur :", QLineEdit::Normal, "", &ok);
            if (!ok) return;

            // Mise à jour
            if (type == "Domicile") {
                int index = options.indexOf(choix);
                champs[index + 1] = nouvelleValeur;  // +1 car l'attribut ID est à l'index 0
            } else {
                int index = options.indexOf(choix);
                champs[index + 1] = nouvelleValeur;  // Mise à jour du mode de fonctionnement
            }

            ligne = champs.join(";");
        }

        lignes.append(ligne);
    }

    file.close();

    if (!trouve) {
        QMessageBox::warning(this, "Erreur", "Secteur avec cet ID non trouvé.");
        return;
    }

    // Réécriture du fichier
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (const QString& l : lignes)
            out << l << "\n";
        file.close();
        QMessageBox::information(this, "Succès", "Secteur modifié avec succès.");
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible d'écrire dans le fichier.");
    }
}

void MainWindow::chercherSecteur()
{
    bool secteurTrouve = false;
    QString idRecherche = QInputDialog::getText(this, "Rechercher un secteur", "Entrez l'ID du secteur:");

    if (idRecherche.isEmpty()) {
        QMessageBox::information(this, "Recherche", "Aucun ID saisi.");
        return;
    }

    QString message;

    // === Recherche dans les secteurs DOMICILES ===
    QFile fileDomicile("domicile.txt");
    if (fileDomicile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileDomicile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() >= 9 && parts[0] == idRecherche) {
                secteurTrouve = true;
                message += "Secteur Domicile trouvé :\n";
                message += "- ID: " + parts[0] +
                           ", Tension: " + parts[1] +
                           "V, Puissance: " + parts[2] +
                           "kW, Horaires: " + parts[3] +
                           ", Priorité: " + parts[4] +
                           ", Période: " + parts[5] +
                           ", ID Gouv: " + parts[6] +
                           ", Énergie Renouvelable: " + (parts[7] == "1" ? "Oui" : "Non") +
                           ", Maisons: " + parts[8] + "\n";
                break;  // Sortie de la boucle si secteur trouvé
            }
        }
        fileDomicile.close();
    }

    // === Recherche dans les secteurs INDUSTRIELS ===
    QFile fileIndustriel("industriel.txt");
    if (fileIndustriel.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileIndustriel);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(";");
            if (parts.size() >= 10 && parts[0] == idRecherche) {
                secteurTrouve = true;
                message += "Secteur Industriel trouvé :\n";
                message += "- ID: " + parts[0] +
                           ", Tension: " + parts[1] +
                           "V, Puissance: " + parts[2] +
                           "kW, Horaires: " + parts[3] +
                           ", Priorité: " + parts[4] +
                           ", Période: " + parts[5] +
                           ", ID Gouv: " + parts[6] +
                           ", Industrie: " + parts[7] +
                           ", Puissance Réactive: " + parts[8] + "kVAR" +
                           ", Mode: " + parts[9] + "\n";
                break;  // Sortie de la boucle si secteur trouvé
            }
        }
        fileIndustriel.close();
    }

    // Affichage du résultat de la recherche
    if (secteurTrouve) {
        QMessageBox::information(this, "Secteur trouvé", message);
    } else {
        QMessageBox::information(this, "Secteur non trouvé", "Aucun secteur trouvé avec l'ID " + idRecherche);
    }
}


//les button
void MainWindow::on_pushButton_clicked()
{
    ajouterCentrale();
}


void MainWindow::on_pushButton_2_clicked()
{
    chercherCentrale();
}


void MainWindow::on_pushButton_3_clicked()
{
    afficherCentrales();
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_7_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_8_clicked()
{
    ajouterGouvernorat();
}


void MainWindow::on_pushButton_9_clicked()
{
    affichierGouvernorat();
}


void MainWindow::on_pushButton_10_clicked()
{
    ajoutelaision();
}


void MainWindow::on_pushButton_11_clicked()
{
    afficherGouvernorats();
}


void MainWindow::on_pushButton_12_clicked()
{
    affichierCentraleGouvernorat();
}


void MainWindow::on_pushButton_13_clicked()
{
    ajouterSecteur();
}


void MainWindow::on_pushButton_14_clicked()
{
    afficherSecteurs();
}


void MainWindow::on_pushButton_16_clicked()
{
    chercheGouvernorat();
}


void MainWindow::on_pushButton_15_clicked()
{
    chercherSecteur();
}


void MainWindow::on_pushButton_17_clicked()
{
    supprimerCentrale();
}


void MainWindow::on_pushButton_18_clicked()
{
    supprimerGouvernorat();
}


void MainWindow::on_pushButton_19_clicked()
{
    afficherToutesLesLiaisons();
}


void MainWindow::on_pushButton_20_clicked()
{
    afficherCentralesParGouvernorat();
}



void MainWindow::on_pushButton_21_clicked()
{
    supprimerSecteur();
}


void MainWindow::on_pushButton_22_clicked()
{
    afficherSecteursParGouvernorat();
}


void MainWindow::on_pushButton_23_clicked()
{
    modifierSecteur();
}


void MainWindow::on_pushButton_24_clicked()
{
    modifierCentrale();
}


void MainWindow::on_pushButton_25_clicked()
{
    calculerProduction();
}


void MainWindow::on_pushButton_26_clicked()
{
    bool ok;

    // 1. Ask for ID Gouv with a numeric input
    int idGouv = QInputDialog::getInt(this, "ID Gouvernorat", "Entrez l'ID du gouvernorat (1-24):", 1, 1, 24, 1, &ok);
    if (!ok) return;

    // 2. Saison drop-down
    QStringList saisons = {"HIVER", "PRINTEMPS", "ETE", "AUTOMNE"};
    QString saisonStr = QInputDialog::getItem(this, "Saison", "Choisissez la saison :", saisons, 0, false, &ok);
    if (!ok) return;

    Saison saison;
    if (saisonStr == "HIVER") saison = HIVER;
    else if (saisonStr == "PRINTEMPS") saison = PRINTEMPS;
    else if (saisonStr == "ETE") saison = ETE;
    else saison = AUTOMNE;

    // 3. Heure drop-down
    QStringList heures = {"NUIT", "MATIN", "MIDI", "APRES_MIDI", "SOIR"};
    QString heureStr = QInputDialog::getItem(this, "Heure", "Choisissez l'heure :", heures, 0, false, &ok);
    if (!ok) return;

    Heure heure;
    if (heureStr == "NUIT") heure = NUIT;
    else if (heureStr == "MATIN") heure = MATIN;
    else if (heureStr == "MIDI") heure = MIDI;
    else if (heureStr == "APRES_MIDI") heure = APRES_MIDI;
    else heure = SOIR;

    // 4. Call the calculation function
    double total = calculateConsommation(idGouv, heure, saison);

    // 5. Show the result
    QMessageBox::information(this, "Consommation Totale", "Consommation estimée : " + QString::number(total, 'f', 2));
}

void MainWindow::on_actionCredit_triggered()
{
    QMessageBox::information(this, "Crédits", "-----------------------------------------------------------------\n"
                                              "                         Développé par :                         \n"
                                              "                                                                 \n"
                                              "             Abdelkerim El Bani & Ahmed Mayekhav                 \n"                        
                                              "                                                                 \n"
                                              "                           Encadré par :                         \n"
                                              "                                                                 \n"
                                              "                        Mme. Wiem taktak                         \n" 
                                              "-----------------------------------------------------------------\n");
}

