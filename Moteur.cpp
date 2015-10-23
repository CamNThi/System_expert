#include "Moteur.h"

using namespace std;


/* Constructeur */
Moteur::Moteur()
{

}


/* Méthode qui réalise un chaînage avant sur la base de connaissance passée en paramètre */
vector<Element> Moteur::chainageAvant(BaseDeConnaissances *base, string const &typeChainage)
{
    //Vecteur qu'on va retourner, avec la liste des éléments ajoutés à la base de faits
    vector<Element> faitsAjoutes;

    //On réinitialise le tableau des règles appliquées
    base->viderReglesAppliquees("avant");

    //On recherche une règle applicable
    vector <Regle*> r = chercherRegleApplicableChainageAvant(base, typeChainage);
    //Tant qu'on trouve une règle pour compléter la base de faits, on continue la recherche
    while(r.size() != 0)
    {
        for(unsigned int i=0; i<r.size(); i++)
        {
            //On ajoute tous les éléments de la conclusion de la règle dans le vecteur
            for(unsigned int j=0; j<r[i]->getConclusion().size(); j++)
            {
                faitsAjoutes.push_back(r[i]->getConclusion()[j]);
            }
            ajouterConclusion(base, r[i]);
            base->retenirRegle(r[i], "avant");
            supprimerRegle(base, r[i]);
        }
        r = chercherRegleApplicableChainageAvant(base, typeChainage);
    }
    return faitsAjoutes;
}


/* Méthode qui réalise un chaînage mixte sur la base de connaissance */
vector<Element> Moteur::chainageMixte(BaseDeConnaissances *base)
{
    vector<Element> elementsAjoutes; //Vecteur qui va contenir les éléments ajoutés à la base de faits en tout
    vector<Element> e; //Vecteur qui va contenir les éléments ajoutés à la base de faits pendant le chaînage avant, puis pendant le chaînage arrière

    do
    {
        //On effectue le chaînage avant
        e = chainageAvant(base, "largeur");
        //On renseigne les faits ajoutés
        for(int i=0; i<e.size(); i++)
        {
            elementsAjoutes.push_back(e[i]);
        }
        //On effectue un chaînage arrière sur la base de faits obtenue
        e = chainageArriere(base, e);
        //On renseigne les faits ajoutés
        for(int i=0; i<e.size(); i++)
        {
            elementsAjoutes.push_back(e[i]);
        }
    }while(e.size() != 0); //Exécution de la boucle jusqu'à ce qu'on ne trouve plus de faits déductibles
    return elementsAjoutes;
}


/* Méthode qui va renvoyer les règles applicables pour la base de connaissance
Si le dernier paramètre indique un chainage avant en profondeur, une seule règle est déclenchée chaque niveau de déduction
Sinon, s'il s'agit d'un chainage avant en largeur, on va enrichir la base de fait de tous les faits qu'on peut déduire à chaque niveau de déduction */
vector<Regle*> Moteur::chercherRegleApplicableChainageAvant(BaseDeConnaissances *base, string const &typeChainage)
{
    //Curseur pour parcourir la liste (on le met au début de la liste)
    Regle *curseur = base->getDebut();
    //Variable qui compte le nombre de correspondances
    unsigned int correspondance = 0;
    //Contient les règles applicables
    vector<Regle*> regles;

    //Tant qu'on est pas à la fin de la liste, on continue
    while(curseur!=NULL)
    {
        for(unsigned int i=0; i<curseur->getPremisse().size(); i++)
        {
            for(unsigned int j=0; j<base->getBaseDeFaits().size(); j++)
            {
                if(base->getBaseDeFaits()[j] == curseur->getPremisse()[i])
                    correspondance++;
            }
        }

        //Si on a suffisemment de correspondances, la règle est applicable
        if(correspondance==curseur->getPremisse().size())
        {
            regles.push_back(curseur);
            if(typeChainage == "profondeur")
                break;
        }

        curseur = curseur->getSuivant();
        correspondance = 0;
    }

    return regles;
}


/* Méthode qui va ajouter la conclusion de la règle passée en paramètres à la base de faits */
void Moteur::ajouterConclusion(BaseDeConnaissances *base, Regle *regle)
{
    //On ajoute chaque élément de la conclusion dans la base de faits
    for(unsigned int i=0; i<regle->getConclusion().size(); i++)
    {
        base->getBaseDeFaits().push_back(regle->getConclusion()[i]);
    }
}


