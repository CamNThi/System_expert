#ifndef FENETRETRACESABREGES_H
#define FENETRETRACESABREGES_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <vector>
#include <QPushButton>
#include <QTextEdit>

#include "Basedeconnaissances.h"
#include "Element.h"


/* Fenêtre qui va permettre d'afficher les traces du chaînage */
class FenetreTracesAbreges : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void afficherTracesCompletes();
    void quitter();

    public:
        FenetreTracesAbreges(BaseDeConnaissances *b, std::vector<Element> &e);

    private:
        QLabel *labelRegles;
        QLabel *labelFaits;
        QHBoxLayout *layout_boutons;
        QPushButton *bouton_traces;
        QPushButton *bouton_annuler;
        QVBoxLayout *layout_global;
        BaseDeConnaissances *base;
        std::vector<Element> elements;
};

#endif
