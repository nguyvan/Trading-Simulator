#include "evolutionviewer.h"
#include "simulation.h"
EvolutionViewer::EvolutionViewer(EvolutionCours* e,QWidget *parent):
    QWidget(parent),evolution(e)
{
    series = new QCandlestickSeries;
    series->setName(evolution->getPaireDevises().toString());
    series->setIncreasingColor(QColor(Qt::green));
    series->setIncreasingColor(QColor(Qt::red));

    o_series = new QBarSeries();
    o_series->setName(evolution->getPaireDevises().toString());

    QStringList o_categories;
    QStringList categories;
    QBarSet *set0 = new QBarSet("cours");

    for(EvolutionCours::iterator it = evolution->begin(); it!=evolution->end(); ++it){
        CoursOHLC& cours = *it;
        *set0 << cours.getVolume();
        Bougie* bougie = new Bougie(cours.getOpen(),cours.getHigh(),cours.getLow(),cours.getClose(),&cours);
        connect(bougie, SIGNAL(clickBougie(Bougie*)),this,SLOT(viewCoursOHLC(Bougie*)));
        categories << cours.getDate().toString("yy.MM.dd");
        o_categories << cours.getDate().toString("yy.MM.dd");
        series->append(bougie);
    }
    o_series->append(set0);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cours OHLC");
    chart->createDefaultAxes();
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);

    chart->setAxisX(axisX,series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView = new QChartView(chart,this);
    chartView->setFixedHeight(400);
    chartView->setFixedWidth(1500);

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

    open = new QLineEdit(this);
    close = new QLineEdit(this);
    high = new QLineEdit(this);
    low = new QLineEdit(this);
    forme = new QLineEdit(this);
    openl = new QLabel("Open",this);
    highl = new QLabel("High",this);
    closel = new QLabel("Close",this);
    lowl = new QLabel("Low",this);
    formel = new QLabel("Forme",this);
    save = new QPushButton("save",this);
    runauto = new QPushButton("runauto",this); //button run modeautomatique
    paspas = new QPushButton("paspas",this); //button run modepasapas
    copen = new QHBoxLayout;
    cclose = new QHBoxLayout;
    chigh = new QHBoxLayout;
    clow = new QHBoxLayout;
    cforme = new QHBoxLayout;
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

    cforme->addWidget(formel);
    cforme->addWidget(forme);

    chartView->setChart(chart);
    chartView2->setChart(chart2);
    graph->addWidget(chartView2);
    graph->addWidget(chartView);
    fenetre->addLayout(graph);

    coucheCours->addLayout(copen);
    coucheCours->addLayout(chigh);
    coucheCours->addLayout(clow);
    coucheCours->addLayout(cclose);
    coucheCours->addLayout(cforme);
    coucheCours->addWidget(save);
    coucheCours->addWidget(runauto);
    coucheCours->addWidget(paspas);
    fenetre->addLayout(coucheCours);

    connect(save,SIGNAL(clicked(bool)),this,SLOT(saveCoursOHLC()));
    connect(runauto,SIGNAL(clicked(bool)),this,SLOT(runmode()));
    connect(paspas,SIGNAL(clicked(bool)),this,SLOT(runpaspas()));
    setLayout(fenetre);
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
    str.setNum(b->getCoursOHLC().getClose());
    close->setText(str);
    str.setNum(b->getCoursOHLC().getLow());
    low->setText(str);
    str.setNum(b->getCoursOHLC().getHigh());
    high->setText(str);
    //str.setNum(b->getCoursOHLC().getVolume());
    //volume->setText(str);
    b->SetForme();
    forme->setText(b->GetForme());
    lastBougieClicked=b;
}


void EvolutionViewer::saveCoursOHLC(){
    double o=open->text().toDouble();
    double c=close->text().toDouble();
    double l=low->text().toDouble();
    double h=high->text().toDouble();
    lastBougieClicked->getCoursOHLC().setCours(o,h,l,c);

    lastBougieClicked->setOpen(o);
    lastBougieClicked->setClose(c);
    lastBougieClicked->setHigh(h);
    lastBougieClicked->setLow(l);
}

void EvolutionViewer::runmode(){
    EMA *ema = new EMA(evolution,"EMA",10); // initialiser indicateur ema 
    ema->setperiod(9); // set period of period = 9
    EMA::iterator it = ema->begin(); //initialiser it  
    MA_Strategie* ma = new MA_Strategie("MA_Strategie",evolution,0,100000); // initialiser Strategie MA_Strategie
    ma->setmin(10000); // set value minimum of montant 
    ma->setmax(20000); // set value maximum of montant
    ma->setEMA_Iterator(it); 
    RSI *rsi = new RSI(evolution,"EMA",14,70,30);
    rsi->setlookBackPeriod(20);
    RSI::iterator it2 = rsi->begin();
    RSI_Strategie* si = new RSI_Strategie("RSI_Strategie",evolution,0,200000);
    si->setmin(30000);
    si->setmax(40000);
    si->setRSI_Iterator(it2);
    ModeAutomatique* mod = new ModeAutomatique("ModeAutomatique",evolution,evolution->begin(),si,0.001,200000,10000000,30000);
    for (EvolutionCours::iterator i = evolution->begin();i != evolution->end()-1; i++){

         qDebug()<<mod->getTransactionManager()->getMontantBase() <<mod->getTransactionManager()->getMontantContrepartie(); //montant de Base et montant de Contrepartie apres chaque transaction
         mod->setCurrentCours(i);
         mod->iteration();
         it2++;
         si->setRSI_Iterator(it2);
         mod->setStrategie(si);
     }
 }

 void EvolutionViewer::runpaspas(){
     ModePas_Pas* mode = new ModePas_Pas("ModePas_Pas",evolution,evolution->begin(),0.001,10000,100000,30000);
    for (EvolutionCours::iterator it = evolution->begin();it != evolution->end(); it++){
        mode->setCurrentCours(it);
        if(it->getClose()<5000) {mode->vente(1000); qDebug()<<"vente "<<mode->getTransactionManager()->getMontantBase() <<mode->getTransactionManager()->getMontantContrepartie();}
        else if(it->getClose()>7000) {mode->achat(1000); qDebug()<<"achat "<<mode->getTransactionManager()->getMontantBase() <<mode->getTransactionManager()->getMontantContrepartie();}
        mode->iteration();
    }
}

void Bougie::SetForme(){
    double bodySize = getCandleBodySize();
    double candleRange = getCandleRangeSize();
    double percentage1 = (bodySize/candleRange)*100.0;

    bool a1 = percentage1 <= 15;
    bool c1 = qAbs(cours->getOpen() - cours->getClose() < 300);

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

    if (a1&&c1) {this->forme="Doji candle";}
    else if (a2&&c2) {this->forme="Hammer candle";}
    else if (a3&&c3) {this->forme="White Marubozu candle";}
    else if (a4&&c4) {this->forme="Black Marubozu candle";}
    else if (a5&&c5) {this->forme="Spinning Top candle";}
    else {this->forme="Inconnue";}
}
