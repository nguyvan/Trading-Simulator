#include "candle.h"

bool CandleDoji::isValid(Bougie* b){
    double bodySize = getCandleBodySize(b);
    double candleRange = getCandleRangeSize(b);
    double percentage = (bodySize/candleRange)*100.0;
    bool a = percentage <= 15;
    bool c = qAbs(b->open() - b->close() < 300);
    return(a && c);
}

QString CandleDoji::getName(Bougie* b){
    if(isValid(b)) {return "Doji";}
    else {return "Inconnue";}
}

CandleDoji::~CandleDoji(){}


bool CandleHammer::isValid(Bougie* b){
    double candleRange = getCandleRangeSize(b);
    double percentage = (upperWick(b)/candleRange)*100.0;
    bool a = percentage <= 5;
    bool c = (2*lowerWick(b))>getCandleBodySize(b);
    return(a && c);
}
QString CandleHammer::getName(Bougie* b){
    if(isValid(b)) {return "Hammer";}
    else {return "Inconnue";}
}

CandleHammer::~CandleHammer(){}



bool CandleWhiteMarubozu::isValid(Bougie* b){
    bool a = qAbs(b->close() - b->high() < 300);
    bool c = qAbs(b->open() - b->low() < 300);
    return(a && c);
}
QString CandleWhiteMarubozu::getName(Bougie* b){
    if(isValid(b)) {return "White Marubozu";}
    else {return "Inconnue";}
}

CandleWhiteMarubozu::~CandleWhiteMarubozu(){}

bool CandleBlackMarubozu::isValid(Bougie* b){
    bool a = qAbs(b->close() - b->low() < 300);
    bool c = qAbs(b->open() - b->high() < 300);
    return(a && c);
}
QString CandleBlackMarubozu::getName(Bougie* b){
    if(isValid(b)) {return "Black Marubozu";}
    else {return "Inconnue";}
}

CandleBlackMarubozu::~CandleBlackMarubozu(){}



bool CandleSpinningTop::isValid(Bougie* b){
    double bodySize = getCandleBodySize(b);
    double candleRange = getCandleRangeSize(b);
    double percentage = (bodySize/candleRange)*100.0;
    bool a = percentage<=40;
    bool c =qAbs(upperWick(b)-lowerWick(b)<300);
    return(a && c);
}
QString CandleSpinningTop::getName(Bougie* b){
    if(isValid(b)) {return "Spinning Top";}
    else {return "Inconnue";}
}

CandleSpinningTop::~CandleSpinningTop(){}
