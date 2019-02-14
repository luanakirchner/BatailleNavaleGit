
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#define DESSOUS 72
#define HAUT 80
#define ENTER 13
#define ESC 27
#define TAILLE_PSEUDO 50
#define MAX 200

int jouer_tableau_facille(char ligne, char colonne);


/** \brief positionnement des éléments dans la console
 *
 * \param x int ligne
 * \param y int colonne
 * \return void
 *
 */
void gotoxy( int x, int y ){
COORD coord;                //Fonction prix d'internet gotoxy(ligne,colonne)
coord.X = (short)x;
coord.Y = (short)y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/** \brief : Affiche le menu principal
 *
 * \return int : Renvoie l'ption sélectionnée
 *
 */
int MENU_PRINCIPAL(){

int position = 8, touche;
int choix=0;


do{

system("cls");

gotoxy(23,3);printf("-----------------------------");
gotoxy(35,4);printf("MENU");
gotoxy(23,5);printf("-----------------------------");
gotoxy(23,8);printf("S'authentifier");
gotoxy(23,10);printf("Jouer ");
gotoxy(23,12);printf("Avoir de l'aide ");
gotoxy(23,14);printf("Afficher la liste des scores ");
gotoxy(23,16);printf("Sortir ");


gotoxy(18,position);printf("-->");
touche=getch();
if(touche == HAUT) // touche pour aller en bas
{
position=position+2;

if(position==18)
{
position=8;
}

}
if (touche == DESSOUS) //touche pour aller en haut
{
position=position-2;
if(position==6)
{
position=16;
}

}

}while(touche!= ENTER);

switch (position){

case 8: loge_lesfaits("Le joueur a selectionne","Authentifier");
        choix = 1;
        break;
case 10: loge_lesfaits("Le joueur a selectionne","Jouer");
        choix = 2;
        break;
case 12:loge_lesfaits("Le joueur a selectionne","Avoir de l'aide");
        choix = 3;
        break;
case 14:loge_lesfaits("Le joueur a selectionne","Afficher la liste des scores");
        choix = 4;
        break;
case 16: loge_lesfaits("Le joueur a selectionne","Sortir");
        choix= 5;
        break;

 }
return choix;
}

/** \brief Affiche les options de grille
 *
 * \return int : Renvoie l'option sélectionnée
 *
 */
int Choix_grille(){

int position = 8, touche;
int choixgrille=0;


do{

system("cls");

gotoxy(23,3);printf("-----------------------------");
gotoxy(28,4);printf("Choisir un grille");
gotoxy(23,5);printf("-----------------------------");
gotoxy(23,8);printf("Facile");
gotoxy(23,10);printf("Normal");
gotoxy(23,12);printf("Difficile");
gotoxy(23,14);printf("Aleatoire");
gotoxy(23,16);printf("Returner au menu");


gotoxy(18,position);printf("-->");
touche=getch();
if(touche == HAUT) // touche pour aller en bas
{
position=position+2;

if(position==18)
{
position=8;
}

}
if (touche == DESSOUS) //touche pour aller en haut
{
position=position-2;
if(position==6)
{
position=16;
}

}

}while(touche!= ENTER);

switch (position){

case 8: loge_lesfaits("Le joueur a selectionne:","Gille facile");
        choixgrille = 1;
        break;
case 10:loge_lesfaits("Le joueur a selectionne:","Gille Normal");
        choixgrille = 2;
        break;
case 12:loge_lesfaits("Le joueur a selectionne:","Diffcile");
        choixgrille = 3;
        break;
case 14:loge_lesfaits("Le joueur a selectionne:","Grille Aleatoire","");
        choixgrille = 4;
        break;
case 16:loge_lesfaits("Le joueur a selectionne:","Returne au menu","");
        choixgrille = 5;
        break;
 }
return choixgrille;
}

/** \brief Loger les faits dans un fichier .txt
 *
 * \param phrase[MAX] char
 * \param loge[MAX] char
 * \return void
 *
 */
void loge_lesfaits(char phrase[MAX], char loge[MAX]){

    FILE* fichier = NULL;
    time_t times;
    struct tm* current_time;

    fichier = fopen("logs.txt", "r+");
    times = time(NULL);
    current_time = localtime(&times);


    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END);
        //ecrire la date, le temp et les informations dans le fichier
        fprintf(fichier,"[%02d/%02d/%d %02d:%02d:%02d] %s %s\n",current_time->tm_mday,current_time->tm_mon+1,current_time->tm_year+1900,current_time->tm_hour,current_time->tm_min,current_time->tm_sec,phrase,loge);
        fclose(fichier);
    }else{
        printf("impossible de lire le fichier !");
    }
}

/** \brief Enregistre les pseudos et les scores dans un meme fichier .txt
 *
 * \param pseudos[100] char sauvagarder le pseudo
 * \param scores int sauvagarder les scores
 * \return void
 *
 */
void sauvegarde_fichier(char pseudos[30], int scores, char mode[MAX]){

    FILE* fichier = NULL;

    fichier=fopen("Liste Pseudo.txt", "a");

    if(fichier != NULL){

    fprintf(fichier, "%20s          %4i         %15s \n", pseudos, scores, mode);
    fclose(fichier);
    }
}

/** \brief Lir le fichier qui contient les pseudos et les scores
 *
 * \return void
 *
 */
void Lir_fichier(){

    int pseudos=fopen("Liste Pseudo.txt", "r");

    FILE* fichier = NULL;

     fichier=fopen("Liste Pseudo.txt", "r");

     if(fichier== NULL)
         printf("Fichier pas trouve\n");
     else
         do {
            pseudos=fgetc(fichier);
            if(pseudos!=EOF)
                printf("%c", pseudos);
         }while(pseudos!=EOF);


     fclose(fichier);
}

/** \brief Remplir la grille facille avec un fichier qui contient la position des bateaux .txt
 *
 * \param bateaux_facille[12][12] char stoquer la positions de bateaux
 * \return void
 *
 */
void Remplir_grille1_txt(char bateaux_facille[12][12]){
     FILE *fic = fopen("Grille1.txt", "r"); //Fichier à chercher, bateaux pour la grille facille
     int stock;
     int ligne, colonne;
     int position=0;

        if(fic==NULL){
            system("cls");
            printf("Impossible d'ouvrir le fichier");
            Sleep(2000);
        }

        else{
             for(ligne=0; ligne<12; ligne++){
                for(colonne=0; colonne<12; colonne++){
                        stock=0;
                        position=position+1;
                        fscanf(fic, "%i", &stock);
                        bateaux_facille[ligne][colonne]=stock; //Stoquer la valeur trouve dans le tableau
                        fseek(fic,position,SEEK_SET); //La position dans le fichier
                        position=position+1; //Modifier la position du courser dans le fichier
                }
            }
             fclose(fic);
        }
}

