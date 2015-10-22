#ifndef FENETRECONFIG_H
#define FENETRECONFIG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>

#include "FenetreConfig.h"
#include "Config.h"


/* Fenêtre qui va permettre de configurer l'application */
class FenetreConfig : public QDialog
{
    //Macro pour créer le slot personnalisé
    Q_OBJECT

    public slots:
    void configurerAppli();
    void quitter();

    public:
        FenetreConfig(Config *configParam);

    private:
        QLabel *label_param1;
        QRadioButton *option1_param1;
        QRadioButton *option2_param1;
        QHBoxLayout *layout_param1;
        QPushButton *bouton_valider;
        QPushButton *bouton_annuler;
        QHBoxLayout *layout_boutons;
        QVBoxLayout *layout_global;
        Config *config;
};

#endif
