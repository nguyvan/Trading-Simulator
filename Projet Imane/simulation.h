/*#ifndef COMMANDE_H
#define COMMANDE_H
#include "strategie.h"
#include "trading.h"
#include "transaction.h"
#include <QTimer>
class Mode {
protected:
    QString type;
    EvolutionCours& evolutionCours;
    EvolutionCours::iterator currentCours, finishCours;
    TransactionManager transactionManager;
public:
    Mode(QString type, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial):
        type(type), evolutionCours(evolutionCours), currentCours(coursDebut), finishCours(coursFini),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial)) {}
    void achat(const PaireDevises* paire, CoursOHLC* cours, double montant) {transactionManager.addTransaction(paire, cours, true, montant);}
    void vente(const PaireDevises* paire, CoursOHLC* cours, double montant) {transactionManager.addTransaction(paire, cours, false, montant);}
    EvolutionCours::iterator getCurrentCours() const {return currentCours;}
    EvolutionCours::iterator getFinishCours() const {return finishCours;}
    //const TransactionManager* getTransactionManager() const {return &transactionManager;}
};

class ModeManuel : public Mode {
public:
    ModeManuel(EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        Mode("Manuel", evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {}
    void annule() {transactionManager.deleteLastTransaction();}
};


class ModePas_Pas: public QObject, public ModeManuel {
    Q_OBJECT
    QTimer* timer;
public:
    ModePas_Pas(EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, unsigned int time_interval=600000):
        ModeManuel(evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
        type = "Pas_Pas";
        timer = new QTimer();
        timer->setInterval(time_interval);              //set timer interval in ms
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
        timer->start();
    }
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != finishCours) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
    void buy_slot(double montant) {achat(&evolutionCours.getPaireDevises(), currentCours, montant);}
    void sell_slot(double montant) {vente(&evolutionCours.getPaireDevises(), currentCours, montant);}
};



class ModeAutomatique : public QObject, public Mode {
    Q_OBJECT
    TrendingFollowing* stra;
    EMA* a;
    QTimer* timer;                  //timer of between cours
public:
    ModeAutomatique(EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, EvolutionCours::iterator coursFini, double pourcentage, double montantBaseInitial, double montantContrepartieInitial, TrendingFollowing* strategie, unsigned int time_interval=600000):
        Mode("Automatique", evolutionCours, coursDebut, coursFini, pourcentage, montantBaseInitial, montantContrepartieInitial) {
        if (!strategie) throw TradingException("ModeAutomatique: Strategie is null");
        this->stra = strategie;
        timer = new QTimer();
        timer->setInterval(time_interval);              //set timer interval in ms
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(iteration()));
        timer->start();
    }
    TrendingFollowing* getStra(){return stra;}
signals:
    void endSimulation();
private slots:
    void iteration();
public slots:
    void setTimer(unsigned int interval) {timer->setInterval(interval);}
    void pause() {timer->stop();}
    void play() {if (currentCours != finishCours) timer->start();}
    void speedUp() {if(timer->interval() > 10000) timer->setInterval(timer->interval() - 10000);}
    void slowDown() {timer->setInterval(timer->interval() + 10000);}
};

#endif // COMMANDE_H
*/
