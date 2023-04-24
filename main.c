/***
 * @Nom du fichier: main.c
 * @Rôle: gère une formation universitaire
 * @Langage_utlisé: Langage C
 * @Date_d'envoie: 11/11/2022
 * @Auteur: SANTHAKUMAR Shrijith
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <math.h>
#ifdef NAN
/* NAN is supported */
#endif
#ifdef INFINITY
/* INFINITY is supported */
#endif

//définition des constantes
enum {
    NB_SEMESTRES = 2,
    MIN_UE = 3,
    MAX_UE = 6,
    MAX_MATIERES = 10,
    MAX_EPREUVES = 5,
    MAX_ETUDIANTS = 100,
    MAX_CHAR = 30,//Nombre max de caractères pour les noms de matière, épreuve et étudiant
    MAX_NOTES = 1,
};
const float MIN_NOTE = 0.f, MAX_NOTE = 20.f;
//définition des structures de La formation les notes, les étudiants, l'epreuve, la matière, le semestres et la formation
typedef char CH30[MAX_CHAR]; // pour créer une chaine de caractères ayant 30 caractères max.
typedef unsigned int uint; // pour définir des non signés plus rapidement
typedef struct {
    float note;
} Note;

typedef struct {
    CH30 nom;
    uint nbNote;
    Note notes[MAX_NOTES];
} Etudiant;
typedef struct {
    Etudiant etudiant[MAX_ETUDIANTS];
    uint nbEtudiants;
    CH30 nom;
    float coef[MAX_UE];
} Epreuve;
typedef struct {
    CH30 nom;
    uint nbEpreuves;
    Epreuve epreuves[MAX_EPREUVES];
    float moyenne_matiere[MAX_UE];
} Matiere;
typedef struct {
    uint nbMatieres;
    Matiere matieres[MAX_MATIERES];
    float moyenne_sem[MAX_UE];
} Semestre;
typedef struct {
    uint nbUE;
    Semestre semestres[NB_SEMESTRES];
} Formation;

#define true  1


///////////////////////////////////////////////////////////////////////COMMANDE 2////////////////////////////////////////////////////////////////////////////////////////
/**
 * C2: Une fonction de type "void" nommé "formation" qui à en paramètre une variable (un pointeur) de type "Formation" et qui ne retourne rien.
 * Cette fonction  défini une fois le nombre d'UE dans la formation
 * Cette fonction affichera les messages suivantes : -si le nombre d'UE est déjà défini dans la formation
 * (donc qu'il possède déjà une valeur compris entre 3 et 6)
 * alors cela affichera: "Le nombre d'UE est deja defini"
 * -sinon, si si le nombre d'UE n'est compris enrtre 3 et 6 alors cela affichera: "Le nombre d'UE specifie est incorrect"
 * -sinon le nombre d'UE est compris entre 3 et 6 et qu'il n'a été pas été encore défini dans la formation alors cela affichera: "Le nombre d'UE est defini"
  */
void formation(Formation* f) { //C2

    if (f->nbUE != 0) {
        printf("Le nombre d'UE est deja defini\n");
    }
    else {
        scanf_s("%d", &f->nbUE);
        if (f->nbUE < MIN_UE || f->nbUE > MAX_UE) { //Vérifie que le nombre d'UE est compris entre 3 et 6
            printf("Le nombre d'UE specifie est incorrect\n");
            f->nbUE = 0;
        }
        else { printf("Le nombre d'UE est defini\n"); }
    }
}
///////////////////////////////////////////////////////////////////////COMMANDE 3////////////////////////////////////////////////////////////////////////////////////////
/**
 * C3: Une fonction de type "void" nommé "epreuve" qui à en paramètre une variable (un pointeur) de type "Formation" et qui ne retourne rien.
 * Cette fonction  rempli la structure formation (donc initialise le tableau de formation)
 * en ajoutant des matières et des epreuves lié à ces matières à la formation
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte cela affichera: "Le numero de semestre est incorrect"
 * -si le nombre d'UE n'est pas encore défini dans la formation alors cela affichera: "Le nombre d'UE n'est pas encore defini"
 * -si les coefficients demandé sont tous nuls ou que l'un des coefficient demandé est négatif alors cela affichera: "Au moins un des coefficients est incorrect"
 * -si la matière demandée avec son épreuve demandée est déjà initialisé dans la formation alors cela affichera: "Une meme epreuve existe deja"
 * -si la matière demandée est déjà initialisé dans la formation mais pas l'épreuve demandée alors cela affichera: "Epreuve ajoutee a la formation"
 * -sinon la matière demandée avec son épreuve demandée n'est pas encore dans la formation alors cela affichera:
 * "Matiere ajoutee a la formation" et "Epreuve ajoutee a la formation"
  */
