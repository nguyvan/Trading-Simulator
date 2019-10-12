#include "window.h"


FenPrincipale::FenPrincipale(EvolutionCours& e, QWidget *parent) : QMainWindow(parent), evolution(e)/*, transaction(t)*/
{

    setWindowTitle("Trading Simulator");
    stack = new QStackedWidget(this);
    fen1 = new FenSecondaire1(e, this);

    //fen2 = new FenSecondaire2(e, this);
    fen2 = new EvolutionViewer(e,this);

    //fen3 = new TransactionViewer(fen1->getTransactionManager(), this);
    //TransactionManager t = fen1->getTransactionManager();
    //fen3 = new TransactionViewer(t, this);

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionNouveau = new QAction("Charger nouveau fichier", this);
    menuFichier->addAction(actionNouveau);
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(slotDisplayFen1()));

    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QMenu *mode = menuEdition->addMenu("&Mode");
    mode->addAction("Mode automatique");
    mode->addAction("Mode manuel");
    mode->addAction("Mode pas à pas");
    QAction *actionTransaction = new QAction("&Transaction");
    menuEdition->addAction(actionTransaction);



    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    QAction *actionRSI = new QAction("RSI",this);
    menuAffichage->addAction(actionRSI);
    actionRSI->setCheckable(true); // verifier que c'est coché avec isChecked()
    connect(actionRSI, SIGNAL(triggered(bool)), fen2, SLOT(getRSISeries(bool)));

    QAction *actionEMA = new QAction("EMA",this);
    menuAffichage->addAction(actionEMA);
    actionEMA->setCheckable(true);
    connect(actionEMA, SIGNAL(triggered(bool)), fen2, SLOT(getEMASeries(bool)));

    /*QAction *actionMACD = new QAction("MACD",this);
    menuAffichage->addAction(actionMACD);
    actionMACD->setCheckable(true);*/

    //menuBar()->setStyleSheet("color:blue");
    menuBar()->setEnabled(false);

    //stack->addWidget(fen);
    stack->addWidget(fen1);
    stack->addWidget(fen2);
    //stack->addWidget(fen3);

    this->setCentralWidget(stack);
    stack->setCurrentIndex(0); // on affiche la première fenêtre à l'ouverture du programme





    connect(&(fen1->getAnnuler()), SIGNAL(clicked()), this, SLOT(close()));
    connect(&(fen1->getSuivant()), SIGNAL(clicked()), this, SLOT(slotDisplayFen2()));
    //connect(fen2, SIGNAL(askDisplayFen(int)), this, SLOT(slotDisplayFen(int)));
    //connect(&(fen1->getSuivant()), SIGNAL(clicked()), this, SLOT(slotDisplayFen3()));
    //connect(actionTransaction, SIGNAL(triggered()), this, SLOT(quit()));
}


FenPrincipale::~FenPrincipale()
{

}


void FenPrincipale::slotDisplayFen1()
{
    stack->setCurrentIndex(0);
    menuBar()->setEnabled(false);
}

void FenPrincipale::slotDisplayFen2()
{
    stack->setCurrentIndex(1);
    menuBar()->setEnabled(true);
}

/*void FenPrincipale::slotDisplayFen3()
{
    stack->setCurrentIndex(2);
    menuBar()->setEnabled(true);
}*/


