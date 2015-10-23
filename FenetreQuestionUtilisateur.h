#ifndef FENETREQUESTIONUTILISATEUR_H
#define FENETREQUESTIONUTILISATEUR_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "Element.h"


/* Fenêtre qui va permettre de poser une question à l'utilisateur concernant la validité d'un fait */
class FenetreQuestionUtilisateur : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void ajouterFait();
    void quitter();

    public:
        FenetreQuestionUtilisateur();

    private:
        QLabel *label_question;
        QHBoxLayout *layout_boutons;
        QPushButton *bouton_oui;
        QPushButton *bouton_non;
        QVBoxLayout *layout_global;
};

#endif
