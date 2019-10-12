#include "fensecondaire.h"
#include "ui_fensecondaire.h"

FenSecondaire::FenSecondaire(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenSecondaire)
{
    ui->setupUi(this);
    setWindowTitle("Chargement des données");
    ui->dateDebutDonnees->setCalendarPopup(true);
    ui->dateDebutDonnees->setEnabled(false);

    connect(ui->chargerFichier, SIGNAL(toggled(bool)), ui->dateDebutDonnees, SLOT(setEnabled(bool)));

    connect(ui->m_boutonContinuer,SIGNAL(clicked()),this, SLOT(continuer()));
    connect(ui->m_boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

FenSecondaire::~FenSecondaire()
{
    delete ui;
}

void FenSecondaire::continuer(){
    DevisesManager& m=DevisesManager::getManager();
    m.creationDevise("USD", "Dollar Américain","USA");
    m.creationDevise("BTC", "BitCoin","monnaie virtuelle");
    const PaireDevises& BTC_USD=m.getPaireDevises("BTC", "USD");
    EvolutionCours e(BTC_USD);
    if(ui->chargerFichier->isChecked()){
        QString  fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers (*.csv *.txt)");
          if(!fichier.isEmpty()){
              QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
              Reader r;
              QString date, date1;
              date.append(ui->dateDebutDonnees->date().toString("yyyy-MM-dd"));
              date1.append("2010'07'16");
              r.setDate(date1);
              r.setFichier(fichier);
              r.setText(r.getFichier(),r.getDate());

              int gt=0;
              qDebug()<<date;
              qDebug()<<r.getListDate()[gt];
              while(gt<3223 && date!=r.getListDate()[gt]){
                  gt++;
              }
              qDebug()<<gt;
              qDebug()<<date;
              qDebug()<<r.getListDate()[3000];
              if(date==r.getListDate()[gt]){
                  for(int i=gt;i<3223;i++)
                  {
                      QDate ol= QDate::fromString(r.getListDate()[i],"yyyy-MM-dd");
                      e.addCours(r.getOpen()[i].toDouble(),r.getHigh()[i].toDouble(),r.getLow()[i].toDouble(),r.getClose()[i].toDouble(),r.getVolume()[i].toDouble(),ol);
                  }
              }
              else {
                  for(int i=0;i<3223;i++)
                  {
                      QDate ol= QDate::fromString(r.getListDate()[i],"yyyy-MM-dd");
                      e.addCours(r.getOpen()[i].toDouble(),r.getHigh()[i].toDouble(),r.getLow()[i].toDouble(),r.getClose()[i].toDouble(),r.getVolume()[i].toDouble(),ol);
                  }
              }
              //EvolutionViewer v(e);
              FenPrincipale *fenetrePrincipale = new FenPrincipale(e, this);
              fenetrePrincipale->setWindowModality(Qt::ApplicationModal);
              fenetrePrincipale->show();
          }
          else{
              QMessageBox::critical(this, "Fichier", "Vous n'avez pas charger de fichier.");
          }



    }
    if(ui->donneesInitiales->isChecked()){


        e.addCours(4261.48000000,4745.42000000,3400.00000000,4724.89000000,10000,QDate(2017,1,1));
        e.addCours(4689.89000000,4939.19000000,2817.00000000,4378.51000000,5000,QDate(2017,2,1));
        e.addCours(4378.49000000,6498.01000000,4110.00000000,6463.00000000,40000,QDate(2017,3,1));
        e.addCours(6463.00000000,11300.03000000,5325.01000000,9838.96000000,50000,QDate(2017,4,1));
        e.addCours(9837.00000000,19798.68000000,9380.00000000,13716.36000000,80000,QDate(2017,5,1));
        e.addCours(13715.65000000,17176.24000000,9035.00000000,10285.10000000,10000,QDate(2017,6,1));
        e.addCours(10285.10000000,11786.01000000,6000.01000000,10326.76000000,50000,QDate(2017,7,1));
        e.addCours(10325.64000000,11710.00000000,6600.10000000,6923.91000000,44000,QDate(2017,8,1));
        e.addCours(6922.00000000,9759.82000000,6430.00000000,9246.01000000,450012,QDate(2017,9,1));
        e.addCours(9246.01000000,10020.00000000,7032.95000000,7485.01000000,123456,QDate(2017,10,1));
        e.addCours(7485.01000000,7786.69000000,5750.00000000,6390.07000000,456123,QDate(2017,11,1));
        e.addCours(6391.08000000,8491.77000000,6070.00000000,7730.93000000,12345,QDate(2017,12,1));
        e.addCours(7735.67000000,7750.00000000,5880.00000000,7011.21000000,1234512,QDate(2018,1,1));
        e.addCours(7011.21000000,7410.00000000,6111.00000000,6626.57000000,123456,QDate(2018,2,1));
        e.addCours(6626.57000000,7680.00000000,6205.00000000,6371.93000000,100000,QDate(2018,3,1));
        e.addCours(6369.52000000,6615.15000000,3652.66000000,4041.32000000,15203,QDate(2018,4,1));
        e.addCours(4041.27000000,4312.99000000,3156.26000000,3702.90000000,123000,QDate(2018,5,1));
        e.addCours(3701.23000000,4069.80000000,3349.92000000,3434.10000000,100000,QDate(2018,6,1));
        e.addCours(3434.10000000,4198.00000000,3373.10000000,3813.69000000,45000,QDate(2018,7,1));
        e.addCours(3814.26000000,4140.00000000,3670.69000000,4106.65000000,45000,QDate(2018,8,1));


        //EvolutionViewer v(e);
        FenPrincipale *fenetrePrincipale = new FenPrincipale(e, this);
        fenetrePrincipale->setWindowModality(Qt::ApplicationModal);
        fenetrePrincipale->show();
    }
}


