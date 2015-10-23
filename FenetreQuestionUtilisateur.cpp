#include "FenetreQuestionUtilisateur.h"

using namespace std;

/* On passe en paramètres du constructeur l'élément sur lequel on questionne l'utilisateur */
FenetreQuestionUtilisateur::FenetreQuestionUtilisateur() : QDialog()
{
    //Titre de la fenêtre
    setWindowTitle("Question utilisateur");

    //Taille de la fenêtre
    setFixedSize(300, 100);

    //Construction des éléments
    label_question = new QLabel("Le fait ci-dessous est-il valide ? Si vous confirmez, il sera ajoute a la base de faits.");
    bouton_oui = new QPushButton("Oui");
    bouton_non = new QPushButton("Non");

    //Création du layout et ajout des boutons
    layout_boutons = new QHBoxLayout;
    layout_boutons->addWidget(bouton_oui);
    layout_boutons->addWidget(bouton_non);

    //Création du layout global
    layout_global = new QVBoxLayout;
    layout_global->addWidget(label_question);
    layout_global->addLayout(layout_boutons);

    //Ajout du layout dans la fenêtre
    setLayout(layout_global);

    //Connexion des boutons
    QObject::connect(bouton_oui, SIGNAL(clicked()), this, SLOT(ajouterFait()));
    QObject::connect(bouton_non, SIGNAL(clicked()), this, SLOT(quitter()));
}


/* Slot personnalisé qui ferme la fenêtre */
void FenetreQuestionUtilisateur::quitter()
{
    this->close();
}


/* Slot personnalisé qui va permettre de sauvegarder le fait comme but */
void FenetreQuestionUtilisateur::ajouterFait()
{

}
