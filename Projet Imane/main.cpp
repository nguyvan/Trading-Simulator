#include <QApplication>
#include "trading.h"
#include "evolutionviewer.h"
#include "fensecondaire.h"
#include "test_parser.h"
#include "window.h"
using namespace std;

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    FenSecondaire fenetre;
    fenetre.show();

    return app.exec();
}

