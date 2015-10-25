#include "FenetreButChainage.h"

using namespace std;


/* Widget qui servira de fenêtre secondaire pour permettre à l'utilisateur d'initialiser les buts
On passe en paramètre la base de connaissances
On indique également le type de chaînage en paramètre */
FenetreButChainage::FenetreButChainage(BaseDeConnaissances *b, string const &typeChainage) : QDialog()
{
    //Création des labels
    label = new QLabel("Selectionnez le but a atteindre: ");
    //Création de la liste déroulante
    listeButs = new QComboBox;

    //On va récupérer tous les éléments de façon unique
    Regle *curseur = b->getDebut(); //Curseur pour parcourir la liste (on le met au début de la liste)
    //Tant qu'on est pas à la fin de la liste, on continue
    while(curseur!=NULL)
    {
        for(unsigned int i=0; i<curseur->getPremisse().size(); i++)
        {
            //On vérifie auparavent que l'élément n'est pas déjà dans la liste à afficher pour éviter les doublons
            if(!isButPresent(curseur->getPremisse()[i]))
                liste_buts.push_back(curseur->getPremisse()[i]);
        }
        for(unsigned int j=0; j<curseur->getConclusion().size(); j++)
        {
            if(!isButPresent(curseur->getConclusion()[j]))
                liste_buts.push_back(curseur->getConclusion()[j]);
        }
        curseur = curseur->getSuivant();
    }

    //On remplit la liste déroulante
    for(unsigned int k=0; k<liste_buts.size(); k++)
    {
        string stringListe = liste_buts[k]->toString();
        QString but = QString::fromStdString(stringListe);
        listeButs->addItem(but);
        connect(listeButs,SIGNAL(activated(int)),this,SLOT(retenirButs(int)));
    }

    //Ajout dans le layout
    listeButs->setFixedSize(500, 50);
    layout_global = new QVBoxLayout;
    layout_global->addWidget(label);
    layout_global->addWidget(listeButs);

    //Cas du chaînage avant, on ajoute la possibilité d'effectuer le chaînage sans but précis
    if(typeChainage == "avant")
    {
        bouton = new QPushButton;
        bouton->setText("Ou effectuer le chainage sans but");
        layout_global->addWidget(bouton);
        QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(annuler()));
    }

    setLayout(layout_global);

    //On retient la base de connaissances
    base = b;
}


/* Slot personnalisé qui va permettre d'enregistrer le but dans le vecteur */
void FenetreButChainage::retenirButs(int but)
{
    base->setBut(liste_buts[but]);
    this->close();
}


/* Slot personnalisé qui va permettre de démarrer le chaînage sans but dans le vecteur */
void FenetreButChainage::annuler()
{
    this->close();
}


/* Méthode qui détermine si l'élément est déjà dans la liste des buts à afficher */
bool FenetreButChainage::isButPresent(Element const *e)
{
    for(unsigned int i=0; i<liste_buts.size(); i++)
    {
        if(*e == *liste_buts[i])
            return true;
    }
    return false;
}