void epreuves(Formation* f) { //C3
    uint semestre;
    char matiere[MAX_CHAR] , epreuve[MAX_CHAR] ;
    scanf("%u", &semestre);
    scanf("%s", &matiere);
    scanf("%s", &epreuve);
    int numero_sem = 0;
    int flag = 0;
    float coef = 0;
    int compteur = 0;
    float coefficient[MAX_UE];
    int retour = -1;
    int retour_e=-1;
    if (semestre < 1 || semestre > NB_SEMESTRES) { //Vérifie que le numéro de semestre est égal à 1 ou 2
        printf("Le numero de semestre est incorrect\n");
    }
    else {
        if (f->nbUE == 0) {
            printf("Le nombre d'UE n'est pas encore defini\n");
        }
        else {
            if (semestre == 2) {
                numero_sem = 1;
            }
            else {
                numero_sem = 0;
            }
            // Analyse la formation afin de vérifier s'il y a des matières et épreuve dans formation
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                if (strcmp(matiere, f->semestres[numero_sem].matieres[m].nom) == 0) {
                    retour = m;
                }
                for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                    if (strcmp(epreuve, f->semestres[numero_sem].matieres[m].epreuves[e].nom) == 0) {
                        retour_e=e;
                    }
                }
            }

            for (uint i = 0; i < f->nbUE; ++i) {//demande des coefficients en fonction du nombre d'ue

                scanf_s("%f", &coef);
                coefficient[i] = coef;
                if (coefficient[i] == 0) {//  vérifie si tous les coefficients sont à zero
                    compteur += 1;
                }
                else if (coef < 0) {//  vérifie si un des coefficients est inférieur à zero
                    flag = 1;
                    break;
                }
                else
                {
                    flag = 0;
                }
            }
            if (flag == 1 || compteur == f->nbUE) {
                printf("Au moins un des coefficients est incorrect.\n");
            }
                // vérifier s'il y a des matières et épreuve dans formation
                // vérifiant les différentes conditions:
                //********** si les matière et epreuve existe déjà alors on affiche un message résumant cela
                //********** si la matière existe et que l'epreuve n'existe pas alors on ajoute sont épreuve
                //********** Sinon on ajoute la matière et l'épreuve à la formation
            else {
                if (strcmp(matiere, f->semestres[numero_sem].matieres[retour].nom)==0 && strcmp(epreuve, f->semestres[numero_sem].matieres[retour].epreuves[retour_e].nom) == 0) {
                    printf("Une meme epreuve existe deja\n");
                    retour = -1;
                }
                else if (strcmp(matiere, f->semestres[numero_sem].matieres[retour].nom)==0 && strcmp(epreuve, f->semestres[numero_sem].matieres[retour].epreuves[f->semestres[numero_sem].matieres[retour].nbEpreuves].nom) == 1) {
                    // ajouter une épreuve dans une matière qui existe déjà
                    if(retour==MAX_MATIERES){
                        retour=MAX_MATIERES-1;
                    }
                    if(f->semestres[numero_sem].matieres[retour].nbEpreuves==5){
                        f->semestres[numero_sem].matieres[retour].nbEpreuves=4;
                    }
                    strcpy(f->semestres[numero_sem].matieres[retour].epreuves[f->semestres[numero_sem].matieres[retour].nbEpreuves].nom, epreuve);
                    for (int i = 0; i < f->nbUE; ++i) {
                        f->semestres[numero_sem].matieres[retour].epreuves[f->semestres[numero_sem].matieres[retour].nbEpreuves].coef[i] = coefficient[i];
                    }
                    f->semestres[numero_sem].matieres[retour].nbEpreuves += 1;
                    printf("Epreuve ajoutee a la formation\n");
                }
                else {
                    if(f->semestres[numero_sem].nbMatieres==MAX_MATIERES){
                        f->semestres[numero_sem].nbMatieres=MAX_MATIERES-1;
                    }
                    if(f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nbEpreuves==5){
                        f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nbEpreuves=4;
                    }
                    // ajouter une épreuve et une matière dans la formation
                    strcpy(f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nom, matiere);
                    strcpy(f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].epreuves[f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nbEpreuves].nom, epreuve);

                    for (int i = 0; i < f->nbUE; ++i) {
                        f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].epreuves[f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nbEpreuves].coef[i] = coefficient[i];
                    }

                    printf("Matiere ajoutee a la formation\n");
                    printf("Epreuve ajoutee a la formation\n");
                    f->semestres[numero_sem].matieres[f->semestres[numero_sem].nbMatieres].nbEpreuves += 1;
                    f->semestres[numero_sem].nbMatieres += 1;



                }
            }

        }

    }


}





///////////////////////////////////////////////////////////////////////COMMANDE 4////////////////////////////////////////////////////////////////////////////////////////
/**
 * C4: Une fonction de type "void" nommé "coefficients" qui à en paramètre une variable (un pointeur) de type "Formation" et qui ne retourne rien.
 * Cette fonction vérifie si les coefficients d'une UE sont correcte pour un semestre c'est-à-dire que que touts les coefficients d'une UE ne sont pas tous nuls
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte cela affichera: "Le numero de semestre est incorrect"
 * -si il n'y a pas d'epreuve dans le semestres alors cela affichera:"Le semestre ne contient aucune epreuve"
 * -si il les coefficients d'une UE sont tous nuls alors cela affichera:"Les coefficients d'au moins une UE de ce semestre sont tous nuls"
 * -sinon les coefficient des UE pour un semestres sont non nul alors cela affichera: "Coefficients corrects"
  */

