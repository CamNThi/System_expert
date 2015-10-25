#include "FenetreQuestionUtilisateur.h"

using namespace std;

/* On passe en paramètres du constructeur l'élément sur lequel on questionne l'utilisateur
On lui passe également l'élément sur lequel on questionne l'utilisateur */
FenetreQuestionUtilisateur::FenetreQuestionUtilisateur(BaseDeConnaissances *base, Element *e) : QDialog()
{
    //Titre de la fenêtre
    setWindowTitle("Question utilisateur");

    //Taille de la fenêtre
    setFixedSize(600, 150);

    //Construction des éléments
    label_question = new QLabel("Le fait ci-dessous est-il valide ? Si vous confirmez, il sera ajoute a la base de faits.");
    label_fait = new QLabel;
    string faitString = e->toString();
    QString fait = QString::fromStdString(faitString);
    label_fait->setText(fait);
    bouton_oui = new QPushButton("Oui");
    bouton_non = new QPushButton("Non");

    //Création du layout et ajout des boutons
    layout_boutons = new QHBoxLayout;
    layout_boutons->addWidget(bouton_oui);
    layout_boutons->addWidget(bouton_non);

    //Création du layout global
    layout_global = new QVBoxLayout;
    layout_global->addWidget(label_question);
    layout_global->addWidget(label_fait);
    layout_global->addLayout(layout_boutons);

    //Ajout du layout dans la fenêtre
    setLayout(layout_global);

    //Connexion des boutons
    QObject::connect(bouton_oui, SIGNAL(clicked()), this, SLOT(ajouterFait()));
    QObject::connect(bouton_non, SIGNAL(clicked()), this, SLOT(quitter()));

    //Pour retenir la base de connaissances
    baseDeConnaissances=base;
    //Pour retenir l'élément concerné
    element = e;
}


/* Slot personnalisé qui ferme la fenêtre */
void FenetreQuestionUtilisateur::quitter()
{
    this->close();
}


/* Slot personnalisé qui va permettre de sauvegarder le fait comme but */
void FenetreQuestionUtilisateur::ajouterFait()
{
    baseDeConnaissances->getBaseDeFaits().push_back(element);
    this->close();
}
