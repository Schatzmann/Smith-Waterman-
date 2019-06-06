/*-------------------------------------------------------------------------------------------------------
  Annelyse Schatzmann - GRR20151731
  Eduardo Zimermam Pereira - GRR20152952  
------------------------------------------------------------------------------------------------------*/

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

#define MAXLEITURA 10000

typedef struct smithWaterman {
  int valor;
  int origem;
} smithWaterman;

char *sequenciaA, *sequenciaB, *alinhamentoA, *alinhamentoB;
int tamSequencia, maxI, maxJ, tamAlinOtimos;
smithWaterman *matrizValores;

void ajustaNovaMatriz(int tamAlocacao, smithWaterman *bufferColuna, smithWaterman *bufferLinha){

	matrizValores = malloc((tamAlocacao*tamAlocacao) * sizeof(smithWaterman));           //aloca um vetor de ponteiros

	for(int i = 1; i < tamAlocacao; ++i){
		for(int j = 1; j < tamAlocacao; ++j) {
			matrizValores[i * tamAlocacao + j].valor = 0;
     		matrizValores[i * tamAlocacao + j].origem = 0;
		}
	}

	for(int i = 0; i < tamAlocacao; ++i){
		matrizValores[i] = bufferLinha[i];
	}

	for(int i = 0; i < tamAlocacao; ++i){
		matrizValores[i * tamAlocacao] = bufferColuna[i];
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
	
 	sequenciaA = malloc(tamSequencia * sizeof(char));
 	sequenciaB = malloc(tamSequencia * sizeof(char));

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

void calcSmithWaterman(){

	int score;
	
 	smithWaterman diagonal, topo, esquerda;

	diagonal.origem = DIAGONAL;
	topo.origem = TOPO;
	esquerda.origem = ESQUERDA;
  

	for(int i = 1; i < tamSequencia; ++i){
		for(int j = 1; j < tamSequencia; ++j){
			score = sequenciaB[i - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
			diagonal.valor = matrizValores[(i - 1) * tamSequencia + (j - 1)].valor + score;
			topo.valor = matrizValores[(i - 1) * tamSequencia + j].valor + GAP;
			esquerda.valor = matrizValores[i * tamSequencia + (j - 1)].valor + GAP;
			matrizValores[i * tamSequencia + j] = maxValor(diagonal, topo, esquerda);

			if(matrizValores[i * tamSequencia + j].valor >= matrizValores[maxI * tamSequencia + maxJ].valor){
    	 		maxI = i;
     			maxJ = j;
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
 	int tamAlocacao, posicaoA, posicaoB;
  	double start, end;
  	smithWaterman *bufferLinha, *bufferColuna;

	nomeArq = argv[1];
	
	lerSequencias(nomeArq);

	posicaoA = 0;
	posicaoB = 0;

	if((posicaoA + MAXLEITURA) < tamSequencia && (posicaoB + MAXLEITURA) < tamSequencia){
		tamAlocacao = MAXLEITURA;
	} else {
		tamAlocacao = tamSequencia - posicaoA;
	}

	bufferLinha = malloc(tamAlocacao * sizeof(smithWaterman));
	bufferColuna = malloc(tamAlocacao * sizeof(smithWaterman));

	for(int i = 0; i < tamAlocacao; ++i){
		bufferLinha[i].origem = 0;
		bufferColuna[i].origem = 0;
		bufferLinha[i].valor = 0;
		bufferColuna[i].valor = 0;
	}

	while(posicaoA < tamSequencia && posicaoB < tamSequencia){
	
		ajustaNovaMatriz(tamAlocacao, bufferColuna, bufferLinha);
	
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

	 	if((posicaoA + MAXLEITURA) < tamSequencia && (posicaoB + MAXLEITURA) < tamSequencia){
			tamAlocacao = MAXLEITURA;
		} else {

			if((tamSequencia - posicaoA) < (tamSequencia - posicaoB))
				tamAlocacao = tamSequencia - posicaoA;
			else 
				tamAlocacao = tamSequencia - posicaoB;
		}
 	}

	return(0); 
}