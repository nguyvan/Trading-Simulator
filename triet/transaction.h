#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "trading.h"

class Transaction {
    friend class TransactionManager;
    Transaction* transactionDernier = nullptr;
    const PaireDevises& paire;
    CoursOHLC* cours;
    bool achat;
    double montantBaseInitial;
    double montantContrepartieInitial;
    double montantBase;
    double montantContrepartie;
    Transaction(Transaction* transactionDernier, const PaireDevises& paire, CoursOHLC* cours, bool achat, double montantBase, double montantContrepartie, double montantBaseInitial, double montantContrepartieInitial):
    transactionDernier(transactionDernier), paire(paire), cours(cours), achat(achat), montantBase(montantBase), montantContrepartie(montantContrepartie), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial) {}
public:

    double differenceBase() const {
        if(!transactionDernier) return this->montantBase - montantBaseInitial;
        return this->montantBase - transactionDernier->montantBase;
    }

    double differenceContrepartie() const {
        if(!transactionDernier) return this->montantContrepartie - montantContrepartieInitial;
        return this->montantContrepartie - transactionDernier->montantContrepartie;
    }

    double montantTotal() const {return montantBase*cours->getClose() + montantContrepartie;}

    double roi(double montantTotalInitial) const {return montantTotal()/ montantTotalInitial;}

    double getMontantBase() const {return montantBase;}

    double getMontantContrepartie() const {return montantContrepartie;}

    CoursOHLC* getCours() const {return cours;}

    bool est_achat() const {return achat;}

    Transaction* getLastTransaction() const {return transactionDernier;}

    Transaction* next() const {return getLastTransaction();}

    bool hasNext() const {if (transactionDernier) {return true;} else {return false;}}
};


class TransactionManager {
    friend class Mode; /**<déclaration d'amitié : Simulation*/
    Transaction* listeTransaction = nullptr;
    double pourcentage;
    double montantBaseInitial;
    double montantContrepartieInitial;
    double montantTotalInitial; /**<montantTotalInitial :double montant total disposé avant la simulation */

    TransactionManager(double pourcentage, double montantBaseInitial, double montantContrepartieInitial, double montantTotalInitial):
    pourcentage(pourcentage), montantBaseInitial(montantBaseInitial), montantContrepartieInitial(montantContrepartieInitial), montantTotalInitial(montantTotalInitial) {}

    ~TransactionManager();

    void clearTransactions();
public:

    void addTransaction_cours(const PaireDevises& paire, CoursOHLC* cours, bool achat, double montant);

    void addTransaction(const PaireDevises& paire, CoursOHLC* cours, bool achat, double montantBase, double montantContrepartie);

    void deleteLastTransaction();

    double solde() const;                       //retourne le solde en devise de contrepartie

    double getMontantBase() const {
        if (!listeTransaction) {return montantBaseInitial;}
            return listeTransaction->getMontantBase();
    }

    double getPourcentage() const {return pourcentage;}

    double getMontantContrepartie() const {
        if (!listeTransaction) {return montantContrepartieInitial;}
            return listeTransaction->getMontantContrepartie();
    }

    double getMontantTotalInitial() const {return montantTotalInitial;}
    using iterator = Transaction*;

    iterator head() const {return listeTransaction;}
};


#endif // TRANSACTION_H
