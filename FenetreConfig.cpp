#include "FenetreConfig.h"

/* Constructeur */
FenetreConfig::FenetreConfig(Config *configParam)
{
    //Titre de la fenêtre
    setWindowTitle("Parametres de configuration");

    //Taille de la fenêtre
    setFixedWidth(600);

    //Création du paramètre 1
    layout_param1 = new QHBoxLayout;
    label_param1 = new QLabel;
    label_param1->setText("Type de chainage avant: ");
    option1_param1 = new QRadioButton("En profondeur");
    option2_param1 = new QRadioButton("En largeur");
    if(configParam->getTypeChainageAvant() == "profondeur")
        option1_param1->setChecked(true);
    else
        option2_param1->setChecked(true);
    layout_param1->addWidget(label_param1);
    layout_param1->addWidget(option1_param1);
    layout_param1->addWidget(option2_param1);

    //Création des boutons
    bouton_valider = new QPushButton(QIcon("images/accept.png"), "Valider cette configuration");
    bouton_annuler = new QPushButton(QIcon("images/cancel.png"), "Annuler");
    layout_boutons = new QHBoxLayout;
    layout_boutons->addWidget(bouton_valider);
    layout_boutons->addWidget(bouton_annuler);

    //Ajout du layout dans la fenêtre
    layout_global = new QVBoxLayout();
    layout_global->setAlignment(Qt::AlignTop);
    layout_global->addLayout(layout_param1);
    layout_global->addLayout(layout_boutons);
    setLayout(layout_global);

    //On renseigne la configuration actuelle
    config = configParam;

    //Connexion des boutons
    QObject::connect(bouton_valider, SIGNAL(clicked()), this, SLOT(configurerAppli()));
    QObject::connect(bouton_annuler, SIGNAL(clicked()), this, SLOT(quitter()));
}


/* Slot personnalisé pour configurer l'application */
void FenetreConfig::configurerAppli()
{
    //On sauvegarde la configuration
    if(option1_param1->isChecked())
        config->setTypeChainageAvant("profondeur");
    else
        config->setTypeChainageAvant("largeur");
    //Fermeture de la fenêtre
    quitter();
}


/* Slot personnalisé qui ferme la fenêtre */
void FenetreConfig::quitter()
{
    this->close();
}
