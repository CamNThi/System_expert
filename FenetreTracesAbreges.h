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


/* Fenêtre qui va permettre d'afficher les traces du chaînage (avant, arriere ou mixte) */
class FenetreTracesAbreges : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void afficherTracesCompletes();
    void quitter();

    public:
        FenetreTracesAbreges(BaseDeConnaissances *b, std::vector<Element *> const &e, std::string const &chainage);

    private:
        QLabel *labelRegles;
        QLabel *labelFaits;
        QHBoxLayout *layout_boutons;
        QPushButton *bouton_traces;
        QPushButton *bouton_annuler;
        QVBoxLayout *layout_global;
        //Pour retenir la base de connaissances
        BaseDeConnaissances *base;
        //Pour retenir les éléments ajoutés à la base de faits lors du dernier chaînage
        std::vector<Element *> elements;
        //Pour retenir le type de chaînage (avant, arriere ou mixte)
        std::string typeChainage;
};

#endif
