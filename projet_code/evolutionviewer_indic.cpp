#include "candle.h"
#include "evolutionviewer_indic.h"

Bougie::~Bougie(){}
bool Bougie::isValid(Bougie* b){
    //return false;
    double bodySize = getCandleBodySize(b);
    double candleRange = getCandleRangeSize(b);
    double percentage = (bodySize/candleRange)*100.0;
    bool a = percentage <= 15;
    bool c = qAbs(b->open() - b->close() < 300);
    return(a && c);
}
QString Bougie::getName(Bougie* b){
    /*if(isValid(b))return "Bougie inconnue";
    else return "bz";*/
    if(isValid(b)) {return "Doji";}
    else {return "Inconnue";}
}

EvolutionViewer::EvolutionViewer(EvolutionCours& e,QWidget *parent):
    QWidget(parent),evolution(e)
{
    series = new QCandlestickSeries;
    series->setName(evolution.getPaireDevises().toString());
    series->setIncreasingColor(QColor(Qt::green));
    series->setIncreasingColor(QColor(Qt::red));

    o_series = new QBarSeries();
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

    for(EvolutionCours::iterator it = evolution.begin(); it!=evolution.end(); ++it){
        CoursOHLC& cours = *it;
        *set0 << cours.getVolume();
        Bougie* bougie = new Bougie(cours.getOpen(),cours.getHigh(),cours.getLow(),cours.getClose(),&cours);
        connect(bougie, SIGNAL(clickBougie(Bougie*)),this,SLOT(viewCoursOHLC(Bougie*)));
        categories << cours.getDate().toString("yy.MM");
        o_categories << cours.getDate().toString("yy.MM");
        series->append(bougie);
    }
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

    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);

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


    open = new QLineEdit(this);
    close = new QLineEdit(this);
    high = new QLineEdit(this);
    low = new QLineEdit(this);
    bougie = new QLineEdit(this);
    openl = new QLabel("Open",this);
    highl = new QLabel("High",this);
    closel = new QLabel("Close",this);
    lowl = new QLabel("Low",this);
    bougiel = new QLabel("Bougie",this);
    save = new QPushButton("save",this);
    copen = new QHBoxLayout;
    cclose = new QHBoxLayout;
    chigh = new QHBoxLayout;
    clow = new QHBoxLayout;
    cbougie = new QHBoxLayout;
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

    cbougie->addWidget(bougiel);
    cbougie->addWidget(bougie);

    chartView->setChart(chart);
    chartView2->setChart(chart2);
    graph->addWidget(chartView2);
    graph->addWidget(chartView);
    fenetre->addLayout(graph);

    coucheCours->addLayout(copen);
    coucheCours->addLayout(chigh);
    coucheCours->addLayout(clow);
    coucheCours->addLayout(cclose);
    coucheCours->addLayout(cbougie);
    coucheCours->addWidget(save);
    fenetre->addLayout(coucheCours);

    connect(save,SIGNAL(clicked(bool)),this,SLOT(saveCoursOHLC()));

    setLayout(fenetre);
}

Simulation::Simulation(const QString &fileName, QWidget *parent)
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
}



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
    bougie->setText(b->getName(b));
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

