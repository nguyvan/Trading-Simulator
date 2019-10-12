#ifndef STRATEGIE_H
#define STRATEGIE_H
#include "indicateur.h"
#include "transaction.h"
#include "trading.h"
class Strategie {
protected:
    QString nom = "unnamed strategie";
    EvolutionCours* evolutionCours = nullptr;
    Strategie(QString nom) : nom(nom){}
    Strategie(Strategie* strategie) = delete;
    void setEvolutionCours(EvolutionCours* evolutionCours) {this->evolutionCours = evolutionCours;}
public:
    virtual ~Strategie() = default;
    virtual Strategie* clone() {
        Strategie* clone = new Strategie(nom);
        clone->setEvolutionCours(evolutionCours);
        return clone;
    }
    const QString& getNom() const {return nom;}
    virtual double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours){return 0;}
};

class MA_Strategie : public Strategie {
    EMA* ema=nullptr;
    EMA::iterator ema_Iterator=nullptr;
    MA_Strategie(): Strategie("MA Strategie") {}
public:
    ~MA_Strategie() {delete ema;}
    Strategie* clone();
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};
class RSI_Strategie : public Strategie {
    RSI* rsi=nullptr;
    RSI::iterator rsi_Iterator=nullptr;
    RSI_Strategie() : Strategie("RSI Strategie") {}
public:
    ~RSI_Strategie() {delete rsi;}
    Strategie* clone();
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

#endif // STRATEGIE_H