#ifndef EDITEUR_TEXTE_TEST_H
#define EDITEUR_TEXTE_TEST_H
#include <QString>
#include <QTextEdit>
#include <cstring>

class EditeurText {
private :
    QString nomFichier;
    QString text;

public :
    static QTextEdit editor;
    void setText(QString& txt) {text.append(txt);}
    void setText(const char* txt){text.append(txt);}
    QString getText() {return text;}
    QString getTextEditor(QTextEdit& e){return e.toPlainText();}
    void setEditorFromText(QString txt) {editor.setText(txt);}
    QString getNomFichier(){return nomFichier;}
    void setNomFichier(QString& fichier){nomFichier.append(fichier);}
    void setNomFichier(const char* fichier){nomFichier.append(fichier);}
    EditeurText(){}

};

#endif // EDITEUR_TEXTE_TEST_H
