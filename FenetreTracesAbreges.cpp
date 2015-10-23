#include "FenetreTracesAbreges.h"

using namespace std;

/* On passe en paramètres du constructeur la base de connaissance
ainsi qu'un vecteur contenant les éléments ajoutés à la base de faits lors du chaînage
 et on indique le type de chaînage (avant, arriere ou mixte) */
FenetreTracesAbreges::FenetreTracesAbreges(BaseDeConnaissances *b, vector<Element> const &e, string const &chainage) : QDialog()
{
    //Titre de la fenêtre
    setWindowTitle("Traces du chainage");

    //Taille de la fenêtre
    setFixedSize(500, 100);

    //Construction des éléments
    labelRegles = new QLabel;
    labelFaits = new QLabel;

    //On récupère le nombre de règles appliquées
    int nbReglesString;
    if(chainage == "avant")
        nbReglesString = b->getReglesAppliqueesAvant().size();
    else if(chainage == "arriere")
        nbReglesString = b->getReglesAppliqueesArriere().size();
    else if(chainage == "mixte")
        nbReglesString = b->getReglesAppliqueesAvant().size()+b->getReglesAppliqueesArriere().size();
    QString nbRegles = QString::number(nbReglesString);
    labelRegles->setText("Nombre de regles appliquees a la base de faits: "+nbRegles);

    //On récupère le nombre de faits déduits
    int nbFaitsString;
    nbFaitsString = e.size();
    QString nbFaits = QString::number(nbFaitsString);
    labelFaits->setText("Nombre de faits deduits: "+nbFaits);

    //Création des boutons
    bouton_traces = new QPushButton(">>> Afficher les traces");
    bouton_annuler = new QPushButton("Retour");

    //Création du layout et ajout des boutons
    layout_boutons = new QHBoxLayout;
    layout_boutons->addWidget(bouton_traces);
    layout_boutons->addWidget(bouton_annuler);

    //Création du layout
    layout_global = new QVBoxLayout;
    layout_global->addWidget(labelRegles);
    layout_global->addWidget(labelFaits);
    layout_global->addLayout(layout_boutons);

    //Ajout du layout dans la fenêtre
    setLayout(layout_global);

    //Connexion des boutons
    QObject::connect(bouton_traces, SIGNAL(clicked()), this, SLOT(afficherTracesCompletes()));
    QObject::connect(bouton_annuler, SIGNAL(clicked()), this, SLOT(quitter()));

    //On retient la base de connaissances, les éléments ajoutés et le type de chaînage
    base = b;
    elements = e;
    typeChainage = chainage;
}


/* Slot personnalisé qui ferme la fenêtre */
void FenetreTracesAbreges::quitter()
{
    this->close();
}


/* Slot personnalisé qui permet d'afficher la fenêtre avec les traces du chaînage */
void FenetreTracesAbreges::afficherTracesCompletes()
{
    //Création d'une nouvelle fenêtre
    QDialog fenetreTraces(this);

    //Titre de la fenêtre
    fenetreTraces.setWindowTitle("Traces du chainage");

    //Taille de la fenêtre
    fenetreTraces.setFixedSize(500, 300);

    //Construction des éléments
    QLabel label;
    QLabel label2;
    if(typeChainage == "mixte")
    {
        label.setText("Regles qui ont ete appliquees par chainage avant: ");
        label2.setText("Regles qui ont ete appliquees par chainage arriere: ");
    }
    else
        label.setText("Regles qui ont ete appliquees a la base de faits: ");
    QLabel labelFaits("Faits deduits: ");
    QTextEdit regles_appliquees;
    QTextEdit regles_appliquees2;
    QTextEdit faits_deduits;

    //On récupère les règles appliquées en fonction du type de chaînage
    string reglesString = "";
    if(typeChainage == "avant")
        reglesString = base->afficheReglesAppliquees("avant");
    else if(typeChainage == "arriere")
        reglesString = base->afficheReglesAppliquees("arriere");
    else if(typeChainage == "mixte")
    {
        string reglesString2 = "";
        reglesString = base->afficheReglesAppliquees("avant");
        reglesString2 = base->afficheReglesAppliquees("arriere");
        QString regles2 = QString::fromStdString(reglesString2);
        regles_appliquees2.setText(regles2);
        regles_appliquees2.setReadOnly(true);
    }
    QString regles = QString::fromStdString(reglesString);
    regles_appliquees.setText(regles);
    regles_appliquees.setReadOnly(true);

    //On récupère les faits déduits
    std::string faitsString = "";
    for(unsigned int i=0; i<elements.size(); i++)
    {
        faitsString += elements[i].toString();
        faitsString+="\n";
    }
    QString faits = QString::fromStdString(faitsString);
    faits_deduits.setText(faits);
    faits_deduits.setReadOnly(true);

    //Création du layout et ajout des éléments
    QVBoxLayout layout_global;
    layout_global.addWidget(&label);
    layout_global.addWidget(&regles_appliquees);
    if(typeChainage=="mixte")
    {
        layout_global.addWidget(&label2);
        layout_global.addWidget(&regles_appliquees2);
    }
    layout_global.addWidget(&labelFaits);
    layout_global.addWidget(&faits_deduits);

    //Ajout du layout dans la fenêtre
    fenetreTraces.setLayout(&layout_global);

    fenetreTraces.exec();
}