/** \brief Remplir la grille difficile avec un fichier qui contient la position des bateaux .txt
 *
 * \param tableau_difficille[][12] char stoquer la positions de bateaux
 * \return void
 *
 */
void Remplir_grille3_txt(char tableau_difficille[][12]){

     FILE *fic = fopen("Grille3.txt", "r"); //Fichier à chercher, bateaux pour la grille difficile
     int stock;
     int ligne, colonne;
     int position=0;


        if(fic==NULL){ //Fichier pas trouve
            system("cls");
            printf("Impossible d'ouvrir le fichier");
            Sleep(2000);
        }

        else{
             for(ligne=0; ligne<12; ligne++){
                for(colonne=0; colonne<12; colonne++){
                        stock=0;
                        position=position+1;
                        fscanf(fic, "%i", &stock);
                        tableau_difficille[ligne][colonne]=stock;
                        fseek(fic,position,SEEK_SET);
                        position=position+1;
                }
            }
             fclose(fic);
        }
}

/** \brief Transformer la lettre de la ligne en nombre entier
 *
 * \param x char lettre entree par le joueur
 * \return int un nombre entier
 *
 */
int optiondeligne(char x){

      int ligne;
      switch(x){
     case 'a':
      case 'A': ligne=1;
                break;
      case 'b':
      case 'B': ligne=2;
                break;
      case 'c':
      case 'C': ligne=3;
                break;
      case 'd':
      case 'D': ligne=4;
                break;
      case 'e':
      case 'E': ligne=5;
                break;
      case 'f':
      case 'F': ligne=6;
                break;
      case 'g':
      case 'G': ligne=7;
                break;
      case 'h':
      case 'H': ligne=8;
                break;
      case 'i':
      case 'I': ligne=9;
                break;
      case 'j':
      case 'J': ligne=10;
                break;
      case 'm':
      case 'M': ligne=11;
                break;

      case 'z':
      case 'Z':ligne=12;
                break;
    default: ligne=0;
                break;


  }

return ligne;
}

/** \brief Afficher aide
 *
 * \return void
 *
 */
void affiche_aide(){

int explication=0;
int whexplication;

gotoxy(5,1);printf("AIDE");
gotoxy(5,2);printf("----");

gotoxy(3,6);printf("Pour gagne le jeu vous devez detruit tous les bateux existante");
gotoxy(3,7);printf("pour ca, vous devez choisir une ligne de la colonne (numero entier)");
gotoxy(3,8);printf("tapez sur enter, choisir une lettre de la ligne et tapez enter");
gotoxy(3,9);printf("le jeu va vous afficher une message si vous avez touche ou detruit");
gotoxy(3,10);printf("un bateux.");
gotoxy(3,12);printf("Quant le jeu vous demande un lettre de la ligne vous pouvez retourne au menu");
gotoxy(3,13);printf("en tapant sur M");
gotoxy(3,14);printf("Vous pouvez aussi afficher de l'aide en tapant sur Z");

whexplication=1;
while(whexplication){
gotoxy(3,17);printf("Vous voulez encore une explication anime? [1 (Oui) ] / [2 (Non) ]");
gotoxy(3,18);scanf("%d", &explication);

    if(explication==1){
    afficher_aide_detaille();
    }
    if(explication==2);{
        whexplication=0;
    }
    if ((explication!=1)&&(explication!=2)){
       gotoxy(3,19);printf("Tapez 1 ou 2");
       whexplication=1;
    }
}

gotoxy(3,25);system("pause");


}

/** \brief Afficher aide plus detaille, animation
 *
 * \return void
 *
 */
void afficher_aide_detaille(){

  system("cls");
  int y, x;
  char ligne, colonne;
  char tableautext[12][12];
  int numeroporteavion=1, numerocroisseur=1, numerocontretorpilleur=2, numerotropilleur=2, numerosousmarin=3;

   gotoxy(1,1);printf("Voici votre tableau a 0 : ");

    y=4;
    for(ligne=1; ligne<11; ligne++){
            y=y+1;
            x=5;
            for(colonne=1; colonne<12; colonne++){
                tableautext[ligne][colonne] = '.';
                gotoxy(x,y);printf(" %c  ", tableautext[ligne][colonne]);
                x=x+4;

            }
}
detail_tableau();

gotoxy(2,18);printf("Le numero de la colonne:    <-- Vous devez entrer un numero entier");
Sleep(2000);
gotoxy(2,18);printf("Le numero de la colonne: 11 <-- Vous devez entrer un numero entier");
Sleep(2000);
gotoxy(2,19);printf("La lettre de la ligne:      <-- Vous devez entrer une lettre ");
Sleep(2000);
gotoxy(2,19);printf("La lettre de la ligne: J    <-- Vous devez entrer une lettre");
Sleep(2000);
gotoxy(2,21);printf("Felicitation vous avez coule un contre-torpilleur!! <-- Touche un bateux");
Sleep(2200);
system("cls");
tableautext[10][10]='X';
gotoxy(1,1);printf("Voici votre tableau  : ");
  y=4;
                for(ligne=1; ligne<11; ligne++){

                        y=y+1;
                        x=5;
                        for(colonne=1; colonne<12; colonne++){
                            gotoxy(x,y);printf(" %c  ", tableautext[ligne][colonne]);
                            x=x+4;

                    }
                }

        detail_tableau();
        gotoxy(55,6); printf("Porte-avion - %i ", numeroporteavion);
        gotoxy(55,7); printf("Croisseur - %i ", numerocroisseur);
        gotoxy(55,8); printf("Contre-torpilleur - %i ", numerocontretorpilleur);
        gotoxy(55,9); printf("Torpilleur - %i ", numerotropilleur);
        gotoxy(55,10); printf("Sous-marin - %i ", numerosousmarin);


    gotoxy(59,12);printf("^");
    gotoxy(59,13);printf("|");

    gotoxy(54,15);printf("Voici la quantite des bateaux que vous avez");

gotoxy(2,18);printf("Le numero de la colonne:   <-- Vous devez entrer un numero entier ");
Sleep(2200);
gotoxy(2,18);printf("Le numero de la colonne: 8 <-- Vous devez entrer un numero entier ");
Sleep(2000);
gotoxy(2,19);printf("La lettre de la ligne:     <-- Vous devez entrer une lettre ");
Sleep(2000);
gotoxy(2,19);printf("La lettre de la ligne: J   <-- Vous devez entrer une lettre");
Sleep(2000);
gotoxy(2,21);printf("Votre bombe est tombe dans l'eau");
tableautext[10][8]='~';
gotoxy(1,1);printf("Voici votre tableau  : ");
  y=4;
                for(ligne=1; ligne<11; ligne++){

                        y=y+1;
                        x=5;
                        for(colonne=1; colonne<12; colonne++){
                            gotoxy(x,y);printf(" %c  ", tableautext[ligne][colonne]);
                            x=x+4;

                    }
                }

        detail_tableau();
        gotoxy(55,6); printf("Porte-avion - %i ", numeroporteavion);
        gotoxy(55,7); printf("Croisseur - %i ", numerocroisseur);
        gotoxy(55,8); printf("Contre-torpilleur - %i ", numerocontretorpilleur);
        gotoxy(55,9); printf("Torpilleur - %i ", numerotropilleur);
        gotoxy(55,10); printf("Sous-marin - %i ", numerosousmarin);

Sleep(2500);

}

