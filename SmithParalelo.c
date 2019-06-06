/*-------------------------------------------------------------------------------------------------------
  Annelyse Schatzmann - GRR20151731
  Eduardo Zimermam Pereira - GRR20152952  
-------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define MATCH      2
#define MISMATCH  -1
#define GAP       -1

#define TOPO     3
#define DIAGONAL 2
#define ESQUERDA 1

typedef struct smithWaterman {
  int valor;
  int origem;
} smithWaterman;

char *sequenciaA, *sequenciaB, *alinhamentoA, *alinhamentoB;
smithWaterman *matrizValores;
int tamSequencia, maxI, maxJ, tamAlinOtimos;

void alocarMatriz(){

	matrizValores = malloc((tamSequencia*tamSequencia) * sizeof(smithWaterman));           //aloca um vetor de ponteiros

	for (int i = 0; i < tamSequencia; ++i){
		for (int j = 0; j < tamSequencia; ++j) {
			matrizValores[i * tamSequencia + j].valor = 1;
      		matrizValores[i * tamSequencia + j].origem = 1;
		}
	}

	for (int i = 0; i < tamSequencia; ++i){
		matrizValores[i * tamSequencia].valor = 0;
		matrizValores[i * tamSequencia].origem = 0;
	}

	for (int i = 0; i < tamSequencia; ++i){
		matrizValores[i].valor = 0;
		matrizValores[i].origem = 0;
	}
}

void lerSequencias(char *nomeArq){
	FILE *arq;

	arq = fopen(nomeArq, "r");    

	if ( !arq ){
	  perror("Erro ao abrir arquivo") ;
	  exit(1);
	}

	fscanf(arq, "%d", &tamSequencia);

	tamSequencia++;
	
 	sequenciaA = malloc((tamSequencia * 2) * sizeof(char));
 	sequenciaB = malloc((tamSequencia * 2) * sizeof(char));

	fscanf(arq, "%s", sequenciaA);
  	fscanf(arq, "%s", sequenciaB); 
  	
  	fclose(arq);
}

smithWaterman maxValor(smithWaterman a, smithWaterman b, smithWaterman c){
	smithWaterman max;

  	max.valor = 0;
 	max.origem = 0;

	max = max.valor > a.valor ? max : a;
	max = max.valor > b.valor ? max : b;
	max = max.valor > c.valor ? max : c;
 
	return max; 
}


void calcSmithWaterman() {

    int score, max_i;
 	smithWaterman diagonal, topo, esquerda;

 	diagonal.origem = DIAGONAL;
 	topo.origem = TOPO;
 	esquerda.origem = ESQUERDA;
 	score = 0;

 	max_i = tamSequencia - 1;
	
	for(int i = 0; i < 2*tamSequencia - 1; i++){
		if((tamSequencia - 1 - i) >= 0){
			#pragma omp parallel for firstprivate(score, diagonal, topo, esquerda)
			for(int j = 0; j <= i; j++){
				int flagI = i - j;
				if(matrizValores[flagI * tamSequencia + j].valor == 1){
		            score = sequenciaB[flagI - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
					diagonal.valor = matrizValores[(flagI - 1) * tamSequencia + (j - 1)].valor + score;
					topo.valor = matrizValores[(flagI - 1) * tamSequencia + j].valor + GAP;
					esquerda.valor = matrizValores[flagI * tamSequencia + (j - 1)].valor + GAP;
					matrizValores[flagI * tamSequencia + j] = maxValor(diagonal, topo, esquerda);
				    
					if(matrizValores[flagI * tamSequencia + j].valor >= matrizValores[maxI * tamSequencia + maxJ].valor){
				   		#pragma omp critical
		        		{
		        			maxI = flagI;
		       				maxJ = j;
		       			}
					} 
				}
			}
		}else {

			int min_i = abs(2*tamSequencia - i - 1 - max_i);
				
			#pragma omp parallel for firstprivate(score, diagonal, topo, esquerda)
			for (int j = max_i; j > min_i ; j--){
				int flagI = i - j;
				if(matrizValores[flagI * tamSequencia + j].valor == 1){
					score = sequenciaB[flagI - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
					diagonal.valor = matrizValores[(flagI - 1) * tamSequencia + (j - 1)].valor + score;
					topo.valor = matrizValores[(flagI - 1) * tamSequencia + j].valor + GAP;
					esquerda.valor = matrizValores[flagI * tamSequencia + (j - 1)].valor + GAP;
					matrizValores[flagI * tamSequencia + j] = maxValor(diagonal, topo, esquerda);
	
					if(matrizValores[flagI * tamSequencia + j].valor >= matrizValores[maxI * tamSequencia + maxJ].valor){
		        		#pragma omp critical
		        		{
		        			maxI = flagI;
		       				maxJ = j;
		       			}
					} 
				
				}
			}
		}
	}
}


void backtrace(){
	char ch = '-';

  	tamAlinOtimos = 0;

	alinhamentoA = malloc((tamSequencia * 2) * sizeof(char));
	alinhamentoB = malloc((tamSequencia * 2) * sizeof(char));

  	while(matrizValores[maxI * tamSequencia + maxJ].valor != 0){

	    if(matrizValores[maxI * tamSequencia + maxJ].origem == DIAGONAL){

	    	alinhamentoA[tamAlinOtimos] = sequenciaA[maxJ-1];
	    	alinhamentoB[tamAlinOtimos] = sequenciaB[maxI-1];

	      	maxI--;
	      	maxJ--;
	    } else if(matrizValores[maxI * tamSequencia + maxJ].origem == TOPO){
	   
	      	alinhamentoA[tamAlinOtimos] = ch;
			alinhamentoB[tamAlinOtimos] = sequenciaB[maxI-1];

	      	maxI--;

	   	} else if(matrizValores[maxI * tamSequencia + maxJ].origem == ESQUERDA){
	       
	   		alinhamentoA[tamAlinOtimos] = sequenciaA[maxJ-1];
			alinhamentoB[tamAlinOtimos] = ch;
		
	      	maxJ--;
	    }

	    tamAlinOtimos++;
	}
}

void imprimeAlinhamentosOtimos(){
	for (int j = 0; j < tamAlinOtimos; j++){
  		printf("%c", alinhamentoA[j]);
	}
	printf("\n");
	
	for (int j = 0; j < tamAlinOtimos; ++j){
  		printf("%c", alinhamentoB[j]);
	}
	printf("\n");
}

void imprimeMat(smithWaterman *mat){

    printf("MATRIZ DE VALORES:\n");

  	for (int i = 0; i < tamSequencia; ++i){
  		for (int j = 0; j < tamSequencia; ++j){
  			printf("%d ", mat[i * tamSequencia + j].valor);
  		}
  		printf("\n");
  	}

    printf("\n\n\n");

    printf("MATRIZ DE ORIGENS:\n");

    for (int i = 0; i < tamSequencia; ++i){
     	for (int j = 0; j < tamSequencia; ++j){
        	printf("%d ", mat[i * tamSequencia + j].origem);
      	}
      printf("\n");
    }
}


int main(int argc, char **argv){
  
	char *nomeArq;
  	double start, end;

	nomeArq = argv[1];
	
	lerSequencias(nomeArq);

	alocarMatriz();
 	
  	start = omp_get_wtime();

	calcSmithWaterman();	

	backtrace();

 	end = omp_get_wtime();

 	printf("TEMPO: %lf\n", end - start);

  	free(sequenciaA);
 	free(sequenciaB);
 	free(alinhamentoA);
 	free(alinhamentoB);
 	free(matrizValores);

	return(0); 
}