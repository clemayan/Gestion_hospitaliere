#include <stdio.h>
#include <stdlib.h>
#include "struct_hopital.h"
#include <string.h>

/* définitions des fonctions */
void ajout(FILE *f,nb_patients,num_doss);
void ajout_medecin();
void recherche();
void afficher();
int dernier_num();
int compte(FILE *fichier);

int choix=0;
char med[100][20]={"Michel","Noe","Mazuet","Bouchard"};
char chambres_occupees[100][5]={"A21","A23","A29","B89","C42","B23","A56","C77","A24","B24"};
int nb_ch=10; //nombre de chambres occupées
int num_doss; //numéro de dossier

int main() {
    /* menu principal */
    num_doss=dernier_num();
    while (choix != -1){
    	printf("------------------------------------"); //séparation pour mieux structurer le programme
    	printf("\n\nQue voulez vous faire (-1 pour arrêter)? : \n1-ajouter un dossier patient\n2-ajouter un dossier medecin\n3-rechercher un dossier patient\n4-afficher les dossiers\n5-supprimer un dossier\n6-modifier un dossier\n");
    	scanf("%d",&choix);
    	while ((choix>6||choix<1)&& (choix !=-1)){ //test si valeur entrée par utilisateur non conforme
        	printf("choix non valide !\n\n");
        	printf("Que voulez vous faire (-1 pour arrêter)? : \n1-ajouter un dossier patient\n2-ajouter un dossier medecin\n3-rechercher un dossier patient\n4-afficher les dossiers\n5-supprimer un dossier\n6-modifier un dossier\n");
        	scanf("%d",&choix);
    	}
    	int choix2=0;
    	switch(choix){
        	case 1: 
    			printf("Vous voulez ajouter un dossier :\n1-service consultation\n2-service urgence\n");
    			scanf("%d",&choix2);
    			while (choix2>2||choix2<1){ //valeur entrée par utilisateur non conforme
        			printf("choix non valide !\n\n");
        			printf("Vous voulez ajouter un dossier :\n1-service consultation\n2-service urgence\n");
        			scanf("%d",&choix2);
    			}
                    
    			FILE *f;
    			if (choix2==1){
        			//ajout du client sur le fichier consultations.txt
        			f=fopen("consultations.txt","a+");//ouvrir le fichier consultations.txt en mode append
        		}
    			else{ //choix2==2 
    				//ajout du client sur le fichier urgences.txt
        			f=fopen("urgences.txt","a+");//ouvrir le fichier urgences.txt en mode append
        		}
        		//message d'erreur d'ouverture de f
        		if (f==NULL){
        				fprintf(stderr,"\nErreur d'ouverture du fichier !");
        				return (EXIT_FAILURE);
        			}
        		
    			int nb_patients=compte(f); /*compte le nombre de patients déjà enregistrés*/
				num_doss=num_doss+1; //numéro du dossier du patient à ajouté
        		ajout(f,nb_patients,num_doss);   
        		fclose(f);      		
        		break;
        	case 2: ajout_medecin(); break;
        	case 3: recherche(); break;
        	case 4: afficher(); break;
        	case 5: recherche(); break;
        	case 6: recherche();break;
    	}
	}
}


/********************************************************************************/
/*             FONCTION QUI COMPTE LE NOMBRE DE PATIENTS DÉJÀ ENTRÉS            */
/********************************************************************************/

int compte(FILE *fichier){
  char c;
  int nLignes = 0;
  char c2 = '\0';

  while((c=fgetc(fichier)) != EOF){
    if(c=='\n')
      nLignes++;
    c2 = c;
  }
  /*c2 est le caractère juste avant le EOF */
  if(c2 != '\n')
    nLignes++; /* Dernière ligne non finie */
  return nLignes;
}


/**********************************************************************************/
/*             FONCTION QUI DONNE LE DERNIER NUMÉRO DE DOSSIER ATTRIBUÉ           */
/**********************************************************************************/


int dernier_num(){
	FILE *f;
	f=fopen("consultations.txt","r");
	FILE *g;
	g=fopen("urgences.txt","r");
	int nb_lignef=compte(f), nb_ligneg=compte(g),ligne=1,numf, numg;
	char c;
	
	rewind(f);
	c=fgetc(f);
	 while (c!=EOF && ligne<nb_lignef){ //arriver à la dernière ligne
	 		c=fgetc(f);
           if (c=='\n')
            ligne++;
    }
    fscanf(f, "%d,",&numf);    
    rewind(g);
    ligne=1;
	c=fgetc(g);
	 while (c!=EOF && ligne<nb_ligneg){ //arriver à la dernière ligne
	 		c=fgetc(g);
           if (c=='\n')
            ligne++;
    }
    fscanf(g, "%d,",&numg);
	fclose(f);
	fclose(g);
	
	if (numf>numg) //comparer les deux derniers numéro de dossier
		return numf;
	else
		return numg;
	
}
/************************************************************************/
/*             FONCTION QUI REMPLIT LE FICHIER DES PATIENTS             */
/************************************************************************/

