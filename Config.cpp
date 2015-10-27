#include "Config.h"

using namespace std;


/* Le constructeur va se charger d'initialiser tous les paramètres de l'application par défaut */
Config::Config():typeChainageAvant("profondeur"), gestionConflit("ordre")
{

}


/* Modificateurs */

void Config::setTypeChainageAvant(string const &typeChainage)
{
    typeChainageAvant = typeChainage;
}

void Config::setGestionConflit(std::string const &gestion)
{
    gestionConflit = gestion;
}


/* Accesseurs */

string &Config::getTypeChainageAvant()
{
    return typeChainageAvant;
}

string &Config::getGestionConflit()
{
    return gestionConflit;
}
