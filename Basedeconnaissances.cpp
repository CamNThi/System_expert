#include "Basedeconnaissances.h"

using namespace std;


/* Constructeur */
BaseDeConnaissances::BaseDeConnaissances() : debut(NULL), butChainage(NULL)
{

}


/* Destructeur */
BaseDeConnaissances::~BaseDeConnaissances()
{
    delete debut;
}


/* Méthode qui va récupérer les éléments qui composent la règle */
vector<Element *> BaseDeConnaissances::getElements(string const &ligneTexte)
{
    string ligne = ligneTexte;

    //Tableau qui va contenir les éléments
    vector<Element *> elements;

    int indiceEt;

    //Tant qu'il y a un "ET", c'est à dire un élément suivant, on continue la boucle
    do
    {
        //On créé un nouvel élément
        Element *e = new Element;

        //Stocke le résultat de la recherche pour le caractère
        int recherche;
        //Tableau qui contient les opérateurs à rechercher
        string operateurs[] = {"=", "!=", ">", "<", ">=", "<="};
        //Stocke le nombre de caractères qu'occupe l'opérateur
        unsigned int nbCarOp = 0;

        recherche = -1; //-1 veut dire qu'on a rien trouvé
        //On parcourt le tableau pour rechercher tous les opérateurs
        for(unsigned int i = 0; i<6; i++)
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
        e->setAttribut(ligne.substr(0, recherche));
        e->setOperateur(ligne.substr(recherche, nbCarOp));
        string valeur = ligne.substr(recherche+nbCarOp);

        //On recherche s'il y a un "ET"
        indiceEt = valeur.find("ET");

        //Cas où il y a un "ET", c'est qu'il y a d'autres éléments
        if(indiceEt != -1)
        {
            e->setValeur(valeur.substr(0, indiceEt));
            ligne = valeur.substr(indiceEt + 2);
        }
        //Sinon, c'est qu'on est donc à la fin de la ligne
        else
        {
            e->setValeur(valeur);
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

            // récupération des vecteurs avant vérification de cohérance
            std::vector<Element *> vpremisse = getElements(premisse);
            std::vector<Element *> vconclusion = getElements(conclusion);
          
            
            //Vérification de cohérence
            if(RegleCoherente(vpremisse,vconclusion)){
                //Ajout que les regles cohérentes
                Regle *r = this->AjouteRegle(vpremisse,vconclusion);
                
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


/* Méthode qui va se charger de vider le vecteur contenant les règles appliquées par le chaînage avant ou arrière */
void BaseDeConnaissances::viderReglesAppliquees(string const &chainage)
{
    //On supprime les éléments du vecteur du chaînage avant
    if(chainage == "avant")
    {
        reglesAppliqueesAvant.clear();
    }
    else if(chainage == "arriere")
    {
        reglesAppliqueesArriere.clear();
    }
}



//Méthode qui se charge de retenir la règle passée en paramètre, c'est à dire de l'enregistrer dans un vecteur pour le chaînage avant ou le chaînage arrière
void BaseDeConnaissances::retenirRegle(Regle *r, string const &chainage)
{
    if(chainage == "avant")
        reglesAppliqueesAvant.push_back(r);
    else if(chainage == "arriere")
        reglesAppliqueesArriere.push_back(r);
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
            retour += baseDeFaits[i]->toString();
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


/* Méthode qui affiche les règles appliquées pour le chaînage avant ou le chaînage arrière */
string BaseDeConnaissances::afficheReglesAppliquees(string const &chainage)
{
    string vecteur;
    string retour = "";

    if(chainage == "avant")
    {
        //Cas où il n'y a pas de règles appliquées
        if(reglesAppliqueesAvant.size()==0)
            return "Aucune regle n'a ete appliquee.";
        else
        {
            for(unsigned int i=0; i<reglesAppliqueesAvant.size(); i++)
            {
                if(chainage == "avant")
                    retour += reglesAppliqueesAvant[i]->toString();
                else if(chainage == "arriere")
                    retour += reglesAppliqueesAvant[i]->toString();
                retour += "\n";
            }
        }
    }
    else if(chainage == "arriere")
    {
        //Cas où il n'y a pas de règles appliquées
        if(reglesAppliqueesArriere.size()==0)
            return "Aucune regle n'a ete appliquee.";
        else
        {
            for(unsigned int i=0; i<reglesAppliqueesArriere.size(); i++)
            {
                if(chainage == "avant")
                    retour += reglesAppliqueesArriere[i]->toString();
                else if(chainage == "arriere")
                    retour += reglesAppliqueesArriere[i]->toString();
                retour += "\n";
            }
        }
    }




    return retour;
}


/* Accesseurs */

Regle *BaseDeConnaissances::getDebut() const
{
    return debut;
}

vector<Element *> &BaseDeConnaissances::getBaseDeFaits()
{
    return baseDeFaits;
}

vector<Regle*> &BaseDeConnaissances::getReglesAppliqueesAvant()
{
    return reglesAppliqueesAvant;
}

vector<Regle*> &BaseDeConnaissances::getReglesAppliqueesArriere()
{
    return reglesAppliqueesArriere;
}

Element *BaseDeConnaissances::getBut()
{
    return butChainage;
}


/* Modificateur */
void BaseDeConnaissances::setDebut(Regle *r)
{
    debut = r;
}

void BaseDeConnaissances::setBut(Element *e)
{
    butChainage = e;
}


/* Vérifie l'unicité d'un attribut des éléments de conclusion */
bool BaseDeConnaissances::attributPresent(vector<Element *> &conclusion, const Element *e)
{
    //si l'attribut des élément est dans le vecteur de conclusions
    for (unsigned i=0; i <conclusion.size(); i++){
        if (e->getAttribut() == conclusion[i]->getAttribut()){
            return true;
        }
    }
    return false;
}


//verification de doublon dans un vecteur
bool BaseDeConnaissances::Doublon(std::vector<Element*> &vector_to_check, const Element* value){
    
    int check = 0;
        for(int i=0; i< vector_to_check.size(); ++i){
            if(value->getAttribut() == vector_to_check[i]->getAttribut()){
                check += 1; 
            }
            // L'element ne doit pas être présent  plus d'une fois
            if(check > 1){
                return true;
            }
        }
        //L'element n'est présent qu'une fois 
        return false;
    }

//Vérifie la cohérence des règles sur la base 
// "Une règle ayant des attribut distinct est considérée comme cohérente !
bool BaseDeConnaissances::RegleCoherente(std::vector<Element *> &premisse, std::vector<Element *> &conclusion){
    // un doublon d'attribut d'element est présent dans les pemisses 
    
    for(unsigned i=0; i < premisse.size(); ++i){;
        //Verification des premisses  ou  premisse et conclusion
        if(this->Doublon(premisse, premisse[i])||this->attributPresent(conclusion,premisse[i]) ){
            //cout<< "Doublon d'attibuts sur les premisse ou entre premisse et conclusion";
            return false;
            }
        }
    
    //Doublon présent sur les conclusions
    for(unsigned i=0; i < conclusion.size(); ++i){
        if(Doublon(conclusion,conclusion[i])){
            //cout<< "Doublon d'attibuts au sein de la conclusion";
            return false;
            } 
        }   
        // Aucun doublon sur la règle !  Elle est cohérente. 
        return true;
    }

//Factorisation du bloc d'ajout de règle
Regle * BaseDeConnaissances::AjouteRegle(std::vector<Element *> &premisse, std::vector<Element *> &conclusion){
    //On récupère les éléments qui composent la prémisse
    vector<Element *> e1 = premisse;

    //On récupère les éléments qui composent la conclusion
    vector<Element *> e2 = conclusion;
    //On créé le premier élément de la liste
    Regle *r = new Regle();
    //On initialise cet élément
    r->remplirPremisse(e1);
    r->remplirConclusion(e2);
    //On met l'élément suivant à NULL puisqu'il s'agit du dernier élément de la liste
    r->setSuivant(NULL);

    return r;
    }