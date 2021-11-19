

#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[]) {
    int rang, iter;
    int const nb_valeurs = 1000;
    int etiquette = 99;
    double valeurs[nb_valeurs];
    MPI_Status statut;
    double temps_debut, temps_fin;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rang);

    if (rang == 0) {
        for (iter = 0; iter < nb_valeurs; iter++)
            valeurs[iter] = rand() / (RAND_MAX + 1.);
        temps_debut = MPI_Wtime();
        MPI_Send(valeurs, nb_valeurs, MPI_DOUBLE, 1, etiquette, MPI_COMM_WORLD);
        MPI_Recv(valeurs, nb_valeurs, MPI_DOUBLE, 1, etiquette, MPI_COMM_WORLD, &statut);
        temps_fin = MPI_Wtime();
        printf("Moi, processus 0, j'ai envoye et recu %d valeurs"
            "(derniere = %g) du processus 1 en %f secondes.\n",
            nb_valeurs, valeurs[nb_valeurs - 1], temps_fin - temps_debut);
    }
    else if (rang == 1) {
        MPI_Recv(valeurs, nb_valeurs, MPI_DOUBLE, 0, etiquette, MPI_COMM_WORLD, &statut);
        MPI_Send(valeurs, nb_valeurs, MPI_DOUBLE, 0, etiquette, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
