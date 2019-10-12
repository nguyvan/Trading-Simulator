#include "strategie.h"

Strategie* MA_Strategie::clone() {
    MA_Strategie* clone = new MA_Strategie();
    clone->ema = this->ema;
    clone->ema_Iterator = this->ema_Iterator;
    return clone;
}


double MA_Strategie::operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours) {
    double montantBase = transactionManager->getMontantBase();
    double montantContrepartie = transactionManager->getMontantContrepartie();
    while(ema_Iterator->getDate() < currentCours->getDate()) {
        ema_Iterator++;
    }
    if(ema_Iterator->getDate() > currentCours->getDate()) {
        return 0;
    }
    if (currentCours->getOpen() > ema_Iterator->getIndice() && montantContrepartie > 0) {
        return montantContrepartie;
    }
    else if (currentCours->getOpen() < ema_Iterator->getIndice() && montantBase > 0){
        return - montantBase;
    }
    else {
        return 0;
    }
}

Strategie* RSI_Strategie::clone() {
    RSI_Strategie* clone = new RSI_Strategie();
    clone->rsi = this->rsi;
    clone->rsi_Iterator = this->rsi_Iterator;
    return clone;
}


double RSI_Strategie::operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours) {
    double montantBase = transactionManager->getMontantBase();
    double montantContrepartie = transactionManager->getMontantContrepartie();
    // move rsi_Iterator to current date
    while(rsi_Iterator->getDate() < currentCours->getDate()) {
        rsi_Iterator++;
    }
    if(rsi_Iterator->getDate() > currentCours->getDate()) {
        //hold until has enough indicateur data
        return 0;
    }

    if (rsi_Iterator->getIndice() <= 20 && montantContrepartie > 0) {
        //buy signal
        return montantContrepartie;
    }
    else if (rsi_Iterator->getIndice() >= 80 && montantBase > 0) {
        //sell signal
        return - montantBase;
    }
    else {
        return 0;
    }
}