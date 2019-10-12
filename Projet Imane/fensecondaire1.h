#ifndef FENSECONDAIRE1_H
#define FENSECONDAIRE1_H
#include <QtWidgets>
#include <QDebug>
//#include"evolutionviewer.h"
#include "test_parser.h"
#include "transaction.h"

class FenSecondaire1: public QWidget{
    Q_OBJECT
    public:
    explicit FenSecondaire1(EvolutionCours& e, QWidget *parent = nullptr);
    //EvolutionCours& getEvolution()const {return evolution;}
    //void setEvolution(EvolutionCours e) {evolution = e;}
    //static QString& getNomFichier(){return fichier;}
    //static void setNomFichier(QString f){fichier=f;}
    //QFileDialog* Fenetre;
    //QDialog* FenetreValid;
    TransactionManager* getTransactionManager(){return transaction;}

    private:
        //QPushButton *m_boutonOuvrirFichier;
        QPushButton *valider;
        QPushButton *annuler;
        QRadioButton *modeAutomatique;
        QComboBox *listeStrategie;
        QComboBox *listePaireDevises;
        QRadioButton *modeManuel;
        QRadioButton *modePas;
        QDateEdit *date;
        QLineEdit *deviseBase;
        QLineEdit *deviseContrepartie;
        QLineEdit *tauxCommission;
        //static QString fichier;
        EvolutionCours& evolution;
        TransactionManager* transaction;
        //TransactionViewer* tview;

    signals:
        //void envoyer(QString* fichier);
    public slots:
        //void ouvrirFichier(QString fich);
        void validation();
        //void annulation();
        QPushButton& getSuivant(){return *valider;}
        QPushButton& getAnnuler(){return *annuler;}

};

#endif // FENSECONDAIRE1_H