/** \brief Les detail autour du tableau de jeu
 *
 * \return void
 *
 */
void detail_tableau(){

gotoxy(3,5);printf("A"); gotoxy(3,6);printf("B"); gotoxy(3,7);printf("C"); gotoxy(3,8);printf("D"); gotoxy(3,9);printf("E");
gotoxy(3,10);printf("F"); gotoxy(3,11);printf("G"); gotoxy(3,12);printf("H"); gotoxy(3,13);printf("I"); gotoxy(3,14);printf("J");
gotoxy(6,4);printf("1");gotoxy(10,4);printf("2"); gotoxy(14,4);printf("3"); gotoxy(18,4);printf("4"); gotoxy(22,4);printf("5");
gotoxy(26,4);printf("6"); gotoxy(30,4);printf("7"); gotoxy(34,4);printf("8");gotoxy(38,4);printf("9"); gotoxy(42,4);printf("10");
gotoxy(46,4);printf("11");

}

/** \brief Tableau de jeu
 *
 * \param doit etre modifie à tout le moment
 * \param
 * \return
 *
 */
char tableau[12][12]={
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'},
                    {'.','.','.','.','.','.','.','.','.','.','.','.'}};

/** \brief Position des bateaux pour le mode "Normal"
 *
 * \param Premiere position des bateaux fait
 * \param
 * \return
 *
 */
char bateaux[11][12] = {
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //(1) porte-avion = 5 (5 cases);
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //(1) croisseur = 4 (4 cases);
                           {0, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5},    //(2) contre-torpilleur = 3 (3 cases);
                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    //(2) torpilleur = 2 (2 cases);
                           {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},    //(3)sous-marin = 1 (1 cases);
                           {0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 2, 0},
                           {0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 2, 0},
                           {0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 4, 0, 2, 2, 0, 3, 3, 3}};

/** \brief Afficher mon tableau de jeu pendant les parties
 *
 * \return void
 *
 */
void Affichermontableau1(){

    int x=4;
    int y=4;
    char ligne, colonne;

   y=4;
    for(ligne=1; ligne<11; ligne++){
            y=y+1;
            x=5;
            for(colonne=1; colonne<12; colonne++){
                gotoxy(x,y);printf(" %c  ", tableau[ligne][colonne]);
                x=x+4;
        }
    }
     detail_tableau();
}

/** \brief Demander le numero de la colonne du tableau de jeu
 *
 * \return int Renvoie le numero choisie
 *
 */
int colonne_choix(){

char colonne;

int vraicolonne=1;
while(vraicolonne){

  colonne=0;
  fflush(stdin);
  Affichermontableau1();
  gotoxy(2,18);printf("Le numero de la colonne: ");
  scanf("%d", &colonne);

  if ((colonne<12)&&(colonne>0)){
    vraicolonne=0;
      }

else {
       gotoxy(2,20);printf("Oops Cette ligne n'existe pas");
       gotoxy(2,24);system("pause");
       vraicolonne=1;
       system("cls");

    }
}
return colonne;
}

/** \brief Demander la lettre de la ligne du tableu de jeu
 *
 * \return int Renvoie la lettre choisie
 *
 */
int ligne_choix(){

char ligne;
int vrailigne=1;
int whretournemenu,  tapez_retournemenu;

while(vrailigne){


          ligne=0;
          fflush(stdin);
          gotoxy(2,19);printf("La lettre de la ligne: ");
          scanf("%c", &ligne);

          ligne=optiondeligne(ligne); //tranforme le caractere en chiffre entier

        if(ligne!=0){

          if(ligne==11){ //option pour retourne au menu (M)

                whretournemenu=1;
                while(whretournemenu){

                    system("cls");
                    Affichermontableau1();
                    gotoxy(2,20); printf("Vous voulez retourne au menu? [1 (oui) / 0 (non)]");
                    tapez_retournemenu=0;
                    gotoxy(2,22);scanf("%d", &tapez_retournemenu);


                        if(tapez_retournemenu==1){
                            vrailigne=0;
                            whretournemenu=0;
                            ligne=25;

                        }
                        if(tapez_retournemenu==0){
                            whretournemenu=0;
                            gotoxy(2,24);system("pause");
                            system("cls");
                            Affichermontableau1();

                        }
                        if((tapez_retournemenu!=0)&& (tapez_retournemenu!=1)){
                            gotoxy(2,25); printf("tapez 1 ou 0 ");
                            gotoxy(2,26);system("pause");
                            system("cls");
                            Affichermontableau1();

                        }
                    }
                }
             if(ligne==12){ //option pour avoir de l'aide (Z)
                    system("cls");
                    affiche_aide();
                    gotoxy(2,24);system("pause");
                    system("cls");
                    Affichermontableau1();
             }
           else{
            vrailigne=0;

           }
  }
          if(ligne==0){

            gotoxy(2,20);printf("Cette ligne n'existe pas");
            gotoxy(2,24);system("pause");
            system("cls");
            Affichermontableau1();


            }
            }
return ligne;
}

/** \brief touche et détruit les bateaux, dans le mode "Normal"
 *
 * \param ligne char ligne du tableau sélectionnée
 * \param colonne char colonne du tableau sélectionnée
 * \return int renvoie les scores fait pendand sa partie
 *
 */
