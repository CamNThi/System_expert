#include "Element.h"

using namespace std;

/* Constructeur */
Element::Element()
{

}


/* Méthode qui modifie l'attribut */
void Element::setAttribut(string const &attribut)
{
    m_attribut = attribut;
}


/* Méthode qui modifie l'opérateur */
void Element::setOperateur(string const &operateur)
{
    m_operateur = operateur;
}


/* Méthode qui modifie la valeur */
void Element::setValeur(string const &valeur)
{
    m_valeur = valeur;
}


/* Accesseurs */
string const &Element::getAttribut() const
{
    return m_attribut;
}


string const &Element::getOperateur() const
{
    return m_operateur;
}


string const &Element::getValeur() const
{
    return m_valeur;
}


/* Méthode qui affiche le contenu d'un élément */
std::string Element::toString() const
{
    return m_attribut+" "+m_operateur+" "+m_valeur+"\n";
}


/* On redéfinit l'opérateur de comparaison */
bool operator==(Element const &element1, Element const &element2)
{
    if(element1.getAttribut() == element2.getAttribut() && element1.getOperateur() == element2.getOperateur() && element1.getValeur() == element2.getValeur())
        return true;
    else
        return false;
}