void ajout(FILE *f,nb_patients,num_doss){
    FILE *g;
    g=fopen("medecins.txt","r");//ouvrir le fichier medecins.txt en mode lecture

    Dossier Patient;
    /* demande des informations du patient */
    printf("\nimmatricule (entier) du patient : ");
    scanf("%d",&Patient.immatricule);      
    printf("nom du patient : ");
    scanf("%s",Patient.coor.nom);
    printf("prénom du patient : ");
    scanf("%s",Patient.coor.prenom);
    printf("adresse du patient (numéro rue ville) : ");
    scanf("%d%s%s",&Patient.coor.adresse.num,Patient.coor.adresse.rue,Patient.coor.adresse.ville);
    printf("numero de téléphone du patient : +33 ");
    scanf("%d",&Patient.coor.numtel);
    while (Patient.coor.numtel>999999999||Patient.coor.numtel<100000000)
    {
        printf("numéro de téléphone non conforme : de type +33 610101010 !\n\n");
        printf("numero de téléphone du patient : +33 ");
    	scanf("%d",&Patient.coor.numtel);
    }
    printf("âge du patient : ");
    scanf("%d",&Patient.coor.age);
    while (Patient.coor.age>150||Patient.coor.age<0)
    {
        printf("âge non conforme !\n\n");
        printf("âge du patient : ");
        scanf("%d",&Patient.coor.age);
    }
    printf("sexe du patient (H, F ou N) : ");
    scanf(" %c", &Patient.coor.sexe);
    while (Patient.coor.sexe != 'H' && Patient.coor.sexe != 'F' && Patient.coor.sexe != 'N') 
    {
        printf("sexe non conforme !\n\n");
        printf("sexe du patient (H, F ou N) : "); 
        scanf(" %c", &Patient.coor.sexe);
    }
    printf("description maladie du patient (retour pour arrêter) : ");
	scanf(" %[^\n]", Patient.maladie);
	
    printf("examen : \n1-Accouchement\n2-Bilan de santé\n3-Opération du canal carpien\n4-ORL\n5-Échographie\n6-Coloscopie\n7-IRM\n: ");
	scanf(" %d", &Patient.examen);
	while (Patient.examen>7||Patient.examen<1)
    {
        printf("l'examen n'existe pas !\n\n");
        printf("examen : \n1-Accouchement\n2-Bilan de santé\n3-Opération du canal carpien\n4-ORL\n5-Échographie\n6-Coloscopie\n7-IRM\n: ");
		scanf(" %d", &Patient.examen);
    }
	
    printf("description des antécédent(s) du patient (retour pour arrêter) : ");
    scanf(" %[^\n]",Patient.antecedent);

    printf("batiment et numéro de chambre du patient (A 98) : ");
    scanf(" %c%d",&Patient.batiment,&Patient.num_chambre);
    while ((Patient.num_chambre>100||Patient.num_chambre<1) || (Patient.batiment!='A' && Patient.batiment!='B' && Patient.batiment!='C'))
    { // il y a 100 chambres et 3 bâtiments 
        printf("chambre non conforme !\nil y a 100 chambres et 3 bâtiments (A,B,C)\n\n");
        printf("batiment et numéro de chambre du patient (A 98) : ");
        scanf(" %c%d",&Patient.batiment,&Patient.num_chambre);
    }    
    int chb_existe=0;
    char num[4];
    char ch[5];
  	sprintf(num, "%d", Patient.num_chambre); //tranformer l'entier en chaine de caractères
  	
    ch[0]=Patient.batiment;
    for (int i=1;i<5;i++)
    	ch[i]=num[i-1]; //concatener le batiment et le numéro
    //printf("%s",ch);
    
    for (int i = 0; i < nb_patients+1; i++) {
    	//printf("%s",chambres_occupees[i]);
    	if (strcmp(chambres_occupees[i],ch)==0){
    		chb_existe=1;
    	}
  	}
  	
  	while (chb_existe==1){ //la chambre est attribuée
  		printf("la chambre est déjà attribuée ! Voici la liste des chambres attribuées :\n\n");
  		for (int i = 0; i < nb_ch; i++) {
    		printf("%s\t",chambres_occupees[i]);
    	}
    	chb_existe=0;
  		printf("\nbatiment et numéro de chambre du patient (A 98) : ");
    	scanf(" %c%d",&Patient.batiment,&Patient.num_chambre);
    	
  		sprintf(num, "%d", Patient.num_chambre); //tranformer l'entier en chaine de caractères
  	
    	ch[0]=Patient.batiment;
    	for (int i=1;i<5;i++)
    	ch[i]=num[i-1]; //concatener le batiment et le numéro
    	
    	for (int i = 0; i < nb_patients+1; i++) {
    		if (strcmp(chambres_occupees[i],ch)==0){ //la chambre est déjà attribué
    			chb_existe=1;
    		}
  		}
  	}
  	//ajout de la chambre aux chambres occupées -> ne focntionne pas
    nb_ch=nb_ch+1;
    for (int i=0;i<nb_ch;i++)
     chambres_occupees[nb_ch][i]= ch[i];
     
    /*
  	for (int i = 0; i < nb_ch+1; i++) {
    	printf("%s",chambres_occupees[i]);
  	}*/
  	
    
    printf("date entrée du patient (jj mm aaaa): ");
    scanf("%d%d%d",&Patient.date_entree.jour,&Patient.date_entree.mois,&Patient.date_entree.annee);
    while (Patient.date_entree.jour>31|| Patient.date_entree.jour<1||Patient.date_entree.mois>12||Patient.date_entree.mois<1||Patient.date_entree.annee>2024||Patient.date_entree.annee<1998) //date non conforme hopital crée en 1998
    {
        printf("date non conforme !\n\n");
        printf("date entrée du patient (jj mm aaaa): ");
        scanf("%d%d%d",&Patient.date_entree.jour,&Patient.date_entree.mois,&Patient.date_entree.annee);
        
    }
    
    printf("date du départ estimé du patient (jj mm aaaa): ");
    scanf("%d%d%d",&Patient.date_fin.jour,&Patient.date_fin.mois,&Patient.date_fin.annee);
    while (Patient.date_fin.jour>31|| Patient.date_fin.jour<1||Patient.date_fin.mois>12||Patient.date_fin.mois<1||Patient.date_fin.annee<1998) //date non conforme hopital crée en 1998
    {
        printf("date non conforme !\n\n");
        printf("date entrée du patient (jj mm aaaa): ");
        scanf("%d%d%d",&Patient.date_fin.jour,&Patient.date_fin.mois,&Patient.date_fin.annee);
        
    }
    printf("heure entrée du patient (heure minutes) : ");
    scanf("%d%d",&Patient.horraire_entree.heure,&Patient.horraire_entree.minutes);
    while (Patient.horraire_entree.heure>23||Patient.horraire_entree.minutes>59) //heure non conforme
    {
        printf("Heure non conforme !\n\n");
        printf("heure entrée du patient (heure minutes) : ");
        scanf("%d%d",&Patient.horraire_entree.heure,&Patient.horraire_entree.minutes);
    }    
    int nb_med=compte(g);
    printf("nom médecin : ");
    scanf("%s",Patient.med.coor.nom);
    int med_existe=0;
    for (int i = 0; i < nb_med+1; i++) {
    	//printf("%s",med[i]);
    	if (strcmp(med[i],Patient.med.coor.nom)==0){
    		med_existe=1;
    	}
  	}
  	while (med_existe==0){ //le medecin n'existe pas
  		printf("le médecin n'existe pas ! Voici la liste des médecins :\n");
  		for (int i = 0; i < nb_med+1; i++) {
    		printf("%s\t",med[i]);
    	}
  		printf("\n\nnom médecin : ");
    	scanf("%s",Patient.med.coor.nom);
    	//printf("%s",Patient.med.coor.nom);
    	for (int i = 0; i < nb_med+1; i++) {
    		//printf("%s",med[i]);
    		if (strcmp(med[i],Patient.med.coor.nom)==0){ //le medecin fait partie de ceux enregistrés
    			med_existe=1;
    		}
  		}
  	}    
    
    /*Calcul du devis*/
    int nb_jours = 0;
    int nb_mois = 0;
    if(Patient.date_entree.mois!=Patient.date_fin.mois || Patient.date_entree.annee!=Patient.date_fin.annee){
    	nb_jours=30-Patient.date_entree.jour; //nb de jours avant le prochain mois
    
    	//printf("%d\n",nb_jours);
    	//printf("%d\n",Patient.date_entree.mois+1);
    	if((Patient.date_entree.annee<Patient.date_fin.annee) && (Patient.date_entree.mois+1!=13 && Patient.date_entree.mois+1!=Patient.date_fin.mois)){ //pas la même année
    		nb_mois=12-(Patient.date_entree.mois+1)+(Patient.date_fin.mois-1); 
    	}else if((Patient.date_entree.annee==Patient.date_fin.annee) && (Patient.date_entree.mois+1!=13 && Patient.date_entree.mois+1!=Patient.date_fin.mois)){ //même année
    		nb_mois=Patient.date_fin.mois-Patient.date_entree.mois;
    	}
    	nb_jours=nb_jours+30.4167*nb_mois+Patient.date_fin.jour; //nombre de jours total
    }else{ // même mois et même année
    nb_jours=Patient.date_fin.jour-Patient.date_entree.jour;
    }
    Patient.devis=nb_jours*68; //68€ la nuit
    
    //printf("nombre de jours : %d\n",nb_jours);
    //printf("le cout des chambres est %d\n",Patient.devis);
    
    switch(Patient.examen){
    	case 1:Patient.devis=Patient.devis+2600;break; //accouchement
    	case 2:Patient.devis=Patient.devis+50;break; //Bilan de santé
    	case 3:Patient.devis=Patient.devis+1250;break; //Opération du canal carpien
    	case 4:Patient.devis=Patient.devis+35;break;//ORL
    	case 5:Patient.devis=Patient.devis+85;break;//Échographie
    	case 6:Patient.devis=Patient.devis+190;break;//Coloscopie
    	case 7:Patient.devis=Patient.devis+400;break; //IRM
    }
    
    printf("Le devis est de %d€\n",Patient.devis);
    
    
    /* écriture du dossier dans le fichier correspondant */
    fprintf(f, "%d,%d,%s,%s,%d_%s_%s,%d,%d,%c,",
            num_doss,Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, Patient.coor.adresse.num,Patient.coor.adresse.rue,Patient.coor.adresse.ville,
            Patient.coor.numtel,Patient.coor.age,Patient.coor.sexe);
            
    for (int i = 0; i < strlen(Patient.maladie); i++) {
    	if (Patient.maladie[i] == ' ') {
    		fprintf(f,"_"); //remplacer les espaces par _ dans le fichier consultations
    	} else {
      		fprintf(f,"%c", Patient.maladie[i]);
    	}
  	}
  	fprintf(f, ",%d,",Patient.examen);
    for (int i = 0; i < strlen(Patient.antecedent); i++) {
    	if (Patient.antecedent[i] == ' ') {
    		fprintf(f,"_"); //remplacer les espaces par _ dans le fichier consultations
    	} else {
      		fprintf(f,"%c", Patient.antecedent[i]);
    	}
  	}
    fprintf(f, ",%c%d,%d/%d/%d,%d/%d/%d,%dh%d,%s,%d€\n",Patient.batiment,Patient.num_chambre,Patient.date_entree.jour,Patient.date_entree.mois,Patient.date_entree.annee,Patient.date_fin.jour,Patient.date_fin.mois,Patient.date_fin.annee,Patient.horraire_entree.heure,Patient.horraire_entree.minutes,Patient.med.coor.nom,Patient.devis);
    
	fclose(g);
    printf("Dossier enregistré avec succés !\n");
    return 0;
}



