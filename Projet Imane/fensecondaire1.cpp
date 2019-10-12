#include "fensecondaire1.h"


/*void FenSecondaire1::ouvrirFichier(){
    //Fenetre = new QFileDialog;

      QString  fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers (*.csv *.txt)");
        if(!fichier.isEmpty()){

            QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
            FenSecondaire1::setNomFichier(fichier);
            qDebug() << "Nom du Fichier" << getNomFichier();
            emit envoyer(&fichier);
        }
        else{
            QMessageBox::critical(this, "Fichier", "Vous n'avez pas charger de fichier.");
        }

}*/

void FenSecondaire1::validation(){
    //FenetreValid = new QDialog;
    int reponse  = QMessageBox::question(this, "Validation", "Voulez-vous vraiment passer à la suite?", QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes){
        QMessageBox::information(this, "Bienvenue", "C'est partie pour la simulation");
        //setNomFichier(fichier);
        //qDebug() << "Nom du Fichier valid:" << getNomFichier();
        QString deviseBaseFinale = deviseBase->text();
        QString deviseContrepartieFinale = deviseContrepartie->text();
        QString tauxCommissionFinale = tauxCommission->text();
        double p = tauxCommissionFinale.toDouble();
        double b = deviseBaseFinale.toDouble();
        double c = deviseContrepartieFinale.toDouble();
        transaction = new TransactionManager(p,b,c);
        qDebug()<<"validation"<<transaction;
        //tview = new TransactionViewer(*transaction, this);
        //tview->show();

    }
    else if (reponse == QMessageBox::No){
        QMessageBox::critical(this, "Echec", "Vous n'avez pas valider vos choix de données, recommencez !");
    }

}

//QString FenSecondaire1::fichier = "C:/Users/mouna/Desktop/projet - fichiers exemples/AMZN.csv";

FenSecondaire1::FenSecondaire1(EvolutionCours& e, QWidget *parent):
    QWidget(parent), evolution(e) {


        QVBoxLayout *layout1 = new QVBoxLayout;

        QLabel *texte = new QLabel("<strong>Bienvenue sur la plateforme Trading Simulator</strong>", this);

        texte->setAlignment(Qt::AlignCenter);
        texte->setStyleSheet("color:blue");
        texte->setFont(QFont("Comic Sans MS", 15));

        layout1->addWidget(texte);

        //QVBoxLayout *layout2 = new QVBoxLayout;
        //m_boutonOuvrirFichier = new QPushButton("Charger le ficher de données");
        //m_boutonOuvrirFichier->setMaximumWidth(300);
        //layout2->addWidget(m_boutonOuvrirFichier);
        //QGroupBox *groupChargementFichier = new QGroupBox("Chargement des données");
        //groupChargementFichier->setLayout(layout2);


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
        listePaireDevises = new QComboBox;
        listePaireDevises->addItem("BTC_USD");
        /*date = new QDateEdit;
        date->setDate(QDate::currentDate()QDate::fromString(r.getListDate()[0],"yyyy-MM-dd")); // changer avec la date de début de données*/
        deviseBase = new QLineEdit;
        deviseContrepartie = new QLineEdit;
        tauxCommission = new QLineEdit;
        deviseBase->setPlaceholderText("0");
        deviseContrepartie->setPlaceholderText("1000000");
        tauxCommission->setPlaceholderText("0.001");
        QValidator *validator = new QIntValidator(0,10000000);
        deviseBase->setValidator(validator);
        deviseContrepartie->setValidator(validator);
        QFormLayout *layout4 = new QFormLayout;
        layout4->addRow("Paire de devises", listePaireDevises);
        //layout4->addRow("Date de début des données", date);
        layout4->addRow("Devise de base", deviseBase);
        layout4->addRow("Devise de contrepartie", deviseContrepartie);
        layout4->addRow("Taux de commission", tauxCommission);
        groupParametre->setLayout(layout4);

        valider = new QPushButton("Valider");
        annuler = new QPushButton("Annuler");
        valider->setMaximumWidth(300);
        annuler->setMaximumWidth(300);
        QHBoxLayout *layout6 = new QHBoxLayout;
        layout6->addWidget(valider);
        layout6->addWidget(annuler);


        QVBoxLayout *layout = new QVBoxLayout;
        layout->addLayout(layout1);
        //layout->addWidget(groupChargementFichier);
        layout->addWidget(groupMode);
        layout->addWidget(groupParametre);
        layout->addLayout(layout6);

        setLayout(layout);


        //connect(m_boutonOuvrirFichier, SIGNAL(clicked()),this, SLOT(ouvrirFichier()));

        //QSignalMapper *signalMapper = new QSignalMapper(this);
        //connect(m_boutonOuvrirFichier,SIGNAL(clicked()), signalMapper, SLOT(map()));
        //signalMapper->setMapping(m_boutonOuvrirFichier, fichier);
        //connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(ouvrirFichier(QString)));

        connect(valider, SIGNAL(clicked()),this, SLOT(validation()));
        connect(annuler, SIGNAL(clicked()), this, SLOT(close()));

        //if(FenetreValid->exec()==0){
            //Reader r;
            //QString date;
            //date.append("2019'05'12");
            //r.setDate(date);
            //r.setFichier(fichier);
            //qDebug() << "Nom du Fichier" << fichier;
            //r.setText(r.getFichier(),r.getDate());
            //DevisesManager& m=DevisesManager::getManager();
            //m.creationDevise("USD", "Dollar Américain","USA");
            //m.creationDevise("BTC", "BitCoin","monnaie virtuelle");
            //const PaireDevises& BTC_USD=m.getPaireDevises("BTC", "USD");
            //setEvolution(BTC_USD);

            //int taille=r.getLow().size();
            //for(int gt=3000;gt<3220;gt++)
            //{
               // QDate ol= QDate::fromString(r.getListDate()[gt],"yyyy-MM-dd");
               // getEvolution().addCours(r.getOpen()[gt].toDouble(),r.getHigh()[gt].toDouble(),r.getLow()[gt].toDouble(),r.getClose()[gt].toDouble(),r.getVolume()[gt].toDouble(),ol);
            //}
        //}

}



