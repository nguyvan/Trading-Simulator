#ifndef INDICATEUR_H
#define INDICATEUR_H
#include <QString>
#include "trading.h"
/*Information de Indicateurs (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators)
 */
class IndiceIndicateur {
private:
        double donnee;
        QDate  date;
public:
        IndiceIndicateur(){}
        double getIndice() const { return donnee;}
        QDate  getDate() const { return date;}
        void setIndice(double donnee) { this->donnee = donnee;}
        void setDate(QDate date) { this->date = date;}
        //for debugging
        QString toString() const {return date.toString() + " indicateur: " + QString::number(donnee);}
};

//classe abstrait des indicateur

class Indicateur {
protected:
    EvolutionCours& evolutionCours;
    QString nom;
    IndiceIndicateur* indices;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
public:
    Indicateur(EvolutionCours& evolutionCours, QString nom);
    ~Indicateur(){delete[] indices;}
    IndiceIndicateur* getIndicateur() {return indices;}
    using iterator = IndiceIndicateur*;
    using const_iterator = const IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
    const_iterator cbegin() const {return indices;}
    const_iterator cend() const {return indices+ nbIndicateur;}
    IndiceIndicateur* searchIndice(CoursOHLC* cours);
};


class EMA : public Indicateur{
private:
    unsigned int period;
public:
    void setperiod(unsigned int p){period=p;}
    EMA(EvolutionCours& evolutionCours, QString nom="EMA", unsigned period=10);
};


class RSI : public Indicateur {
private:
    unsigned int lookBackPeriod;
    double overboughtBound, oversoldBound;
public:
    RSI(EvolutionCours& evolutionCours, QString nom="RSI", unsigned int lookbackPeriod = 14, double overboughtBound= 70, double oversoldBound= 30);
};


class MACD : public Indicateur {
private:
    unsigned int longPeriod;
    unsigned int shortPeriod;
    unsigned int signalPeriod;
    IndiceIndicateur* signalLine;
    IndiceIndicateur* histogram;
public:
    MACD(EvolutionCours& evolutionCours, QString nom="MACD", unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9);
};
/*
class IndicateurManage {
private:
    Indicateur* listeIndicateur;
    int nbIndicateur;
};
*/
#endif // INDICATEUR_H
