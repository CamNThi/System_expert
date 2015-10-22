#include <QApplication>
#include "FenetrePrincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Création de la fenêtre principale
    FenetrePrincipale fenetrePrincipale;
    fenetrePrincipale.show();

    //Démarrage du programme et affichage des fenêtres
    return app.exec();
}
