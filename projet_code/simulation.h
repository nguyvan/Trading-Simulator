#ifndef COMMANDE_H
#define COMMANDE_H
#include "strategie.h"
#include "trading.h"
#include "transaction.h"
#include <QTimer>
class Mode {
protected:
    QString type;
    QString nom;
    EvolutionCours& evolutionCours;
    EvolutionCours::iterator currentCours = evolutionCours.begin();
    TransactionManager transactionManager;
public:

    Mode(QString type, QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage, double montantBaseInitial, double montantContrepartieInitial) :
        type(type), evolutionCours(evolutionCours), currentCours(coursDebut),
        transactionManager(TransactionManager(pourcentage, montantBaseInitial, montantContrepartieInitial, montantContrepartieInitial + montantBaseInitial*coursDebut->getClose())) {
        //if (!verifierNomSimulation(nom)) throw TradingException("Simulation: ce nom est déjà pris");
        this->nom = nom;
    }

    ~Mode();

    void achat(CoursOHLC* cours, double montant) {transactionManager.addTransaction_cours(evolutionCours.getPaireDevises(), cours, true, montant);}

    void vente(CoursOHLC* cours, double montant) {transactionManager.addTransaction_cours(evolutionCours.getPaireDevises(), cours, false, montant);}

    EvolutionCours& getEvolutionCours() const {return evolutionCours;}

    const QString& getNom() const {return nom;}

    const QString& getType() const {return type;}

    EvolutionCours::iterator getCurrentCours() const {return currentCours;}

    TransactionManager* getTransactionManager() {return &transactionManager;}
};




class ModeManuel : public Mode {

public:

    ModeManuel(QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000) :
        Mode("Manuel", nom, evolutionCours, coursDebut, pourcentage, montantBaseInitial, montantContrepartieInitial) {}

    virtual ~ModeManuel() = default;



    void annule() {transactionManager.deleteLastTransaction();}
};


class ModePas_Pas: public QObject, public ModeManuel {
    Q_OBJECT
    QTimer* timer;
public:

    ModePas_Pas(QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=30000, QObject* parent=nullptr);

    ~ModePas_Pas() {delete timer;}

    void setTimer(unsigned int interval) {timer->setInterval(interval); qDebug() << timer->interval();}

    void achat(double montant) {transactionManager.addTransaction_cours(evolutionCours.getPaireDevises(), currentCours, true, montant);}

    void vente(double montant) {transactionManager.addTransaction_cours(evolutionCours.getPaireDevises(), currentCours, false, montant);}
signals:

    void coursChanged();

    void endSimulation();
private slots:

    void iteration();
public slots:

    void goBack(QDate date);

};


class ModeAutomatique : public QObject, public Mode {
    Q_OBJECT
    Strategie* strategie = nullptr;
    QTimer* timer;                  //timer of between cours
public:

    ModeAutomatique(QString nom, EvolutionCours& evolutionCours, EvolutionCours::iterator coursDebut, Strategie* strategie, double pourcentage=0.001, double montantBaseInitial=0, double montantContrepartieInitial=1000000, unsigned int time_interval=30000, QObject* parent=nullptr);

    ~ModeAutomatique() {delete strategie;   delete timer;}


    QString getStrategieName() const {return strategie->getNom();}

    void setTimer(unsigned int interval) {timer->setInterval(interval);}
signals:

    void coursChanged();

    void endSimulation();
private slots:

    void iteration();

};

#endif // COMMANDE_H