int joeur_tableua_normal(char ligne, char colonne){


    int x,y; //function gotoxy
    int tapez_retournemenu=0, whretournemenu=1; //Pour retourne au menu
    char porteavion=0, croisseur=0, contretorpilleur=0, torpilleur=0, sousmarin=0, bombeslance=0, findujeu=1;
    int numeroporteavion=1, numerocroisseur=1, numerocontretorpilleur=2, numerotropilleur=2, numerosousmarin=3, bombesdanseau=0; //Quantite de bateux
    int vrailigne=1, vraicolonne=1;
    int prend_les_scores=0;
    int scores=0;


    while(findujeu){
    // Detruire le sous-marin

     if(bateaux[ligne][colonne] == 1){

                        if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi

                            tableau[ligne][colonne] = 'X';
                            sousmarin = sousmarin+1;

                            if (sousmarin<3){
                                gotoxy(2,21);printf("Felicitation vous avez detruit un Sous-marin!!");
                                bombeslance=bombeslance+1;

                                numerosousmarin=numerosousmarin-1;
                                gotoxy(2,24);system("pause");
                                system("cls");


                            }

                            if(sousmarin==3){
                                gotoxy(2,21);printf("Felicitation vous avez detruit tous les Sous-Marin!!");
                                bombeslance=bombeslance+1;

                                numerosousmarin=numerosousmarin-1;
                                gotoxy(2,24);system("pause");
                                system("cls");

                            }
                        }
                        else{
                            gotoxy(2,21);printf("vous avez deja choisi cela");
                            gotoxy(2,24);system("pause");
                            system("cls");
                        }

     }
    //Detruire le torpilleur
    if(bateaux[ligne][colonne] == 2){

                        if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi

                            tableau[ligne][colonne] = 'X';
                            torpilleur = torpilleur+1;
                            bombeslance=bombeslance+1;

                            if(ligne==10){
                                if(colonne==7||colonne==6){
                                    if((tableau[10][7]=='X') && (tableau[10][6]=='X')){ //Verifie si le bateux est vraiment detruit
                                         gotoxy(2,21);printf("Felicitation vous avez detruit un torpilleur!!");
                                         numerotropilleur=numerotropilleur-1;
                                         gotoxy(2,24);system("pause");
                                         system("cls");
                                    }
                                    else{
                                        gotoxy(2,21);printf("Felicitation vous avez touche un torpilleur!!");
                                        gotoxy(2,24);system("pause");
                                        system("cls");
                                    }
                                }
                            }
                            if(colonne==10){
                                if(ligne==8||ligne==7){
                                    if((tableau[8][10]=='X') && (tableau[7][10]=='X')){ //Verifie si le bateux est vraiment detruit
                                        gotoxy(2,21);printf("Felicitation vous avez detruit un torpilleur!!");
                                         numerotropilleur=numerotropilleur-1;
                                         gotoxy(2,24);system("pause");
                                         system("cls");
                                    }
                                    else{
                                        gotoxy(2,21);printf("Felicitation vous avez touche un torpilleur!!");
                                        gotoxy(2,24);system("pause");
                                        system("cls");
                                    }
                                }
                            }
                        }


                        else{
                            gotoxy(2,21);printf("vous avez deja choisi cela");
                            gotoxy(2,24);system("pause");
                            system("cls");
                        }
    }

    // detruit le contre-torpilleur
    if(bateaux[ligne][colonne] == 3){

                        if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi


                            tableau[ligne][colonne]='X';
                            contretorpilleur = contretorpilleur+1;
                            bombeslance=bombeslance+1;


                          if (ligne==10){

                            if(colonne==11 || colonne==10 || colonne==9){

                                if ((tableau[10][11]=='X')&&(tableau[10][10]=='X')&&(tableau[10][9]=='X')){ //Verifie si le bateux est vraiment detruit
                                 numerocontretorpilleur=numerocontretorpilleur-1;
                                  gotoxy(2,21);printf("Felicitation vous avez detruit un contre-torpilleur!!");
                                   gotoxy(2,24);system("pause");

                                    system("cls");
                            }

                            else{
                                gotoxy(2,21);printf("Felicitation vous avez touche un contre-torpilleur!!");
                                gotoxy(2,24);system("pause");

                                system("cls");

                                }
                            }
                         }

                          if(ligne==4 || ligne==5 || ligne==6){

                            if(colonne==6){

                                if((tableau[4][6]=='X')&&(tableau[5][6]=='X')&&(tableau[6][6]=='X')){ //Verifie si le bateux est vraiment detruit
                                numerocontretorpilleur=numerocontretorpilleur-1;
                                  gotoxy(2,21);printf("Felicitation vous avez detruit un contre-torpilleur!!");
                                   gotoxy(2,24);system("pause");
                                    system("cls");

                            }
                            else{
                                gotoxy(2,21);printf("Felicitation vous avez touche un contre-torpilleur!!");
                                 gotoxy(2,24);system("pause");
                                    system("cls");
                            }
                        }
                    }
                }
                    else{
                            gotoxy(2,21);printf("vous avez deja choisi cela");
                            gotoxy(2,24);system("pause");
                            system("cls");
                        }

    }
    //Detruire un croisseur
    if(bateaux[ligne][colonne] == 4){

                        if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi

                            tableau[ligne][colonne] = 'X';
                            croisseur = croisseur+1;

                            if(croisseur<4){
                                gotoxy(2,21);printf("Felicitation vous avez touche un croisseur!!");
                                  bombeslance=bombeslance+1;

                                gotoxy(2,24);system("pause");
                                system("cls");
                            }

                            if(croisseur==4){
                                gotoxy(2,21);printf("Felicitation vous avez detruit un croisseur!!");
                                  bombeslance=bombeslance+1;

                                numerocroisseur=numerocroisseur-1;
                                gotoxy(2,24);system("pause");
                                system("cls");
                            }
                        }

                        else{
                            gotoxy(2,21);printf("vous avez deja choisi cela");
                            gotoxy(2,24);system("pause");
                            system("cls");
                        }

                }
    //Détruire un porte-avion
    if(bateaux[ligne][colonne] == 5){

                        if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi

                            tableau[ligne][colonne] = 'X';
                            porteavion=porteavion+1;

                            if(porteavion<5){
                                gotoxy(2,21);printf("Felicitation vous avez touche un Porte-avion!!");
                                  bombeslance=bombeslance+1;

                                gotoxy(2,24);system("pause");
                                system("cls");
                            }

                            if(porteavion==5){
                                gotoxy(2,21);printf("Felicitation vous avez detruit le Porte-avion!!");
                                  bombeslance=bombeslance+1;

                                numeroporteavion=numeroporteavion-1;
                                gotoxy(2,24);system("pause");
                                system("cls");
                            }
                        }

                         else{
                            gotoxy(2,21);printf("vous avez deja choisi cela");
                            gotoxy(2,24);system("pause");
                            system("cls");
                        }

                }

    //lance une bombe dans eau
    if(bateaux[ligne][colonne]==0){

            if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi

                tableau[ligne][colonne] = '~';
                bombesdanseau=bombesdanseau+1;
                gotoxy(2,21);printf("Votre bombe est tombe dans l'eau");
                bombeslance=bombeslance+1;
                gotoxy(2,24);system("pause");
                system("cls");
            }
            else{
                gotoxy(2,21);printf("vous avez deja choisi cela");
                gotoxy(2,24);system("pause");
                system("cls");
            }
    }


    if((numeroporteavion==0)&&(numerocontretorpilleur==0)&&(numerocroisseur==0)&&(numerosousmarin==0)&&(numerotropilleur==0)){ // Le jouer a detruit tout les bateaux
        findujeu=0;
        prend_les_scores=1;
        //fin du jeu
    }


    if((numeroporteavion!=0)||(numerocontretorpilleur!=0)||(numerocroisseur!=0)||(numerosousmarin!=0)||(numerotropilleur!=0)){
        Affichermontableau1();
        gotoxy(55,6); printf("Porte-avion - %i ", numeroporteavion);
        gotoxy(55,7); printf("Croisseur - %i ", numerocroisseur);
        gotoxy(55,8); printf("Contre-torpilleur - %i ", numerocontretorpilleur);
        gotoxy(55,9); printf("Torpilleur - %i ", numerotropilleur);
        gotoxy(55,10); printf("Sous-marin - %i ", numerosousmarin);



colonne=colonne_choix();
ligne =ligne_choix();
    if (ligne==25){
    findujeu=0;
    }

            }

    if (prend_les_scores==1){
        scores=100-(bombesdanseau*2);
        system("cls");
        gotoxy(6,3);printf("FELICITATION VOUS AVEZ VAINCU LA BATAILLE!!");
        gotoxy(6,4);printf("--------------------------------------------");
        gotoxy(3,6);printf("Votre resume du match:");
        gotoxy(3,9);printf("Bombes lance - %d", bombeslance);
        gotoxy(3,10);printf("Bombes lance dans eau - %d", bombesdanseau);
        gotoxy(3,12); printf("Votre score final - %d", scores);
        gotoxy(3,24);system("pause");
        system("cls");


    }
}
return scores;
}

