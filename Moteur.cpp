#include "Moteur.h"

using namespace std;


/* Constructeur */
Moteur::Moteur(BaseDeConnaissances *base)
{
    //Pour retenir la base de connaissances
    baseDeConnaissances = base;
}


/* Méthode qui réalise un chaînage avant sur la base de connaissance passée en paramètre
On renseigne également le type de chaînage (en profondeur ou en largeur)
ainsi que la gestion des conflits (ordre, nbPremisseSup, nbPremisseInf) */
vector<Element *> Moteur::chainageAvant(BaseDeConnaissances *base, string const &typeChainage, string const &gestionConflit)
{
    //Vecteur qu'on va retourner, avec la liste des éléments ajoutés à la base de faits
    vector<Element *> faitsAjoutes;

    //On réinitialise le tableau des règles appliquées
    base->viderReglesAppliquees("avant");

    //Pour indiquer si on a atteint le but
    bool butAtteint = false;

    //On effectue le chaînage dans le cas où le but n'est pas présent dans la base de faits, ou encore dans le cas où on a pas sélectionné de but
    if(base->getBut()==NULL || base->getBut()!=NULL && !elementPresent(base->getBaseDeFaits(), base->getBut()))
    {
        //On recherche une règle applicable
        vector <Regle *> r = chercherRegleApplicableChainageAvant(base);

        //On trie les règles en fonction de la gestion des conflits, sauf dans le cas où on prends les règles dans l'ordre d'appariton
        if(gestionConflit!="ordre")
            trierRegles(r, gestionConflit);

        //Tant qu'on trouve une règle pour compléter la base de faits, on continue la recherche
        while(r.size() != 0 && butAtteint==false)
        {
            //Si on est dans un chaînage en largeur, on applique toutes les règles trouvées
            if(typeChainage == "largeur")
            {
                for(unsigned int i=0; i<r.size(); i++)
                {
                    //On ajoute tous les éléments de la conclusion de la règle dans le vecteur
                    for(unsigned int j=0; j<r[i]->getConclusion().size(); j++)
                    {
                        faitsAjoutes.push_back(r[i]->getConclusion()[j]);
                        if(base->getBut()!=NULL && *r[i]->getConclusion()[j] == *base->getBut())
                        {
                            butAtteint = true;
                        }
                    }
                    ajouterConclusion(base, r[i]);
                    base->retenirRegle(r[i], "avant");
                    supprimerRegle(base, r[i]);
                    //On incrémente l'indice de la règle qui indique sa récence d'utilisation
                    r[i]->incUtilisation();
                }
            }
            //Sinon, dans le cas d'un chaînage en profondeur, on applique juste une seule règle: la première du vecteur
            else
            {
                //On ajoute tous les éléments de la conclusion de la règle dans le vecteur
                for(unsigned int j=0; j<r[0]->getConclusion().size(); j++)
                {
                    faitsAjoutes.push_back(r[0]->getConclusion()[j]);
                    if(base->getBut()!=NULL && *r[0]->getConclusion()[j] == *base->getBut())
                    {
                        butAtteint = true;
                    }
                }
                ajouterConclusion(base, r[0]);
                base->retenirRegle(r[0], "avant");
                supprimerRegle(base, r[0]);
                //On incrémente l'indice de la règle qui indique sa récence d'utilisation
                r[0]->incUtilisation();
            }

             r = chercherRegleApplicableChainageAvant(base);

            //On trie les règles en fonction de la gestion des conflits, sauf dans le cas où on prends les règles dans l'ordre d'appariton
            if(gestionConflit!="ordre")
                trierRegles(r, gestionConflit);

        }
    }
    return faitsAjoutes;
}


/* Méthode qui réalise un chaînage mixte sur la base de connaissance */
vector<Element *> Moteur::chainageMixte(BaseDeConnaissances *base, const std::string &gestionConflit)
{
    vector<Element *> elementsAjoutes; //Vecteur qui va contenir les éléments ajoutés à la base de faits en tout
    vector<Element *> e; //Vecteur qui va contenir les éléments ajoutés à la base de faits pendant le chaînage avant, puis pendant le chaînage arrière

    //On effectue le chaînage dans le cas où le but n'est pas présent dans la base de faits
    if(!elementPresent(base->getBaseDeFaits(), base->getBut()))
    {
        do
        {
            //On effectue le chaînage avant
            e = chainageAvant(base, "largeur", gestionConflit);
            //On renseigne les faits ajoutés
            for(unsigned int i=0; i<e.size(); i++)
            {
             elementsAjoutes.push_back(e[i]);
            }
            //On effectue un chaînage arrière si on est coincé, s'il n'y a pas d'autres faits déductibles, et si on a pas atteint le but
            if(!(elementsAjoutes.back() == base->getBut()))
            {
                e = chainageArriere(base, e);
                //On renseigne les faits ajoutés
                for(unsigned int i=0; i<e.size(); i++)
                {
                    elementsAjoutes.push_back(e[i]);
                }
            }
        }while(e.size() != 0); //Exécution de la boucle jusqu'à ce qu'on ne trouve plus de faits déductibles
    }
    return elementsAjoutes;
}


