#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nom_processus[20];
    int date_arrivee;
    int duree_cycles;
    int priorite;
} Processus;

void genererFichierConfig(int n, int debut, int fin, int debutDuree, int finDuree, int debutPriorite, int finPriorite) {
    FILE *fichier = fopen("config.txt", "w");
    for (int i = 0; i < n; i++) {
        int date_arrivee = rand() % (fin - debut + 1) + debut;
        int priorite = rand() % (finPriorite - debutPriorite + 1) + debutPriorite;
        int duree_cycles = rand() % (finDuree - debutDuree + 1) + debutDuree;

        fprintf(fichier, "P%d %d %d %d\n", i + 1, date_arrivee, duree_cycles, priorite);
    }
    fclose(fichier);
}

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("Usage: %s <nb_processus> <debutArrivee> <finArrivee> <debutDuree_cycle> <finDuree_cycle> <debutPriorite> <finPriorite>\n", argv[0]);
        return 1;
    }
    int nb_processus = atoi(argv[1]);
    int debut = atoi(argv[2]);
    int fin = atoi(argv[3]);
    int debutDuree = atoi(argv[4]);
    int finDuree = atoi(argv[5]);
    int debutPriorite = atoi(argv[6]);
    int finPriorite = atoi(argv[7]);
    genererFichierConfig(nb_processus, debut, fin, debutDuree, finDuree, debutPriorite, finPriorite);

    printf("Fichier de configuration généré avec succès.\n");

    return 0;
}

