#ifndef FENSECONDAIRE1_H
#define FENSECONDAIRE1_H
#include <QtWidgets>

class FenSecondaire1: public QWidget{
    Q_OBJECT
    public:
    FenSecondaire1(QWidget *parent = 0);

public slots:
    void ouvrirFichier();
    void validation();
    //void annulation();
    QPushButton& getSuivant(){return *suivant;}

    private:
        QPushButton *m_boutonOuvrirFichier;
        QPushButton *valider;
        QPushButton *suivant;
        QRadioButton *modeAutomatique;
        QComboBox *listeStrategie;
        QRadioButton *modeManuel;
        QRadioButton *modePas;
        QDateEdit *date;
        QLineEdit *deviseBase;
        QLineEdit *deviseContrepartie;
};

#endif // FENSECONDAIRE1_H
