import shutil
import os
import csv 
import matplotlib.pyplot as plt

#tranformation des fichiers txt en fichiers csv
if os.path.exists("consultations.txt"):
  shutil.copyfile('consultations.txt', 'consultations.csv')
if os.path.exists("urgences.txt"):
  shutil.copyfile('urgences.txt', 'urgences.csv')
if os.path.exists("medecins.txt"):
  shutil.copyfile('medecins.txt', 'medecins.csv')



def part_examens(nom):
    with open (nom, "r") as f:
        lire=csv.reader(f)
        n=0 #nombre de lignes
        occurences={1:0,2:0,3:0,4:0,5:0,6:0,7:0} #dictionnaire avec l'occurence des examens dans fichier f
        for ligne in lire: 
            #print(ligne[9])
            n=n+1
            for i in range(1,8): #test de chaque examen
                if (int(ligne[9])==i): #examen i
                    occurences[i]=occurences[i]+1 #incrémentation du dictionnaire
    #print(occurences)

    labels=["Accouchement","Bilan de santé","Opération du canal carpien", "ORL","Échographie","Coloscopie", "IRM"]
    sizes=[] #calculer le pourcentage les parts des examens
    for i in range(1,8):
        sizes.append((occurences[i]/n)*100)#remplir le pourcentage de chaque examen
    #print(sizes)

    ##affichage des statistiques à l'écran :
    print("Dans",nom)
    print("la part d'accouchement est de",sizes[0],"%")
    print("la part de bilan de santé est de",sizes[1],"%")
    print("la part d'opération du canal carpien est de",sizes[2],"%")
    print("la part d'ORL de",sizes[3],"%")
    print("la part d'échographie est de",sizes[4],"%")
    print("la part de coloscopie est de",sizes[5],"%")
    print("la part d'IRM est de",sizes[6],"%")

    ##graphiques camembert:
    fig,ax=plt.subplots()
    ax.pie(sizes,labels=labels,autopct='%1.1f%%')
    plt.title("Part des examens")
    plt.show()


def part_examens_total():
    with open ("consultations.csv", "r") as f1: 
        lire1=csv.reader(f1)
        n=0
        occurences={1:0,2:0,3:0,4:0,5:0,6:0,7:0} #dictionnaire avec l'occurence des examens dans fichier f1
        for ligne in lire1: 
            #print(ligne[9])
            n=n+1
            for i in range(1,8): #test de chaque examen
                if (int(ligne[9])==i): #examen i
                    occurences[i]=occurences[i]+1 #incrémentation du dictionnaire
    with open ("urgences.csv", "r") as f2:
      lire2=csv.reader(f2)
      n=0
      for ligne in lire2: 
            #print(ligne[9])
            n=n+1
            for i in range(1,8): #test de chaque examen
                if (int(ligne[9])==i): #examen i
                    occurences[i]=occurences[i]+1 #incrémentation du dictionnaire


    labels=["Accouchement","Bilan de santé","Opération du canal carpien", "ORL","Échographie","Coloscopie", "IRM"]
    sizes=[] #calculer le pourcentage les parts des examens
    for i in range(1,8):
        sizes.append((occurences[i]/n)*100)#remplir le pourcentage de chaque examen


    ##affichage des statistiques à l'écran :
    print("Au total")
    print("la part d'accouchement est de",sizes[0],"%")
    print("la part de bilan de santé est de",sizes[1],"%")
    print("la part d'opération du canal carpien est de",sizes[2],"%")
    print("la part d'ORL de",sizes[3],"%")
    print("la part d'échographie est de",sizes[4],"%")
    print("la part de coloscopie est de",sizes[5],"%")
    print("la part d'IRM est de",sizes[6],"%")

    ##graphiques camembert:
    #print(sizes)
    fig,ax=plt.subplots()
    ax.pie(sizes,labels=labels,autopct='%1.1f%%')
    plt.title("Part des examens")
    plt.show()


def nb_patients_mois(annee):
    with open ("consultations.csv", "r") as f1, open ("urgences.csv", "r") as f2:
        lire1=csv.reader(f1)
        lire2=csv.reader(f2)
        n=0 #nombre de lignes
        patients={1:0,2:0,3:0,4:0,5:0,6:0,7:0,8:0,9:0,10:0,11:0,12:0} #dictionnaire avec le nombre de patients par mois
        for ligne in lire1: 
            date=ligne[12].split('/') #date entree du type jj/mm/aaaa donc dat=[jj,mm,aaaa]
            #print(date)
            if int(date[2])==annee: #correspond à l'annéee étudiée
                for i in range(1,13): #test de chaque mois
                    if (int(date[1])==i): #mois i
                        patients[i]=patients[i]+1 #incrémentation du dictionnaire

        for ligne in lire2: 
            date=ligne[12].split('/') #date entree du type jj/mm/aaaa donc dat=[jj,mm,aaaa]
            #print(date)
            if int(date[2])==annee: #correspond à l'annéee étudiée
                for i in range(1,13): #test de chaque mois
                    if (int(date[1])==i): #mois i
                        patients[i]=patients[i]+1 #incrémentation du dictionnaire

    #print(patients)
    ######afficher graphique batonnets
    mois = [i for i in range(1,13)]
    nb = [patients[i] for i in range(1,13)]
    plt.bar(mois,nb, width = 2, color = 'purple')
    plt.xlabel("Mois")
    plt.xlabel("Nombre de patients entrés")
    titre="Nombre de patients au cours de l'année"+str(annee)
    plt.title(titre)
    plt.show()




from datetime import datetime

