#ifndef FENETREBUTCHAINAGE_H
#define FENETREBUTCHAINAGE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>

#include <vector>

#include "Basedeconnaissances.h"


/* Fenêtre qui va permettre à l'utilisateur d'initialiser les buts pour le chaînage arrière/arrière */
class FenetreButChainage : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
        void retenirButs(int but);
        void annuler();

    public:
        FenetreButChainage(BaseDeConnaissances *base, std::string const &typeChainage);
        //Méthode qui détermine si l'élément est déjà dans la liste des buts à afficher
        bool isButPresent(Element const *e);

    private:
        QLabel *label;
        QComboBox *listeButs;
        QVBoxLayout *layout_global;
        QPushButton *bouton;
        //Pour contenir les éléments qui seront dans la liste déroulante
        std::vector<Element *> liste_buts;
        //Pour retenir la base de connaissances
        BaseDeConnaissances *base;
};

#endif
