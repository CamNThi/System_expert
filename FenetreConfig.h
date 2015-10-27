#ifndef FENETRECONFIG_H
#define FENETRECONFIG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QButtonGroup>

#include "Config.h"


/* Fenêtre qui va permettre de configurer l'application */
class FenetreConfig : public QDialog
{
    //Macro pour créer les slots personnalisés
    Q_OBJECT

    public slots:
    void configurerAppli();
    void quitter();

    public:
        FenetreConfig(Config *configuration);

    private:
        QLabel *label_param1;
        QRadioButton *option1_param1;
        QRadioButton *option2_param1;
        QButtonGroup *param1;
        QHBoxLayout *layout_param1;
        QLabel *label_param2;
        QRadioButton *option1_param2;
        QRadioButton *option2_param2;
        QRadioButton *option3_param2;
        QRadioButton *option4_param2;
        QButtonGroup *param2;
        QPushButton *bouton_valider;
        QPushButton *bouton_annuler;
        QHBoxLayout *layout_boutons;
        QVBoxLayout *layout_global;
        //Pour enregistrer les configurations de l'application
        Config *config;
};

#endif
