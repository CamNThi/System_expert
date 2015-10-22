#ifndef FENETREBASEDEREGLES_H
#define FENETREBASEDEREGLES_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

#include "Basedeconnaissances.h"


/* Fenêtre qui va afficher les contenus de la base de faits/base de règles */
class FenetreAfficheBase : public QDialog
{
    public:
        FenetreAfficheBase(BaseDeConnaissances *baseDeConnaissances, std::string const &base);

    private:
        QTextEdit *contenu;
        QVBoxLayout *layout_global;
};

#endif