##Nombre de jour moyen passé à l'hopital selon l'examen
def nb_jour_moyen():
  with open ("consultations.csv", "r") as f1, open ("urgences.csv", "r") as f2:
    lire1 = csv.reader(f1)
    lire2 = csv.reader(f2)
    a = [0] * 7
    nb_patient = [0] * 7

    for ligne in lire1:
      date_debut = datetime.strptime(ligne[12], "%d/%m/%Y")
      date_fin = datetime.strptime(ligne[13], "%d/%m/%Y")
      nb_jour = (date_fin - date_debut).days
      a[int(ligne[9]) - 1] += nb_jour
      nb_patient[int(ligne[9]) - 1] += 1

    for ligne in lire2:
      date_debut = datetime.strptime(ligne[12], "%d/%m/%Y")
      date_fin = datetime.strptime(ligne[13], "%d/%m/%Y")
      nb_jour = (date_fin - date_debut).days
      a[int(ligne[9]) - 1] += nb_jour
      nb_patient[int(ligne[9]) - 1] += 1

    nb_moyen = []
    for i in range(7):
      if nb_patient[i] != 0:
          nb_moyen.append(a[i] // nb_patient[i])
      else:
          nb_moyen.append(0)

    examen = ["Accouchement", "Bilan de santé", "Opération du \n canal carpien", "ORL","Echographie", "Coloscopie", "IRM"]

  plt.bar(examen, nb_moyen, color = 'green')
  plt.ylabel("Nombre de jours moyens")
  plt.title(f"Nombre de jours moyens en fonction de l'examen ")
  plt.xticks(rotation=45)
  plt.show()


##Heures d'affluence
def heures_affluence():
  with open ("consultations.csv", "r") as f1, open ("urgences.csv", "r") as f2:
    lire1 = csv.reader(f1)
    lire2 = csv.reader(f2)
    nb_heure = [0] * 24
    for ligne in lire1:
      heure = datetime.strptime(ligne[14], "%Hh%M")
      nb_heure[int(heure.hour)] += 1

    for ligne in lire2:
      heure = datetime.strptime(ligne[14], "%Hh%M")
      nb_heure[int(heure.hour)] += 1

  plt.plot(nb_heure, marker="o", linestyle="-", color = 'red')
  plt.xlabel("Heure")
  plt.ylabel("Affluence")
  plt.title("Heure d'affluence")
  plt.show()


#Part des genres à l'hopital
def genres():
  with open ("consultations.csv", "r") as f1, open ("urgences.csv", "r") as f2:
    lire1 = csv.reader(f1)
    lire2 = csv.reader(f2)
    genre = ["Homme", "Femme", "Neutre"]
    nb_genre = [0] * 3
    for ligne in lire1:
      if ligne[7] == "H":
          nb_genre[0] += 1
      elif ligne[7] == "F":
          nb_genre[1] += 1
      else:
          nb_genre[2] += 1
  fig, ax = plt.subplots()
  ax.pie(nb_genre, labels=genre, autopct='%1.1f%%')
  plt.title(f"Patients selon leur sexe")
  plt.show()



##Evolution du nombre de patients par année
def evolution():
  with open ("consultations.csv", "r") as f1, open ("urgences.csv", "r") as f2:
    lire1 = csv.reader(f1)
    lire2 = csv.reader(f2)
    annee = [i for i in range(2000, 2024)]
    an = [0] * 24
    for ligne in lire1:
      annee_debut = ligne[12][-2:]
      annee_fin = ligne[13][-2:]
      if annee_debut == annee_fin:
          an[int(annee_debut)] += 1
      else:
        for j in range(int(annee_debut), int(annee_fin)):
          an[j] += 1
    for ligne in lire2:
      annee_debut = ligne[12][-2:]
      annee_fin = ligne[13][-2:]
      if annee_debut == annee_fin:
          an[int(annee_debut)] += 1
      else:
          for j in range(int(annee_debut), int(annee_fin)):
            an[j] += 1

  plt.bar(annee, an)
  plt.xlabel("Année")
  plt.ylabel("Nombre de patient")
  plt.title(f"Nombre de patient par année")
  plt.show()

choix=0
while (choix!=-1):
  choix=int(input("Vous êtes dans la partie statistique, que voulez vous afficher (-1 pour arrêter)?\n1-La part des examens\n2-La part des genres à l'hopital\n3-Le nombre de patients par période à une année donnée\n4-L'évolution du nombre de patients par année\n5-Le nombre de jour moyen passé à l'hopital en fonction de l'examen \n6-Les heures d'affluence\n"))
  while (choix<1 or choix>6):
      choix=int(input("Choix non valide ! que voulez vous afficher ?\n1-La part des examens\n2-La part des genres à l'hopital\n3-Le nombre de patients par période à une année donnée\n4-L'évolution du nombre de patients par année\n5-Le nombre de jour moyen passé à l'hopital en fonction de l'examen \n6-Les heures d'affluence\n"))

  if (choix==1):
    choix2=int(input("\n1-les consultations \n2-les urgences\n3-total\n"))
    while (choix2<0 or choix2>3):
        choix=int(input("choix non valide !\n1-les consultations \n2-les urgences\n3-total\n"))
    if (choix2==1): #part des examens en consultation
          part_examens("consultations.csv")
    elif (choix2==2): #part des examens en consultation
          part_examens("urgences.csv")
    else:
          part_examens_total()

  elif (choix==2):  #part de genres     
      genres()
  elif (choix==3): #nb de patients par periode
      annee=int(input("entrer l'année d'étude : "))
      nb_patients_mois(annee)
  elif (choix==4): #l'évolution du nombre de patients par année
    evolution()
  elif (choix==5): #nb de jour moyen passé à l'hopital en fonction de l'examen
    nb_jour_moyen()
  elif (choix==6): #6-Les heures d'affluence
    heures_affluence()