#ifndef WINDOW_H
#define WINDOW_H
#include <QtCharts>
#include "trading.h"
#include "evolutionviewer.h"
#include <QTabWidget>
#include "fensecondaire1.h"


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

        public:
            FenPrincipale(EvolutionCours& e);
            ~FenPrincipale();


        public slots:
            void slotDisplayFen(bool ok);


        private:
            QStackedWidget *stack;
            FenSecondaire1 *fen1;
            EvolutionViewer *fen2;
            EvolutionCours& evolution;

};






#endif // WINDOW_H