void coefficients(const Formation* f) {//C4
    uint semestre;
    uint numero_sem = 0;
    uint flag = 0;
    int indice=0;
    scanf_s("%d", &semestre);
    float somme = 0;
    float tab[MAX_UE];

    if (semestre < 1 || semestre > NB_SEMESTRES) { //Vérifie que le numéro de semestre est égal à 1 ou 2
        printf("Le numero de semestre est incorrect\n");
    }
    else {
        if (semestre == 2) {
            numero_sem = 1;
        }
        else {
            numero_sem = 0;
        }

        if (f->semestres[numero_sem].nbMatieres == 0) {
            printf("Le semestre ne contient aucune epreuve\n");
        }
        else {
            //Analyse le tableau afin de récupérer les coefficents en fonction du nombre d'ue et les ajouter dans un tableau
            for (int i = 0; i < f->nbUE; ++i) {
                for (int j = 0; j <f->semestres[numero_sem].nbMatieres ; ++j) {
                    for (int k = 0; k < f->semestres[numero_sem].matieres[j].nbEpreuves; ++k) {
                        somme+=f->semestres[numero_sem].matieres[j].epreuves[k].coef[i];
                        tab[i]=somme;// on utlise cette variable pour savoir si la somme des coefficients d'une UE est nul




                    }

                }
                somme=0;
            }
            for (int i = 0; i < f->nbUE; ++i) {// Analyse le tableau
                if (tab[i]==0){// le flag servira à savoir si les coefficients d'une UE est correcte
                    flag=1;// 1 pour dire pas correcte
                }
            }
            if (flag==1){
                printf("Les coefficients d\'au moins une UE de ce semestre sont tous nuls\n");
            }
            else{
                printf("Coefficients corrects\n");

            }
        }
    }
}


///////////////////////////////////////////////////////////////////////COMMANDE 5////////////////////////////////////////////////////////////////////////////////////////
/**
 * C5: Une fonction de type "void" nommé "note" qui à en paramètre une variable (un pointeur) de type "Formation" et qui ne retourne rien.
 * Cette fonction initialise la formation en ajoutant des étudiants avec leur note (en fonction du semestre) dans la formation
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte cela affichera: "Le numero de semestre est incorrect"
 * -si la Matière n'existe pas dans la formation alors cela affichera: "Matiere inconnue"
 * -si l'épreuve n'existe pas dans la formation alors cela affichera: "Epreuve inconnue"
 * -sinon si il y a un étudiant dans la formation et qu'il déjà une note à cette epreuve alors cela affiichera: "Une note est deja definie pour cet etudiant"
 * -sinon si il y a un étudiant dans la formation mais qu'il n'a pas de note dans l'epreuve demandé alors
 * on lui ajoute une note et cela affichera: "Note ajoutee a l'etudiant"
 * sinon, si l'étudiant demandé n'est pas dans la formation alors on ajoutera l'étudiant avec la note demandé et cela affichera:
 * "Etudiant ajoute a la formation" et "Note ajoutee a l'etudiant"
  */
void note(Formation* f) { //C5
    int semestre;
    char matiere[MAX_CHAR], etudiant[MAX_CHAR], epreuve[MAX_CHAR];
    float note;
    int id_etu = -1;
    int id_e = -1;
    int id_m = -1;
    int flag_e = 0;
    int flag_m = 0;
    int flag_etu = 0;
    int flag_note = 0;
    int numero_sem = 0;
    //Demande des informations pour ajouter la note
    scanf_s("%d", &semestre);
    scanf_s("%s", &etudiant, MAX_CHAR);
    scanf_s("%s", &matiere, MAX_CHAR);
    scanf_s("%s", &epreuve, MAX_CHAR);
    scanf_s("%f", &note);
    if (semestre < 1 || semestre > NB_SEMESTRES) { //Vérifie que le numéro de semestre est égal à 1 ou 2
        printf("Le numero de semestre est incorrect\n");
    }
    else {
        if (note < MIN_NOTE || note > MAX_NOTE) { //Vérifie que la note est comprise entre 0 et 20
            printf("Note incorrecte\n");//TODO
        }
        else {
            if (semestre == 2) {
                numero_sem = 1;
            } else {
                numero_sem = 0;
            }
            // Analyse la formation (avec la boucle) pour savoir si il y a des étudiants, que la formation possède bien les matières et épreuves demandés
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                if (strcmp(matiere, f->semestres[numero_sem].matieres[m].nom) == 0) {
                    flag_m = 1;
                    id_m = m;
                }
                for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                    if (strcmp(epreuve, f->semestres[numero_sem].matieres[id_m].epreuves[e].nom) == 0) {
                        flag_e = 1;
                        id_e = e;
                    }
                    for (int i = 0; i < f->semestres[numero_sem].matieres[m].epreuves[e].nbEtudiants; ++i) {
                        if (strcmp(etudiant, f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[i].nom) ==0) {
                            flag_etu = 1;
                            id_etu = i;
                        }
                        for (int j = 0; j < MAX_NOTE; ++j) {
                            if (f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[i].notes[j].note != -1)
                                flag_note = 1;
                        }
                    }
                }
            }
            // vérifier s'il y a des matières et épreuve, des étudiants et ses notes dans formation en fonction du semestre
            // vérifiant les différentes conditions:
            //********** si les matière n'existe pas dans la formation on affiche un message résumant cela
            //********** si les épreuve n'existe pas dans la formation on affiche un message résumant cela
            //********** si l'étudiant existe déjà et qu'il a une note on affiche un message résumant cela
            //********** si l'étudiant existe déjà mais qu'il n'a pas de note on ajoute une note à l'étudiant
            //********** sinon on ajoute l'étudiant et sa note à la formation
            if (flag_m == 0) {
                printf("Matiere inconnue\n");
            }
            else if (flag_m == 1 && flag_e == 0) {
                printf("Epreuve inconnue\n");
            }
            else if (strcmp(etudiant, f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[id_etu].nom)==0 && f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[id_etu].notes[MAX_NOTES-1].note != -1) {
                printf("Une note est deja definie pour cet etudiant\n");
            }
            else if (strcmp(etudiant, f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[id_etu].nom)==0 && f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[id_etu].notes[MAX_NOTES-1].note == -1) {
                if(id_etu==MAX_ETUDIANTS){
                    id_etu=MAX_ETUDIANTS-1;
                }
                f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[id_etu].notes[MAX_NOTES -1].note = note;
                printf("Note ajoutee a l\'etudiant\n");

            }
            else {
                if(f->semestres[numero_sem].matieres[id_m].epreuves[id_e].nbEtudiants==MAX_ETUDIANTS){
                    f->semestres[numero_sem].matieres[id_m].epreuves[id_e].nbEtudiants=MAX_ETUDIANTS-1;
                }
                for (int fo = 0; fo < NB_SEMESTRES; ++fo) {
                    for (int m = 0; m < MAX_MATIERES; ++m) {
                        for (int e = 0; e < MAX_EPREUVES; ++e) {
                            for (int i = 0; i < MAX_ETUDIANTS; ++i) {
                                strcpy(f->semestres[fo].matieres[m].epreuves[e].etudiant[f->semestres[fo].matieres[m].epreuves[e].nbEtudiants].nom,etudiant);
                            }
                        }
                    }

                }
                f->semestres[numero_sem].matieres[id_m].epreuves[id_e].etudiant[f->semestres[numero_sem].matieres[id_m].epreuves[id_e].nbEtudiants].notes[MAX_NOTES - 1].note = note;
                for (int fo = 0; fo < NB_SEMESTRES; ++fo) {
                    for (int m = 0; m < MAX_MATIERES; ++m) {
                        for (int e = 0; e < MAX_EPREUVES; ++e) {
                            f->semestres[fo].matieres[m].epreuves[e].nbEtudiants+=1;
                        }
                    }
                }
                printf("Etudiant ajoute a la formation\n");
                printf("Note ajoutee a l\'etudiant\n");


            }
        }
    }
}
///////////////////////////////////////////////////////////////////////COMMANDE 6////////////////////////////////////////////////////////////////////////////////////////
/**
 * C6: Une fonction de type "void" nommé "notes" qui à en paramètre une variable (un pointeur) de type const et de type "Formation" et qui ne retourne rien.
 * Cette fonction vérifie si l'étudiant à une note dans la formation pour le semestre demandé
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte cela affichera: "Le numero de semestre est incorrect"
 * -si l'étudiant n'est dans la formation : "Etudiant inconnu"
 * -si l'étudiant est dans la formation mais qu'il n'a pas de note alors cela affichera: "Il manque au moins une note pour cet etudiant"
 * -si l'étudiant est dans la formation "Notes correctes"
  */
