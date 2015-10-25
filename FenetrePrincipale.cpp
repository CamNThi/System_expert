#include "FenetrePrincipale.h"

using namespace std;


/* Widget qui servira de fenêtre principale */
FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    //On créé la base de connaissances
    baseDeConnaissances = new BaseDeConnaissances;
    //On créé le moteur
    moteur = new Moteur;
    //On créé la configuration de l'application
    config = new Config;

    //On fixe les dimensions de la fenêtre
    setFixedSize(700, 600);

    //On renseigne le titre de la fenêtre
    setWindowTitle("Systeme Expert");

    //Construction des boutons du haut
    bouton5 = new QPushButton(QIcon("images/database_go.png"), "BF");
    bouton6 = new QPushButton(QIcon("images/database_go.png"), "BR");
    bouton7 = new QPushButton(QIcon("images/cog_go.png"), "");
    bouton8 = new QPushButton(QIcon("images/database_red.png"), "Vider toute la base de connaissances");
    //Pour ajouter une infobulle aux boutons
    bouton5->setToolTip("Voir base de faits");
    bouton6->setToolTip("Voir base de regles");
    bouton7->setToolTip("Parametres de chainage");
    bouton8->setToolTip("Vider BF + BR");
    //Réduction de la taille des boutons
    bouton5->setFixedSize(50, 30);
    bouton6->setFixedSize(50, 30);
    bouton7->setFixedSize(50, 30);

    //Création du layout et ajout des boutons du haut
    layout_boutons_haut = new QHBoxLayout;
    layout_boutons_haut->addWidget(bouton5);
    layout_boutons_haut->addWidget(bouton6);
    layout_boutons_haut->addWidget(bouton7);
    layout_boutons_haut->addWidget(bouton8);
    layout_boutons_haut->setAlignment(Qt::AlignLeft);

    //Construction des boutons du bas
    bouton0 = new QPushButton(QIcon("images/download.png"), "Initialiser base de regles", this);
    bouton1 = new QPushButton("Chainage Avant");
    bouton2 = new QPushButton("Chainage Arriere");
    bouton3 = new QPushButton("Chainage Mixte");

    //Création du layout et ajout des boutons du bas
    layout_boutons_bas = new QHBoxLayout;
    //Ajout des boutons dans le layout
    layout_boutons_bas->addWidget(bouton0);
    layout_boutons_bas->addWidget(bouton1);
    layout_boutons_bas->addWidget(bouton2);
    layout_boutons_bas->addWidget(bouton3);

    //Construction des deux labels au-dessus des zones de texte
    label_BFInitial = new QLabel;
    label_BFInitial->setFixedHeight(30);
    label_BFInitial->setAlignment(Qt::AlignBottom);
    label_BFMoteur = new QLabel;
    label_BFMoteur->setFixedHeight(30);
    label_BFMoteur->setAlignment(Qt::AlignBottom);

    //Construction du layout et ajout des labels
    layoutBF_labels = new QHBoxLayout;
    layoutBF_labels->addWidget(label_BFInitial);
    layoutBF_labels->addWidget(label_BFMoteur);

    //Construction des zones de texte ainsi que du bouton concernant la base de faits
    bouton4 = new QPushButton(QIcon("images/download.png"), "Initialiser base de faits", this);
    BFInitial = new QTextEdit;
    BFMoteur = new QTextEdit;
    //Pour ne pas rendre le texte modifiable dans les zones de texte
    BFInitial->setReadOnly(true);
    BFMoteur->setReadOnly(true);
    //Pour encadrer le champ
    BFInitial->setStyleSheet("border: 1px solid grey");
    BFMoteur->setStyleSheet("border: 1px solid grey");
    //On met à jour la base de faits graphiquement : remplissage des zones de texte
    refreshBF();

    //Création du layout et ajout de la zone de texte gauche et du bouton
    layoutBF_gauche = new QVBoxLayout;
    layoutBF_gauche->addWidget(BFInitial);
    layoutBF_gauche->addWidget(bouton4);

    //Création du layout et ajout des deux zones de texte
    layoutBF_global = new QHBoxLayout;
    layoutBF_global->addLayout(layoutBF_gauche);
    //Trait de séparation vertical
    QFrame * line = new QFrame;
    line->setGeometry(QRect(160, 150, 3, 61));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    layoutBF_global->addWidget(line);
    layoutBF_global->addWidget(BFMoteur);

    //Construction du texte à afficher
    texte = new QLabel;
    //Pour aligner le texte en haut
    texte->setAlignment(Qt::AlignTop);
    //Remplissage du texte
    texte->setText("############################ Systeme Expert ############################");
    texte->setText(texte->text()+"\n\n\nCette application permet d'effectuer une simulation de raisonnements deductifs.");
    texte->setText(texte->text()+"\n\nPour que le moteur puisse fonctionner, veuillez remplir la base de regles en cliquant sur \"Initialiser base de regles\", puis la base de faits avec le bouton \"Initialiser base de faits\".");
    texte->setText(texte->text()+"\n\nPuis, pour lancer le moteur d'inference, cliquez sur l'un des 3 boutons correspondant aux 3 types de chainage ci-dessous.");
    //Pour justifier le texte
    texte->setWordWrap(true);
    //Construction du message qui s'affichera en fonction des actions de l'utilisateur
    message = new QLabel;
    message->setText("");
    message->setFixedHeight(40);
    //pour justifier le texte
    message->setWordWrap(true);
    message->setAlignment(Qt::AlignCenter);

    //Création du layout global et ajout des éléments
    layout_global = new QVBoxLayout;
    layout_global->addLayout(layout_boutons_haut);
    layout_global->addWidget(texte);
    layout_global->addWidget(message);
    layout_global->addLayout(layoutBF_labels);
    layout_global->addLayout(layoutBF_global);
    layout_global->addLayout(layout_boutons_bas);

    //Ajout du layout dans la fenêtre
    setLayout(layout_global);

    //Connexion des clics des boutons
    QObject::connect(bouton0, SIGNAL(clicked()), this, SLOT(remplirBR()));
    QObject::connect(bouton1, SIGNAL(clicked()), this, SLOT(chainageAvant()));
    QObject::connect(bouton2, SIGNAL(clicked()), this, SLOT(chainageArriere()));
    QObject::connect(bouton3, SIGNAL(clicked()), this, SLOT(chainageMixte()));
    QObject::connect(bouton4, SIGNAL(clicked()), this, SLOT(remplirBF()));
    QObject::connect(bouton5, SIGNAL(clicked()), this, SLOT(voirBF()));
    QObject::connect(bouton6, SIGNAL(clicked()), this, SLOT(voirBR()));
    QObject::connect(bouton7, SIGNAL(clicked()), this, SLOT(voirConfig()));
    QObject::connect(bouton8, SIGNAL(clicked()), this, SLOT(viderBase()));
}


