#include "fenetreChainageArriere.h"

using namespace std;


/* Widget qui servira de fenêtre secondaire pour permettre à l'utilisateur d'initialiser les buts */
FenetreChainageArriere::FenetreChainageArriere(BaseDeConnaissances *base) : QDialog()
{
    //Création des labels
    label1 = new QLabel("Elements extraits de la base de regles. Selectionnez les buts a atteindre: ");
    label2 = new QLabel("Buts a atteindre: ");
    layout_bouton = new QHBoxLayout;
    //On va récupérer tous les éléments de façon unique
    Regle *curseur = base->getDebut(); //Curseur pour parcourir la liste (on le met au début de la liste)
    //Tant qu'on est pas à la fin de la liste, on continue
    while(curseur!=NULL)
    {
        for(unsigned int i=0; i<curseur->getPremisse().size(); i++)
        {
            liste_buts.push_back(curseur->getPremisse()[i]);
        }
        for(unsigned int j=0; j<curseur->getConclusion().size(); j++)
        {
            liste_buts.push_back(curseur->getPremisse()[j]);
        }
        curseur = curseur->getSuivant();
    }
    //Création des boutons: un élément par bouton
    for(unsigned int k=0; k<liste_buts.size(); k++)
    {
        string stringListe = liste_buts[k].toString();
        QString but = QString::fromStdString(stringListe);
        QPushButton *bouton = new QPushButton;
        bouton->setText(but);
        layout_bouton->addWidget(bouton);
    }
    layout_global = new QVBoxLayout;
    layout_global->addWidget(label1);
    layout_global->addLayout(layout_bouton);
    layout_global->addWidget(label2);
    buts = new QTextEdit;
    layout_global->addWidget(buts);
    setLayout(layout_global);
}
