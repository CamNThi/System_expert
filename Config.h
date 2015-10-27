#ifndef CONFIG_H
#define CONFIG_H

#include <string>


/* Classe qui va se charger de retenir la configuration choisit */
class Config
{
    private:
        std::string typeChainageAvant;
        std::string gestionConflit;

    public:
        //Constructeur
        Config();
        //Modificateurs
        void setTypeChainageAvant(std::string const &typeChainage);
        void setGestionConflit(std::string const &gestion);
        //Accesseurs
        std::string &getTypeChainageAvant();
        std::string &getGestionConflit();
};

#endif
