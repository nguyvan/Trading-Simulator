#include "strategie.h"
/*
double TrendingFollowing::algorithm (EMA::iterator it){
        if (it->getIndice()<=30){
            return -(rand()%(getMax()-getMin()+1)+getMin());
        }
        else {
            return (rand()%(getMax()-getMin()+1)+getMin());
        }
}


double HighFrequency::algorithm(RSI::iterator it){
        if (it->getIndice()<=20){
            return -(rand()%(getMax()-getMin()+1)+getMin());
        }
        else if (it->getIndice()>=80) {
            return (rand()%(getMax()-getMin()+1)+getMin());
        }
        else {return 0;}
}

/*double algoMACD::algorithm(MACD::iterator it){
        MACD::iterator it2 = it;
        it2++;
        if (it->getIndice()<0){
            if(it2>it){
                return -(rand()%(automatique.getMax()-automatique.getMin()+1)+automatique.getMin());
            }
            else {return 0;}
        }else {
            if (it2<it){
               return (rand()%(automatique.getMax()-automatique.getMin()+1)+automatique.getMin());
            } else return 0;
        }
}*/