/************************************************************************/
/*             FONCTION QUI REMPLIT LE FICHIER DES MEDECINS             */
/************************************************************************/

void ajout_medecin(){
    FILE *f;
    Medecin Med;
    
    f=fopen("medecins.txt","a+");//ouvrir le fichier medecins.txt en mode append et lecture
    //message d'erreur d'ouverture de f
    if (f==NULL){
        fprintf(stderr,"\nErreur d'ouverture du fichier !");
        return (EXIT_FAILURE);
    }
    
    int nb_med=compte(f);
    
    /* demande des informations du médecin */
    printf("\nspécialité du médecin :\nGynécologie\nChirurgie\nGastrologie\nRadiologie\nGénérale\n: ");
    scanf("%s",Med.specialite);
    while (strcmp(Med.specialite,"Gynécologie")!=0 && strcmp(Med.specialite,"Chirurgie")!=0 && strcmp(Med.specialite,"Gastrologie")!=0 && strcmp(Med.specialite,"Radiologie")!=0 && strcmp(Med.specialite,"Générale")!=0)
    {
    	printf("spécialité non conforme ! \n\nGynécologie\nChirurgie\nGastrologie\nRadiologie\nGénérale\n: ");
    	scanf("%s",Med.specialite);
    }
    
    printf("nom du médecin : ");
    scanf(" %s",Med.coor.nom);
    nb_med=nb_med+1;	
  	for (int i = 0; i < 20; i++) {
    	med[nb_med][i] = Med.coor.nom[i];
  	}//ajout du medecin au tableau
  	/*
  	for (int i = 0; i < nb_med+1; i++) {
    	printf("%s",med[i]);
  	}*/
    printf("prénom du médecin : ");
    scanf(" %s",Med.coor.prenom);
    printf("adresse du médecin (numéro rue ville) : ");
    scanf("%d%s%s",&Med.coor.adresse.num,Med.coor.adresse.rue,Med.coor.adresse.ville);
    printf("numero de téléphone du médecin : +33 ");
    scanf("%d",&Med.coor.numtel);
    while (Med.coor.numtel>999999999||Med.coor.numtel<100000000)
    {
        printf("numéro de téléphone non conforme : de type +33 610101010 !\n\n");
        printf("numero de téléphone du médecin : +33 ");
    	scanf("%d",&Med.coor.numtel);
    }
    printf("âge du médecin : ");
    scanf("%d",&Med.coor.age);
    while (Med.coor.age>150||Med.coor.age<18)
    {
        printf("âge non conforme !\n\n");
        printf("âge du médecin : ");
        scanf("%d",&Med.coor.age);
    }
    printf("sexe du médecin (H, F ou N) : ");
    scanf(" %c", &Med.coor.sexe);
    while (Med.coor.sexe != 'H' && Med.coor.sexe != 'F' && Med.coor.sexe != 'N') 
    {
        printf("sexe non conforme !\n\n");
        printf("sexe du médecin (H, F ou N) : ");
        scanf(" %c", &Med.coor.sexe);
    }
    fprintf(f, "%s,%s,%s,%d%s%s,%d,%d,%c\n",Med.specialite,Med.coor.nom,Med.coor.prenom,Med.coor.adresse.num,Med.coor.adresse.rue,Med.coor.adresse.ville,Med.coor.numtel,Med.coor.age,Med.coor.sexe);
    
    fclose(f);//fermer le fichier medecins.txt
    printf("Médecin enregistré avec succés !\n");

}



