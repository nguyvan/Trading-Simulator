#include "fensecondaire1.h"

void FenSecondaire1::ouvrirFichier(){
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers (*.csv *.txt)");
    if(!fichier.isEmpty()){
        QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    }
    else{
        QMessageBox::critical(this, "Fichier", "Vous n'avez pas charger de fichier.");
    }

}

void FenSecondaire1::validation(){
    int reponse  = QMessageBox::question(this, "Validation", "Voulez-vous vraiment passer à la suite?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        QMessageBox::information(this, "Bienvenue", "C'est partie pour la simulation");
    }
    else if (reponse == QMessageBox::No){
        QMessageBox::critical(this, "Echec", "Vous n'avez pas valider vos choix de données, recommencez !");
    }
}


FenSecondaire1::FenSecondaire1(QWidget *parent): QWidget(parent){

        QVBoxLayout *layout1 = new QVBoxLayout;

        QLabel *texte = new QLabel("<strong>Bienvenue sur la plateforme Trading Simulator</strong>", this);

        texte->setAlignment(Qt::AlignCenter);
        texte->setStyleSheet("color:blue");
        texte->setFont(QFont("Comic Sans MS", 15));

        layout1->addWidget(texte);

        QVBoxLayout *layout2 = new QVBoxLayout;
        m_boutonOuvrirFichier = new QPushButton("Charger le ficher de données");
        m_boutonOuvrirFichier->setMaximumWidth(300);
        layout2->addWidget(m_boutonOuvrirFichier);
        QGroupBox *groupChargementFichier = new QGroupBox("Chargement des données");
        groupChargementFichier->setLayout(layout2);
        connect(m_boutonOuvrirFichier, SIGNAL(clicked()),this, SLOT(ouvrirFichier()));

        QGroupBox *groupMode = new QGroupBox("Modes");
        modeAutomatique = new QRadioButton("Mode Automatique");

        QComboBox* listeStrategie = new QComboBox;
        listeStrategie->addItem("Strategie 1");
        listeStrategie->addItem("Strategie 2");
        listeStrategie->addItem("Strategie 3");
        listeStrategie->setEnabled(false);

        connect(modeAutomatique, SIGNAL(toggled(bool)), listeStrategie, SLOT(setEnabled(bool)));


        QVBoxLayout *layout5 = new QVBoxLayout;
        layout5->addWidget(modeAutomatique);
        layout5->addWidget(listeStrategie);

        modeManuel = new QRadioButton("Mode Manuel");
        modePas = new QRadioButton("Mode Pas à Pas");

        QVBoxLayout *layout3 = new QVBoxLayout;
        layout3->addLayout(layout5);
        layout3->addWidget(modeManuel);
        layout3->addWidget(modePas);
        groupMode->setLayout(layout3);

        QGroupBox *groupParametre = new QGroupBox("Paramètres de simulation");
        date = new QDateEdit;
        date->setDate(QDate::currentDate()); // changer avec la date de début de données
        deviseBase = new QLineEdit;
        deviseContrepartie = new QLineEdit;
        deviseBase->setPlaceholderText("0");
        deviseContrepartie->setPlaceholderText("1000000");
        QValidator *validator = new QIntValidator(0,10000000);
        deviseBase->setValidator(validator);
        deviseContrepartie->setValidator(validator);
        QFormLayout *layout4 = new QFormLayout;
        layout4->addRow("Date de début des données", date);
        layout4->addRow("Devise de base", deviseBase);
        layout4->addRow("Devise de contrepartie", deviseContrepartie);
        groupParametre->setLayout(layout4);

        valider = new QPushButton("Valider");
        suivant = new QPushButton("Suivant");
        valider->setMaximumWidth(300);
        suivant->setMaximumWidth(300);
        QHBoxLayout *layout6 = new QHBoxLayout;
        layout6->addWidget(valider);
        layout6->addWidget(suivant);
        connect(valider, SIGNAL(clicked()),this, SLOT(validation()));


        QVBoxLayout *layout = new QVBoxLayout;
        layout->addLayout(layout1);
        layout->addWidget(groupChargementFichier);
        layout->addWidget(groupMode);
        layout->addWidget(groupParametre);
        layout->addLayout(layout6);

        setLayout(layout);


}


