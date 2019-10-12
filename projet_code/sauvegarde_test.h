#ifndef SAUVERGARDE_TEST_H
#define SAUVERGARDE_TEST_H
#include "transaction.h"
#include "editeur_texte_test.h"
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlStreamReader>
//faire un héritage avec classe mère abstraite pour les writer

class EcritureTransaction : public QObject {
    Q_OBJECT
private:

    QDomElement transacManager;
    // le nombre de document enregistre
    QDomDocument doc;
    QFile file;
    QTextStream out;

public slots:
    void demande_ajout(TransactionManager& t);
public :
    EcritureTransaction();
    ~EcritureTransaction();

};
////////////////////////////////////////////////

class EcritureDonnees : public QObject
{
    Q_OBJECT
    public:
        EcritureDonnees();
        ~EcritureDonnees();
    public slots :

        void demande_ajout(EvolutionCours& t);
    private :
        int n=0;// le nombre de document enregistre
        QDomDocument doc;
        QDomElement evolcours;
        QFile file;
        QTextStream out;
};
////////////////////////////////////////////////////
class EcritureNote : public QObject
{
    Q_OBJECT
    public:
        EcritureNote();
        ~EcritureNote();
    public slots :

        void demande_ajout(EditeurText& t);
    private :
        int n=0;// le nombre de document enregistre
        QDomDocument doc;
        QDomElement note;
        QFile file;
        QTextStream out;
};

///////////////////////////////////////////////////////////////

class LectureTransaction : public QObject{
    Q_OBJECT
private :
    QDomDocument doc;
    public:
        LectureTransaction();
        ~LectureTransaction();
    public slots :
        Transaction lire();

};
//////////////////////////////////////////////////////////////////
class LectureNote : public QObject{
    Q_OBJECT
private :
    QDomDocument doc;
    public:
        LectureNote();
        ~LectureNote();
    public slots :
        void lire();
///////////////////////////////////////////////////////////////////
};

class LectureDonnee : public QObject{
    Q_OBJECT
private :
    QDomDocument doc;
    public:
        LectureDonnee();
        ~LectureDonnee();
    public slots :
        void lire();

};
///////////////////////////////////////////////////////////////////
class Sauvegarde{

    QString nomFichierTransaction, nomFichierDonnees, nomFIchierNote;
    EvolutionCours* ct;
    TransactionManager* t;
    EditeurText* et;
public :
    EvolutionCours* getECours() const { return ct;}
    TransactionManager* getTManager() const { return t;}
    EditeurText* getEditeurText() const {return et;}

};
class SauvergardeManager{};// à voir si c'est vraiment utile

#endif // SAUVERGARDE_TEST_H