void notes(const Formation* f) { //C6
    int semestre;
    char etudiant[MAX_CHAR];
    int numero_sem=0;
    int flag_etu =0;
    int flag_note=0;
    int id_etu=0;
    scanf_s("%d", &semestre);
    scanf_s("%s", &etudiant, MAX_CHAR);
    if (semestre < 1 || semestre > NB_SEMESTRES) { //Vérifie que le numéro de semestre est égal à 1 ou 2
        printf("Le numero de semestre est incorrect\n");
    }
    else {
        if (semestre == 1) {
            numero_sem = 0;
        } else {
            numero_sem = 1;
        }
        // Analyse la formation (avec la boucle) pour savoir si il y a l'étudiant demandé et qu'il a une notes à la formation
        for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
            //printf("%s\n",f->semestres[numero_sem].matieres[m].nom);
            for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                //printf("%s\n",f->semestres[numero_sem].matieres[m].epreuves[e].nom);
                for (int i = 0; i < f->semestres[numero_sem].matieres[m].epreuves[e].nbEtudiants; ++i) {
                    if (strcmp(etudiant, f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[i].nom) ==0) {
                        flag_etu = 1;// indicateur permettant de savoir si il y a l'étudiant dans la formation; 1 pour dire l'étudiant ne l'est pas
                        id_etu=i;
                    }
                    for (int j = 0; j < MAX_NOTES; ++j) {
                        if (f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[i].notes[j].note == -1)// indicateur permettant de savoir si il y a l'étudiant à une note
                            // ; 1 pour dire d'étudiant n'a pas de note
                            flag_note = 1;
                    }
                }
            }
        }

        if(flag_etu==0){
            printf("Etudiant inconnu\n");
        }
        else if (flag_note==1){
            printf("Il manque au moins une note pour cet etudiant\n");
        }
        else{
            printf("Notes correctes\n");
        }
    }
}
///////////////////////////////////////////////////////////////////////COMMANDE 7////////////////////////////////////////////////////////////////////////////////////////
/**
 * C7: Une fonction de type "void" nommé "releves" qui à en paramètre une variable (un pointeur) de type const et de type "Formation" et qui ne retourne rien.
 * Cette fonction affiche le relevé de note de l'étudiant
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte (n'est pas compris entre 1 et 2) cela affichera:
 * "Le numero de semestre est incorrect"
 * -si l'étudiant n'est dans la formation : "Etudiant inconnu"
 * -si l'étudiant est dans la formation mais qu'il n'a pas de note alors cela affichera: "Il manque au moins une note pour cet etudiant"
 * -si il les coefficients d'une UE sont tous nuls alors cela affichera:"Les coefficients d'au moins une UE de ce semestre sont tous nuls"
 * sinon elle affiche le relever de note de l'étudiant
  */
