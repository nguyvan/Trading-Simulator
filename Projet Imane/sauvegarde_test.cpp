/*#include "sauvergarde_test.h"

EcritureTransaction::EcritureTransaction()
{
    transacManager = doc.createElement("transactions"); // création de la balise "mesures"
    doc.appendChild(transacManager); // filiation de la balise "mesures"
    file.setFileName("transaction.xml");
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return; // en écriture
    out.setDevice(&file); // association du flux au fichier
}

void EcritureTransaction::demande_ajout(TransactionManager& t){//le faire avec un transcation manager
    QString o, h, l, c, p, mpi, mpci,m,b ;
    int i = 0;
    //création du noeud pourcentage
    QDomElement pourcentage = doc.createElement("pourcentage");
    transacManager.appendChild(pourcentage);
    QDomText qpourcentage = doc.createTextNode(p.number(t.getPourcentage()));
    pourcentage.appendChild(qpourcentage);
    //création du noeud montant de base initial
    QDomElement mbi = doc.createElement("montant de base intial");
    transacManager.appendChild(mbi);
    QDomText qmbi = doc.createTextNode(mpi.number(t.getMontantBase()));
    mbi.appendChild(qmbi);
    //création du noeud montant de contre partie initial
    QDomElement mcpi = doc.createElement("montant de contre partie initial");
    transacManager.appendChild(mcpi);
    QDomText qmcpi = doc.createTextNode(mpci.number(t.getMontantContrePartie()));
    mcpi.appendChild(qmcpi);
    //creation du noeud achat


    //creation du noeud représentant les transactions
    for(TransactionManager::iterator it = t.begin(); it!= t.end(); it++){

    QDomElement transaction = doc.createElement("transaction");
    transacManager.appendChild(transaction);
    transaction.setAttribute("numero",i);

        QDomElement PaireDevise = doc.createElement("Paire Devise");
        transaction.appendChild(PaireDevise);
        QDomText nomPaire = doc.createTextNode(t.getTrans()->getPaireDevise()->getSurnom());
        PaireDevise.appendChild(nomPaire);

        QDomElement surnom = doc.createElement("surnom");
        PaireDevise.appendChild(surnom);
        QDomText qsurnom = doc.createTextNode(t.getTrans()->getPaireDevise()->getSurnom());
        surnom.appendChild(qsurnom);

            QDomElement PDeviseBase = doc.createElement("Devise B");
            PaireDevise.appendChild(PDeviseBase);
            QDomElement codeB = doc.createElement("codeB");
                PDeviseBase.appendChild(codeB);
                QDomText qscode = doc.createTextNode(t.getTrans()->getPaireDevise()->getBase().getCode());
                codeB.appendChild(qscode);
                QDomElement zoneB = doc.createElement("zoneB");
                PDeviseBase.appendChild(zoneB);
                QDomText qzoneB = doc.createTextNode(t.getTrans()->getPaireDevise()->getBase().getZoneGeographique());
                zoneB.appendChild(qzoneB);
                QDomElement monnaieB = doc.createElement("monnaieB");
                PDeviseBase.appendChild(monnaieB);
                QDomText qmonnaieB = doc.createTextNode(t.getTrans()->getPaireDevise()->getBase().getMonnaie());
                monnaieB.appendChild(qmonnaieB);

            QDomElement PDeviseCP = doc.createElement("Devise CP");
            PaireDevise.appendChild(PDeviseCP);
                QDomElement codeCP = doc.createElement("codeCP");
                PDeviseCP.appendChild(codeCP);
                QDomText qcode = doc.createTextNode(t.getTrans()->getPaireDevise()->getContrepartie().getCode());
                codeCP.appendChild(qcode);
                QDomElement zoneCP = doc.createElement("zoneCP");
                PDeviseCP.appendChild(zoneCP);
                QDomText qzoneCP = doc.createTextNode(t.getTrans()->getPaireDevise()->getContrepartie().getZoneGeographique());
                zoneCP.appendChild(qzoneCP);
                QDomElement monnaieCP = doc.createElement("monnaieCP");
                PDeviseCP.appendChild(monnaieCP);
                QDomText qmonnaieCP = doc.createTextNode(t.getTrans()->getPaireDevise()->getContrepartie().getMonnaie());
                monnaieCP.appendChild(qmonnaieCP);



        QDomElement coursOHLC = doc.createElement("coursOHLC");
        transaction.appendChild(coursOHLC);

            QDomElement open = doc.createElement("Open");
            coursOHLC.appendChild(open);
            QDomText nomOpen = doc.createTextNode(o.number(t.getTrans()->getCours()->getOpen()));
            open.appendChild(nomOpen);

            QDomElement high = doc.createElement("High");
            coursOHLC.appendChild(high);
            QDomText nomHigh = doc.createTextNode(h.number(t.getTrans()->getCours()->getHigh()));
            high.appendChild(nomHigh);

            QDomElement low = doc.createElement("Low");
            coursOHLC.appendChild(low);
            QDomText nomLow = doc.createTextNode(h.number(t.getTrans()->getCours()->getLow()));
            high.appendChild(nomLow);

            QDomElement close = doc.createElement("Close");
            coursOHLC.appendChild(close);
            QDomText nomClose = doc.createTextNode(c.number(t.getTrans()->getCours()->getClose()));
            high.appendChild(nomClose);

            QDomElement date = doc.createElement("date");
            transaction.appendChild(close);
            QDomText qdate = doc.createTextNode(t.getTrans()->getDate().toString());
            date.appendChild(qdate);

    QDomElement montant = doc.createElement("montant");
    transaction.appendChild(montant);
    QDomText qmontant = doc.createTextNode(m.number(t.getTrans()->getMontant()));
    montant.appendChild(qmontant);

    QDomElement achat = doc.createElement("achat");
    transaction.appendChild(achat);
    QDomText qachat = doc.createTextNode(b.number(t.getTrans()->getBuy()));
    achat.appendChild(qachat);
    i++;
    }

}

EcritureTransaction::~EcritureTransaction()
{
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
    file.close();
}
///////////////////////////////////////////////////////////////////////////////////////:
EcritureDonnees::EcritureDonnees()
{
    evolcours = doc.createElement("note"); // création de la balise "mesures"
    doc.appendChild(evolcours); // filiation de la balise "mesures"
    file.setFileName("evolcours.xml");
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return; // en écriture
    out.setDevice(&file); // association du flux au fichier
}

void EcritureDonnees::demande_ajout(EvolutionCours& ct){//le faire avec un transcation manager
    QString o, h, l, c;
    int i= 0;

    QDomElement PaireDevise = doc.createElement("Paire Devise");
    evolcours.appendChild(PaireDevise);
    QDomText nomPaire = doc.createTextNode(ct.getPaireDevises().getSurnom());
    PaireDevise.appendChild(nomPaire);

        QDomElement surnom = doc.createElement("surnom");
        PaireDevise.appendChild(surnom);
        QDomText qsurnom = doc.createTextNode(ct.getPaireDevises().getSurnom());
        surnom.appendChild(qsurnom);

        QDomElement PDeviseBase = doc.createElement("Devise B");
        PaireDevise.appendChild(PDeviseBase);
        QDomElement codeB = doc.createElement("codeB");
            PDeviseBase.appendChild(codeB);
            QDomText qscode = doc.createTextNode(ct.getPaireDevises().getBase().getCode());
            codeB.appendChild(qscode);
            QDomElement zoneB = doc.createElement("zoneB");
            PDeviseBase.appendChild(zoneB);
            QDomText qzoneB = doc.createTextNode(ct.getPaireDevises().getBase().getZoneGeographique());
            zoneB.appendChild(qzoneB);
            QDomElement monnaieB = doc.createElement("monnaieB");
            PDeviseBase.appendChild(monnaieB);
            QDomText qmonnaieB = doc.createTextNode(ct.getPaireDevises().getBase().getMonnaie());
            monnaieB.appendChild(qmonnaieB);

        QDomElement PDeviseCP = doc.createElement("Devise CP");
        PaireDevise.appendChild(PDeviseCP);
            QDomElement codeCP = doc.createElement("codeCP");
            PDeviseCP.appendChild(codeCP);
            QDomText qcode = doc.createTextNode(ct.getPaireDevises().getContrepartie().getCode());
            codeCP.appendChild(qcode);
            QDomElement zoneCP = doc.createElement("zoneCP");
            PDeviseCP.appendChild(zoneCP);
            QDomText qzoneCP = doc.createTextNode(ct.getPaireDevises().getContrepartie().getZoneGeographique());
            zoneCP.appendChild(qzoneCP);
            QDomElement monnaieCP = doc.createElement("monnaieCP");
            PDeviseCP.appendChild(monnaieCP);
            QDomText qmonnaieCP = doc.createTextNode(ct.getPaireDevises().getContrepartie().getMonnaie());
            monnaieCP.appendChild(qmonnaieCP);

    for(EvolutionCours::iterator it = ct.begin(); it != ct.end(); it++){
    QDomElement coursOHLC = doc.createElement("coursOHLC");
    evolcours.appendChild(coursOHLC);
    coursOHLC.setAttribute("numero",i);

    QDomElement open = doc.createElement("Open");
    coursOHLC.appendChild(open);
    QDomText nomOpen = doc.createTextNode(o.number(ct.getCours()->getOpen()));
    open.appendChild(nomOpen);

    QDomElement high = doc.createElement("High");
    coursOHLC.appendChild(high);
    QDomText nomHigh = doc.createTextNode(h.number(ct.getCours()->getHigh()));
    high.appendChild(nomHigh);

    QDomElement low = doc.createElement("Low");
    coursOHLC.appendChild(low);
    QDomText nomLow = doc.createTextNode(h.number(ct.getCours()->getLow()));
    high.appendChild(nomLow);

    QDomElement close = doc.createElement("Close");
    coursOHLC.appendChild(close);
    QDomText nomClose = doc.createTextNode(c.number(ct.getCours()->getClose()));
    high.appendChild(nomClose);

    QDomElement date = doc.createElement("date");
    coursOHLC.appendChild(close);
    QDomText qdate = doc.createTextNode(ct.getCours()->getDate().toString());
    date.appendChild(qdate);

    i++;
    }
}

EcritureDonnees::~EcritureDonnees()
{
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
    file.close();
}
///////////////////////////////////////////////////////////////////////////////////
EcritureNote::EcritureNote()
{
    note = doc.createElement("note"); // création de la balise "mesures"
    doc.appendChild(note); // filiation de la balise "mesures"
    file.setFileName("transaction.xml");
    if (!file.open(QIODevice::WriteOnly)) // ouverture du fichier de sauvegarde
        return; // en écriture
    out.setDevice(&file); // association du flux au fichier
}

void EcritureNote::demande_ajout(EditeurText& et){//le faire avec un transcation manager


    QDomElement paragraphe = doc.createElement("paragraphe");
    note.appendChild(paragraphe);
    //QString text = et.getTextEditor();
    QDomText para = doc.createTextNode(et.getTextEditor());// il y a un problème avec cette ligne la je comprends pas à revoir
    paragraphe.appendChild(para);
}

EcritureNote::~EcritureNote()
{
    // insertion en début de document de <?xml version="1.0" ?>
    QDomNode noeud = doc.createProcessingInstruction("xml","version=\"1.0\"");
    doc.insertBefore(noeud,doc.firstChild());
    // sauvegarde dans le flux (deux espaces de décalage dans l'arborescence)
    doc.save(out,2);
    file.close();
}
//////////////////////////////////////////////////////////////////////////////////////
LectureTransaction::LectureTransaction()
{
    QFile file("mesures.xml");
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file))
    {
        file.close(); // établit le document XML à partir des données du fichier (hiérarchie, etc.)
        return;
    }
    file.close();
}

Transaction LectureTransaction::lire()
{
    QXmlStreamReader reader;//Objet servant à la navigation
    QString fileName = "developpez.xml";
    QString PBsurnom, PBcode, PBzone, PBmonnaie, PCPcode, PCPzone, PCPmonnaie;
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text); //Ouverture du fichier XML en lecture seul et en mode texte
    reader.setDevice(&file);//Initialise l'instance reader avec le flux XML venant de file


    //Le but de cette boucle est de parcourir le fichier et de vérifier si l'on est au debut d'un element.
    reader.readNext();
    while (!reader.atEnd())
    {
        if (reader.isStartElement())
        {
            if (reader.name() == "Paire Devise")
            {
                reader.readNext();//On va au prochain token
                while(reader.isStartElement()==false)//Tant que celui-ci n'est pas un element de depart on avance au token suivant.
                    reader.readNext();

                if(reader.name() == "surnom ")
                {

                    PBsurnom = reader.readElementText();
                    reader.readNext();
                }

                else if(reader.name() == "Devise B"){
                    reader.readNext();
                    if(reader.name()== "codeB"){
                        PBcode = reader.readElementText();
                        reader.readNext();
                       }
                    else if(reader.name()== "zoneB"){
                        PBzone = reader.readElementText();
                        reader.readNext();
                       }
                    else if(reader.name()== "monnaieB"){
                        PBmonnaie = reader.readElementText();
                        reader.readNext();
                    }

                }
                else if(reader.name()=="Devise CP"){
                    reader.readNext();
                    if(reader.name()== "codeCP"){
                        PCPcode = reader.readElementText();
                        reader.readNext();
                       }
                    if(reader.name()== "zoneCP"){
                        PCPzone = reader.readElementText();
                        reader.readNext();
                       }
                    if(reader.name()== "monnaieCP"){
                        PCPmonnaie = reader.readElementText();
                        reader.readNext();
                    }

                }



            }

        }
        reader.readNext();//On va au prochain Token
    }
    file.close();
    return;//ici il faudra construire un objet de type transactionManager et e renvoyer

}
*/
