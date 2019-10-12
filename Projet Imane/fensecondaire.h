#ifndef FENSECONDAIRE_H
#define FENSECONDAIRE_H

#include "window.h"
#include"evolutionviewer.h"
#include <QWidget>

namespace Ui {
class FenSecondaire;
}

class FenSecondaire : public QWidget
{
    Q_OBJECT

public:
    explicit FenSecondaire(QWidget *parent = nullptr);
    ~FenSecondaire();

private slots:
    void continuer();
private:
    Ui::FenSecondaire *ui;
};

#endif // FENSECONDAIRE_H
