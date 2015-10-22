#include "Config.h"

using namespace std;


/* Le constructeur va se charger d'initialiser tous les paramètres de l'application par défaut */
Config::Config():typeChainageAvant("profondeur")
{

}


/* Modificateurs */

void Config::setTypeChainageAvant(string const &typeChainage)
{
    typeChainageAvant = typeChainage;
}


/* Accesseurs */

string &Config::getTypeChainageAvant()
{
    return typeChainageAvant;
}
