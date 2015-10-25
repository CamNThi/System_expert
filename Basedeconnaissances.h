#ifndef BASEDECONNAISSANCES_H
#define BASEDECONNAISSANCES_H

#include <vector> //Pour pouvoir utiliser les vecteurs
#include <fstream> //Pour pouvoir lire un fichier txt
#include <string>

#include "Regle.h"


/* Classe qui contient la base de connaissances à savoir la base de faits et la base de règles
Elle va permettre d'effectuer des opérations sur cette base de connaissances */
class BaseDeConnaissances
{
    public:
        //Constructeur
        BaseDeConnaissances();
        //Constructeur avec paramètres

        //Destructeur
        ~BaseDeConnaissances();
        //Méthode qui va récupérer chaque élément qui composent la règle, contenus dans une ligne de texte
        std::vector<Element *> getElements(std::string const &ligneTexte);
        //Méthode qui va remplir la base de règles à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé
        bool remplirBR(std::string const &nomFichier);
        //Méthode qui va remplir la base de faits à partir d'un fichier .txt, elle renvoie vrai si le remplissage s'est bien passé
        bool remplirBF(std::string const &nomFichier);
        //Méthode qui va se charger de vider la base de faits
        void viderBF();
        //Méthode qui va se charger de vider les règles appliquées par le chaînage avant ou arrière
        void viderReglesAppliquees(std::string const &chainage);
        //Méthode qui va se charger de retenir la règle passée en paramètre, c'est à dire de l'enregistrer dans un vecteur pour le chaînage avant ou le chaînage arrière
        void retenirRegle(Regle *r, std::string const &chainage);
        //Méthode qui affiche la base de faits
        std::string afficheBF();
        //Méthode qui affiche la base de règles
        std::string afficheBR();
        //Méthode qui affiche les règles appliquées pour le chaînage avant ou le chaînage arrière
        std::string afficheReglesAppliquees(std::string const &chainage);
        //Accesseurs
        Regle *getDebut() const;
        std::vector<Element *> &getBaseDeFaits();
        std::vector<Regle *> &getReglesAppliqueesAvant();
        std::vector<Regle *> &getReglesAppliqueesArriere();
        Element *getBut();
        //Modificateur
        void setDebut(Regle *r);
        void setBut(Element *e);

    private:
        //Eléments qui servira de repère dans la liste chainée
        Regle *debut; //Pointe vers le 1er élément de la liste
        //Tableau qui contient la base de faits
        std::vector<Element *> baseDeFaits;
        //Tableau qui contient les règles appliquées pendant le chainage avant
        std::vector<Regle *> reglesAppliqueesAvant;
        //Tableau qui contient les règles appliquées pendant le chaînage arrière
        std::vector<Regle *> reglesAppliqueesArriere;
        //Variable qui contient le but à atteindre pour le chaînage
        Element *butChainage;
};

#endif

