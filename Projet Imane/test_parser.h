#ifndef TEST_PARSER_H
#define TEST_PARSER_H
#include <QString>
#include <QFile>
#include <QDate>
#include "trading.h"

//en vrai ce serait peut être plus intelligent de faire un héritage ici, avec la classe mère sera abstraite. Je sais pas si lire les fichiers ligne par ligne
//est la meilleure solution ou si on récupère tout le fichier et on se débrouille avec
//ça m'a l'air mieux de prendre tout le texte avec le reader et d'écrire dans le fichier ligne par ligne comme ça on peut incrémenter au fur et à mesure les transactions

class Reader {

    QDate date;
    QString nomFichier;
    QString text;
    QStringList listDate;
    QStringList open;
    QStringList high;
    QStringList low;
    QStringList close;
    QStringList volume;


public :
    Reader(){}
    QString getNameDevise(const QString& nomFichier);
    QString getFichier()const {return nomFichier;}
    void setFichier(QString& file) {nomFichier.append(file);}
    void setFichier(const char* file) {nomFichier.append(file);}
    QString getText()const {return text;}
    void setText(const QString& nomFichier, QDate date);

    QDate getDate() const {return date;}
    void setDate(QDate& day){date = day;}
    void setDate(QString& str){date = QDate::fromString(str,"yyyy-MM-dd");}
    QStringList getOpen()const{return open;}
    QStringList getListDate()const{return listDate;}
    QStringList getHigh()const{return high;}
    QStringList getLow()const{return low;}
    QStringList getClose()const{return close;}
    QStringList getVolume()const{return volume;}


};

class Writer{
    QString nomFichier;
    QString line;
public :
    QString getFichier(){return nomFichier;}
    void setFichier(QString& file) {nomFichier.append(file);}
    QString getLine(){return line;}
    // il nous faudrait peut être une classe/fonction qui converti les coursOHLC en string adaptée pourles rentrer dans le fichier à sauvegarder
    //la fonction me semble plus adpatée

    //QString transforme(CoursOHLC& c); quelque chose comme ça
    void setLine(QString& cours){line.append(cours);}
};

#endif