/** \brief Afficher le bateau d'initialisation de jeu
 *
 * \return void
 *
 */
void afficherbateaux(){

int i, x;


gotoxy(1,2);printf("                                              ----------                                                                          ");
gotoxy(1,3);printf("                                              |        |                                                                          ");
gotoxy(1,4);printf("                                              |        |                                                                          ");
gotoxy(1,5);printf("                                              |        |                                                                           ");
gotoxy(1,6);printf("                                          ------------------                                                                       ");
gotoxy(1,7);printf("                                          |                |                                                                       ");
gotoxy(1,8);printf("                                          |                |                                                                       ");
gotoxy(1,9);printf("                                          |                |                                                                      ");
gotoxy(1,10);printf("                                          |                |                                                                      ");
gotoxy(1,11);printf("                                          |                |                                                                      ");
gotoxy(1,12);printf("                                  ---------------------------------                                                               ");
gotoxy(1,13);printf("                                  |                               |                                                                         ");
gotoxy(1,14);printf("                                  |                               |                                                                          ");
gotoxy(1,15);printf("                                  |                               |                             / |                                          ");
gotoxy(1,16);printf("                                  |                               |                            /  |                                             ");
gotoxy(1,17);printf("          -----------------       |                               |               ------------- --|                                      ");
gotoxy(1,18);printf("          |               |       ---------------------------------              |                |                                      ");
gotoxy(1,19);printf("          |   |-------|   |                    |      |                          |                |                                         ");
gotoxy(1,20);printf("          |   |       |   |                    |      |                          |                |                                          ");
gotoxy(1,21);printf("          |   |       |   |                    |      |                          |                |                                              ");
gotoxy(1,22);printf("          |   |-------|   |-------------------------------------------------------                |                                          ");
gotoxy(1,23);printf("          |                                                                                       |                                          ");
gotoxy(1,24);printf("          |                                                                                       |                                              ");
gotoxy(1,25);printf("          |                       Bienvenue sur le jeu de bataille navale!!                       |                                                ");
gotoxy(1,26);printf("          |                                                                                       |                                            ");
gotoxy(1,27);printf("          |                                                                                       |                                                 ");
gotoxy(1,28);printf("          |---------------------------------------------------------------------------------------|                                                  ");

x=1;
for(i=0; i<5;i++){

gotoxy(x,29);printf("    ~~~~            ~~~~~~                ~~~~~~~               ~~~~~~~~                 ~~~~~~              ~~~~~~~                                ");
gotoxy(x,30);printf("          ~~~~~~              ~~~~~~~                ~~~~~~                 ~~~~~~~              ~~~~~~~                                     ");
x=x+4;
Sleep(1000);

if (x>12){
    x=1;
}

}





}

/** \brief touche et détruit les bateaux dans le mode "Facille"
 *
 * \param ligne char ligne du tableau sélectionnée
 * \param colonne char colonne du tableau sélectionnée
 * \return int renvoie les scores fait pendand sa partie
 *
 */
