#include "FenetreConfig.h"

/* Constructeur
On lui passe en paramètre la configuration actuelle pour que la classe puisse la modifier */
FenetreConfig::FenetreConfig(Config *configuration) : QDialog()
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
    if(configuration->getTypeChainageAvant() == "profondeur")
        option1_param1->setChecked(true);
    else
        option2_param1->setChecked(true);
    layout_param1->addWidget(label_param1);
    layout_param1->addWidget(option1_param1);
    layout_param1->addWidget(option2_param1);
    //Pour regrouper les options
    param1 = new QButtonGroup;
    param1->addButton(option1_param1);
    param1->addButton(option2_param1);

    //Création du paramètre 2
    label_param2 = new QLabel;
    label_param2->setText("Gestion des conflits. Lors des conflits, la regle qui a la priorite est : ");
    option1_param2 = new QRadioButton("la regle qui apparait en premier dans la liste");
    option2_param2 = new QRadioButton("la regle qui a le plus de premisses");
    option3_param2 = new QRadioButton("la regle qui a le moins de premisses");
    option4_param2 = new QRadioButton("la regle utilisee le plus recemment");
    //Pour regrouper les options
    param2 = new QButtonGroup;
    param2->addButton(option1_param2);
    param2->addButton(option2_param2);
    param2->addButton(option3_param2);
    param2->addButton(option4_param2);
    if(configuration->getGestionConflit() == "ordre")
        option1_param2->setChecked(true);
    else if(configuration->getGestionConflit() == "nbPremisseSup")
        option2_param2->setChecked(true);
    else if(configuration->getGestionConflit() == "nbPremisseInf")
        option3_param2->setChecked(true);
    else if(configuration->getGestionConflit() == "recenceUtilisation")
        option4_param2->setChecked(true);

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
    layout_global->addWidget(label_param2);
    layout_global->addWidget(option1_param2);
    layout_global->addWidget(option2_param2);
    layout_global->addWidget(option3_param2);
    layout_global->addWidget(option4_param2);
    layout_global->addLayout(layout_boutons);
    setLayout(layout_global);

    //On renseigne la configuration actuelle
    config = configuration;

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
    if(option1_param2->isChecked())
        config->setGestionConflit("ordre");
    else if(option2_param2->isChecked())
        config->setGestionConflit("nbPremisseSup");
    else if(option3_param2->isChecked())
        config->setGestionConflit("nbPremisseInf");
    else if(option4_param2->isChecked())
        config->setGestionConflit("recenceUtilisation");
    //Fermeture de la fenêtre
    quitter();
}


/* Slot personnalisé qui ferme la fenêtre */
void FenetreConfig::quitter()
{
    this->close();
}
