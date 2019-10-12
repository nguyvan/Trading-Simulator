#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QDate>
#include "indicateur.h"
#include "trading.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QBarSet>
#include <QTabWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QLineSeries>


class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLC* cours;
    QString forme;
public:
    Bougie(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp = 0.0, QObject *parent = nullptr):
        QCandlestickSet(open, high, low, close, timestamp, parent), cours(c){
        connect(this,SIGNAL(clicked()),this, SLOT(viewCoursOHLC()));
    }
    CoursOHLC& getCoursOHLC() { return *cours; }
    const CoursOHLC& getCoursOHLC() const { return *cours; }
    void SetForme();
    QString GetForme(){return forme;}
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
    void viewCoursOHLC();
};



class EvolutionViewer : public QWidget{
    Q_OBJECT
    EvolutionCours& evolution;
    EMA::Indicateur *ind;
    QBarSeries* o_series;
    QLineSeries* l_series;
    QCandlestickSeries* series; // un ensemble de bougies
    QChart *chart; // un graphique sur un ensemble de bougies
    QChart * chart2;
    QChart * chart3;
    QChartView *chartView; // un viewer de graphique
    QChartView *chartView2;
    QChartView *chartView3;
    QLineEdit* open; // barres d’édition
    QLineEdit* high;
    QLineEdit* low;
    QLineEdit* close;
    QLineEdit* volume;
    QLineEdit* forme;
    QLabel* openl; // labels
    QLabel* highl;
    QLabel* lowl;
    QLabel* closel;
    QLabel* volumel;
    QLabel* formel;
    QPushButton* save; // bouton
    QPushButton* addnewonglet;
    QHBoxLayout* copen; // couches de placement
    QHBoxLayout* chigh;
    QHBoxLayout* clow;
    QHBoxLayout* cclose;
    QHBoxLayout* cvolume;
    QHBoxLayout* cforme;
    QVBoxLayout* coucheCours;
    QHBoxLayout* fenetre;
    QVBoxLayout* graph;

    Bougie* lastBougieClicked=nullptr;
public:
    explicit EvolutionViewer(EvolutionCours& e,QWidget *parent = nullptr);
signals:
    private slots:
        void viewCoursOHLC(Bougie* c);
        void saveCoursOHLC();
    public slots:

};

class Simulation : public QDialog
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


#endif

