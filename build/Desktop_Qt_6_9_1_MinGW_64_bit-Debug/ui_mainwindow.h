/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCredit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QPushButton *pushButton_12;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_24;
    QPushButton *pushButton_17;
    QPushButton *pushButton_25;
    QPushButton *pushButton_26;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_16;
    QPushButton *pushButton_22;
    QPushButton *pushButton_18;
    QPushButton *pushButton_20;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_15;
    QPushButton *pushButton_14;
    QPushButton *pushButton_13;
    QPushButton *pushButton_21;
    QPushButton *pushButton_23;
    QDateTimeEdit *dateTimeEdit;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_19;
    QPushButton *pushButton_11;
    QPushButton *pushButton_10;
    QWidget *page_4;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QMenu *menuabout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionCredit = new QAction(MainWindow);
        actionCredit->setObjectName("actionCredit");
        actionCredit->setMenuRole(QAction::AboutRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");

        horizontalLayout->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");

        horizontalLayout->addWidget(pushButton_5);

        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName("pushButton_7");

        horizontalLayout->addWidget(pushButton_7);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        pushButton_12 = new QPushButton(page_3);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(30, 430, 721, 23));
        groupBox = new QGroupBox(page_3);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 0, 231, 321));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 90, 211, 23));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 30, 211, 23));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 60, 211, 23));
        pushButton_24 = new QPushButton(groupBox);
        pushButton_24->setObjectName("pushButton_24");
        pushButton_24->setGeometry(QRect(10, 120, 211, 23));
        pushButton_17 = new QPushButton(groupBox);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(10, 150, 211, 21));
        pushButton_25 = new QPushButton(groupBox);
        pushButton_25->setObjectName("pushButton_25");
        pushButton_25->setGeometry(QRect(10, 200, 211, 51));
        pushButton_26 = new QPushButton(groupBox);
        pushButton_26->setObjectName("pushButton_26");
        pushButton_26->setGeometry(QRect(10, 260, 211, 51));
        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(270, 0, 241, 321));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(10, 90, 221, 23));
        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(10, 30, 221, 23));
        pushButton_16 = new QPushButton(groupBox_2);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(10, 60, 221, 23));
        pushButton_22 = new QPushButton(groupBox_2);
        pushButton_22->setObjectName("pushButton_22");
        pushButton_22->setGeometry(QRect(20, 230, 181, 23));
        pushButton_18 = new QPushButton(groupBox_2);
        pushButton_18->setObjectName("pushButton_18");
        pushButton_18->setGeometry(QRect(10, 150, 221, 23));
        pushButton_20 = new QPushButton(groupBox_2);
        pushButton_20->setObjectName("pushButton_20");
        pushButton_20->setGeometry(QRect(10, 200, 221, 61));
        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(540, 0, 231, 321));
        pushButton_15 = new QPushButton(groupBox_3);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setGeometry(QRect(10, 60, 211, 23));
        pushButton_14 = new QPushButton(groupBox_3);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(10, 30, 211, 23));
        pushButton_13 = new QPushButton(groupBox_3);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(10, 90, 211, 23));
        pushButton_21 = new QPushButton(groupBox_3);
        pushButton_21->setObjectName("pushButton_21");
        pushButton_21->setGeometry(QRect(10, 150, 211, 23));
        pushButton_23 = new QPushButton(groupBox_3);
        pushButton_23->setObjectName("pushButton_23");
        pushButton_23->setGeometry(QRect(10, 120, 211, 23));
        dateTimeEdit = new QDateTimeEdit(groupBox_3);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setGeometry(QRect(20, 210, 194, 41));
        plainTextEdit = new QPlainTextEdit(groupBox_3);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(30, 270, 181, 31));
        groupBox_4 = new QGroupBox(page_3);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setGeometry(QRect(10, 330, 761, 171));
        pushButton_19 = new QPushButton(groupBox_4);
        pushButton_19->setObjectName("pushButton_19");
        pushButton_19->setGeometry(QRect(20, 70, 721, 23));
        pushButton_11 = new QPushButton(groupBox_4);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(20, 130, 721, 23));
        pushButton_10 = new QPushButton(groupBox_4);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(20, 40, 721, 23));
        stackedWidget->addWidget(page_3);
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox_2->raise();
        groupBox->raise();
        pushButton_12->raise();
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        pushButton_4 = new QPushButton(page_4);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(330, 0, 80, 23));
        stackedWidget->addWidget(page_4);

        gridLayout->addWidget(stackedWidget, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuabout = new QMenu(menubar);
        menuabout->setObjectName("menuabout");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuabout->menuAction());
        menuabout->addAction(actionCredit);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Grid - C++ Project", nullptr));
        actionCredit->setText(QCoreApplication::translate("MainWindow", "Credit", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "page1", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "page2", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Chercher les Centrales Par ID Gouvernerat", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Centrale", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Ajouter Centrale", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Afficher Centrale", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Chercher Centrale ", nullptr));
        pushButton_24->setText(QCoreApplication::translate("MainWindow", "Modifier Centrale", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Suprimer Centrale", nullptr));
        pushButton_25->setText(QCoreApplication::translate("MainWindow", "Calculer Production", nullptr));
        pushButton_26->setText(QCoreApplication::translate("MainWindow", "Calculer Consommation", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Gouvernerat", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Ajouter Gouvernerat", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Afficher Gouvernerat", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Chercher Gouvernerat", nullptr));
        pushButton_22->setText(QCoreApplication::translate("MainWindow", "affiche les secteur", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "Suprimer Gouvernerat", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MainWindow", "Centrale Fournissants", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Secteur", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Chercher Secteur", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "Afficher Secteur", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Ajouter Secteur", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MainWindow", "Suprimer Secteur", nullptr));
        pushButton_23->setText(QCoreApplication::translate("MainWindow", "Modifier Secteur", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("MainWindow", "                 M\303\251teo\n"
"", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Liaison", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MainWindow", "Afficher Toutes les Liaisons", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Chercher les Gouvernerats par ID Centrale", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Ajouter une Liaison", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "page2", nullptr));
        menuabout->setTitle(QCoreApplication::translate("MainWindow", "about", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
