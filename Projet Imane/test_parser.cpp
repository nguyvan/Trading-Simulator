#include "test_parser.h"
#include <iostream>
#include <fstream>
#include <QTextStream>

using namespace std;
void Reader::setText(const QString &nomfichier,QDate date){

    int n=0,d=0, v=0, o=0,h=0, l=0,c=0,i=0;
    QFile fichier(nomfichier);
    QString line;
    QStringList tabOHLC;



    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream flux(&fichier);
       while(!flux.atEnd()){
           line = flux.readLine();
           tabOHLC = line.split(',');

           if(n==0){
               for (QStringList::iterator it = tabOHLC.begin(); it != tabOHLC.end(); ++it)
               {

                   const QString& src = *it;
                   if(src.toLower()=="date")
                    d=tabOHLC.indexOf(src);
                   if(src.toLower()=="open")
                    o=tabOHLC.indexOf(src);
                   if(src.toLower()=="high")
                    h=tabOHLC.indexOf(src);
                   if(src.toLower()=="close")
                    c=tabOHLC.indexOf(src);
                   if(src.toLower()=="low")
                    l=tabOHLC.indexOf(src);
                   if(src.toLower()=="volume")
                    v=tabOHLC.indexOf(src);
               }

               n=1;
           }else{
               QDate date2 = QDate::fromString(tabOHLC[d],"yyyy-MM-dd");
               if(date<=date2){
                   listDate.append(tabOHLC[d]);
                   open.append(tabOHLC[o]);
                   high.append(tabOHLC[h]);
                   low.append(tabOHLC[l]);
                   close.append(tabOHLC[c]);
                   volume.append(tabOHLC[v]);
               }
               /*if(date<=date2){
                   line.append("\n");
                   text.append(line);
               }*/

           }
           //qDebug()<<volume;
           //qDebug()<<open;
       }fichier.close();
    }else {
        std::cout<<"erreur lors du chargement du fichier"<<std::endl;
    }
}

QString Reader::getNameDevise(const QString &nomfichier)
{
     QFileInfo fich(nomfichier);
     return fich.baseName();
}
