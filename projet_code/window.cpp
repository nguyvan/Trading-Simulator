#include "window.h"


FenPrincipale::FenPrincipale(EvolutionCours& e) : QMainWindow(), evolution(e)
{
    setWindowTitle("Trading Simulator");
    stack = new QStackedWidget(this);
    fen1 = new FenSecondaire1(this);
    fen2 = new EvolutionViewer(e,this);

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionNouveau = new QAction("Charger nouveau fichier", this);
    menuFichier->addAction(actionNouveau);
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *mode = menuEdition->addMenu("&Mode");
    mode->addAction("Mode automatique");
    mode->addAction("Mode manuel");
    mode->addAction("Mode pas à pas");

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    QAction *actionRSI = new QAction("RSI",this);
    menuAffichage->addAction(actionRSI);
    actionRSI->setCheckable(true); // verifier que c'est coché avec isChecked()
    QAction *actionEMA = new QAction("EMA",this);
    menuAffichage->addAction(actionEMA);
    actionEMA->setCheckable(true);
    QAction *actionMACD = new QAction("MACD",this);
    menuAffichage->addAction(actionMACD);
    actionMACD->setCheckable(true);

    //menuBar()->setStyleSheet("color:blue");
    menuBar()->setEnabled(false);

    stack->addWidget(fen1);
    stack->addWidget(fen2);


    this->setCentralWidget(stack);
    stack->setCurrentIndex(0); // on affiche la première fenêtre à l'ouverture du programme

    connect(&(fen1->getSuivant()), SIGNAL(clicked(bool)), this, SLOT(slotDisplayFen(bool)));
    //connect(fen2, SIGNAL(askDisplayFen(int)), this, SLOT(slotDisplayFen(int)));



}


FenPrincipale::~FenPrincipale()
{

}


void FenPrincipale::slotDisplayFen(bool)
{
    stack->setCurrentIndex(1);
    menuBar()->setEnabled(true);
}


