#ifndef CANDLE_H
#define CANDLE_H
#include <QtGlobal>
#include "evolutionviewer.h"


class CandleDoji : public Bougie{
    Q_OBJECT
private:
    QString name;
public:
    CandleDoji(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp=0.0, QObject* parent = nullptr, QString n=""):Bougie(open,high,low,close,c,timestamp,parent), name(n){}
    virtual ~CandleDoji();
    bool isValid(Bougie* b);
    QString getName(Bougie* b);
};



class CandleHammer : public Bougie{
    Q_OBJECT
private:
    QString name;
public:
    CandleHammer(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp=0.0, QObject* parent = nullptr, QString n=""):Bougie(open,high,low,close,c,timestamp,parent), name(n){}
    virtual ~CandleHammer();
    bool isValid(Bougie* b);
    QString getName(Bougie* b);
};

class CandleWhiteMarubozu : public Bougie{
    Q_OBJECT
private:
    QString name;
public:
    CandleWhiteMarubozu(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp=0.0, QObject* parent = nullptr, QString n=""):Bougie(open,high,low,close,c,timestamp,parent), name(n){}
    virtual ~CandleWhiteMarubozu();
    bool isValid(Bougie* b);
    QString getName(Bougie* b);
};

class CandleBlackMarubozu : public Bougie{
    Q_OBJECT
private:
    QString name;
public:
    CandleBlackMarubozu(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp=0.0, QObject* parent = nullptr, QString n=""):Bougie(open,high,low,close,c,timestamp,parent), name(n){}
    virtual ~CandleBlackMarubozu();
    bool isValid(Bougie* b);
    QString getName(Bougie* b);
};

class CandleSpinningTop : public Bougie{
    Q_OBJECT
private:
    QString name;
public:
    CandleSpinningTop(qreal open, qreal high, qreal low, qreal close, CoursOHLC* c, qreal timestamp=0.0, QObject* parent = nullptr, QString n=""):Bougie(open,high,low,close,c,timestamp,parent), name(n){}
    virtual ~CandleSpinningTop();
    bool isValid(Bougie* b);
    QString getName(Bougie* b);

};

#endif // CANDLE_H