/* Slot personnalisé pour initialiser la base de faits */
void FenetrePrincipale::remplirBF()
{
    if(baseDeConnaissances->getBaseDeFaits().size()!=0)
    {
        //On vide la base de faits
        baseDeConnaissances->viderBF();

        //On met l'affichage à vide pour la base de faits
        BFInitial->setText("");
        BFMoteur->setText("");
    }

    //On initialise la base de faits à partir du fichier
    bool result = baseDeConnaissances->remplirBF("BF.txt");

    //Cas où on ne trouve pas le fichier correspondant
    if(!result)
    {
        QMessageBox::critical(this, "Erreur", "Erreur, le fichier BF.txt n'a pas ete trouve dans le repertoire \"donnees\"");

    }
    //Cas où on a trouvé le fichier
    else
    {
        //Mis à jour du message de confirmation
        message->setText("Base de faits initialisee avec succes.");
        message->setStyleSheet("color: green");

        //On renomme le bouton
        bouton4->setText("Reinitialiser base de faits");

        //On efface l'ancien affichage de la base de faits
        BFInitial->setText("");

        //Mise à jour de l'affichage de la base de faits
        refreshBF();

        //On met à jour le label au-dessus de la zone de texte
        label_BFInitial->setText("Base de fait initiale:");
        label_BFMoteur->setText("");
    }
}


/* Slot personnalisé qui permet de remplir la base de règles */
void FenetrePrincipale::remplirBR()
{
    //Cas où la base de règles est déjà remplie, on affiche un message d'erreur
    if(baseDeConnaissances->getDebut()!=NULL)
    {
        message->setText("Echec de l'initialisation, la base de regles n'est pas vide.");
        message->setStyleSheet("color: red");
    }
    else
    //Cas où la base de règles est vide
    {
        //On initialise la base de règles à partir du fichier
        bool result = baseDeConnaissances->remplirBR("BR.txt");

        //Cas où on a pas trouvé le fichier
        if(!result)
        {
            QMessageBox::critical(this, "Erreur", "Erreur, le fichier BR.txt n'a pas ete trouve dans le repertoire \"donnees\"");

        }
        //Cas où on a trouvé le fichier
        else
        {
            //Mise à jour du message de confirmation
            message->setText("Base de regles initialisee avec succes.");
            message->setStyleSheet("color: green");
        }
    }
}