/************************************************************************************************/
/*             FONCTION DE RECHERCHE, DE MODIFICATION ET DE SUPPRESION D'UN DOSSIER             */
/************************************************************************************************/

void recherche(){ // + modification et suppression
    int choix_action=0, choix3=0,choix4=0, choixmodif=0, trouvef=0;
    int recherche_dos=0;
    char recherche_nom[100],recherche_prenom[100];
    
    Dossier Patient;	
    printf("1-recherche dans les consultations\n2-recherche dans les urgences\n");
    scanf("%d",&choix3);
    while (choix3>2||choix3<1){
        printf("choix non valide !\n");
        printf("1-recherche dans les consultations\n2-recherche dans les urgences\n");
        scanf("%d",&choix3);
    	}
    FILE *f;
    FILE *h;
    FILE *g;
    if (choix3==1){
    	f=fopen("consultations.txt","r");//ouvrir le fichier consultations.txt en mode lecture
    	if (choix==5){ //supression
    		g=fopen("suivi_consultations.txt","a");//ouvrir le fichier suivi_consultations.txt 
    		if (g==NULL){
  				fprintf(stderr,"\nErreur d'ouverture du fichier !");
   				return (EXIT_FAILURE);  
   				}  		
   		}
    }else{
    	f=fopen("urgences.txt","r");//ouvrir le fichier urgences.txt en mode lecture
    	if (choix==5){ //supression
    		g=fopen("suivi_urgences.txt","a");//ouvrir le fichier suivi_consultations.txt 
    		if (g==NULL){
  				fprintf(stderr,"\nErreur d'ouverture du fichier !");
   				return (EXIT_FAILURE);    		
   			}   
   		} 	
    } 
    if (choix==5||choix==6){
    		h=fopen("nouv.txt","w");//ouvrir le fichier nouv.txt en mode écriture        
    		if (h==NULL){
        		fprintf(stderr,"\nErreur d'ouverture du fichier !");
        	return (EXIT_FAILURE);
    	}  	
    }	
    //message d'erreur d'ouverture des fichiers :
    if (f==NULL){
        fprintf(stderr,"\nErreur d'ouverture du fichier !");
        return (EXIT_FAILURE);
    }  	
        
    int nb_patients=compte(f);
    rewind(f);
    char date_d[40],date_f[40],adresse[40],chbr[10],heure[10];
    printf("1-recherche par numéro de dossier\n2-recherche par nom\n");
    scanf("%d",&choix_action);
    while (choix_action>2||choix_action<1){
        printf("choix non valide !\n");
        printf("1-recherche par dossier\n2-recherche par nom\n");
        scanf("%d",&choix_action);
    }
    if (choix_action==1){ //num dossier
    	printf("entrer le numéro de dossier du patient à rechercher : ");
    	scanf("%d", &recherche_dos);
    }else{ //nom complet
    	printf("entrer le nom et le prénom du patient à rechercher : ");
    	scanf("%s%s",recherche_nom,recherche_prenom);
    }
    while(!feof(f)){
    	fscanf(f, "%d,%d,%[^,],%[^,],%[^,],%d,%d,%c,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d€\n",
    		&Patient.num_dossier,&Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, 
      		adresse, &Patient.coor.numtel,&Patient.coor.age,&Patient.coor.sexe,Patient.maladie,&Patient.examen,Patient.antecedent,
      		chbr,date_d,date_f,heure,Patient.med.coor.nom,&Patient.devis);
      		
       	if ((recherche_dos == Patient.num_dossier) || ((strcmp(recherche_prenom, Patient.coor.prenom) == 0) && (strcmp(recherche_nom, Patient.coor.nom) == 0))){ //dossier trouvé
			//afficher le dossier du patient 
			printf("Le dossier a été trouvé !\n\n");
           	printf("Informations du Patient :\n");
			printf("Dossier : %d\n",Patient.num_dossier);
    		printf("Immatricule : %d\n",Patient.immatricule);
    		printf("Nom : %s\n",Patient.coor.nom);
			printf("Prénom : %s\n",Patient.coor.prenom);
    		printf("Adresse : %s\n",adresse);
    		printf("Numéro de téléphone : +33%d\n",Patient.coor.numtel);
    		printf("Âge : %d\n",Patient.coor.age);
    		printf("Sexe : %c\n",Patient.coor.sexe);
    		printf("Description de la maladie : %s\n",Patient.maladie);
    		printf("Numéro d'examen : %d\n",Patient.examen);
    		printf("Antécédent(s) : %s\n",Patient.antecedent);
    		printf("Chambre : %s\n",chbr);
    		printf("Date d'arrivée : %s\n", date_d);
    		printf("Date de départ estimée : %s\n",date_f);
    		printf("Horaire : %s\n",heure);
    		printf("Médecin : %s\n", Patient.med.coor.nom);
    		printf("Devis : %d€\n\n",Patient.devis);
    		
    		if (choix==5){ //confirmation suppression du patient
    			printf("Voulez-vous confirmer la supression de ce dossier ?\n1-oui\n2-non\n");
				scanf("%d",&choix4);
				trouvef=1;
				while (choix4>2||choix4<0){
    				printf("choix non valide !\n");
    		   		printf("Voulez vous confirmer la supression de ce dossier ?\n1-oui\n2-non\n");
        			scanf("%d",&choix4);
    			}
    			
    			if (choix4==1)
    				fprintf(g, "%d,%d,%s,%s,%s,%d,%d,%c,%s,%d,%s,%s,%s,%s,%s,%s,%d€\n",Patient.num_dossier,Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, adresse, Patient.coor.numtel, Patient.coor.age,Patient.coor.sexe,Patient.maladie,Patient.examen,Patient.antecedent,chbr,date_d,date_f,heure,Patient.med.coor.nom,Patient.devis);
    		}else if(choix==6){ //confirmation modification du patient
    			printf("Voulez-vous modifier ce dossier ?\n1-oui\n2-non\n");
				scanf("%d",&choixmodif);
				trouvef=1;
				while (choixmodif>2||choixmodif<0){
    				printf("choix non valide !\n");
    		    	printf("Voulez vous modifier ce dossier ?\n1-oui\n2-non\n");
        			scanf("%d",&choixmodif);
    			}    	
				if (choixmodif==1)
					ajout(h,nb_patients,Patient.num_dossier); //ajout des nouvelles coordonnées en gardant le même numéro de dossier
    				if (feof(f))
    					return 0; //renvoi au menu si tous les dossiers ont été parcouru
    		}else{ //recherche
    			return 0; //renvoi au menu
    		}	
    	}else{
       		if(choix==5||choix==6) //écriture des informations non recherchées dans le fichier temporaire
       			fprintf(h, "%d,%d,%s,%s,%s,%d,%d,%c,%s,%d,%s,%s,%s,%s,%s,%s,%d€\n",Patient.num_dossier,Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, adresse, Patient.coor.numtel, Patient.coor.age,Patient.coor.sexe,Patient.maladie,Patient.examen,Patient.antecedent,chbr,date_d,date_f,heure,Patient.med.coor.nom,Patient.devis);
    	}
    }
    if (trouvef!=1){//aucun dossier trouvé
        printf("Le dossier recherché n'existe pas.\n");
        return 0;
    }else{
    	if (choix==5 || choix ==6){
    		if (choix4==2 || choixmodif==2){//changement d'avis  
    			remove("nouv.txt");//supprimer le fichier temporaire
			}else{ //suppression
	 			if (choix3==1){//suppression des consultations
					remove("consultations.txt");//suppression ancien fichier
					rename( "nouv.txt","consultations.txt");
				}else{//suppression des urgences
					remove("urgences.txt");//suppression ancien fichier
					rename( "nouv.txt","urgences.txt");
				}
			}			
		}
    }    
	fclose(h);  
    fclose(g);  
    fclose(f); 
    return 0;
}


