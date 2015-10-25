#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>

#include "FenetreConfig.h"
#include "FenetreButChainage.h"
#include "FenetreAfficheBase.h"
#include "FenetreTracesAbreges.h"
#include "FenetreQuestionUtilisateur.h"
#include "Moteur.h"


/* Interface principale, point de départ de l'application */
class FenetrePrincipale : public QWidget
{
    //Macro pour créer les slots personnalisés
    Q_OBJECT

    public slots:
        void remplirBF();
        void remplirBR();
        void chainageAvant();
        void chainageArriere();
        void chainageMixte();
        void voirBF();
        void voirBR();
        void voirConfig();
        void viderBase();

    public:
        FenetrePrincipale();
        //Méthode qui met à jour graphiquement l'affichage de la base de faits
        void refreshBF();
        //Méthode qui lance l'affichage de la fenêtre des traces du chaînage réalisé
        void afficherTracesChainage(std::vector<Element *> const &e, std::string const &chainage);
        //Accesseur
        Config *getConfig() const;

    private:
        //Les 4 boutons du bas du menu
        QPushButton *bouton0;
        QPushButton *bouton1;
        QPushButton *bouton2;
        QPushButton *bouton3;
        //Le layout en bas qui va contenir les boutons du bas
        QHBoxLayout *layout_boutons_bas;
        //Le texte à afficher
        QLabel *texte;
        //Message en fonction des actions effectuées
        QLabel *message;
        //Les zones de texte pour afficher le contenu de la base de faits avant et après le passage du moteur
        QTextEdit *BFInitial;
        QTextEdit *BFMoteur;
        //Les labels pour indiquer à quoi correspondent les deux zones de texte
        QLabel *label_BFInitial;
        QLabel *label_BFMoteur;
        //Le layout qui contient les labels
        QHBoxLayout *layoutBF_labels;
        //Le layout qui va contenir les deux zones de texte
        QHBoxLayout *layoutBF_global;
        //Le layout qui va contenir la zone de texte gauche ainsi que le bouton concernant la base de faits
        QVBoxLayout *layoutBF_gauche;
        //Le bouton concernant la base de faits;
        QPushButton *bouton4;
        //Boutons du haut
        QPushButton *bouton5;
        QPushButton *bouton6;
        QPushButton *bouton7;
        QPushButton *bouton8;
        //le layout qui contient les boutons du haut
        QHBoxLayout *layout_boutons_haut;
        //Le layout global qui va contenir tous les éléments
        QVBoxLayout *layout_global;

        //La base de connaissance
        BaseDeConnaissances *baseDeConnaissances;
        //Le moteur
        Moteur *moteur;
        //Contient la configuration de l'application
        Config *config;
        //La fenêtre qui s'affiche pour renseigner des règles qui remplissent la base de règles
        FenetreAfficheBase *fenetreBase;
        //La fenêtre de configuration de l'application
        FenetreConfig *fenetreConfig;
        //Fenêtre qui affiche les traces du chaînage réalisé
        FenetreTracesAbreges *fenetreTraces;
        //Fenêtre pour initialiser les buts pour le chaînage avant/arrière
        FenetreButChainage *fenetreChainageArriere;
};

#endif
