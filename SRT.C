#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom_processus[20];
    int date_arrivee;
    int duree_cycles;
    int priorite;
} Processus;


struct exe_processus {
    char nom[10];
    int debut;
    int fin;
};

void afficher(int n, struct exe_processus t[50]) {
    for (int i = 0; i < n; i++) {
        printf("|-------");
    }
    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("| %-5s ", t[i].nom);        
        }

    printf("|\n");

    for (int i = 0; i < n; i++) {
        printf("|-------");
    }
        printf("|\n");
         
   printf("%-6d  %d", t[0].debut,t[0].fin);
    for (int i = 1; i < n; i++) {
printf("%8d", t[i].fin);        
    }    
    printf("\n");
}

void ajoute_exe_proc(struct exe_processus t[], int *n, char nom[], int debut, int fin) {
    strcpy(t[*n].nom, nom);
    t[*n].debut = debut;
    t[*n].fin = fin;
    (*n)++;
}

int recuperer_duree(char *nom_processus, Processus processus2[], int n) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(nom_processus, processus2[i].nom_processus) == 0) {
            return processus2[i].duree_cycles;
        }
    }
    return -1;
}

void executerSRT(Processus processus[], int n,Processus processus2[]) {
    int temps_actuel = 0;
    int processus_termine = 0;
    int temps_rotation_total = 0;
    int temps_attente_total = 0;
    int temps_rotation_p;
    int temps_attente_p;
    int deb;
    int fin;
    
    struct exe_processus tableau[50];
    int nombre = 0;

    while (processus_termine < n)
     {
        int indice_plus_court = -1;
        int duree_minimale = 8989898;
      
        for (int i = 0; i < n; i++)
          {
            if (processus[i].date_arrivee <= temps_actuel && processus[i].duree_cycles < duree_minimale && processus[i].duree_cycles > 0) {
                indice_plus_court = i;
                duree_minimale = processus[i].duree_cycles;
            }
          }
         
        if (indice_plus_court == -1)
          {
            temps_actuel++;
            continue;
          }
          
        ajoute_exe_proc(tableau, &nombre, processus[indice_plus_court].nom_processus,temps_actuel,temps_actuel+1); 

        processus[indice_plus_court].duree_cycles--;
        temps_actuel++;



        if (processus[indice_plus_court].duree_cycles == 0) 
          {
            processus_termine++;  
      	    temps_rotation_p = temps_actuel - processus[indice_plus_court].date_arrivee ;
      	    
            int duree_cycle_p= recuperer_duree(processus[indice_plus_court].nom_processus,processus2,n);			   
     	temps_attente_p = temps_rotation_p - duree_cycle_p;    			   
     	 printf("temps de rotation de (%s) = %d 	 temps d attente de (%s) = %d \n ",processus[indice_plus_court].nom_processus,temps_rotation_p,processus[indice_plus_court].nom_processus,temps_attente_p );
     			   	   
            temps_rotation_total += temps_rotation_p;
            temps_attente_total += temps_attente_p;
          }      
    }
     
         printf("\nTemps de rotation total : %d \n", temps_rotation_total);
  	 printf("Temps de rotation moyen : %.2f \n", (float)temps_rotation_total / (float)n);
 	 printf("Temps d'attente total : %d \n", temps_attente_total);
 	 printf("Temps d'attente moyen : %.2f \n", (float)temps_attente_total / (float)n);
    printf("\n digramme de gant (SRT) \n");   
   	 afficher(nombre, tableau);


}

void lireFichierConfig(char *nom_fichier, Processus processus[], int *n) {
    FILE *fichier = fopen(nom_fichier, "r");    
    *n = 0;
    char nom_processus[20];
    int date_arrivee; 
    int duree_cycles;
    int priorite;

    while (fscanf(fichier, "%s %d %d %d", nom_processus, &date_arrivee, &duree_cycles, &priorite) == 4) {
        if (duree_cycles != 0) {
            strcpy(processus[*n].nom_processus, nom_processus);
            processus[*n].date_arrivee = date_arrivee;
            processus[*n].duree_cycles = duree_cycles;
            processus[*n].priorite = priorite;
            (*n)++;
        }
    }
    fclose(fichier);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_config>\n", argv[0]);
        return 1;
    }
    Processus processus[100],copieProcessus[100]; 
    int n;
    lireFichierConfig(argv[1], processus, &n);
    	for (int i=0;i<n;i++){
	copieProcessus[i]=processus[i];
	}
    executerSRT(processus, n,copieProcessus);
    return 0;
}

