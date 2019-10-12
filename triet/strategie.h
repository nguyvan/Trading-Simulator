#ifndef STRATEGIE_H
#define STRATEGIE_H
#include "indicateur.h"
#include "transaction.h"
#include "trading.h"
#include <cstdlib>
class Strategie {
protected:
    QString nom = "unnamed strategie";
    EvolutionCours* evolutionCours = nullptr;
    int min; // montant minimal pour chaque transaction
    int max; // montant maximal pour chaque transaction
    Strategie(QString nom) : nom(nom){}
    Strategie(Strategie* strategie) = delete;
    void setEvolutionCours(EvolutionCours* evolutionCours) {this->evolutionCours = evolutionCours;}
    void setNom(QString nom){this->nom = nom;}
public:
    Strategie(QString nom, EvolutionCours* evolutionCours, int min, int max): nom(nom),evolutionCours(evolutionCours), min(min), max(max){}
    void setmin(int m){min = m;}
    void setmax(int m){max = m;}
    int getmin(){return min;}
    int getmax(){return max;}
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
    EMA::iterator ema_Iterator=nullptr;
    MA_Strategie(): Strategie("MA Strategie") {}
public:
    MA_Strategie(QString nom, EvolutionCours* evolutionCours, int min, int max):Strategie(nom,evolutionCours,min,max){}
    ~MA_Strategie() {delete ema_Iterator;}
    void setEMA_Iterator(EMA::iterator it){ema_Iterator=it;}
    EMA::iterator getEMA_Iterator(){return ema_Iterator;}
    Strategie* clone();
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};
class RSI_Strategie : public Strategie {
    RSI::iterator rsi_Iterator=nullptr;
    RSI_Strategie() : Strategie("RSI Strategie") {}
public:
    RSI_Strategie(QString nom, EvolutionCours* evolutionCours, int min, int max):Strategie(nom,evolutionCours,min,max){}
    ~RSI_Strategie() {delete rsi_Iterator;}
    void setRSI_Iterator(RSI::iterator it){rsi_Iterator=it;}
    RSI::iterator getRSI_Iterator(){return rsi_Iterator;}
    Strategie* clone();
    double operator()(TransactionManager* transactionManager, EvolutionCours::iterator currentCours);
};

#endif // STRATEGIE_H