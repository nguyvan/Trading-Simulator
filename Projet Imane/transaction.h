#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "trading.h"

class Transaction {
    const PaireDevises* paire;
    const CoursOHLC* cours;
    double montant;
    bool buy;
    QDate date;
public:
    Transaction(){}
    Transaction(PaireDevises& p, const CoursOHLC* c, double m, bool b) :paire(&p), cours(c), montant(m), buy(b) {}
    double getMontant(){return montant;}
    void setTransaction(const PaireDevises* p,const CoursOHLC* c,bool b, double m);
    const CoursOHLC* getCours() const {return cours;}
    const PaireDevises* getPaire() const {return paire;}
    bool Buy(){return buy;}
    QDate getDate() { return date = cours->getDate(); }
};


class TransactionManager{
    double pourcentage=0.001;
    double montantBaseInitial = 0;
    double montantContrePartieInitial = 1000000;
    Transaction* trans = nullptr ;
    unsigned int nbTrans = 0;
    unsigned int nbMaxTrans = 0;
public:
    TransactionManager(double p, double b, double c) :pourcentage(p), montantBaseInitial(b), montantContrePartieInitial(c) {}
    ~TransactionManager();
    TransactionManager(const TransactionManager& e);
    TransactionManager& operator=(const TransactionManager& e);
    unsigned int getNBTrans() const { return nbTrans; }
    double getPourcentage(){return pourcentage;}
    double getMontantBase(){return montantBaseInitial;}
    double getMontantContrePartie(){return montantContrePartieInitial;}
    double getROI(){return trans->getMontant()*trans->getCours()->getOpen()/(getMontantBase()*trans->getCours()->getOpen()+getMontantContrePartie());}
    using iterator = Transaction*;
    iterator begin() { return iterator(trans); }
    iterator end() { return iterator(trans + nbTrans); }
    using const_iterator = const Transaction*;
    const_iterator begin() const { return trans; }
    const_iterator end() const { return trans + nbTrans; }
    const_iterator cbegin() const { return trans; }
    const_iterator cend() const { return trans + nbTrans; }
    void addTransaction(const PaireDevises* p,const CoursOHLC* cours, bool i, double montant);
    void deleteLastTransaction();
};


#endif // TRANSACTION_H
