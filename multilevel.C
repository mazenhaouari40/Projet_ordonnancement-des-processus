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


void executerMultiLevelQueue( Processus processus[], int n, int quantum) {
    int temps_actuel = 0;
    int processus_termine = 0;
    int max = -1;
    int indice_pro_exe;
    int k = 0;
    struct exe_processus tableau[50];
    int nombre = 0;
        int temps_rotation_total = 0;
    int temps_attente_total = 0;
    int temps_rotation_p;
    int temps_attente_p;
    while (n > 0) {
        int j = 0; 
        int priorite_prec = max;
        for (int i = 0; i < n; i++) 
        {
            if (processus[i].date_arrivee <= temps_actuel && processus[i].duree_cycles > 0 && processus[i].priorite >= max) {
                indice_pro_exe = i;
                j++; 
                max = processus[i].priorite;
            }
        }

        if ((j == 1) || (max > priorite_prec)) 
        {
            //ajoute_exe_proc(tableau, &nombre, processus[indice_pro_exe].nom_processus,temps_actuel,temps_actuel+1);  
            printf("Processus %s en cours d'exécution au temps %d \n", processus[indice_pro_exe].nom_processus, temps_actuel);
            processus[indice_pro_exe].duree_cycles--;
            temps_actuel++;
        } 
        else 
        {
            indice_pro_exe = -1;
            while (k < n ) {
                if  (processus[k].date_arrivee <= temps_actuel && processus[k].duree_cycles > 0  && processus[k].priorite == max ) {
                    indice_pro_exe = k;
                    break;
                } 
                k++;
            }
            
            if (indice_pro_exe != -1) { 
                //ajoute_exe_proc(tableau, &nombre, processus[indice_pro_exe].nom_processus,temps_actuel,temps_actuel+quantum);              
                printf("Processus %s en cours d'exécution au temps %d \n", processus[indice_pro_exe].nom_processus, temps_actuel);            
            	processus[indice_pro_exe].duree_cycles -= quantum;
            	temps_actuel += quantum;
            }
            else 
            {
                            k = 0;
            }
   	 }

        if (processus[indice_pro_exe].duree_cycles == 0) 
        {
        	printf("Processus %s terminé au temps %d\n", processus[indice_pro_exe].nom_processus, temps_actuel);
        	
        	       temps_rotation_p = temps_actuel - processus[indice_pro_exe].date_arrivee ;
      		       temps_attente_p = temps_rotation_p - processus[indice_pro_exe].duree_cycles;
       		       temps_rotation_total += temps_rotation_p;
 		       temps_attente_total += temps_attente_p;
        	
       		int processus_en_cours = indice_pro_exe;    		
       		// Suppression du processus terminé en décalant les processus restants
       		for (int j = processus_en_cours; j < n - 1; j++) {
        	    processus[j] = processus[j + 1];
        	}
        	n--;         	        	
        	//verif si tous proce sont ter 
        	int test=0;
        	for(int h=0;h<n;h++)
        	{
        		if (processus[h].priorite == max && processus[h].date_arrivee <= temps_actuel  )
        		{ 
        		test=1;
        		}
                 }
                 if (test == 0 ) { max = -1 ; priorite_prec=-1; }
         }         
    }
    
        // printf("digramme de gant (Multilevel) \n");   
   	// afficher(nombre, tableau);
       	printf("\nTemps de rotation total : %d \n", temps_rotation_total);
  	  printf("Temps de rotation moyen : %.2f \n", (float)temps_rotation_total / (float)n);
  	  printf("Temps d'attente total : %d \n", temps_attente_total);
  	  printf("Temps d'attente moyen : %.2f \n", (float)temps_attente_total / (float)n); 
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
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <fichier_config> <quantum>\n", argv[0]);
        return 1;
    }
    Processus processus[100];
    int n;
    lireFichierConfig(argv[1], processus, &n);

    // Convertir l'argument quantum en entier
    int quantum = atoi(argv[2]);

    executerMultiLevelQueue(processus, n, quantum);

    return 0;
}
