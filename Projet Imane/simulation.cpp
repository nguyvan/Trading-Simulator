#include "simulation.h"

/*---------------------------------------------------------- Methodes de Mode Automatique -------------------------------------------------------*/
/*void ModeAutomatique::iteration() {
    a = new EMA(evolutionCours,"EMA",10);
    for (EMA::iterator it = a->begin();it != a->end(); it++){
        double decision = stra->algorithm(it);
        if (decision > 0) {
            achat(&evolutionCours.getPaireDevises(), currentCours, decision);
        }
        else if (decision < 0) {
            vente(&evolutionCours.getPaireDevises(), currentCours, -decision);
        }
        if(currentCours == finishCours) {
            timer->stop();
            emit endSimulation();
        }
    }
    currentCours++;        //move to next day
}*/

/*---------------------------------------------------------- Methodes de Mode Pas à pas -------------------------------------------------------*/
/*void ModePas_Pas::iteration(){
    if(currentCours == finishCours) {
        timer->stop();
        emit endSimulation();
    }
    currentCours++;
}*/
