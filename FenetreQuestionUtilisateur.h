#ifndef FENETREQUESTIONUTILISATEUR_H
#define FENETREQUESTIONUTILISATEUR_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "Element.h"
#include "Basedeconnaissances.h"


/* Fenêtre qui va permettre de poser une question à l'utilisateur concernant la validité d'un fait */
class FenetreQuestionUtilisateur : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void ajouterFait();
    void quitter();

    public:
        FenetreQuestionUtilisateur(BaseDeConnaissances *base, Element *e);

    private:
        QLabel *label_question;
        QLabel *label_fait;
        QHBoxLayout *layout_boutons;
        QPushButton *bouton_oui;
        QPushButton *bouton_non;
        QVBoxLayout *layout_global;
        //Pour retenir la base de connaissances
        BaseDeConnaissances *baseDeConnaissances;
        //Pour retenir l'élément concerné
        Element *element;
};

#endif