/* Slot personnalisé pour lancer le chainage avant */
void FenetrePrincipale::chainageAvant()
{
    //Cas où la base de règles n'est pas remplie, on affiche un message d'erreur
    if(baseDeConnaissances->getDebut()==NULL)
    {
        message->setText("Erreur dans l'execution du chainage avant, la base de regles est vide.\nCliquez sur \"Initialiser base de regles\".");
        message->setStyleSheet("color: red");
    }
    //Cas où la base de faits n'est pas remplie, on affiche un message d'erreur
    else if(baseDeConnaissances->getBaseDeFaits().size()==0)
    {
        message->setText("Erreur dans l'execution du chainage avant, la base de faits est vide.\nCliquez sur \"Initialiser base de faits\".");
        message->setStyleSheet("color: red");
    }
    else
    {
        //On remet à zéro le but
        baseDeConnaissances->setBut(NULL);

        //On ouvre la fenêtre qui va permettre à l'utilisateur de renseigner le but à atteindre
        fenetreChainageArriere = new FenetreButChainage(baseDeConnaissances, "avant");
        fenetreChainageArriere->exec();

        //On effectue le chaînage avant en récupérant la liste des éléments ajoutés à la base de faits, renvoyée par la méthode de chaînage
        vector<Element *> e = moteur->chainageAvant(baseDeConnaissances, config->getTypeChainageAvant());

        //Mise à jour de la base de faits graphiquement
        refreshBF();

        //On met à jour les labels au-dessus des zones de texte
        label_BFInitial->setText("Base de fait avant chainage avant:");
        label_BFMoteur->setText("Base de fait apres chainage avant:");

        //Mise à jour du message de confirmation
        message->setText("Le chainage avant s'est deroule avec succes.");
        message->setStyleSheet("color: green");

        //Fenêtre qui affiche les traces du chaînage
        afficherTracesChainage(e, "avant");
    }
}


/* Slot personnalisé pour effectuer le chainage arrière */
void FenetrePrincipale::chainageArriere()
{
    //Cas où la base de règles n'est pas remplie, on affiche un message d'erreur
    if(baseDeConnaissances->getDebut()==NULL)
    {
        message->setText("Erreur dans l'execution du chainage arriere, la base de regles est vide.\nCliquez sur \"Initialiser base de regles\".");
        message->setStyleSheet("color: red");
    }
    //Cas où la base de faits n'est pas remplie
    else if(baseDeConnaissances->getBaseDeFaits().size()==0)
    {
        message->setText("Erreur dans l'execution du chainage arriere, la base de faits est vide.\nCliquez sur \"Initialiser base de faits\".");
        message->setStyleSheet("color: red");
    }
    else
    {
        //On remet à zéro le but
        baseDeConnaissances->setBut(NULL);

        //On ouvre la fenêtre qui va permettre à l'utilisateur de renseigner le but à atteindre
        fenetreChainageArriere = new FenetreButChainage(baseDeConnaissances, "arriere");
        fenetreChainageArriere->exec();

        //Cas où le but n'a pas été rentré
        if(baseDeConnaissances->getBut()==NULL)
        {
            //Mise à jour du message de confirmation
            message->setText("Attention, vous devez rentrer un but pour ce type de chainage.");
            message->setStyleSheet("color: red");
        }
        //Cas où le but a été rentré correctement
        else
        {
            vector<Element *> buts;
            buts.push_back(baseDeConnaissances->getBut());

            //On effectue le chaînage arrière en récupérant la liste des éléments ajoutés à la base de faits, renvoyée par la méthode de chaînage
            vector<Element *> e = moteur->chainageArriere(baseDeConnaissances, buts);

            //Mise à jour de la base de faits
            refreshBF();

            //On met à jour les labels au-dessus des zones de texte
            label_BFInitial->setText("Base de fait avant chainage arriere:");
            label_BFMoteur->setText("Base de fait apres chainage arriere:");

            //Mise à jour du message de confirmation
            message->setText("Le chainage arriere s'est deroule avec succes.");
            message->setStyleSheet("color: green");

            //Fenêtre qui affiche les traces du chaînage
            afficherTracesChainage(e, "arriere");
        }
    }
}


