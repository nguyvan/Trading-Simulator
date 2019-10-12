#include "transaction.h"
void Transaction::setTransaction(const PaireDevises* p,const CoursOHLC* c,bool i, double m){
    if (p == nullptr || c == nullptr || m<0) throw ;
    paire = p;
    cours = c;
    buy = i;
    if (i == true){montant = m;}
    else {montant=-m;}
}

TransactionManager::~TransactionManager() {
    delete[] trans;
}

void TransactionManager::addTransaction(const PaireDevises* paire,const CoursOHLC* cours, bool i, double montant) {
    if (nbMaxTrans == nbTrans) { // agrandissement du tableau
        Transaction* newtab = new Transaction[nbMaxTrans + 100];
        for (unsigned int i = 0; i < nbTrans; i++) newtab[i] = trans[i];
        // mise � jour des attributs
        Transaction* old = trans;
        trans = newtab;
        nbMaxTrans += 100;
        delete[] old; // destruction de l'ancien tableau
    }
    trans[nbTrans].setTransaction(paire,cours,i,montant);
    nbTrans++;
}

void TransactionManager::deleteLastTransaction() {
    if (nbTrans!=0) { // si la liste n'est pas nulle
        delete &trans[nbTrans-1];
        nbTrans--;
    }

}

TransactionManager::TransactionManager(const TransactionManager& e) :
    pourcentage(e.pourcentage),
    montantBaseInitial(e.montantBaseInitial),
    montantContrePartieInitial(e.montantContrePartieInitial),
    trans(new Transaction[e.nbTrans]),
    nbTrans(e.nbTrans),
    nbMaxTrans(e.nbTrans)
{
    for (unsigned int i = 0; i < nbTrans; i++) trans[i] = e.trans[i];
}

TransactionManager& TransactionManager::operator=(const TransactionManager& e) {
    if (this != &e) { // se proteger de l'auto-affectation
        pourcentage = e.pourcentage;
        montantBaseInitial = e.montantBaseInitial;
        montantContrePartieInitial = e.montantContrePartieInitial;
        nbTrans = 0;
        for (unsigned int i = 0; i < e.nbTrans; i++)
            addTransaction(e.trans[i].getPaire(),e.trans[i].getCours(),e.trans[i].Buy(),e.trans[i].getMontant());
    }
    return *this;
}