/***********************************************************/
/*             FONCTION D'AFFICHAGE DE DOSSIER             */
/***********************************************************/ 

void afficher(){
	int choixdoss,choixtri;
	printf("Que voulez-vous afficher ?\n1-les consultations\n2-les urgences\n:");
	scanf("%d",&choixdoss);
    while (choixdoss>2||choixdoss<0){
       	printf("choix non valide !\n");
    	printf("Que voulez-vous afficher ?\n1-les consultations\n2-les urgences\n:");
       	scanf("%d",&choixdoss);
  	}
	printf("Comment voulez-vous trier ?\n1-tout afficher\n2-par ordre alphabétique\n3-à une date précise\n:");
	scanf("%d",&choixtri);
	while (choixtri>3||choixtri<0){
      	printf("choix non valide !\n");
      	printf("Comment voulez-vous trier ?\n1-tout afficher\n2-par ordre alphabétique\n3-à une date précise\n:");
     	scanf("%d",&choixtri);
 	}
 	FILE *f;
    if (choixdoss==1){
    	f=fopen("consultations.txt","r");//ouvrir le fichier consultations.txt en mode lecture
    }else{
    	f=fopen("urgences.txt","r");//ouvrir le fichier consultations.txt en mode lecture
    }//message d'erreur d'ouverture de f
    if (f==NULL){
     	fprintf(stderr,"\nErreur d'ouverture du fichier !");
     	return (EXIT_FAILURE);
    }
    
    int nb_patients=compte(f);
    rewind(f);
    char date_d[40],date_f[40],adresse[40],chbr[10],heure[10],date_cherchee[12];
    int trouvef=0,i=0;
    Dossier Patient;
    char (*tab)[40] = malloc(nb_patients * sizeof *tab); //tableau dynamique ordre alphabétique

    if(tab == NULL){ 
        printf("Erreur d'allocation mémoire");
    	exit(1);
    }
    
    if (choixtri==3){
    	printf("entrer la date sous la forme 'jj/mm/aaaa' : ");
    	scanf(" %s",date_cherchee);
    	while (strlen(date_cherchee)<10){ //verification de la date rentrée
    		printf("date non valide ! entrer la date sous la forme 'jj/mm/aaaa' : ");
    		scanf(" %s",date_cherchee);
    	}
    }
    while(!feof(f)){
    		fscanf(f, "%d,%d,%[^,],%[^,],%[^,],%d,%d,%c,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d€\n",
    			&Patient.num_dossier,&Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, 
      			adresse, &Patient.coor.numtel,&Patient.coor.age,&Patient.coor.sexe,Patient.maladie,&Patient.examen,Patient.antecedent,
      			chbr,date_d,date_f,heure,Patient.med.coor.nom,&Patient.devis);
      		
    	
    	if (choixtri==1 || strcmp(date_d,date_cherchee)==0){
       		//afficher le dossier du patient 
			printf("Dossier : %d\n",Patient.num_dossier);
    		printf("Immatricule : %d\n",Patient.immatricule);
    		printf("Nom : %s\n",Patient.coor.nom);
			printf("Prénom : %s\n",Patient.coor.prenom);
    		printf("Adresse : %s\n",adresse);
    		printf("Numéro de téléphone : +33%d\n",Patient.coor.numtel);
    		printf("Âge : %d\n",Patient.coor.age);
    		printf("Sexe : %c\n",Patient.coor.sexe);
    		printf("Description de la maladie : %s\n",Patient.maladie);
    		printf("Numéro d'examen : %d\n",Patient.examen);
    		printf("Antécédent(s) : %s\n",Patient.antecedent);
    		printf("Chambre : %s\n",chbr);
    		printf("Date d'arrivée : %s\n", date_d);
    		printf("Date de départ estimée : %s\n",date_f);
    		printf("Horaire : %s\n",heure);
    		printf("Médecin : %s\n", Patient.med.coor.nom);
    		printf("Devis : %d€\n\n",Patient.devis);	
    		trouvef=1;
    	}else if(choixtri==2){//alphabétique
    		for (int k=0;k<sizeof(Patient.coor.nom)/sizeof(*Patient.coor.nom);k++){
        		tab[i][k]=Patient.coor.nom[k]; //ajout du noms dans la liste
        	}
        	i=i+1;
    	}
	}    
    if (choixtri==3 && trouvef!=1){//aucune date trouvée
        printf("Aucun patient n'est arrivé à la date %s\n",date_cherchee);        	
    }
    /*
    for (int j = 0; j < nb_patients; j++){
        	printf("%s\n", tab[j]);
    }  */
    if (choixtri==2){
    	//tri de la liste des noms.
        char *temp[40]; 
        int i, j;
        for (i = 0; i < nb_patients-1; i++){ 
        	for (j = i+1; j < nb_patients; j++){
        		//printf("%s et %s\n",tab[i],tab[j]);
             	if (strcmp(tab[i], tab[j]) > 0){
                	//temp = tab[i];
                	for (int k=0;k<sizeof(tab[i])/sizeof(*tab[i]);k++){
        				temp[k] = tab[i][k];
        			}
                	//tab[i] = tab[j];
                	for (int k=0;k<sizeof(tab[j])/sizeof(*tab[j]);k++){
        				tab[i][k] = tab[j][k];
        			}
                	//tab[j] = temp;
                	for (int k=0;k<sizeof(temp)/sizeof(*temp);k++){
        				tab[j][k] = temp[k];
        			}
               	}
            }
        }
        /*
    	for (int j = 0; j < nb_patients; j++){
        	printf("%s\n", tab[j]);
    	}*/
    	for (int i=0;i<nb_patients;i++){
    		rewind(f); //retour au début du fichier
    		while(!feof(f)){
    			fscanf(f, "%d,%d,%[^,],%[^,],%[^,],%d,%d,%c,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d€\n",
    				&Patient.num_dossier,&Patient.immatricule, Patient.coor.nom, Patient.coor.prenom, 
      				adresse, &Patient.coor.numtel,&Patient.coor.age,&Patient.coor.sexe,Patient.maladie,&Patient.examen,Patient.antecedent,
      				chbr,date_d,date_f,heure,Patient.med.coor.nom,&Patient.devis);
      			
       			if (strcmp(tab[i], Patient.coor.nom) == 0){ //dossier trouvé
					//afficher le dossier du patient 
					printf("Dossier : %d\n",Patient.num_dossier);
    				printf("Immatricule : %d\n",Patient.immatricule);
    				printf("Nom : %s\n",Patient.coor.nom);
					printf("Prénom : %s\n",Patient.coor.prenom);
    				printf("Adresse : %s\n",adresse);
    				printf("Numéro de téléphone : +33%d\n",Patient.coor.numtel);
    				printf("Âge : %d\n",Patient.coor.age);
    				printf("Sexe : %c\n",Patient.coor.sexe);
    				printf("Description de la maladie : %s\n",Patient.maladie);
    				printf("Numéro d'examen : %d\n",Patient.examen);
    				printf("Antécédent(s) : %s\n",Patient.antecedent);
    				printf("Chambre : %s\n",chbr);
    				printf("Date d'arrivée : %s\n", date_d);
    				printf("Date de départ estimée : %s\n",date_f);
    				printf("Horaire : %s\n",heure);
    				printf("Médecin : %s\n", Patient.med.coor.nom);
    				printf("Devis : %d€\n\n",Patient.devis);
    			}
    		}
    	}  
    }
    free(tab);
    fclose(f);
}

