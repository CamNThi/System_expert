#ifndef MOTEUR_H
#define MOTEUR_H

#include <string>
#include <vector>

#include "Basedeconnaissances.h"
#include "FenetreQuestionUtilisateur.h"


/* Moteur d'inférence qui va effectuer les chaînages */
class Moteur
{
    public:
        //Constructeur
        Moteur(BaseDeConnaissances *base);
        //Méthode qui réalise un chaînage avant sur la base de connaissance et qui renvoie les éléments ajoutés à la base de faits
        std::vector<Element *> chainageAvant(BaseDeConnaissances *base, std::string const &typeChainage);
        //Méthode qui lance le chaînage arrière sur la base de connaissance, et pour une liste de buts
        std::vector<Element *> chainageArriere(BaseDeConnaissances *base, std::vector<Element *> &but);
        //Méthode qui réalise un chaînage mixte sur la base de connaissance
        std::vector<Element *> chainageMixte(BaseDeConnaissances *base);
        //Effectue le chaînage arrière pour un but donné
        void initChainageArriere(BaseDeConnaissances *base, Element *but, std::vector<Element *> &faitsAjoutes);
        //Vérifie l'existence d'un élément de conclusion dans un vecteur d'élément
        bool elementPresent(std::vector<Element *> &conclusion, const Element *e);
        //Méthode qui vérifie l'existence de la règle dans un vecteur de règles
        bool reglePresente(std::vector<Regle *> &vecteur_regles, Regle *ptr_regle);
        //Méthode qui va renvoyer les règles applicables pour la base de connaissance
        std::vector<Regle*> chercherRegleApplicableChainageAvant(BaseDeConnaissances *base, std::string const &typeChainage);
        //Méthode qui va ajouter la conclusion de la règle passée en paramètres à la base de faits
        void ajouterConclusion(BaseDeConnaissances *base, Regle *regle);
        //Méthode qui va ajouter la prémisse de la règle passée en paramètres à la base de faits
        void ajouterPremisse(BaseDeConnaissances *base, Regle *regle);
        //Méthode qui va supprimer une règle de la base de règles
        void supprimerRegle(BaseDeConnaissances *base, Regle *r);

    private:
        //Pour retenir la base de connaissances
        BaseDeConnaissances *baseDeConnaissances;
};

#endif
