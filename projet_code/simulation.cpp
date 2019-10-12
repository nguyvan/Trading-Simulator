#include "simulation.h"

ModeAutomatique::ModeAutomatique(QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut,  Strategie* strategie, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval, QObject* parent):
    QObject(parent), Mode("Automatique", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {
    if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
    this->strategie = strategie;
    timer = new QTimer(this);
    timer->setInterval(time_interval);              //set timer interval in ms
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
    timer->start();
}

void ModeAutomatique::iteration() {
    double decision = (*strategie)(&transactionManager, currentCours);
    qDebug() << "decision" + QString::number(decision);
    if (decision > 0) {
        achat(currentCours, decision);
    }
    else if (decision < 0) {
        vente(currentCours, -decision);
    }
    currentCours++;        //move to next day

    if(currentCours == evolutionCours.end()) {
        timer->stop();
        emit endSimulation();
    }
    emit coursChanged();
}
ModePas_Pas::ModePas_Pas(QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval, QObject* parent):
    QObject(parent), ModeManuel(nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {
    type = "Pas_Pas";
    timer = new QTimer(this);
    timer->setInterval(time_interval);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
    timer->start();
}


void ModePas_Pas::iteration(){
    currentCours++;
    if(currentCours == evolutionCours.end()) {
        timer->stop();
        emit endSimulation();
    }
    emit coursChanged();
}