int jouer_tableau_facille(char ligne, char colonne){

  int x,y;
    int tapez_retournemenu=0, whretournemenu=1; //Pour retourne au menu
    char porteavion=0,contretorpilleur=0, torpilleur=0, bombeslance=1, bombesdanseau=0, findujeu=1;
    int numeroporteavion=1, numerocontretorpilleur=1, numerotropilleur=1, numerosousmarin=1; //Quantite de bateaux
    int vrailigne=1, vraicolonne=1;
    int prend_les_scores=0;
    int scores=0;
    char bateaux_facille[11][12];

    Remplir_grille1_txt(bateaux_facille);

     while(findujeu){
     if(tableau[ligne][colonne]== '.'){ //Verifier si la case n'etait pas choisi
            bombeslance=bombeslance+1;

        //Détruire un sous-marin
        if (bateaux_facille[ligne][colonne]==1){
            tableau[ligne][colonne]='X';
            gotoxy(2,21);printf("Felicitation vous avez detruit un Sous-marin!!");
            gotoxy(2,24);system("pause");
            numerosousmarin=0;
            system("cls");

       }
       //Détruire un torpilleur
       if (bateaux_facille[ligne][colonne]==2){
             tableau[ligne][colonne]='X';
             torpilleur=torpilleur+1;

             if(torpilleur<2){
                 gotoxy(2,21);printf("Felicitation vous avez touche un torpilleur!!");
                 gotoxy(2,24);system("pause");
                 system("cls");
             }
             else{
                 gotoxy(2,21);printf("Felicitation vous avez detruit un torpilleur!!");
                 numerotropilleur=0;
                 gotoxy(2,24);system("pause");
                  system("cls");
             }
       }
       //Détruire un contre-torpilleur
       if(bateaux_facille[ligne][colonne]==3){
            tableau[ligne][colonne]='X';
            contretorpilleur=contretorpilleur+1;

            if(contretorpilleur<3){
                gotoxy(2,21);printf("Felicitation vous avez touche un contre-torpilleur!!");
                gotoxy(2,24);system("pause");
                system("cls");
            }
            else{
                gotoxy(2,21);printf("Felicitation vous avez detruit un contre-torpilleur!!");
                gotoxy(2,24);system("pause");
                numerocontretorpilleur=0;
                system("cls");
            }
       }
       //Détruire un porte-avion
       if(bateaux_facille[ligne][colonne]==5){
            tableau[ligne][colonne]='X';
            porteavion=porteavion+1;

            if(porteavion<5){
                gotoxy(2,21);printf("Felicitation vous avez touche un Porte-avion!!");
                gotoxy(2,24);system("pause");
                system("cls");
                scores=2;
            }
            else{
                 gotoxy(2,21);printf("Felicitation vous avez detruit le Porte-avion!!");
                 numeroporteavion=0;
                 gotoxy(2,24);system("pause");
                 system("cls");
            }
       }
       //lance une bombe dans eau
       if(bateaux_facille[ligne][colonne]==0){

                tableau[ligne][colonne] = '~';
                bombesdanseau=bombesdanseau+1;
                gotoxy(2,21);printf("Votre bombe est tombe dans l'eau");
                gotoxy(2,24);system("pause");
                system("cls");
            }
     }
    else{
        gotoxy(2,21);printf("vous avez deja choisi cela");
        gotoxy(2,24);system("pause");
        system("cls");
        }

    if((numerocontretorpilleur==0) && (numeroporteavion==0) && (numerotropilleur==0) && (numerosousmarin==0)){ //Le joeur a detruit tous le bateaux
        prend_les_scores=1;
        //fin du jeu
    }
    if((numerocontretorpilleur!=0) || (numeroporteavion!=0)|| (numerotropilleur!=0) || (numerosousmarin!=0)){
        Affichermontableau1();
        gotoxy(55,6); printf("Porte-avion - %i ", numeroporteavion);
        gotoxy(55,7); printf("Contre-torpilleur - %i ", numerocontretorpilleur);
        gotoxy(55,8); printf("Torpilleur - %i ", numerotropilleur);
        gotoxy(55,9); printf("Sous-marin - %i ", numerosousmarin);

    colonne=colonne_choix();
    ligne =ligne_choix();
    if (ligne==25){
        findujeu=0;
    }
  }
        if(prend_les_scores==1){ //fin de jeu
            scores=100-(bombesdanseau);
            system("cls");
            gotoxy(6,3);printf("FELICITATION VOUS AVEZ VAINCU LA BATAILLE!!");
            gotoxy(6,4);printf("--------------------------------------------");
            gotoxy(3,6);printf("Votre resume du match:");
            gotoxy(3,9);printf("Bombes lance - %d", bombeslance);
            gotoxy(3,10);printf("Bombes lance dans eau - %d", bombesdanseau);
            gotoxy(3,12); printf("Votre score final - %d", scores);
            gotoxy(3,24);system("pause");
            system("cls");
            findujeu=0;
        }
     }
  return scores;
}


/** \brief touche et détruit les bateaux dans le mode "Difficile"
 *
 * \param ligne char : ligne du tableau sélectionnée
 * \param colonne char : colonne du tableau  sélectionnée
 * \return int renvoie les scores fait pendand sa partie
 *
 */
