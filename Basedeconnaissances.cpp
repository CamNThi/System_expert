#include "Basedeconnaissances.h"

using namespace std;


/* Constructeur */
BaseDeConnaissances::BaseDeConnaissances() : debut(NULL)
{

}


/* Destructeur */
BaseDeConnaissances::~BaseDeConnaissances()
{
    delete debut;
}


/* Méthode qui va récupérer les éléments qui composent la règle */
vector<Element> BaseDeConnaissances::getElements(string const &ligneTexte)
{
    string ligne = ligneTexte;

    //Tableau qui va contenir les éléments
    vector<Element> elements;

    int indiceEt;

    //Tant qu'il y a un "ET", c'est à dire un élément suivant, on continue la boucle
    do
    {
        //On créé un nouvel élément
        Element e;

        //Stocke le résultat de la recherche pour le caractère
        int recherche;
        //Tableau qui contient les opérateurs à rechercher
        string operateurs[] = {"=", "!=", ">", "<", ">=", "<="};
        //Stocke le nombre de caractères qu'occupe l'opérateur
        unsigned int nbCarOp = 0;

        recherche = -1; //-1 veut dire qu'on a rien trouvé
        //On parcourt le tableau pour rechercher tous les opérateurs
        for(int i = 0; i<6; i++)
        {
            //Si on a trouvé un opérateur à une position dont l'indice est inférieur à la position actuelle trouvée...
            if((recherche > ligne.find(operateurs[i]) || recherche == -1) && (ligne.find(operateurs[i]) != -1))
            {
                //...On met à jour la position
                recherche = ligne.find(operateurs[i]);
                if(i == 1 || i == 4 || i == 5)
                    nbCarOp = 2;
                else
                    nbCarOp = 1;
            }
        }

        //On initialise les valeurs
        e.setAttribut(ligne.substr(0, recherche));
        e.setOperateur(ligne.substr(recherche, nbCarOp));
        string valeur = ligne.substr(recherche+nbCarOp);

        //On recherche s'il y a un "ET"
        indiceEt = valeur.find("ET");

        //Cas où il y a un "ET", c'est qu'il y a d'autres éléments
        if(indiceEt != -1)
        {
            e.setValeur(valeur.substr(0, indiceEt));
            ligne = valeur.substr(indiceEt + 2);
        }
        //Sinon, c'est qu'on est donc à la fin de la ligne
        else
        {
            e.setValeur(valeur);
        }

        //On ajoute l'élément au tableau
        elements.push_back(e);

    }while(indiceEt != -1);

    return elements; //On retourne le tableau d'éléments
}


/* Méthode qui va remplir la base de règles à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé */
bool BaseDeConnaissances::remplirBR(string const &nomFichier)
{
    Regle *curseur = NULL; //Curseur pour parcourir la liste

    //On ouvre le fichier en lecture
    //On utilise c_str() pour convertir la chaine de caractères string en char* afin de la passer à la fonction
    string nom = "donnees/"+nomFichier;
    ifstream fichier(nom.c_str(), ios::in);

    //Si l'ouverture a réussi
    if(fichier)
    {
        //Va stocker la ligne du fichier actuelle
        string ligne;

        while(getline(fichier, ligne))
        {
            //On coupe en deux la phrase pour récupérer d'un côté la prémisse et de l'autre la conclusion
            string premisse = ligne.substr(0, ligne.find("->"));
            string conclusion = ligne.substr(ligne.find("->")+2);

            //On récupère les éléments qui composent la prémisse
            vector<Element> e1 = getElements(premisse);

            //On récupère les éléments qui composent la conclusion
            vector<Element> e2 = getElements(conclusion);

            //On créé le premier élément de la liste
            Regle *r = new Regle();
            //On initialise cet élément
            r->remplirPremisse(e1);
            r->remplirConclusion(e2);
            //On met l'élément suivant à NULL puisqu'il s'agit du dernier élément de la liste
            r->setSuivant(NULL);

            //On a pas commencé à remplir la liste, celle-ci est encore vide
            if(debut == NULL)
            {
                //On met à jour le curseur
                curseur = r;
                //On renseigne le 1er élément de la liste
                debut = r;
            }
            //Sinon, la liste est non vide
            else
            {
                //On met à jour l'élément suivant du curseur (qui n'est plus le dernier élément maintenant)
                curseur->setSuivant(r);
                //On met à jour le curseur
                curseur = r;
            }
        }

        //Fermeture du fichier
        fichier.close();

        return true;
    }
    else
    {
        return false;
    }
}


