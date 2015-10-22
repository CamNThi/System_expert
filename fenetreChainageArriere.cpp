#include "fenetreChainageArriere.h"

using namespace std;


/* Widget qui servira de fenêtre secondaire pour permettre à l'utilisateur d'initialiser les buts */
FenetreChainageArriere::FenetreChainageArriere(BaseDeConnaissances *b) : QDialog()
{
    //Création des labels
    label = new QLabel("Elements extraits de la base de regles. Selectionnez les buts a atteindre: ");
    //Création de la liste déroulante
    listeButs = new QComboBox;
    //On va récupérer tous les éléments de façon unique
    Regle *curseur = b->getDebut(); //Curseur pour parcourir la liste (on le met au début de la liste)
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
    //On remplit la liste déroulante
    for(unsigned int k=0; k<liste_buts.size(); k++)
    {
        string stringListe = liste_buts[k].toString();
        QString but = QString::fromStdString(stringListe);
        listeButs->addItem(but);
        connect(listeButs,SIGNAL(activated(int)),this,SLOT(retenirButs(int)));
    }
    listeButs->setFixedSize(500, 50);
    layout_global = new QVBoxLayout;
    layout_global->addWidget(label);
    layout_global->addWidget(listeButs);
    setLayout(layout_global);

    base = b;
}


void FenetreChainageArriere::retenirButs(int but)
{
    base->setBut(liste_buts[but]);
    this->close();
}
