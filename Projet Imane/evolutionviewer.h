#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QDate>
#include "trading.h"
#include "indicateur.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QBarSet>
#include <QTabWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineSeries>
#include "transaction.h"
#include "fensecondaire1.h"


class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLC* cours;
    QString forme;
    QString information;
public:
    Bougie(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp = 0.0, QObject *parent = nullptr):
        QCandlestickSet(open, high, low, close, timestamp, parent), cours(c){
        connect(this,SIGNAL(clicked()),this, SLOT(viewCoursOHLC()));
    }
    CoursOHLC& getCoursOHLC() { return *cours; }
    const CoursOHLC& getCoursOHLC() const { return *cours; }
    void SetForme();
    QString GetForme()const{return forme;}
    QString getInformation()const{return information;}
    bool isUp(){
        return (cours->getClose()>=cours->getOpen());
    }
    double upperWick(){
        double upperBody = qMax(cours->getClose(),cours->getOpen());
        return(cours->getHigh()-upperBody);
    }
    double lowerWick(){
        double lowerBody = qMin(cours->getClose(),cours->getOpen());
        return (lowerBody - cours->getLow());
    }
    double getCandleRangeSize(){
        return qAbs(cours->getHigh() - cours->getLow());
    }
    double getCandleBodySize(){
        return qAbs(cours->getClose() - cours->getOpen());
    }
signals:
    void clickBougie(Bougie* c);
private slots:
    void viewCoursOHLC(){ emit clickBougie(this);}
};


class EvolutionViewer : public QWidget{
    Q_OBJECT
    EvolutionCours& evolution;
    EMA Indic_EMA(EvolutionCours);
    RSI Indic_RSI(EvolutionCours);
    FenSecondaire1* fen1;
    //MACD Indic_MACD(EvolutionCours);
    QLineSeries* ema_series;
    QLineSeries* rsi_series;
    //QLineSeries* macd_series;
    QBarSeries* o_series;
    QCandlestickSeries* series; // un ensemble de bougies
    QChart *chart; // un graphique sur un ensemble de bougies
    QChart * chart2;
    QChartView *chartView; // un viewer de graphique
    QChartView *chartView2;
    QLineEdit* open; // barres d’édition
    QLineEdit* high;
    QLineEdit* low;
    QLineEdit* close;
    QLineEdit* volume;
    QLabel *dateDebl;
    QLabel* dateFinl;
    QComboBox* dateDeb;
    QComboBox* dateFin;
    QLabel* openl; // labels
    QLabel* highl;
    QLabel* lowl;
    QLabel* closel;
    QLabel* volumel;
    QLabel* formel;
    QLabel* erreur;
    QPushButton* save; // bouton
    QPushButton* changementDate;
    QPushButton* boutonTransaction;
    QPushButton* addnewonglet;
    QHBoxLayout* date;
    QHBoxLayout* copen; // couches de placement
    QHBoxLayout* chigh;
    QHBoxLayout* clow;
    QHBoxLayout* cclose;
    QHBoxLayout* cvolume;
    QHBoxLayout* cforme;
    QHBoxLayout* cerreur;
    QVBoxLayout* coucheCours;
    QHBoxLayout* fenetre;
    QVBoxLayout* graph;
    QBarCategoryAxis* axisX;
    Bougie* lastBougieClicked=nullptr;
public:
    explicit EvolutionViewer(EvolutionCours& e,QWidget *parent = nullptr);
signals:
    private slots:
        void viewCoursOHLC(Bougie* b);
        void saveCoursOHLC();
        void changerDate();
        void afficherTransaction();
    public slots:
        void getRSISeries(bool ok){ema_series->setVisible(ok); }
        void getEMASeries(bool ok){rsi_series->setVisible(ok); }
};

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
};*/

class TransactionViewer : public QDialog{
    Q_OBJECT
    TransactionManager& transaction;
    QTableWidget *table1;
    QTableView *tableView1;
    QVBoxLayout* tab;
    QHBoxLayout* main;
    QPushButton* annulerTransaction;
    QPushButton* ajouterTransaction;
    QHBoxLayout* coucheTrans;
    QVBoxLayout* achat;
    QVBoxLayout* vente;
    enum Colonne
    {
        DATE, DEVISEBASE, DEVISECONTERPARTIE, ROI
    };
public:
    explicit TransactionViewer(TransactionManager& e, QWidget *parent = nullptr);




};


#endif
