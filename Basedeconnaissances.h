#ifndef BASEDECONNAISSANCES_H
#define BASEDECONNAISSANCES_H

#include <vector> //Pour pouvoir utiliser les vecteurs
#include <string>
#include "Element.h"
#include "Regle.h"
#include <fstream> //Pour pouvoir lire un fichier txt


/* Classe qui contient la base de connaissances à savoir la base de faits et la base de règles */
class BaseDeConnaissances
{
    public:
        //Constructeur
        BaseDeConnaissances();
        //Constructeur avec paramètres

        //Destructeur
        ~BaseDeConnaissances();
        //Méthode qui va récupérer chaque élément qui composent la règle, contenus dans une ligne de texte
        std::vector<Element> getElements(std::string const &ligneTexte);
        //Méthode qui va remplir la base de règles à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé
        bool remplirBR(std::string const &nomFichier);
        //Méthode qui va remplir la base de faits à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé
        bool remplirBF(std::string const &nomFichier);
        //Méthode qui va se charger de vider la base de faits
        void viderBF();
        //Méthode qui va se charger de vider les règles appliquées
        void viderReglesAppliquees();
        //Méthode qui va se charger de retenir la règle passée en paramètre, c'est à dire de l'enregistrer dans un vecteur
        void retenirRegle(Regle *r);
        //Méthode qui affiche la base de faits
        std::string afficheBF();
        //Méthode qui affiche la base de règles
        std::string afficheBR();
        //Méthode qui affiche les règles appliquées
        std::string afficheReglesAppliquees();
        //Accesseurs
        Regle *getDebut();
        std::vector<Element> &getBaseDeFaits();
        std::vector<Regle *> &getReglesAppliquees();
        //Modificateur
        void setDebut(Regle *r);

    private:
        //Eléments qui servira de repère dans la liste chainée
        Regle *debut; //Pointe vers le 1er élément de la liste
        //Tableau qui contient la base de faits
        std::vector<Element> baseDeFaits;
        //Tableau qui contient les règles appliquées pendant le chainage
        std::vector<Regle*> reglesAppliquees;
};

#endif