void releve( Formation* f) {//C7

    int semestre;
    char etudiant[MAX_CHAR];
    int numero_sem=0;
    int flag_etu =0;
    int flag_note=0;
    int id_etu=0;
    float moy_matiere[MAX_UE];
    float moyennes[MAX_UE];
    float somme=0;
    int indice=0;
    int flag=0;
    int tab1[MAX_MATIERES];
    float tab[MAX_UE];
    int max=0;
    scanf_s("%d", &semestre);
    scanf_s("%s", &etudiant, MAX_CHAR);
    if (semestre < 1 || semestre > NB_SEMESTRES) { //Vérifie que le numéro de semestre est égal à 1 ou 2
        printf("Le numero de semestre est incorrect\n");
    }
    else {
        if (semestre == 1) {
            numero_sem = 0;
        } else {
            numero_sem = 1;
        }

        // Même Analyse qu'avec la C4 et la C6 pour les notes, l'étudiant, et les coefficients
        for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                for (int i = 0; i < f->semestres[numero_sem].matieres[m].epreuves[e].nbEtudiants; ++i) {
                    if (strcmp(etudiant, f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[i].nom) ==0) {
                        flag_etu = 1;
                        id_etu=i;
                    }
                    for (int j = 0; j < MAX_NOTES; ++j) {
                        if (f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[id_etu].notes[j].note == -1)
                            flag_note = 1;
                    }
                }
            }
        }
        for (int i = 0; i < f->nbUE; ++i) {
            for (int j = 0; j <f->semestres[numero_sem].nbMatieres ; ++j) {
                for (int k = 0; k < f->semestres[numero_sem].matieres[j].nbEpreuves; ++k) {
                    somme+=f->semestres[numero_sem].matieres[j].epreuves[k].coef[i];
                    indice=i;
                    tab[indice]=somme;

                }

            }
            somme=0;
        }
        for (int i = 0; i < f->nbUE; ++i) {
            //printf(" %f ",tab[i]);
            if (tab[i]==0.){
                flag=1;
            }

        }

        if(flag_etu==0){
            printf("Etudiant inconnu\n");

        }
        else if (flag_note == 1){
            printf("Il manque au moins une note pour cet etudiant\n");

        }
        else if (flag==1){
            printf("Les coefficients de ce semestre sont incorrects\n");
        }
        else{
            //Calcul de la moyenne des matière et du semestre
            float somme_c = 0;
            float somme_n = 0;
            float coef[MAX_MATIERES][MAX_UE];
            float notes[MAX_MATIERES][MAX_EPREUVES];
            int id_etu = 0;
            float coef_note[MAX_MATIERES][MAX_EPREUVES][MAX_UE];
            float moyennes = 0;
            float addition[MAX_MATIERES][MAX_UE];
            float notes_sem[MAX_UE];
            float somme_coef=0;
            float tab_c[MAX_UE];
            float somme_sem=0;
            // somme des coefficients en fonction de la matière
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                for (int c = 0; c < f->nbUE; ++c) {
                    for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                        somme_c += f->semestres[numero_sem].matieres[m].epreuves[e].coef[c];
                        coef[m][c] = somme_c;
                    }
                    somme_c = 0;
                }
            }
            // récupére les notes de l'étudiant
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                    for (int i = 0; i < f->semestres[numero_sem].matieres[m].epreuves[e].nbEtudiants; ++i) {
                        if (strcmp(etudiant, f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[i].nom) == 0) {
                            id_etu = i;
                            notes[m][e]=f->semestres[numero_sem].matieres[m].epreuves[e].etudiant[id_etu].notes[0].note;
                        }
                    }
                }
            }
           // multiplie chaque coeffcients par la note de l'étudiant
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                    for (int c = 0; c < f->nbUE; ++c) {;
                        coef_note[m][e][c]=f->semestres[numero_sem].matieres[m].epreuves[e].coef[c]*notes[m][e];


                    }

                }

            }
            // additionne chaque note multiplie par le coefficients en fonction de la matière
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                for (int c = 0; c < f->nbUE; ++c) {;
                    for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {

                        somme_n+=coef_note[m][e][c];
                        addition[m][c]=somme_n;
                    }
                    somme_n=0;
                }
            }
            // additionne chaque note multiplie par le coefficients en fonction du semestre
            for (int c = 0; c < f->nbUE; ++c) { ;
                for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                    for (int e = 0; e < f->semestres[numero_sem].matieres[m].nbEpreuves; ++e) {
                        somme_sem+= coef_note[m][e][c];
                        notes_sem[c] = somme_sem;
                        ;
                    }
                }
                somme_sem = 0;
            }
            // somme des coefficients en fonction du semestre
            for (int i = 0; i < f->nbUE; ++i) {
                for (int j = 0; j <f->semestres[numero_sem].nbMatieres ; ++j) {
                    for (int k = 0; k < f->semestres[numero_sem].matieres[j].nbEpreuves; ++k) {
                        somme_coef+=f->semestres[numero_sem].matieres[j].epreuves[k].coef[i];
                        indice=i;
                        tab_c[indice]=somme_coef;
                    }

                }
                somme_coef=0;
            }
            // Calcul de la moyenne des matières
            for (int i = 0; i < f->semestres[numero_sem].nbMatieres; ++i) {
                for (int j = 0; j < f->nbUE; ++j) {
                    if(coef[i][j]==0){
                        moyennes=-2;
                        f->semestres[numero_sem].matieres[i].moyenne_matiere[j] = moyennes;
                    }
                    else{
                        moyennes = addition[i][j] / coef[i][j];
                        f->semestres[numero_sem].matieres[i].moyenne_matiere[j] = moyennes;
                    }
                }
                moyennes = 0;
                //printf("\n");

            }
            // Calcul de la moyenne du semestre
            for (int i = 0; i <f->nbUE ; ++i) {
                f->semestres[numero_sem].moyenne_sem[i]=notes_sem[i]/tab_c[i];
            }

