#include "fensecondaire2.h"

//QString FenSecondaire2::fichier = "C:/Users/mouna/Desktop/projet - fichiers exemples/AMZN.csv";

/*FenSecondaire2::FenSecondaire2(EvolutionCours& e, QWidget *parent):
    QWidget(parent), evolution(e){



    EvolutionViewer* fenetreGraphique = new EvolutionViewer(e,this);
    //TransactionViewer* transac = new TransactionViewer(getTransactionManager(), this);

}*/

/*Simulation::Simulation(const QString &fileName, QWidget *parent)
    : QDialog(parent)
{
    Reader* b;
    QFileInfo fileInfo(fileName);
    //EvolutionCours& e();

    tabWidget = new QTabWidget;
    tabWidget->addTab(new Accueil(fileInfo), tr("Accueil"));

    //tabWidget->addTab(new EvolutionViewer(), tr("Graphique"));
    //tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Tab Dialog"));
}


Accueil::Accueil(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QLineEdit *fileNameEdit = new QLineEdit(fileInfo.fileName());

    QLabel *pathLabel = new QLabel(tr("Path:"));
    QLabel *pathValueLabel = new QLabel(fileInfo.absoluteFilePath());
    pathValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QLabel *sizeLabel = new QLabel(tr("Size:"));
    qlonglong size = fileInfo.size()/1024;
    QLabel *sizeValueLabel = new QLabel(tr("%1 K").arg(size));
    sizeValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);
    mainLayout->addWidget(fileNameEdit);
    mainLayout->addWidget(pathLabel);
    mainLayout->addWidget(pathValueLabel);
    mainLayout->addWidget(sizeLabel);
    mainLayout->addWidget(sizeValueLabel);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

*/
