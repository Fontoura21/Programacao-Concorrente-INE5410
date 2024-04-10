#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Global Definitions
#define TEMPO_BASE 1000000

typedef enum { 
	CONTINENTE, 
	ILHA 
} cabeceira_t;

typedef struct {
	int id;
	cabeceira_t cabeceira;
	pthread_t thread;
} veiculo_t;

// Global Variables
char cabeceiras[2][11] = { "CONTINENTE", "ILHA" };
int total_veiculos;
int veiculos_turno;
int veiculos_na_ponte;
sem_t semaforo_continente, semaforo_ilha, mutex;

// Initialize the bridge state
void ponte_inicializar() {
	sem_init(&semaforo_continente, 0 , veiculos_turno);
	sem_init(&semaforo_ilha, 0 , 0);
	sem_init(&mutex, 0 , 1);

	printf("\n[PONTE] *** Novo sentido da travessia: CONTINENTE -> ILHA. ***\n\n");
	fflush(stdout);
}
// Vehicle enters the bridge from a specific side
void ponte_entrar(veiculo_t *v) {
	if (!strcmp(cabeceiras[v->cabeceira], "CONTINENTE")) {
		sem_wait(&semaforo_continente);
		sem_wait(&mutex);
		veiculos_na_ponte++;
		sem_post(&mutex);

	} else {
		sem_wait(&semaforo_ilha);
		sem_wait(&mutex);
		veiculos_na_ponte++;
		sem_post(&mutex);
	}
}

// Vehicle exits the bridge
void ponte_sair(veiculo_t *v) {
	sem_wait(&mutex);
	veiculos_na_ponte--;

	if (veiculos_na_ponte == 0) {	
		printf("\n[PONTE] *** Novo sentido da travessia: %s -> %s. ***\n\n", cabeceiras[v->cabeceira], cabeceiras[!v->cabeceira]);
		fflush(stdout);
		
		for (int i = 0; i < veiculos_turno; i++) {
			if (!strcmp(cabeceiras[v->cabeceira], "ILHA")) {
				sem_post(&semaforo_ilha);
			} else {
				sem_post(&semaforo_continente);
			}
		}
	}
	sem_post(&mutex);
}

// Clean up bridge resources
void ponte_finalizar() {
	sem_destroy(&semaforo_continente);
	sem_destroy(&semaforo_ilha);
	sem_destroy(&mutex);
	printf("[PONTE] FIM!\n\n");
	fflush(stdout);

}



// Main vehicle function
void * veiculo_executa(void *arg) {
	veiculo_t *v = (veiculo_t *) arg;
	printf("[Veiculo %3d] Aguardando para entrar na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);
	ponte_entrar(v);
	printf("[Veiculo %3d] ENTROU na ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);
	usleep(TEMPO_BASE + rand() % 1000);
	v->cabeceira = !v->cabeceira;
	printf("[Veiculo %3d] SAIU da ponte pelo(a) %s.\n", v->id, cabeceiras[v->cabeceira]);
	fflush(stdout);
	ponte_sair(v);
	pthread_exit(NULL);
}




int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Indique a quantidade total de veiculos e o numero de veiculos que podem atravessar a ponte por turno:\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}

	total_veiculos = atoi(argv[1]);
	veiculos_turno = atoi(argv[2]);

	if (total_veiculos % (veiculos_turno * 2)) {
		printf("ERRO: O valor [QTD_TOTAL_VEICULOS] deve ser divisivel por ([VEICULOS_POR_TURNO] * 2)!\n\n %s [QTD_TOTAL_VEICULOS] [VEICULOS_POR_TURNO]\n\n", argv[0]);
		return 1;
	}


	srand(time(NULL));

	veiculo_t veiculos[total_veiculos];
	ponte_inicializar();

	for (int i = 0; i < total_veiculos; i++) {
		veiculos[i].id = i;
		veiculos[i].cabeceira = i % 2;
		pthread_create(&veiculos[i].thread, NULL, veiculo_executa, (void *) &veiculos[i]);		
	}

	for (int i = 0; i < total_veiculos; i++) {
		pthread_join(veiculos[i].thread, NULL);
	}

	ponte_finalizar();

	return 0;
}
