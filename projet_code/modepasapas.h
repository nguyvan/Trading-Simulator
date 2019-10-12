#ifndef MODEPASPASWIDGET_H
#define MODEPASPASWIDGET_H


#include "simulation.h"
#include <QWidget>
#include <QMessageBox>


namespace Ui {
    class ModePasPaswidget;
}


class ModePasPaswidget : public QWidget {
    Q_OBJECT
public:

    explicit ModePasPaswidget(ModePas_Pas* modePas_Pas, QWidget *parent = nullptr);

    void updateData();
    ~ModePasPaswidget();
signals:

    void transactionChanged();
private slots:

    void updateCurrentCours();

    void on_goBack_clicked();

    void on_comboBox_timer_currentIndexChanged(const QString &arg1);

    void on_pushButton_achat_clicked();

    void on_pushButton_vente_clicked();

    void on_pushButton_annulerTransaction_clicked();

private:
    Ui::ModePasPaswidget *ui;
    ModePas_Pas* modePas_Pas;
    TransactionManager* transactionManager;
};

#endif // MODEPASPASWIDGET_H
