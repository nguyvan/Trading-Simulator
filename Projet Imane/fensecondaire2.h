#ifndef FENSECONDAIRE2_H
#define FENSECONDAIRE2_H
#include <QWidget>
#include <QtCharts>
#include "trading.h"
#include <QTabWidget>
#include <QDebug>
#include "evolutionviewer.h"
#include "transaction.h"
#include "test_parser.h"
#include "fensecondaire1.h"


/*class FenSecondaire2: public QWidget{
    Q_OBJECT
    public:
    explicit FenSecondaire2(EvolutionCours& e, QWidget *parent = nullptr);
    //EvolutionCours& getEvolution()const {return evolution;}
    //void setEvolution(EvolutionCours e){evolution=e;}
    //TransactionManager& getTransactionManager()const{return transaction;}
    //void setTransactionManager(TransactionManager t)const{transaction = t;}
    //static QString& getNomFichier(){return fichier;}
    //static void setNomFichier(QString f){fichier=f;}

    private:
        EvolutionCours& evolution;
        //TransactionManager& transaction;
        //static QString fichier;
    signals:

    public slots:

};*/

/*class Simulation : public QDialog
{
    Q_OBJECT

public:
    explicit Simulation(const QString &fileName, QWidget *parent = nullptr);

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};

class Accueil : public QWidget
{
    Q_OBJECT

public:
    explicit Accueil(const QFileInfo &fileInfo, QWidget *parent = 0);
};
*/



#endif // FENSECONDAIRE2_H
