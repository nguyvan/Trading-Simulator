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
#include <QMessageBox>

class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLC* cours;
protected:
    bool isUp(Bougie* b){
        return (b->close()>=b->open());
    }
    double upperWick(Bougie* b){
        double upperBody = qMax(b->close(),b->open());
        return(b->high()-upperBody);
    }
    double lowerWick(Bougie* b){
        double lowerBody = qMin(b->close(),b->open());
        return (lowerBody - b->low());
    }
    double getCandleRangeSize(Bougie* b){
        return qAbs(b->high() - b->low());
    }
    double getCandleBodySize(Bougie* b){
        return qAbs(b->close() - b->open());
    }
public:
    Bougie(qreal open, qreal high, qreal low, qreal close,CoursOHLC* c, qreal timestamp = 0.0, QObject *parent = nullptr):
        QCandlestickSet(open, high, low, close, timestamp, parent), cours(c){
        connect(this,SIGNAL(clicked()),this, SLOT( viewCoursOHLC()));
    }
    virtual ~Bougie();
    virtual bool isValid(Bougie* b);
    virtual QString getName(Bougie* b);
    CoursOHLC& getCoursOHLC() { return *cours; }
    const CoursOHLC& getCoursOHLC() const { return *cours; }

signals:
    void clickBougie(Bougie* c);
private slots:
    void viewCoursOHLC(){ emit clickBougie(this); }
};



class EvolutionViewer : public QWidget{
    Q_OBJECT
    EvolutionCours& evolution;
    EMA Indic_EMA(EvolutionCours);
    RSI Indic_RSI(EvolutionCours);
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
    QLineEdit* bougie;
    QLabel* openl; // labels
    QLabel* highl;
    QLabel* lowl;
    QLabel* closel;
    QLabel* volumel;
    QLabel* bougiel;
    QPushButton* save; // bouton
    QPushButton* addnewonglet;
    QHBoxLayout* copen; // couches de placement
    QHBoxLayout* chigh;
    QHBoxLayout* clow;
    QHBoxLayout* cclose;
    QHBoxLayout* cbougie;
    QVBoxLayout* coucheCours;
    QHBoxLayout* fenetre;
    QVBoxLayout* graph;

    Bougie* lastBougieClicked=nullptr;
public:
    explicit EvolutionViewer(EvolutionCours& e,QWidget *parent = nullptr);
signals:
    private slots:
        void viewCoursOHLC(Bougie* b);
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
