#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours& e,QWidget *parent):
    QWidget(parent),evolution(e)
{
    series = new QCandlestickSeries;
    series->setName(evolution.getPaireDevises().toString());
    series->setIncreasingColor(QColor(Qt::green));
    series->setIncreasingColor(QColor(Qt::red));

    l_series = new QLineSeries();
    o_series = new QBarSeries();
    o_series->setName(evolution.getPaireDevises().toString());

    QStringList o_categories;
    QStringList categories;
    QBarSet *set0 = new QBarSet("cours");

    for(EvolutionCours::iterator it = evolution.begin(); it!=evolution.end(); ++it){
        CoursOHLC& cours = *it;
        *set0 << cours.getVolume();
        Bougie* bougie = new Bougie(cours.getOpen(),cours.getHigh(),cours.getLow(),cours.getClose(),&cours);
        connect(bougie, SIGNAL(clickBougie(Bougie*)),this,SLOT(viewCoursOHLC(Bougie*)));
        categories << cours.getDate().toString("yy.MM");
        o_categories << cours.getDate().toString("yy.MM");
        series->append(bougie);
    }
    for(EMA::iterator it = ind->begin();it!=ind->end();it++){
        l_series->append(0,it->getIndice());
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

    chart3 = new QChart();
    chart3->legend()->setVisible(true);
    chart3->addSeries(l_series);
    chart3->createDefaultAxes();
    chart3->setTitle("EMA");

    chartView3 = new QChartView(chart3,this);

    open = new QLineEdit(this);
    close = new QLineEdit(this);
    high = new QLineEdit(this);
    low = new QLineEdit(this);
    volume = new QLineEdit(this);
    forme = new QLineEdit(this);
    openl = new QLabel("Open",this);
    highl = new QLabel("High",this);
    closel = new QLabel("Close",this);
    lowl = new QLabel("Low",this);
    volumel = new QLabel("volume",this);
    formel = new QLabel("forme",this);
    save = new QPushButton("save",this);
    copen = new QHBoxLayout;
    cclose = new QHBoxLayout;
    chigh = new QHBoxLayout;
    clow = new QHBoxLayout;
    cvolume = new QHBoxLayout;
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

    cvolume->addWidget(volumel);
    cvolume->addWidget(volume);

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
    coucheCours->addLayout(cvolume);
    coucheCours->addLayout(cforme);
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


void EvolutionViewer::viewCoursOHLC(Bougie* c){
    QString str;
    str.setNum(c->getCoursOHLC().getOpen());
    open->setText(str);
    str.setNum(c->getCoursOHLC().getClose());
    close->setText(str);
    str.setNum(c->getCoursOHLC().getLow());
    low->setText(str);
    str.setNum(c->getCoursOHLC().getHigh());
    high->setText(str);
    str.setNum(c->getCoursOHLC().getVolume());
    volume->setText(str);
    c->SetForme();
    forme->setText(c->GetForme());
    lastBougieClicked=c;
}

void EvolutionViewer::saveCoursOHLC(){
    double o=open->text().toDouble();
    double c=close->text().toDouble();
    double l=low->text().toDouble();
    double h=high->text().toDouble();
    double v=volume->text().toDouble();

    lastBougieClicked->getCoursOHLC().setCours(o,h,l,c);
    lastBougieClicked->getCoursOHLC().setVolume(v);

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
void Bougie::SetForme(){
    double bodySize = getCandleBodySize();
    double candleRange = getCandleRangeSize();
    double percentage1 = (bodySize/candleRange)*100.0;
    bool a1 = percentage1 <= 15;
    bool c1 = qAbs(cours->getOpen() - cours->getClose() < 0.01);
    if (a1&&c1) {this->forme="Doji candle";}
    double percentage2 = (upperWick()/candleRange)*100.0;
    bool a2 = percentage2 <= 5;
    bool c2 = (2*lowerWick())>getCandleBodySize();
    if (a2&&c2) {this->forme="Hammer candle";}
    bool a3 = qAbs(cours->getClose() - cours->getHigh() < 0.01);
    bool c3 = qAbs(cours->getOpen() - cours->getLow() < 0.01);
    if (a3&&c3) {this->forme="White Marubozu candle";}
    bool a4 = qAbs(cours->getClose() - cours->getLow() < 0.01);
    bool c4 = qAbs(cours->getOpen() - cours->getHigh() < 0.01);
    if (a4&&c4) {this->forme="Black Marubozu candle";}
    double percentage3 = (bodySize/candleRange)*100.0;
    bool a5 = percentage3 <=40;
    bool c5 = qAbs(upperWick()-lowerWick())<0.01;
    if (a5&&c5) {this->forme="Spinning Top candle";}    
}

void Bougie::viewCoursOHLC(){ emit clickBougie(this); }
