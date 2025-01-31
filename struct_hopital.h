/************************************************************/
/*             STRUCTURE CRÉATION D'UNE ADRESSE             */
/************************************************************/

typedef struct TAdresse TAdresse;
struct TAdresse{
    int num;
    char rue[60];
    char ville[30];
};


/***************************************************************/
/*             STRUCTURE COORDONNÉES D'UNE PERSONNE            */
/***************************************************************/

typedef struct TCoor TCoor;
struct TCoor{
    char nom[20]; 
    char prenom[20];
    TAdresse adresse;
    int numtel; 
    int age;
    char sexe; //H(omme),F(emme),N(on genré)
};


/*********************************************************/
/*             STRUCTURE CRÉATION D'UNE DATE             */
/*********************************************************/

typedef struct TDate TDate;
struct TDate{
    int jour;
    int mois;
    int annee;
};


/*******************************************/
/*             STRUCTURE HEURE             */
/*******************************************/

typedef struct THeure THeure;
struct THeure{
    int heure;
    int minutes;
};


/********************************************/
/*             STRUCTURE MÉDECINS           */
/********************************************/

//dossiers des medecins
typedef struct Medecin Medecin;
struct Medecin{
    char specialite[30];
    TCoor coor;
};


/**************************************************************/
/*             STRUCTURE INFORMATIONS DES PATIENTS            */
/**************************************************************/

//dossiers des patients
typedef struct Dossier Dossier;
struct Dossier{
	int num_dossier;
    int immatricule;
    TCoor coor;
    char maladie[100]; 
    int examen;
    char antecedent[100]; 
    int num_chambre;
    char batiment; 
    TDate date_entree;
    TDate date_fin;
    THeure horraire_entree;
    Medecin med;
    int devis;

};