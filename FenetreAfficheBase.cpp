#include "FenetreAfficheBase.h"

using namespace std;


/* Widget qui servira de fenêtre secondaire pour afficher les contenus de la base de règles/base de faits
 On lui passe en paramètre la base de connaissance qui contient les règles et les faits
On lui passe également une chaîne de caractère indiquant la base qu'on veut afficher (base de règles ou base de faits) */
FenetreAfficheBase::FenetreAfficheBase(BaseDeConnaissances *baseDeConnaissances, string const &base) : QDialog()
{
    //On renseigne le titre de la fenêtre en fonction de la base à afficher
    if(base=="BF")
        setWindowTitle("Base de faits actuelle");
    else if(base=="BR")
        setWindowTitle("Base de regles actuelle");

    //Taille de la fenêtre
    setFixedSize(300, 300);

    //Création du texte
    contenu = new QTextEdit();
    //Pas de possibilité de modifier le texte
    contenu->setReadOnly(true);
    //On récupère le contenu de la base passée en paramètres
    string BaseString = "";
    if(base=="BF")
        BaseString = baseDeConnaissances->afficheBF();
    else if(base=="BR")
        BaseString = baseDeConnaissances->afficheBR();
    //On convertit la chaine de caractères en QString pour l'affichage
    QString Base = QString::fromStdString(BaseString);
    contenu->setText(Base);

    //Ajout du layout dans la fenêtre
    layout_global = new QVBoxLayout();
    layout_global->addWidget(contenu);
    setLayout(layout_global);
}
