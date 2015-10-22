#include "Regle.h"

using namespace std;


/* Constructeur */
Regle::Regle() : m_suivant(NULL)
{


}


/* Destructeur */
Regle::~Regle()
{
    delete m_suivant;
}


/* Accesseur pour récupére l'élément suivant */
Regle *Regle::getSuivant() const
{
    return m_suivant;
}


/* Modificateur pour l'élément suivant de la liste */
void Regle::setSuivant(Regle *r)
{
    m_suivant = r;
}


/* Méthode qui remplit le tableau des prémisses */
void Regle::remplirPremisse(vector<Element> const &tabPremisses)
{
    //Remplissage des prémisses
    for(unsigned int i=0; i<tabPremisses.size(); i++)
    {
        m_premisse.push_back(tabPremisses[i]);
    }
}


/* Méthode qui remplit le tableau des conclusions */
void Regle::remplirConclusion(vector<Element> const &tabConclusions)
{
     //Remplissage des conclusions
    for(unsigned int i=0; i<tabConclusions.size(); i++)
    {
        m_conclusion.push_back(tabConclusions[i]);
    }
}


/* Accesseur du tableau des prémisses */
vector<Element> &Regle::getPremisse()
{
    return m_premisse;
}


/* Accesseur du tableau des conclusions */
vector<Element> &Regle::getConclusion()
{
    return m_conclusion;
}


/* Affichage de la règle */
string Regle::toString() const
{
    string retour = "";
    for(unsigned int i=0; i<m_premisse.size(); i++)
    {
        if(i==0)
            retour += "Si ";
        else
            retour += "ET ";
        retour += m_premisse[i].toString();
    }
    retour += "alors ";
    for(unsigned int i=0; i<m_conclusion.size(); i++)
    {
        retour += m_conclusion[i].toString();
    }
    return retour;
}


bool operator==(Regle &element1, Regle &element2)
{
    bool retour = true;
    for(unsigned int i=0; i<element1.getPremisse().size(); i++)
    {
        for(unsigned int j=0; j<element2.getPremisse().size(); j++)
        {
            if(!(element1.getPremisse()[i]==element2.getPremisse()[j]))
            {
                retour=false;
            }
        }
    }
    for(unsigned int i=0; i<element1.getConclusion().size(); i++)
    {
        for(unsigned int j=0; j<element2.getConclusion().size(); j++)
        {
            if(!(element1.getConclusion()[i]==element2.getConclusion()[j]))
            {
                retour=false;
            }
        }
    }
    return retour;
}