/* Méthode qui va ajouter la prémisse de la règle passée en paramètres à la base de faits */
void Moteur::ajouterPremisse(BaseDeConnaissances *base, Regle *regle)
{
   //On ajoute chaque élément de la prémisse dans la base de faits
    for(unsigned int i=0; i<regle->getPremisse().size(); i++)
    {
        base->getBaseDeFaits().push_back(regle->getPremisse()[i]);
    }
}


/* Méthode qui va supprimer une règle de la base de règles */
void Moteur::supprimerRegle(BaseDeConnaissances *base, Regle *r)
{
    //On regarde s'il s'agit du 1er élément
    if(base->getDebut() == r)
    {
        base->setDebut(base->getDebut()->getSuivant());
    }

    //Curseur pour parcourir la liste (on le met au début de la liste)
    Regle *curseur = base->getDebut();

    bool sortir = false;

    //Tant qu'on est pas à la fin de la liste, on continue
    while(!sortir)
    {
        if(curseur->getSuivant() == r)
        {
            curseur->setSuivant(r->getSuivant());
            break;
        }
        else
        {
            if(curseur->getSuivant() == NULL)
                sortir = true;
            else
                curseur = curseur->getSuivant();
        }
    }
}


/* Méthode qui réalise un chaînage arrière sur la base de connaissance passée en paramètre, et à partir d'un ou plusieurs buts, passés en paramètres */
vector<Element> Moteur::chainageArriere(BaseDeConnaissances *base, vector<Element> &conclusions)
{
    //Vecteur qu'on va retourner, avec la liste des éléments ajoutés à la base de faits
    vector<Element> faitsAjoutes;

    //On réinitialise le tableau des règles appliquées
    base->viderReglesAppliquees("arriere");

    //Tant qu'il y a des conclusions, on exécute le chaînage arrière
    for(unsigned i=0; i < conclusions.size(); i++){
        //Initialisation du chaînage arrière
        initChainageArriere(base, conclusions[i], faitsAjoutes);
    }

    return faitsAjoutes;
}


/* Effectue le chaînage arrière pour un but donné */
void Moteur::initChainageArriere(BaseDeConnaissances *base, Element &but, vector<Element> &faitsAjoutes)
{
    //Initialisation de la base de faits
    vector<Element> BF = base->getBaseDeFaits();

    //Initialisation de l'iterateur de la base de règles
    Regle *cursor = base->getDebut();

    //Tant qu'on est pas à la fin de la liste, on continue
    while(cursor!=NULL)
    {
        //Le but est present dans la conclusion de la règle et la règle n'est pas présente dans les règles satisfaisantes
        if(elementPresent(cursor->getConclusion(), but) && !reglePresente(base->getReglesAppliqueesArriere(), cursor)){
            //On parcourt chaque premisse de la règle
            for(unsigned i=0; i < cursor->getPremisse().size(); i++){
                //Variable qui compte le nombre de correspondances
                unsigned int correspondance = 0;
                //Cas où les prémisses ne sont pas présentes dans la base de faits
                if(!elementPresent(BF,cursor->getPremisse()[i]))
                {
                   initChainageArriere(base, cursor->getPremisse()[i], faitsAjoutes);
                 }
                else
                {
                    ++correspondance;

                    //Cas où toutes les prémisses sont toutes dans la base de faits
                    if (correspondance == cursor->getPremisse().size())
                    {
                        base->retenirRegle(cursor, "arriere");
                        if(!elementPresent(BF, but))
                        {
                            //On retient la règle
                            faitsAjoutes.push_back(but);
                            base->getBaseDeFaits().push_back(but);
                        }
                    }
                    //Cas où la règle est partiellement satisfaisante
                    else
                    {
                        //On appelle une méthode de la fenêtre principale pour afficher la fenêtre de question à l'utilisateur
                    }

                }
            }
        }
        cursor = cursor->getSuivant();
    }
}


/* Vérifie l'existence d'un élément de conclusion dans un vecteur d'élément */
bool Moteur::elementPresent(std::vector<Element> &conclusion, const Element &e)
{
    //On regarde si l'élément est dans le vecteur de conclusions
    for (unsigned i=0; i <conclusion.size(); i++){
        if (e == conclusion[i]){
            return true;
        }
    }
    return false;
}


/* Méthode qui vérifie l'existence de la règle dans un vecteur de règles */
bool Moteur::reglePresente(vector<Regle *> &vecteur_regles, Regle *ptr_regle)
{
    for (unsigned i=0; i <vecteur_regles.size(); i++){
        if (ptr_regle == vecteur_regles[i]){
            return true;
        }

    }
    return false;
}
