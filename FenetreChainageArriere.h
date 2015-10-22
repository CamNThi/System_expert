#ifndef FENETRECHAINAGEARRIERE_H
#define FENETRECHAINAGEARRIERE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QLineEdit>

#include <vector>

#include "Basedeconnaissances.h"


/* Fenêtre qui va permettre à l'utilisateur d'initialiser les buts pour le chaînage arrière */
class FenetreChainageArriere : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void retenirButs(int but);

    public:
        FenetreChainageArriere(BaseDeConnaissances *base);
        //Méthode qui détermine si l'élément est déjà dans la liste des buts à afficher
        bool isButPresent(Element &e);

    private:
        QLabel *label;
        QComboBox *listeButs;
        QVBoxLayout *layout_global;
        std::vector<Element> liste_buts;
        BaseDeConnaissances *base;
};

#endif