/////////////////////////////////////////////// AFFICHAGE DU RELEVER/////////////////////////////////////////////////////////////////////////////////////////////////////////
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                tab1[m]=strlen(f->semestres[numero_sem].matieres[m].nom);
            }
            for (int i = 0; i < f->semestres[numero_sem].nbMatieres; ++i) {
                if(max<tab1[i]){
                    max=tab1[i];
                }
            }

            for (int i = 0; i < max+1; ++i) {
                printf(" ");
            }
            if(f->nbUE==3){
                for (int i = 0; i < max+1; ++i) {
                    printf(" ");
                }
                printf("UE1  UE2  UE3\n");
            }
            else if(f->nbUE==4){
                printf("UE1  UE2  UE3  UE4\n");
            }
            else if(f->nbUE==5){
                printf("UE1  UE2  UE3  UE4  UE5\n");
            }
            else if(f->nbUE==6){
                printf("UE1  UE2  UE3  UE4  UE5  UE6\n");
            }
            for (int m = 0; m < f->semestres[numero_sem].nbMatieres; ++m) {
                printf("%s ",f->semestres[numero_sem].matieres[m].nom);
                for (int i = 0; i <max-strlen(f->semestres[numero_sem].matieres[m].nom) ; ++i) {
                    printf(" ");
                }
                for (int i = 0; i < f->nbUE; ++i) {
                    if(f->semestres[numero_sem].matieres[m].moyenne_matiere[i]==-2){
                        printf("ND ");
                    }
                    else{
                        printf("%.1f ", floorf(f->semestres[numero_sem].matieres[m].moyenne_matiere[i]*10.f)/10.f);
                    }

                }
                printf("\n");

            }
            printf("--\n");
            printf("Moyennes");
            for (int i = 0; i < max+1- strlen("Moyennes"); ++i) {
                printf(" ");

            }
            for (int i = 0; i < f->nbUE; ++i) {
                printf("%.1f ", floorf(f->semestres[numero_sem].moyenne_sem[i]*10.f)/10.f);
            }
            printf("\n");

        }
    }
}
///////////////////////////////////////////////////////////////////////COMMANDE 8////////////////////////////////////////////////////////////////////////////////////////
/**
 * C8: Une fonction de type "void" nommé "releves" qui à en paramètre une variable (un pointeur) de type const et de type "Formation" et qui ne retourne rien.
 * Cette fonction affiche le releve de tout le semestre de l'étudiant avec la decision du jury
 * Cette fonction affichera les messages suivantes : -si le numero de semestre est incorrecte (n'est pas compris entre 1 et 2) cela affichera:
 * "Le numero de semestre est incorrect"
 * -si l'étudiant n'est dans la formation : "Etudiant inconnu"
 * -si l'étudiant est dans la formation mais qu'il n'a pas de note alors cela affichera: "Il manque au moins une note pour cet etudiant"
 * -si il les coefficients d'une UE sont tous nuls alors cela affichera:"Les coefficients d'au moins une UE de ce semestre sont tous nuls"
 * sinon elle affiche le releve de tout le semestre de l'étudiant avec la decision du jury
  */
