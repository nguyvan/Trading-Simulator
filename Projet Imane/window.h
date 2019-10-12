#ifndef WINDOW_H
#define WINDOW_H
#include <QtCharts>
#include "trading.h"
#include "evolutionviewer.h"
#include "transaction.h"
#include "test_parser.h"
#include <QTabWidget>
//#include "fensecondaire.h"
//#include "ui_fensecondaire.h"
#include "fensecondaire1.h"
#include "fensecondaire2.h"
#include <QDebug>


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

        public:
            explicit FenPrincipale(EvolutionCours& , QWidget *parent=nullptr);
            ~FenPrincipale();

        private:
            QStackedWidget *stack;
            FenSecondaire1 *fen1;
            EvolutionViewer *fen2;
            TransactionViewer *fen3;
            //FenSecondaire2 *fen2;
            EvolutionCours& evolution;

        signals:
        public slots:
            void slotDisplayFen1();
            void slotDisplayFen2();
            //void slotDisplayFen3();
            //void slotDisplayRSI();
            //void slotDisplayEMA();


};






#endif // WINDOW_H
