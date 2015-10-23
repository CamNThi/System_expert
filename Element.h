#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string.h>


/* Classe qui décrit un élément qui compose la règle */
class Element
{
    public:
        //Constructeur
        Element();
        //Méthode qui modifie l'attribut
        void setAttribut(std::string const &attribut);
        //Méthode qui modifie l'opérateur
        void setOperateur(std::string const &operateur);
        //Méthode qui modifie la valeur
        void setValeur(std::string const &valeur);
        //Accesseurs
        std::string const &getAttribut() const;
        std::string const &getOperateur() const;
        std::string const &getValeur() const;
        //Pour décrire l'élément
        std::string toString() const;

    private:
        std::string m_attribut;
        std::string m_operateur;
        std::string m_valeur;
};

//On redéfinit l'opérateur de comparaison pour pouvoir comparer deux éléments
bool operator==(Element const &element1, Element const &element2);

#endif