void decision(Formation* f) {//C8
    char etudiant[MAX_CHAR];
    int numero_sem = 0;
    int flag_etu = 0;
    int flag_note = 0;
    int id_etu = 0;
    float moyennes[MAX_UE];
    float somme = 0;
    int indice = 0;
    int flag = 0;
    int tab1[MAX_MATIERES];
    float tab[MAX_UE];
    int max = 0;
    scanf_s("%s", &etudiant, MAX_CHAR);
    // Même Analyse qu'avec la C4 et la C6 pour les notes, l'étudiant, et les coefficients
    for (int s = 0; s < NB_SEMESTRES; ++s) {
        for (int m = 0; m < f->semestres[s].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[s].matieres[m].nbEpreuves; ++e) {
                for (int i = 0; i < f->semestres[s].matieres[m].epreuves[e].nbEtudiants; ++i) {
                    if (strcmp(etudiant, f->semestres[s].matieres[m].epreuves[e].etudiant[i].nom) ==
                        0) {
                        flag_etu = 1;
                        id_etu = i;
                    }
                    for (int j = 0; j < MAX_NOTES; ++j) {
                        if (f->semestres[s].matieres[m].epreuves[e].etudiant[id_etu].notes[j].note == -1)
                            flag_note = 1;
                    }
                }
            }
        }
    }
    for (int s = 0; s < NB_SEMESTRES; ++s) {
        for (int i = 0; i < f->nbUE; ++i) {
            for (int j = 0; j < f->semestres[s].nbMatieres; ++j) {
                for (int k = 0; k < f->semestres[s].matieres[j].nbEpreuves; ++k) {
                    somme += f->semestres[s].matieres[j].epreuves[k].coef[i];
                    indice = i;
                    tab[indice] = somme;
                }
            }
            somme = 0;
        }
    }
    for (int i = 0; i < f->nbUE; ++i) {
        if (tab[i] == 0.) {
            flag = 1;
        }

    }

    if (flag_etu == 0) {
        printf("Etudiant inconnu\n");

    } else if (flag_note == 1) {
        printf("Il manque au moins une note pour cet etudiant\n");

    } else if (flag == 1) {
        printf("Les coefficients de ce semestre sont incorrects\n");
    } else {
        float somme_c = 0;
        float somme_n = 0;
        float coef[MAX_MATIERES][MAX_UE];
        float coefs[MAX_UE];
        float notes[NB_SEMESTRES][MAX_MATIERES][MAX_EPREUVES];
        int id_etu = 0;
        float matiere[MAX_MATIERES][MAX_UE];
        float coef_note[NB_SEMESTRES][MAX_MATIERES][MAX_EPREUVES][MAX_UE];
        float moyennes = 0;
        float sem = 0;
        float semestres[MAX_UE];
        float addition[MAX_MATIERES][MAX_UE];
        float notes_sem[MAX_UE];
        float somme_coef = 0;
        float tab_c[MAX_UE];
        float somme_sem = 0;

        float semesT[MAX_UE];
        ////////////////////////1er SEMESTRE//////////////////////
        float coef_note1[MAX_MATIERES][MAX_EPREUVES][MAX_UE];
        float note1[MAX_MATIERES][MAX_EPREUVES];
        float somme_coef1 = 0;
        float semestres1[MAX_UE];
        float somme_sem1 = 0;
        float notes_sem1[MAX_UE];
        float tab_c1[MAX_UE];
        ///////////////////2eme SEMESTRE/////////////////////////
        float coef_note2[MAX_MATIERES][MAX_EPREUVES][MAX_UE];
        float note2[MAX_MATIERES][MAX_EPREUVES];
        float somme_coef2 = 0;
        float semestres2[MAX_UE];
        float somme_sem2 = 0;
        float notes_sem2[MAX_UE];
        float tab_c2[MAX_UE];
////////////////1er SEMESTRE CALCUL DE LA MOYENNE///////////////////////////////////////////////////////////////////////////////////////////
        for (int m = 0; m < f->semestres[0].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[0].matieres[m].nbEpreuves; ++e) {
                for (int i = 0; i < f->semestres[0].matieres[m].epreuves[e].nbEtudiants; ++i) {
                    if (strcmp(etudiant, f->semestres[0].matieres[m].epreuves[e].etudiant[i].nom) == 0) {
                        id_etu = i;
                        for (int j = 0; j < MAX_NOTES; ++j) {
                            note1[m][e]=f->semestres[0].matieres[m].epreuves[e].etudiant[id_etu].notes[j].note;
                        }
                    }
                }
            }
        }
        for (int m = 0; m < f->semestres[0].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[0].matieres[m].nbEpreuves; ++e) {
                for (int c = 0; c < f->nbUE; ++c) {;
                    coef_note1[m][e][c]=f->semestres[0].matieres[m].epreuves[e].coef[c]*note1[m][e];
                }
            }

        }
        for (int c = 0; c < f->nbUE; ++c) { ;
            for (int m = 0; m < f->semestres[0].nbMatieres; ++m) {
                for (int e = 0; e < f->semestres[0].matieres[m].nbEpreuves; ++e) {
                    somme_sem1+= coef_note1[m][e][c];
                    //printf(" %f ", coef_note[e][c]);
                    notes_sem1[c] = somme_sem1;
                    ;
                }
            }
            somme_sem1 = 0;
        }
        for (int i = 0; i < f->nbUE; ++i) {
            for (int j = 0; j <f->semestres[0].nbMatieres ; ++j) {
                for (int k = 0; k < f->semestres[0].matieres[j].nbEpreuves; ++k) {
                    somme_coef1+=f->semestres[0].matieres[j].epreuves[k].coef[i];
                    indice=i;
                    tab_c1[indice]=somme_coef1;
                }
            }
            somme_coef1=0;
        }
        for (int i = 0; i <f->nbUE ; ++i) {
            semestres1[i]=notes_sem1[i]/tab_c1[i];
        }
        ///////////////////////////////////////////////////////////////2ème SEMESTRE CALCUL DE LA MOYENNE ///////////////////////////////////////////////////////////////////////////////////////////
        for (int m = 0; m < f->semestres[1].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[1].matieres[m].nbEpreuves; ++e) {
                for (int i = 0; i < f->semestres[1].matieres[m].epreuves[e].nbEtudiants; ++i) {
                    if (strcmp(etudiant, f->semestres[1].matieres[m].epreuves[e].etudiant[i].nom) == 0) {
                        id_etu = i;
                        for (int j = 0; j < MAX_NOTES; ++j) {
                            note2[m][e]=f->semestres[1].matieres[m].epreuves[e].etudiant[id_etu].notes[j].note;
                        }
                    }
                }
            }
        }
        for (int m = 0; m < f->semestres[1].nbMatieres; ++m) {
            for (int e = 0; e < f->semestres[1].matieres[m].nbEpreuves; ++e) {
                for (int c = 0; c < f->nbUE; ++c) {;
                    coef_note2[m][e][c]=f->semestres[1].matieres[m].epreuves[e].coef[c]*note2[m][e];
                }
            }

        }
        for (int c = 0; c < f->nbUE; ++c) { ;
            for (int m = 0; m < f->semestres[1].nbMatieres; ++m) {
                for (int e = 0; e < f->semestres[1].matieres[m].nbEpreuves; ++e) {
                    somme_sem2+= coef_note2[m][e][c];
                    //printf(" %f ", coef_note[e][c]);
                    notes_sem2[c] = somme_sem2;
                    ;
                }
            }
            somme_sem2= 0;
        }
        for (int i = 0; i < f->nbUE; ++i) { //Si une UE a un coef différent de 0, alors on active le flag
            for (int j = 0; j <f->semestres[1].nbMatieres ; ++j) {
                for (int k = 0; k < f->semestres[1].matieres[j].nbEpreuves; ++k) {
                    somme_coef2+=f->semestres[1].matieres[j].epreuves[k].coef[i];
                    tab_c2[i]=somme_coef2;
                }
            }
            somme_coef2=0;
        }
        for (int i = 0; i <f->nbUE ; ++i) {
            semestres2[i]=notes_sem2[i]/tab_c2[i];
        }