/* Méthode qui va remplir la base de faits à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé */
bool BaseDeConnaissances::remplirBF(string const &nomFichier)
{
    //On ouvre le fichier en lecture
    //On utilise c_str() pour convertir la chaine de caractères string en char* afin de la passer à la fonction
    string nom = "donnees/"+nomFichier;
    ifstream fichier(nom.c_str(), ios::in);

    //Si l'ouverture a réussi
    if(fichier)
    {
        //Va stocker la ligne du fichier actuelle
        string ligne;

        //On récupère la ligne
        getline(fichier, ligne);

        //On récupère les éléments qui composent la base de faits
        baseDeFaits = getElements(ligne);

        //Fermeture du fichier
        fichier.close();

        return true;
    }
    else
    {
        return false;
    }
}


/* Méthode qui va se charger de vider le vecteur contenant les règles appliquées */
void BaseDeConnaissances::viderReglesAppliquees()
{
    //On supprime les éléments du vecteur
    reglesAppliquees.clear();
}


//Méthode qui se charge de retenir la règle passée en paramètre
void BaseDeConnaissances::retenirRegle(Regle *r)
{
    reglesAppliquees.push_back(r);
}


/* Méthode qui va se charger de vider la base de faits */
void BaseDeConnaissances::viderBF()
{
    //On supprime les éléments du vecteur
    baseDeFaits.clear();
}


/* Méthode qui affiche la base de faits */
string BaseDeConnaissances::afficheBF()
{
    string retour = "";
    //Cas où la base de faits est vide
    if(baseDeFaits.size()==0)
        return "La base de faits est vide.";
    else
    {
        for(unsigned int i=0; i<baseDeFaits.size(); i++)
        {
            retour += baseDeFaits[i].toString();
        }
    }
    return retour;
}


/* Méthode qui affiche la base de règles */
string BaseDeConnaissances::afficheBR()
{
    string retour = "";
    //Cas où la base de règles est vide
    if(debut == NULL)
    {
        return "La base de regles est vide.";
    }
    else
    {
        //Curseur pour parcourir la liste (on le met au début de la liste)
        Regle *curseur = debut;
        //Affichage du 1er élément
        retour += curseur->toString();
        retour += "\n";
        //Tant qu'on est pas à la fin de la liste, on l'affiche
         while(curseur->getSuivant()!=NULL)
        {
            //On met à jour le curseur pour passer au prochain élément
            curseur = curseur->getSuivant();
            //On affiche l'élément
            retour += curseur->toString();
            retour += "\n";
        }

    }
    return retour;
}


/* Méthode qui affiche les règles appliquées */
string BaseDeConnaissances::afficheReglesAppliquees()
{
    string retour = "";
    //Cas où il n'y a pas de règles appliquées
    if(reglesAppliquees.size()==0)
        return "Aucune regle n'a ete appliquee.";
    else
    {
        for(unsigned int i=0; i<reglesAppliquees.size(); i++)
        {
            retour += reglesAppliquees[i]->toString();
            retour += "\n";
        }
    }
    return retour;
}


/* Accesseurs */

Regle *BaseDeConnaissances::getDebut()
{
    return debut;
}

vector<Element> &BaseDeConnaissances::getBaseDeFaits()
{
    return baseDeFaits;
}

vector<Regle*> &BaseDeConnaissances::getReglesAppliquees()
{
    return reglesAppliquees;
}


/* Modificateur */
void BaseDeConnaissances::setDebut(Regle *r)
{
    debut = r;
}

