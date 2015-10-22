#ifndef CONFIG_H
#define CONFIG_H

#include <string>


/* Classe qui va se charger de retenir la configuration choisit */
class Config
{
    private:
        std::string typeChainageAvant;

    public:
        //Constructeur
        Config();
        //Modificateurs
        void setTypeChainageAvant(const std::string &typeChainage);
        //Accesseurs
        std::string &getTypeChainageAvant();
};

#endif