///////////////////////////SEMESTRE TOTAL CALCUL DE LA MOYENNE/////////////////////////////////////////////////////
        int compter=0;
        for (int i = 0; i <f->nbUE ; ++i) {
            semesT[i]=(semestres1[i]+semestres2[i])/NB_SEMESTRES;
            // printf(" %f ",semesT[i]);
        }
////////////////////////AFFICHAGE DE LA MOYENNE ET DE LA DECISION////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < strlen("Moyenne annuelles") ; ++i) {
            printf(" ");
        }
        if(f->nbUE==3){
            printf("UE1  UE2  UE3\n");
        }
        else if(f->nbUE==4){
            printf("UE1  UE2  UE3  UE4\n");
        }
        else if(f->nbUE==5){
            printf("UE1  UE2  UE3  UE4  UE5\n");
        }
        else if(f->nbUE==6){
            printf("UE1  UE2  UE3  UE4  UE5  UE6\n");
        }
        printf("S1");
        for (int es = 0; es < strlen("Moyennes annuelles") - strlen("S1"); ++es) {
            printf(" ");
        }
        for (int j = 0; j < f->nbUE; ++j) {
            printf("%.1f ", floorf(semestres1[j]*10.f)/10.f);
        }
        printf("\n");
        printf("S2");
        for (int es = 0; es < strlen("Moyennes annuelles") - strlen("S2"); ++es) {
            printf(" ");
        }
        for (int j = 0; j < f->nbUE; ++j) {
            printf("%.1f ", floorf(semestres2[j]*10.f)/10.f);
        }
        printf("\n");





        printf("--");
        printf("\n");
        printf("Moyennes annuelles " );
        for (int i = 0; i < f->nbUE; ++i) {
            printf("%.1f ", floorf(semesT[i]*10.f)/10.f);
        }
        int compter2=0;
        printf("\n");
        printf("Acquisition");
        for (int es = 0; es < strlen("Moyennes annuelles") - strlen("Acquisition"); ++es) {
            printf(" ");
        }
        int test_virgule =0;
        for (int i = 0; i <f->nbUE ; ++i) {
            if(semesT[i]>=10){
                if(test_virgule){
                    printf(", ");
                }
                else{
                    test_virgule=1;
                }
                printf("UE%d",i+1);
                compter+=1;
            }
            else{
                compter2+=1;
            }

        }
        printf("\n");
        printf("Devenir");
        for (int es = 0; es < strlen("Moyennes annuelles") - strlen("Devenir"); ++es) {
            printf(" ");
        }
        if(compter<=compter2 && compter2<f->nbUE){
            printf("Redoublement\n");
            //printf("\n");
        }
        else{
            printf("Passage\n");
        }
    }
}
int main() {
    Formation f;
    f.nbUE = 0; //Initialisation du nombre n'UE
    char cde[31] = ""; // Commande à entrer
    /**
     * initialise le nombre de matière à 0
     * initialise le nombre d' épreuve à 0
     * initialise le nombre d'étudiant à 0
     * initialise la note à -1 (indicateur pour dire qu'il n'y a pas de note)
     */
    for (int i = 0; i < NB_SEMESTRES; ++i) {
        f.semestres[i].nbMatieres = 0;
        for (int e = 0; e < MAX_MATIERES; ++e) {
            f.semestres[i].matieres[e].nbEpreuves = 0;
            for (int j = 0; j < MAX_EPREUVES ; ++j) {
                f.semestres[i].matieres[e].epreuves[j].nbEtudiants=0;
                for (int et = 0; et < MAX_ETUDIANTS; ++et) {

                    for (int k = 0; k < MAX_NOTES; ++k) {
                        f.semestres[i].matieres[e].epreuves[j].etudiant[et].notes[k].note=-1;
                    }

                }

            }
        }
    }
    /**
     * quand l'utilisateur demande la commande "formation" la fonction "formation" est appelée
     * quand l'utilisateur demande la commande "epreuve" la fonction "epreuve" est appelée
     * quand l'utilisateur demande la commande "coefficient" la fonction "coefficient" est appelée
     * quand l'utilisateur demande la commande "note" la fonction "note" est appelée
     * quand l'utilisateur demande la commande "notes" la fonction "notes" est appelée
     * quand l'utilisateur demande la commande " releve" la fonction "releve" est appelée
     * quand l'utilisateur demande la commande "decision" la fonction "decision" est appelée
     * quand l'utilisateur demande la commande "exit" alors le programme s'arrête
     */
    do {
        scanf_s("%s", &cde, 31);
        if (strcmp(cde, "formation") == 0) // C2
        {
            formation(&f);
        }
        else if (strcmp(cde, "epreuve") == 0) // C3
        {
            epreuves(&f);

        }

        else if (strcmp(cde, "coefficients") == 0) // C4
        {
            coefficients(&f);
        }
        else if (strcmp(cde, "note") == 0) // C5
        {
            note(&f);
        }
        else if (strcmp(cde, "notes") == 0) // C6
        {
            notes(&f);
        }
        else if (strcmp(cde, "releve") == 0) // C7
        {
            releve(&f);
        }
        else if (strcmp(cde, "decision") == 0) // C8
        {
            decision(&f);
        }
    } while (strcmp(cde, "exit") != 0); // C1
}



