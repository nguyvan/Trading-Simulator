#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours& e,QWidget *parent):
    QWidget(parent),evolution(e)
{
    series = new QCandlestickSeries(this);
    series->setName(evolution.getPaireDevises().toString());
    series->setIncreasingColor(QColor(Qt::green));
    series->setIncreasingColor(QColor(Qt::red));

    o_series = new QBarSeries(this);
    o_series->setName(evolution.getPaireDevises().toString());

    QStringList o_categories;
    QStringList categories;
    QBarSet *set0 = new QBarSet("cours");

    ema_series = new QLineSeries;
    ema_series->setName("EMA");
    rsi_series = new QLineSeries;
    rsi_series->setName("RSI");
    //macd_series = new QLineSeries;
    //macd_series->setName("MACD");

    int cpt=0;

    for(EvolutionCours::iterator it = evolution.begin(); it!=evolution.end(); ++it){
        CoursOHLC& cours = *it;
        *set0 << cours.getVolume();
        Bougie* bougie = new Bougie(cours.getOpen(),cours.getHigh(),cours.getLow(),cours.getClose(),&cours);
        bougie->SetForme();
        qDebug()<<"ESN\n"<<bougie->getCoursOHLC().getOpen();
        connect(bougie, SIGNAL(clickBougie(Bougie*)),this,SLOT(viewCoursOHLC(Bougie*)));
        categories << cours.getDate().toString("yy.MM.dd");
        o_categories << cours.getDate().toString("yy.MM.dd");
        series->append(bougie);
        cpt++;
    }
    /*for(EvolutionCours::iterator it = e.begin(); it!=e.end(); ++it){
        CoursOHLC& cours = *it;
        qDebug()<<cours.getOpen();
    }*/
    o_series->append(set0);

    int p=9;
    QString nom="EMA";
    EMA Indic_EMA(&e,nom,p);
    int c=p-1;
    for(auto it = Indic_EMA.begin(); it!=Indic_EMA.end(); ++it){
       ema_series->append(QPoint(c,it->getIndice()));
       c++;
    }
    ema_series->setVisible(false);

    int lookback=4;
    nom="RSI";
    RSI Indic_RSI(&e,nom,lookback);
    c=lookback+1;
    for(auto it = Indic_RSI.begin(); it!=Indic_RSI.end(); ++it){
        rsi_series->append(QPoint(c,it->getIndice()));
        c++;
    }
    rsi_series->setVisible(false);

    /*MACD Indic_MACD(&e);
    c=0;
    for(auto it = Indic_MACD.begin(); it!=Indic_MACD.end(); ++it){
        macd_series->append(QPoint(c,it->getIndice()));
        qDebug()<<it->getIndice();
        c++;
    }*/



    chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(ema_series);
    chart->addSeries(rsi_series);

    chart->setTitle("Cours OHLC");
    //chart->createDefaultAxes();
    axisX = new QBarCategoryAxis();
    axisX->append(categories);
    //axisX->setRange(categories[0],categories[19]);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    chart->addAxis(axisY, Qt::AlignRight);
    rsi_series->attachAxis(axisY);
    axisY->setLinePenColor(rsi_series->pen().color());


    QValueAxis *axisY2 = new QValueAxis();
    axisY2->setRange(0,18000);
    chart->addAxis(axisY2, Qt::AlignLeft);
    series->attachAxis(axisY2);
    ema_series->attachAxis(axisY2);
    axisY2->setLinePenColor(ema_series->pen().color());

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->setAxisX(axisX,series);
    chart->setAxisX(axisX,ema_series);
    chart->setAxisX(axisX,rsi_series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView = new QChartView(chart,this);
    chartView->setFixedHeight(400);
    chartView->setFixedWidth(1500);
    chartView->setRenderHint(QPainter::Antialiasing);

    chart2 = new QChart();
    chart2->addSeries(o_series);
    chart2->setTitle("Volume Cours OHLC");
    chart2->createDefaultAxes();
    QBarCategoryAxis* axisX2 = new QBarCategoryAxis();
    axisX2->append(o_categories);

    chart2->setAxisX(axisX2,o_series);
    chart2->legend()->setVisible(true);
    chart2->legend()->setAlignment(Qt::AlignBottom);
    chartView2 = new QChartView(chart2,this);
    chartView2->setFixedHeight(400);
    chartView2->setFixedWidth(1500);

    /*dateDeb=new QDateEdit(QDate::fromString(categories[0],"yyyy-MM-dd"));
    dateDeb->setMinimumDate(QDate::fromString(categories[0],"yyyy-MM-dd"));
    dateDeb->setMaximumDate(QDate::fromString(categories[cpt-1],"yyyy-MM-dd"));
    dateDeb->setCalendarPopup(true);
    dateDeb->setFixedSize(100,30);
    dateDeb->setDisplayFormat("yyyy.MM.dd");


    dateFin=new QDateEdit(QDate::fromString(categories[cpt-1],"yyyy-MM-dd"));
    dateFin->setMinimumDate(QDate::fromString(categories[0],"yyyy-MM-dd"));
    dateFin->setMaximumDate(QDate::fromString(categories[cpt-1],"yyyy-MM-dd"));
    dateFin->setCalendarPopup(true);
    dateFin->setFixedSize(100,30);
    dateFin->setDisplayFormat("yyyy.MM.dd");*/

    dateDebl = new QLabel("Date début des données");
    dateFinl = new QLabel("Date fin des données");
    dateDeb = new QComboBox();
    dateFin = new QComboBox();
    dateDeb->addItems(categories);
    dateFin->addItems(categories);

    date = new QHBoxLayout;
    date->addWidget(dateDebl);
    date->addWidget(dateDeb);
    date->addWidget(dateFinl);
    date->addWidget(dateFin);

    /*QFormLayout *date = new QFormLayout;
    date->addRow("Date de début des données", dateDeb);
    date->addRow("Date de fin des données", dateFin);*/

    open = new QLineEdit(this);
    close = new QLineEdit(this);
    high = new QLineEdit(this);
    low = new QLineEdit(this);
    volume = new QLineEdit(this);
    //forme = new QLineEdit(this);

    openl = new QLabel("Open",this);
    highl = new QLabel("High",this);
    closel = new QLabel("Close",this);
    lowl = new QLabel("Low",this);
    volumel = new QLabel("Volume", this);
    formel = new QLabel("Information Bougie",this);
    erreur= new QLabel(this);

    save = new QPushButton("Sauvegarder",this);
    changementDate=new QPushButton("Changement Date",this);
    boutonTransaction=new QPushButton("Transaction", this);

    copen = new QHBoxLayout;
    cclose = new QHBoxLayout;
    chigh = new QHBoxLayout;
    clow = new QHBoxLayout;
    cvolume = new QHBoxLayout;
    cforme = new QHBoxLayout;
    cerreur = new QHBoxLayout;
    coucheCours = new QVBoxLayout;
    graph = new QVBoxLayout;
    fenetre = new QHBoxLayout;

    copen->addWidget(openl);
    copen->addWidget(open);

    cclose->addWidget(closel);
    cclose->addWidget(close);

    chigh->addWidget(highl);
    chigh->addWidget(high);

    clow->addWidget(lowl);
    clow->addWidget(low);

    cvolume->addWidget(volumel);
    cvolume->addWidget(volume);

    cforme->addWidget(formel);
    //cforme->addWidget(forme);

    cerreur->addWidget(erreur);

    chartView->setChart(chart);
    chartView2->setChart(chart2);
    graph->addLayout(date);
    graph->addWidget(chartView2);
    graph->addWidget(chartView);
    fenetre->addLayout(graph);

    coucheCours->addLayout(copen);
    coucheCours->addLayout(chigh);
    coucheCours->addLayout(clow);
    coucheCours->addLayout(cclose);
    coucheCours->addLayout(cvolume);
    coucheCours->addLayout(cforme);
    coucheCours->addLayout(cerreur);
    coucheCours->addWidget(save);
    coucheCours->addWidget(changementDate);
    coucheCours->addWidget(boutonTransaction);
    fenetre->addLayout(coucheCours);



    setLayout(fenetre);

    connect(save,SIGNAL(clicked(bool)),this,SLOT(saveCoursOHLC()));
    connect(changementDate, SIGNAL(clicked()), this, SLOT(changerDate()));
    connect(boutonTransaction, SIGNAL(clicked()), this, SLOT(afficherTransaction()));


}

/*Simulation::Simulation(const QString &fileName, QWidget *parent)
    : QDialog(parent)
{
    QFileInfo fileInfo(fileName);
    //EvolutionCours& e(devisename);

    tabWidget = new QTabWidget;
    tabWidget->addTab(new Accueil(fileInfo), tr("Accueil"));

    //tabWidget->addTab(new EvolutionViewer(e), tr("Graphique"));
    //tabWidget->addTab(new ApplicationsTab(fileInfo), tr("Applications"));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Tab Dialog"));
}*/


void EvolutionViewer::viewCoursOHLC(Bougie* b){
    QString str;
    str.setNum(b->getCoursOHLC().getOpen());
    open->setText(str);
    qDebug()<<"singe1\n"<<b->getCoursOHLC().getOpen();
    str.setNum(b->getCoursOHLC().getClose());
    close->setText(str);
    str.setNum(b->getCoursOHLC().getLow());
    low->setText(str);
    str.setNum(b->getCoursOHLC().getHigh());
    high->setText(str);
    str.setNum(b->getCoursOHLC().getVolume());
    volume->setText(str);
    //b->SetForme();
    formel->setText("Forme :"+b->GetForme()+"\nInformation: "+b->getInformation()+"\n\n\n");
    lastBougieClicked=b;

}


void EvolutionViewer::saveCoursOHLC(){

    try {
        QString e="Un ou plusieurs champs n'est pas valide";
        if(open->text().isEmpty()||high->text().isEmpty()||low->text().isEmpty()||close->text().isEmpty()
                ||volume->text().isEmpty())
            throw e;
        double o=open->text().toDouble();
        double c=close->text().toDouble();
        double l=low->text().toDouble();
        double h=high->text().toDouble();
        double v=volume->text().toDouble();
        lastBougieClicked->getCoursOHLC().setCours(o,h,l,c);
        lastBougieClicked->getCoursOHLC().setVolume(v);
        //qDebug()<<lastBougieClicked->getCoursOHLC().getOpen();

        lastBougieClicked->setOpen(o);
        qDebug()<<"singe\n"<<lastBougieClicked->getCoursOHLC().getOpen()<<"\n";
        lastBougieClicked->setClose(c);
        lastBougieClicked->setHigh(h);
        lastBougieClicked->setLow(l);
   } catch(const QString e){
           erreur->setText(e);
        }
}

void Bougie::SetForme(){
    Bougie* b=this;
    double openBougie = b->cours->getOpen();
        double closeBougie = b->cours->getClose();
        double highBougie = b->cours->getHigh();
        double lowBougie = b->cours->getLow();
         qDebug()<<"set forme\n"<<b->getCoursOHLC().getOpen()<<"\n";
    double bodySize = getCandleBodySize();
    double candleRange = getCandleRangeSize();
    double percentage1 = (bodySize/candleRange)*100.0;

    bool a1 = percentage1 <= 15;
    bool c1 = qAbs(cours->getOpen() - cours->getClose() < 300);
    qDebug()<<"set forme"<<cours->getOpen();
    double percentage2 = (upperWick()/candleRange)*100.0;
    bool a2 = percentage2 <= 5;
    bool c2 = (2*lowerWick())>getCandleBodySize();

    bool a3 = qAbs(cours->getClose() - cours->getHigh() < 300);
    bool c3 = qAbs(cours->getOpen() - cours->getLow() < 300);

    bool a4 = qAbs(cours->getClose() - cours->getLow() < 300);
    bool c4 = qAbs(cours->getOpen() - cours->getHigh() < 300);

    double percentage3 = (bodySize/candleRange)*100.0;
    bool a5 = percentage3 <=40;
    bool c5 = qAbs(upperWick()-lowerWick())<300;

    if (a1&&c1) {this->forme="Doji candle"; this->information="Equilibre entre acheteurs et vendeurs \nPause dans une tendance marquée ou retournement de tendance";}
    else if (a2&&c2) {this->forme="Hammer candle"; this->information="Tendance baissière enrayée \nRebond Technique";}
    else if (a3&&c3) {this->forme="White Marubozu candle"; this->information="Tendance très haussière";}
    else if (a4&&c4) {this->forme="Black Marubozu candle"; this->information="Tendance très baissière";}
    else if (a5&&c5) {this->forme="Spinning Top candle"; this->information="Marché équilibré entre haussiers et baissiers \nSi la bougie se forme après une tendance haussière, cela signifie une perte de vitesse des acheteurs \nSi la bougie se forme après une tendance baissière, cela signifie une perte de vitesse des vendeurs";}
    else {this->forme="Inconnue";}
}

void EvolutionViewer:: changerDate(){
    QString dateDebut, dateF;
    dateDebut=dateDeb->currentText();
    dateF=dateFin->currentText();
    axisX->setRange(dateDebut, dateF);
}

void EvolutionViewer:: afficherTransaction(){
    QString deviseBaseFinale = "0";
    QString deviseContrepartieFinale = "1000000";
    QString tauxCommissionFinale = "0.001";
    double p = tauxCommissionFinale.toDouble();
    double b = deviseBaseFinale.toDouble();
    double c = deviseContrepartieFinale.toDouble();
    TransactionManager* t= new TransactionManager(p,b,c);
    TransactionViewer* tview = new TransactionViewer(*t, this);
    tview->setFixedSize(600, 700);
    tview->show();
}
/*Accueil::Accueil(const QFileInfo &fileInfo, QWidget *parent)
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
}*/

TransactionViewer::TransactionViewer(TransactionManager& e,QWidget *parent):
    QDialog(parent),transaction(e)
{
    QVBoxLayout *titre = new QVBoxLayout;
    QVBoxLayout* main = new QVBoxLayout;
    coucheTrans = new QHBoxLayout;
    ajouterTransaction= new QPushButton("Ajouter Transaction",this);
    annulerTransaction= new QPushButton("Annuler Transaction",this);
    tab = new QVBoxLayout;

    QStringList intitules;

    QLabel *texte = new QLabel("<strong>Tableau Transaction</strong>", this);
    texte->setAlignment(Qt::AlignCenter);
    texte->setFont(QFont("Comic Sans MS", 15));
    titre->addWidget(texte);


    table1 = new QTableWidget();
    table1->setRowCount(10);
    table1->setColumnCount(4);
    intitules << "Date" << "DeviseBase" << "DeviseContrePartie" << "ROI";
    table1->setHorizontalHeaderLabels(intitules);
    table1->insertRow(table1->rowCount());

    for(TransactionManager::iterator it = transaction.begin(); it!=transaction.end(); ++it){
            Transaction& tr = *it;
            table1->setItem(table1->rowCount()-1, DATE, new QTableWidgetItem(tr.getDate().toString()));
            table1->setItem(table1->rowCount()-1, DEVISEBASE, new QTableWidgetItem(QString::number(tr.getMontant())));
            //table1->setItem(table1->rowCount()-1, DEVISECONTERPARTIE, new QTableWidgetItem(QString::t(tr.)));
            //table1->setItem(table1->rowCount()-1, ROI, new QTableWidgetItem(QString::number(it->)));
    }


    coucheTrans->addWidget(ajouterTransaction);
    coucheTrans->addWidget(annulerTransaction);
    tab->addWidget(table1);
    main->addLayout(titre);
    main->addLayout(tab);
    main->addLayout(coucheTrans);
    setLayout(main);
    connect(annulerTransaction, SIGNAL(clicked()), this, SLOT(deleteLastTransaction));

}


