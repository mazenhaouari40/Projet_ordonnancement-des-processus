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

typedef struct Noeud {
    int valeur;
    struct Noeud* suivant;
} Noeud;

void ajouter_p(Noeud** tete, int x) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    nouveauNoeud->valeur = x;
    nouveauNoeud->suivant = NULL;
    if (*tete == NULL) {
        *tete = nouveauNoeud;
    } else 
    {
        Noeud* courant = *tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveauNoeud;
    }
}

void supprimer_p(Noeud** tete, int x) {
    if (*tete == NULL) {
        return;
    }
    if ((*tete)->valeur == x) {
        Noeud* temp = *tete;
        *tete = (*tete)->suivant;
        free(temp);
        return;
    }
    Noeud* courant = *tete;
    Noeud* precedent = NULL;
    while (courant != NULL && courant->valeur != x) {
        precedent = courant;
        courant = courant->suivant;
    }
    if (courant != NULL) {
        precedent->suivant = courant->suivant;
        free(courant);
    }
}

int existe_element(Noeud* tete, int x) {
    Noeud* courant = tete;
    while (courant != NULL) {
        if (courant->valeur == x) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

int recuperer_premier_element(Noeud** tete) {
    if (*tete == NULL) {
        fprintf(stderr, "La liste est vide\n");
        exit(EXIT_FAILURE);
    }
    int premier_element = (*tete)->valeur;
    supprimer_p(tete, premier_element);
    return premier_element;
}

void Execution(Processus processus[],int n, int *temps_actuel,int quantum, Noeud** tete , int proc_exe) {
    int temps_fin = (*temps_actuel) + quantum;
    int x = (*temps_actuel) ;
    for (int i = x; i <= temps_fin; i++) {
    
        for (int j = 0; j < n ;j++) {
            if (processus[j].date_arrivee == i && processus[j].duree_cycles > 0 && proc_exe != j) {
                ajouter_p(tete, j);                
            }
        }
        
    }
            (*temps_actuel)=temps_fin;
}

int recuperer_duree(char *nom_processus, Processus processus2[], int n) {
    for (int i = 0; i < n; ++i) {
        if (strcmp(nom_processus, processus2[i].nom_processus) == 0) {
            return processus2[i].duree_cycles;
        }
    }
    return -1;
}


void executerRoundRobin(Processus processus[], int n, int quantum,Processus processus2[]) {
    int temps_actuel = 0;
    int processus_termine = 0;
    Noeud* l = NULL;
     struct exe_processus tableau[50];
    int nombre_processus = 0;       
    int temps_rotation_total = 0;
    int temps_attente_total = 0;
    int temps_rotation_p;
    int temps_attente_p;
    while (processus_termine < n) 
    {
    
        for (int i = 0; i < n; i++) {
            if (processus[i].date_arrivee <= temps_actuel && processus[i].duree_cycles > 0 && existe_element(l,i) == 0) {
    			ajouter_p(&l,i);
            } 
        }
        
        if (l==NULL)
        {
        	temps_actuel++;
        }
        else
        {
        
     	   int proc_exe  = recuperer_premier_element(&l);       
      
        	 if (processus[proc_exe].duree_cycles <= quantum) 
        	 {
                    
                    ajoute_exe_proc(tableau, &nombre_processus, processus[proc_exe].nom_processus,temps_actuel,temps_actuel+processus[proc_exe].duree_cycles);                     
                    Execution(processus,n,&temps_actuel,processus[proc_exe].duree_cycles,&l,proc_exe);                     
                    processus[proc_exe].duree_cycles = 0;                                                                                                  
                    processus_termine++;
                    
     			   temps_rotation_p = temps_actuel - processus[proc_exe].date_arrivee ;
     			   
     			   int duree_cycle_p= recuperer_duree(processus[proc_exe].nom_processus,processus2,n);
     			   
     			   
     			   temps_attente_p = temps_rotation_p - duree_cycle_p;    			   
     			   printf("temps de rotation de (%s) = %d 	 temps d attente de (%s) = %d \n ",processus[proc_exe].nom_processus,temps_rotation_p,processus[proc_exe].nom_processus,temps_attente_p );
     			   
  			   temps_rotation_total += temps_rotation_p;
  			   temps_attente_total += temps_attente_p;
        
                    supprimer_p(&l,proc_exe);
        	 } 
       	       else 
         	{                   
                    ajoute_exe_proc(tableau, &nombre_processus, processus[proc_exe].nom_processus,temps_actuel,temps_actuel+quantum); 
                    Execution(processus,n,&temps_actuel,quantum,&l,proc_exe);
                                        
                    processus[proc_exe].duree_cycles -= quantum;
                    /*if ( processus[proc_exe].duree_cycles == 0)
                    	{
                    	printf("Processus %s terminé au temps %d\n", processus[proc_exe].nom_processus, temps_actuel);
                    	processus_termine++;

	    	            temps_rotation_p = temps_actuel - processus[proc_exe].date_arrivee ;
	    	           int duree_cycle_p= recuperer_duree(processus[proc_exe].nom_processus,processus2,n); 
	     	            temps_attente_p = temps_rotation_p - duree_cycle_p;
	     	            printf("temps de rotation de (%s) = %d 	 temps d attente de (%s) = %d \n ",processus[proc_exe].nom_processus,temps_rotation_p,processus[proc_exe].nom_processus,temps_attente_p );	
	     	            temps_rotation_total += temps_rotation_p;
	    		    temps_attente_total += temps_attente_p;
                
                    	supprimer_p(&l,proc_exe);
                    	}
                    else
                    	{*/
                        ajouter_p(&l,proc_exe);
                   	//}                    
         	}         
        }  
         
    }

    printf("\nTemps de rotation total : %d \n", temps_rotation_total);
    printf("Temps de rotation moyen : %.2f \n", (float)temps_rotation_total / (float)n);
    printf("Temps d'attente total : %d \n", temps_attente_total);
    printf("Temps d'attente moyen : %.2f \n", (float)temps_attente_total / (float)n);
    
     printf("\n \n digramme de gant (Round Robin) \n");   
    afficher(nombre_processus, tableau);


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

    Processus processus[100],copieProcessus[100]; 
    int n;
    int quantum = atoi(argv[2]); 
    lireFichierConfig(argv[1],processus, &n);

	for (int i=0;i<n;i++){
	copieProcessus[i]=processus[i];
	}

    executerRoundRobin(processus, n, quantum,copieProcessus);
    return 0;
}

            