/* Méthode qui va renvoyer les règles applicables pour la base de connaissance
Si le dernier paramètre indique un chainage avant en profondeur, une seule règle est déclenchée chaque niveau de déduction
Sinon, s'il s'agit d'un chainage avant en largeur, on va enrichir la base de fait de tous les faits qu'on peut déduire à chaque niveau de déduction */
vector<Regle *> Moteur::chercherRegleApplicableChainageAvant(BaseDeConnaissances *base)
{
    //Curseur pour parcourir la liste (on le met au début de la liste)
    Regle *curseur = base->getDebut();
    //Variable qui compte le nombre de correspondances
    unsigned int correspondance = 0;
    //Contient les règles applicables
    vector<Regle *> regles;

    //Tant qu'on est pas à la fin de la liste, on continue
    while(curseur!=NULL)
    {
        for(unsigned int i=0; i<curseur->getPremisse().size(); i++)
        {
            for(unsigned int j=0; j<base->getBaseDeFaits().size(); j++)
            {
                if(*base->getBaseDeFaits()[j] == *curseur->getPremisse()[i])
                    correspondance++;
            }
        }

        //Si on a suffisemment de correspondances, la règle est applicable
        if(correspondance == curseur->getPremisse().size())
        {
            regles.push_back(curseur);
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
vector<Element *> Moteur::chainageArriere(BaseDeConnaissances *base, vector<Element *> &conclusions)
{
    //Vecteur qu'on va retourner, avec la liste des éléments ajoutés à la base de faits
    vector<Element *> faitsAjoutes;

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
void Moteur::initChainageArriere(BaseDeConnaissances *base, Element *but, vector<Element *> &faitsAjoutes)
{
    //Initialisation de la base de faits
    vector<Element *> BF = base->getBaseDeFaits();

    //Initialisation de l'iterateur de la base de règles
    Regle *cursor = base->getDebut();

    //Pour retenir le numéro de l'élément de la prémisse à ajouter dans la base de faits
    int numElementPremisse;

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
                   numElementPremisse = i;
                 }
                else
                {
                    ++correspondance;

                    //Cas où toutes les prémisses sont dans la base de faits
                    if (correspondance == cursor->getPremisse().size())
                    {
                        base->retenirRegle(cursor, "arriere");
                        //On incrémente l'indice de la règle qui indique sa récence d'utilisation
                        cursor->incUtilisation();
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
                        //On affiche la fenêtre de question à l'utilisateur
                        FenetreQuestionUtilisateur fenetreQuestionUtilisateur(baseDeConnaissances, cursor->getPremisse()[numElementPremisse++]);
                        fenetreQuestionUtilisateur.exec();
                    }

                }
            }
        }
        cursor = cursor->getSuivant();
    }
}


/* Vérifie l'existence d'un élément de conclusion dans un vecteur d'élément */
bool Moteur::elementPresent(vector<Element *> &conclusion, const Element *e)
{
    //On regarde si l'élément est dans le vecteur de conclusions
    for (unsigned i=0; i <conclusion.size(); i++){
        if (*e == *conclusion[i]){
            return true;
        }
    }
    return false;
}


/* Méthode qui vérifie l'existence de la règle dans un vecteur de règles */
bool Moteur::reglePresente(vector<Regle *> &vecteur_regles, Regle *ptr_regle)
{
    for (unsigned i=0; i <vecteur_regles.size(); i++){
        if (*ptr_regle == *vecteur_regles[i]){
            return true;
        }
    }
    return false;
}


/* Méthode qui va trier des règles, contenues dans un vecteur, passé en paramètre
et en fonction de la gestion des conflits, indiquée en paramètres */
void Moteur::trierRegles(std::vector<Regle *> &r, std::string const &gestionConflit)
{
    for(unsigned i=1; i<r.size(); i++)
    {
        //Cas où la règle a plus de prémisses que la règle précédente, dans la gestion des conflits qui prends la règle avec le plus de prémisses
        //Ou cas où la règle a moins de prémisses que la règle précédente, dans la gestion des conflits qui prends la règle avec le moins de prémisses
        if((gestionConflit == "nbPremisseSup" && r[i]->getPremisse().size() > r[i-1]->getPremisse().size()) || (gestionConflit == "nbPremisseInf" && r[i]->getPremisse().size() < r[i-1]->getPremisse().size()))
        {
            //On retient la règle précédente
            Regle *tmp =  new Regle;
            tmp = r[i-1];
            //On va interchanger les deux règles
            r[i-1] = r[i];
            r[i] = tmp;
        }
        //Cas où on va trier la règle selon sa récence d'utilisation
        else if(gestionConflit == "recenceUtilisation" && r[i]->getRecenceUtilisation() > r[i-1]->getRecenceUtilisation())
        {
            //On retient la règle précédente
            Regle *tmp =  new Regle;
            tmp = r[i-1];
            //On va interchanger les deux règles
            r[i-1] = r[i];
            r[i] = tmp;
        }
    }
}
