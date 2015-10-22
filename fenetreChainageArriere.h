#ifndef FENETRECHAINAGEARRIERE_H
#define FENETRECHAINAGEARRIERE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>

#include <vector>

#include "Basedeconnaissances.h"


/* Fenêtre qui va permettre à l'utilisateur d'initialiser les buts pour le chaînage arrière */
class FenetreChainageArriere : public QDialog
{
    public:
        FenetreChainageArriere(BaseDeConnaissances *base);

    private:
        QLabel *label1;
        QHBoxLayout *layout_bouton;
        QLabel *label2;
        QTextEdit *buts;
        QVBoxLayout *layout_global;
        std::vector<Element> liste_buts;
};

#endif