int jouer_tableau_hard(char ligne, char colonne){
    int x,y;
    int tapez_retournemenu=0, whretournemenu=1; //Pour retourne au menu
    char porteavion=0,contretorpilleur=0, croisseur=0, torpilleur=0, bombeslance=1, sousmarin=0, findujeu=1;
    int numeroporteavion=1,numerocroisseur=1, numerocontretorpilleur=1, numerotropilleur=1, numerosousmarin=7, bombesdanseau=0; //Quantite de bateaux
    int vrailigne=1, vraicolonne=1;
    int prend_les_scores=0;
    int scores=0;
    char bateaux_difficile[11][12];

    Remplir_grille3_txt(bateaux_difficile);

     while(findujeu){
     if(tableau[ligne][colonne]== '.'){ //Si le jouer n'a pas encoire touche cette case
            bombeslance=bombeslance+1;

        //Détruire un sous-marin
        if (bateaux_difficile[ligne][colonne]==1){
            tableau[ligne][colonne]='X';
            numerosousmarin=numerosousmarin-1;
            sousmarin=sousmarin+1;
            if(sousmarin==7){
                gotoxy(2,21);printf("Felicitation vous avez detruit tout les Sous-marin!!");
                gotoxy(2,24);system("pause");
                system("cls");
            }
            else{
            gotoxy(2,21);printf("Felicitation vous avez detruit un Sous-marin!!");
            gotoxy(2,24);system("pause");
            system("cls");
            }
       }
       //Détruire un torpilleur
       if (bateaux_difficile[ligne][colonne]==2){
             tableau[ligne][colonne]='X';
             torpilleur=torpilleur+1;

             if(torpilleur<2){
                 gotoxy(2,21);printf("Felicitation vous avez touche un torpilleur!!");
                 gotoxy(2,24);system("pause");
                 system("cls");
             }
             else{
                 gotoxy(2,21);printf("Felicitation vous avez detruit un torpilleur!!");
                 numerotropilleur=0;
                 gotoxy(2,24);system("pause");
                 system("cls");
             }
       }
       //Détruire un contre-torpilleur
       if(bateaux_difficile[ligne][colonne]==3){
            tableau[ligne][colonne]='X';
            contretorpilleur=contretorpilleur+1;

            if(contretorpilleur<3){
                gotoxy(2,21);printf("Felicitation vous avez touche un contre-torpilleur!!");
                gotoxy(2,24);system("pause");
                system("cls");
            }
            else{
                gotoxy(2,21);printf("Felicitation vous avez detruit un contre-torpilleur!!");
                gotoxy(2,24);system("pause");
                numerocontretorpilleur=0;
                system("cls");
            }
       }
       //Détruire un croisseur
       if(bateaux_difficile[ligne][colonne]==4){
            tableau[ligne][colonne]='X';
            croisseur = croisseur+1;

                if(croisseur<4){
                    gotoxy(2,21);printf("Felicitation vous avez touche un croisseur!!");
                    gotoxy(2,24);system("pause");
                    system("cls");
                    }
                if(croisseur==4){
                    gotoxy(2,21);printf("Felicitation vous avez detruit un croisseur!!");
                    numerocroisseur=0;
                    gotoxy(2,24);system("pause");
                    system("cls");
                }
         }

        //Détruire un porte-avion
       if(bateaux_difficile[ligne][colonne]==5){
            tableau[ligne][colonne]='X';
            porteavion=porteavion+1;

            if(porteavion<5){
                gotoxy(2,21);printf("Felicitation vous avez touche un Porte-avion!!");
                gotoxy(2,24);system("pause");
                system("cls");
                scores=2;
            }
            else{
                 gotoxy(2,21);printf("Felicitation vous avez detruit le Porte-avion!!");
                 numeroporteavion=0;
                 gotoxy(2,24);system("pause");
                 system("cls");
            }
       }
       //lance une bombe dans eau
       if(bateaux_difficile[ligne][colonne]==0){

                tableau[ligne][colonne] = '~';
                bombesdanseau=bombesdanseau+1;
                gotoxy(2,21);printf("Votre bombe est tombe dans l'eau");
                gotoxy(2,24);system("pause");
                system("cls");
            }
     }
    else{
        gotoxy(2,21);printf("vous avez deja choisi cela");
        gotoxy(2,24);system("pause");
        system("cls");
        }
    if((numeroporteavion==0) && (numerocroisseur==0)&& (numerocontretorpilleur==0) && (numerotropilleur==0) && (numerosousmarin==0)){ //Le joeur a detruit tous les bateaux
        prend_les_scores=1;
        //fin du jeu
    }
    if((numeroporteavion!=0) || (numerocroisseur!=0)|| (numerocontretorpilleur!=0)|| (numerotropilleur!=0) || (numerosousmarin!=0)){
        Affichermontableau1();
        gotoxy(55,6); printf("Porte-avion - %i ", numeroporteavion);
        gotoxy(55,7); printf("Contre-torpilleur - %i ", numerocontretorpilleur);
        gotoxy(55,8); printf("Torpilleur - %i ", numerotropilleur);
        gotoxy(55,9); printf("Sous-marin - %i ", numerosousmarin);

    colonne=colonne_choix();
    ligne =ligne_choix();
    if (ligne==25){
        findujeu=0;
    }
  }
        if(prend_les_scores==1){ //Fin de jeu
            scores=100-(bombesdanseau*2);
            system("cls");
            gotoxy(6,3);printf("FELICITATION VOUS AVEZ VAINCU LA BATAILLE!!");
            gotoxy(6,4);printf("--------------------------------------------");
            gotoxy(3,6);printf("Votre resume du match:");
            gotoxy(3,9);printf("Bombes lance - %d", bombeslance);
            gotoxy(3,10);printf("Bombes lance dans eau - %d", bombesdanseau);
            gotoxy(3,12); printf("Votre score final - %d", scores);
            gotoxy(3,24);system("pause");
            system("cls");
            findujeu=0;
        }
     }
  return scores;
}


/** \brief Initialisation du jeu, mettre le tableau à 0.
 *
 * \param option_de_grille int :  La grille qu'était choisie pour jouer
 * \return int renvoie les scores fait pendand sa partie
 *
 */
int initialize_le_jeu(int option_de_grille){

    int scores=0;
    int y, x;
    int e;
    int tapez_retournemenu=0, whretournemenu=1, colonne=0;
    char ligne=0, findujeu=1;
    int prend_les_scores=0;
    int totaljeu=1;
    int reessayer;
    int whreessayer;

    system("cls");
    gotoxy(10,4);printf("--------------------------");
    gotoxy(15,5);printf("ON VA JOUER :D");
    gotoxy(10,6);printf("--------------------------");
    gotoxy(10,9);printf("Avant de commancer un petit rappel");
    gotoxy(10,11);printf("Quand le jeu vous demandera la lettre da la ligne vous pouvez");
    gotoxy(10,12);printf("Tapez Z pour afficher l'aide");
    gotoxy(10,13);printf("Tapez M pour retourne au menu");


    x=9;
    for(e=0;e<4;e++){
       x=x+1;
       gotoxy(x,16); printf("."); //"faux Chargement"
       Sleep(1000);
       if(x==17){
      gotoxy(10,17);printf("Vous etes pret maintenant!!! ");
       }
  }

    gotoxy(10,20);system("pause");
    system("cls");

    totaljeu=1;
    while(totaljeu){



    y=4;
    for(ligne=1; ligne<11; ligne++){
            y=y+1;
            x=5;
            for(colonne=1; colonne<12; colonne++){
                tableau[ligne][colonne] = '.';   //Mettre mon tableau à 0
                gotoxy(x,y);printf(" %c  ", tableau[ligne][colonne]);
                x=x+4;

        }
    }

colonne=colonne_choix();
ligne=ligne_choix();
if(ligne==25){ //25=Returne au menu
   totaljeu=0;
}

else {  //depend du choix de la grille avant fait

        if(option_de_grille==1){
            scores=jouer_tableau_facille(ligne,colonne);
        }
        if(option_de_grille==2){
         scores=joeur_tableua_normal(ligne,colonne);
        }
         if(option_de_grille==3){
            scores=jouer_tableau_hard(ligne,colonne);
         }

        whreessayer=1;
        while(whreessayer){
        system("cls");
        printf("\n\n\n       Vous voulez reessayer la partie?  [1 (Oui) ] / [ 2 (Non) ]\n\n");
        gotoxy(8,8);scanf("%i", &reessayer);

            if(reessayer==1){
                 totaljeu=1;
                 whreessayer=0;
                 system("cls");
            }
            if (reessayer==2){
                totaljeu=0;
                 whreessayer=0;
            }

            if((reessayer!=1)&&(reessayer!=2)){
                printf("Tapez 1 ou 2 ");
            }
        }
    }
}
 return scores;
}


