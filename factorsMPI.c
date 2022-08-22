#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int rank, size;                             //declaramos las variablas que identificaran el tamaño y la ubicación de los procesos
	MPI_Init(&argc, &argv);                     //iniciamos MPI
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);       //identificamos cada proceso
	MPI_Comm_size(MPI_COMM_WORLD, &size);       //Numero de procesos
	
	//printf("I am %d of %d\n", rank, size);
	
	int num;
	
	if (rank == 0){                              //Este es el procesador 0 
		printf("Enter a positive integer: ");
		scanf("%d", &num);
		
		printf("Factors of %d are:\n", num);
		
		// Send number to other processes
		for (int dest = 1; dest < size; dest++){
			int rc;
			rc = MPI_Send(&num, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);    //Envia el numero que se desea factorizar a los otros procesadores
		}
	} else{
		MPI_Status Stat;
		
		int rc;
		rc = MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &Stat);     //Todos los procesadores reciben el numero a factorizar
	}
	
	// Test different numbers in each processor
	for (int i = rank+1; i <= num; i+=size) {                             //Todos los procesadores entran en un ciclo for que aumenta segun el tamaño de numero de procesos
        if (num % i == 0) {                                               //cada procesador divide el numero a factorizar entre un numero diferente y asi encuentran todos los numeros
            printf("%d ", i);
        }
    }
	
	MPI_Finalize();
	return 0;
}
