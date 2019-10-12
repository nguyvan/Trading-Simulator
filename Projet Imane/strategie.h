/*#ifndef STRATEGIE_H
#define STRATEGIE_H
#include "evolutionviewer.h"
#include "indicateur.h"

class strategie{
    int min;
    int max;
public:
    int getMin(){return min;}
    int getMax(){return max;}
    virtual double algorithm(Indicateur::iterator it)=0;
    virtual ~strategie(){}
};

class TrendingFollowing: public strategie{
public:
    double algorithm(EMA::iterator it);
};

class HighFrequency: public strategie{
public:
    double algorithm(RSI::iterator it);
};

class algoMACD: public strategie{
public:
    double algorithm(MACD::iterator it);
};


#endif // STRATEGIE_H
*/