/** \brief Option pour choisir une grille aleatoire
 *
 * \return int Renvoie le grille donne
 *
 */
int choix_grille_aleatoire(){

int x,y, e;
srand(time(NULL));
int numeroaleatoire=rand()%3+1; //Créer un nombre aleatoire
int grille_choix=0;

system("cls");
printf("\n\n");
printf("                            ------------------------\n");
printf("                                Choix aleatoire!!\n"  );
printf("                            ------------------------\n");
printf("\n\n");
printf("  votre grille est:  ");
 x=2;
    for(e=0;e<4;e++){
       x=x+1;
       gotoxy(x,9); printf(".");
       Sleep(1000);
    }
    if(numeroaleatoire==1){
       printf("\n\n");
       printf("        ------------------------\n");
       printf("            Grille facille!!\n"  );
       printf("        ------------------------\n");
       grille_choix=1;
    }
    if(numeroaleatoire==2){
        printf("\n\n");
        printf("       ------------------------\n");
        printf("            Grille normal!!\n"  );
        printf("       ------------------------\n");
        grille_choix=2;
    }
    if(numeroaleatoire==3){
        printf("\n\n");
        printf("       ------------------------\n");
        printf("          Grille difficille!!\n"  );
        printf("       ------------------------\n");
        grille_choix=3;
    }
printf("\n\n\n");
system("\n\nPause");

return grille_choix;

}

int main() {

    int choix, choixgrille;
    char pseudo[100];
    int scores=0;
    int i=0;
    char retournemenu;
    int okauthentifier=1;
    int nomauthentifier=1;
    int total=1;
    int x, y, e;
    int grille_choix_aleatoire=0;


afficherbateaux();
system("cls");

choix=MENU_PRINCIPAL();
system("cls");

while(total){

//S'authentifier
if ( choix == 1){

nomauthentifier=1;
while(nomauthentifier){

    system("cls");


      pseudo[100]=0;
      gotoxy(18,2);printf("---------------------------------------");
      gotoxy(28,3);printf("AUTHENTIFICATION");
      gotoxy(18,4);printf("---------------------------------------");
      gotoxy(20,6);printf("Entrez un pseudo s'il vous plait:\n");
      gotoxy(20,8);scanf("%s", &pseudo);

      gotoxy(20,10);printf("Bienvenu %s ",pseudo );
      loge_lesfaits("Pseudo du joueur:",pseudo);

      okauthentifier=1;
      while (okauthentifier){
      gotoxy(20,12);printf("Tapez M pour retourne au menu ");
      fflush(stdin);
      scanf("%c", &retournemenu);

      switch(retournemenu){

      case 'm':
      case 'M': okauthentifier = 0;
                nomauthentifier=0;
                break;

      default: okauthentifier =1;}
      }
}
choix=MENU_PRINCIPAL();
}

//Jouer apées avoir s'authentifier
if ((nomauthentifier==0)&& (choix==2)){

    grille_choix_aleatoire=0;
    choixgrille=Choix_grille();

   //choisir la grille facile
   if(choixgrille==1){
        scores= initialize_le_jeu(1);
            if(scores>0){
                sauvegarde_fichier(pseudo,scores,"Facile"); //sauvegarder le pseudo avec le score dans un fichier text
            }
   }

    //choisir la grille normal
    if(choixgrille==2){
        scores= initialize_le_jeu(2);
        if(scores>0){
            sauvegarde_fichier(pseudo, scores,"Normal"); //sauvegarder le pseudo avec le score dans un fichier text
        }
    }

    //Choisir la grille dificille
    if(choixgrille==3){
        scores= initialize_le_jeu(3);
            if(scores>0){
                sauvegarde_fichier(pseudo, scores,"Difficile"); //sauvegarder le pseudo avec le score dans un fichier text
        }
    }
    //Choisir grille aleatoire
    if(choixgrille==4){

        grille_choix_aleatoire=choix_grille_aleatoire();

            //Grille facile
            if(grille_choix_aleatoire==1){
                loge_lesfaits("Grille aleatoire:","Grille facile");
                scores= initialize_le_jeu(1);
                 if(scores>0){
                    sauvegarde_fichier(pseudo, scores, "Facile"); //sauvegarder le pseudo avec le score dans un fichier text
                }
            }
            //Grille normal
            if (grille_choix_aleatoire==2){
                loge_lesfaits("Grille aleatoire:","Grille normal");
                scores= initialize_le_jeu(2);
                if(scores>0){
                    sauvegarde_fichier(pseudo, scores, "Normal"); //sauvegarder le pseudo avec le score dans un fichier text
                }
            }
            //Grille difficile
            if (grille_choix_aleatoire==3){
                loge_lesfaits("Grille aleatoire:","Grille difficile");
                scores= initialize_le_jeu(3);
                if(scores>0){
                sauvegarde_fichier(pseudo, scores, "Difficile"); //sauvegarder le pseudo avec le score dans un fichier text
            }
        }
    }


choix=MENU_PRINCIPAL();
        system("cls");

}

//Jouer sans avoir s'authentifier
if((nomauthentifier==1)&& (choix==2)){
    system("cls");
    printf("\n\n    Vous etes pas authentifier..." );
    Sleep(1500);
    choix=MENU_PRINCIPAL();
}

//Afhicer de l'aide
if (choix==3){
    system("cls");
    affiche_aide();
    choix=MENU_PRINCIPAL();
}

//Aficher les scores
if (choix==4){
    system("cls");
    printf("scores\n\n\n ");
    printf("                         LISTE DES SCORES \n ");
    printf("                      ------------------------");
    printf("\n\n\n");
    printf("           Pseudo             scores                 mode\n\n\n");


    Lir_fichier();
    printf("\n\n\n\n");
    system("pause");
    choix=MENU_PRINCIPAL();
}

//Sortir
if(choix==5){
    system("cls");
    printf("Au revoir");
    total=0;
    Sleep(2000);

}
}
}








