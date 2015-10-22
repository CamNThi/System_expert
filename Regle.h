#ifndef REGLE_H
#define REGLE_H

#include "Element.h"
#include <vector>


/* Classe qui décrit une règle (composée d'une prémisse et d'une conclusion)
Les règles sont implémentées selon une liste simplement chaînée */
class Regle
{
    public:
        //Constructeur
        Regle();
        //Destructeur
        ~Regle();
        //Accesseur pour l'élément suivant de la liste
        Regle *getSuivant() const;
        //Modificateur pour l'élément suivant de la liste
        void setSuivant(Regle *r);
        //Pour remplir le tableau des prémisses
        void remplirPremisse(std::vector<Element> const &tabPremisses);
        //Pour remplir le tableau des conclusions
        void remplirConclusion(std::vector<Element> const &tabConclusions);
        //Accesseur du tableau des prémisses
        std::vector<Element> &getPremisse();
        //Accesseur du tableau des conclusions
        std::vector<Element> &getConclusion();
        //Pour décrire la règle
        std::string toString() const;

    private:
        //Vecteur contenant les éléments de la prémisse
        std::vector<Element> m_premisse;
        //Vecteur contenant les éléments de la conclusion
        std::vector<Element> m_conclusion;
        //Pointeur sur l'élément suivant
        Regle *m_suivant;
};

bool operator==(Regle &element1, Regle &element2);

#endif