/* Slot personnalisé pour effectuer le chainage mixte */
void FenetrePrincipale::chainageMixte()
{
    //Cas où la base de règles n'est pas remplie, on affiche un message d'erreur
    if(baseDeConnaissances->getDebut()==NULL)
    {
        message->setText("Erreur dans l'execution du chainage mixte, la base de regles est vide.\nCliquez sur \"Initialiser base de regles\".");
        message->setStyleSheet("color: red");
    }
    //Cas où la base de faits n'est pas remplie
    else if(baseDeConnaissances->getBaseDeFaits().size()==0)
    {
        message->setText("Erreur dans l'execution du chainage mixte, la base de faits est vide.\nCliquez sur \"Initialiser base de faits\".");
        message->setStyleSheet("color: red");
    }
    else
    {
        //On remet à zéro le but
        baseDeConnaissances->setBut(NULL);

        //On ouvre la fenêtre qui va permettre à l'utilisateur de renseigner le but à atteindre
        fenetreChainageArriere = new FenetreButChainage(baseDeConnaissances, "mixte");
        fenetreChainageArriere->exec();

        //Cas où le but n'a pas été rentré
        if(baseDeConnaissances->getBut()==NULL)
        {
            //Mise à jour du message de confirmation
            message->setText("Attention, vous devez rentrer un but pour ce type de chainage.");
            message->setStyleSheet("color: red");
        }
        //Cas où le but a été rentré correctement
        else
        {
            //On effectue le chaînage mixte en récupérant la liste des éléments ajoutés à la base de faits, renvoyée par la méthode de chaînage
            vector<Element *> e = moteur->chainageMixte(baseDeConnaissances);

            //Mise à jour de la base de faits
            refreshBF();

            //On met à jour les labels au-dessus des zones de texte
            label_BFInitial->setText("Base de fait avant chainage mixte:");
            label_BFMoteur->setText("Base de fait apres chainage mixte:");

            //Mise à jour du message de confirmation
            message->setText("Le chainage mixte s'est deroule avec succes.");
            message->setStyleSheet("color: green");

            //Fenêtre qui affiche les traces du chaînage
            afficherTracesChainage(e, "mixte");
        }
    }
}


/* Slot personnalisé qui permet d'ouvrir une fenêtre affichant le contenu de la base de faits */
void FenetrePrincipale::voirBF()
{
    //On ouvre la fenêtre qui contient l'intégral des faits
    fenetreBase = new FenetreAfficheBase(baseDeConnaissances, "BF");
    fenetreBase->exec();
}


/* Slot personnalisé qui permet d'ouvrir une fenêtre affichant le contenu de la base de regles */
void FenetrePrincipale::voirBR()
{
    //On ouvre la fenêtre qui contient l'intégral des règles
    fenetreBase = new FenetreAfficheBase(baseDeConnaissances, "BR");
    fenetreBase->exec();
}


/* Slot personnalisé qui permet d'afficher la fenêtre de configuration des paramètres */
void FenetrePrincipale::voirConfig()
{
    //On ouvre la fenêtre qui va permettre de configurer l'application
    fenetreConfig = new FenetreConfig(config);
    fenetreConfig->exec();
}


/* Slot personnalisé qui permet de vider toute la base */
void FenetrePrincipale::viderBase()
{
    //Suppression de la base actuelle
    delete baseDeConnaissances;
    //Création d'une nouvelle base vide
    baseDeConnaissances = new BaseDeConnaissances;
    //On met à jour l'affichage
    BFMoteur->setText("");
    BFInitial->setText("");
    label_BFInitial->setText("");
    label_BFMoteur->setText("");
    message->setText("La base de faits et la base de regles ont ete vides avec succes.");
    message->setStyleSheet("color: green");
}


/* Méthode qui met à jour graphiquement l'affichage de la base de faits */
void FenetrePrincipale::refreshBF()
{
    //On récupère le contenu de la base de faits
    string BFString = baseDeConnaissances->afficheBF();
    //On convertit la chaine de caractères en QString pour l'affichage
    QString BF = QString::fromStdString(BFString);
    //Si l'affichage gauche est vide, on affiche le contenu de la base de fait à gauche
    if(BFInitial->toPlainText() == "")
    {
        //Mise à jour de la base de faits
        BFInitial->setText(BF);
    }
    //Sinon c'est que la base de faits n'est pas vide
    else
    {
        if(BFMoteur->toPlainText() == "")
        {
            BFMoteur->setText(BF);
        }
        //Sinon on prend l'affichage droit pour le mettre à gauche et on met à jour l'affichage gauche
        else
        {
            BFInitial->setText(BFMoteur->toPlainText());
            BFMoteur->setText(BF);
        }
    }
}


/* Méthode qui lance l'affichage de la fenêtre des traces du chaînage réalisé
On lui passe en paramètres un vecteur contenant les éléments ajoutés à la base de faits lors du chaînage
On lui passe égalemente le type de chaînage réalisé (avant, arriere, mixte) */
void FenetrePrincipale::afficherTracesChainage(vector<Element *> const &e, string const &chainage)
{
    //On ouvre la fenêtre qui contient l'intégral des faits
    fenetreTraces = new FenetreTracesAbreges(baseDeConnaissances, e, chainage);
    fenetreTraces->exec();
}


/* Accesseur */
Config *FenetrePrincipale::getConfig() const
{
    return config;
}


