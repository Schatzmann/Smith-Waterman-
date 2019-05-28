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
  long valor;
  long origem;
} smithWaterman;

char *sequenciaA, *sequenciaB, *alinhamentoOtimoA, *alinhamentoOtimoB;
smithWaterman *matrizValores;
long tamSequenciaA, tamSequenciaB;

void alocarMatriz(){

	matrizValores = malloc((tamSequenciaA*tamSequenciaB) * sizeof(smithWaterman));           //aloca um vetor de ponteiros

	for (int i = 0; i < tamSequenciaA; ++i){
		for (int j = 0; j < tamSequenciaB; ++j) {
			matrizValores[i * tamSequenciaA + j].valor = 0;
      matrizValores[i * tamSequenciaA + j].origem = 0;
		}
	}
}

void lerSequencias(char *nomeArq){
	FILE *arq;

	arq = fopen(nomeArq, "r");    

	if ( !arq ){
	  perror("Erro ao abrir arquivo") ;
	  exit(1);
	}

	fscanf(arq, "%ld %ld", &tamSequenciaA, &tamSequenciaB);

	tamSequenciaA++;
	tamSequenciaB++;

 	sequenciaA = malloc(tamSequenciaA * sizeof(char));
 	sequenciaB = malloc(tamSequenciaB * sizeof(char));

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

	int i, j;
	int score;

  smithWaterman diagonal, topo, esquerda;

  diagonal.origem = DIAGONAL;
  topo.origem = TOPO;
  esquerda.origem = ESQUERDA;

	for(i = 1; i < tamSequenciaA; ++i){
		for(j = 1; j < tamSequenciaB; ++j){
			score = sequenciaB[i - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
			diagonal.valor = matrizValores[(i - 1) * tamSequenciaA + (j - 1)].valor + score;
			topo.valor = matrizValores[(i - 1) * tamSequenciaA + j].valor + GAP;
			esquerda.valor = matrizValores[i * tamSequenciaA + (j - 1)].valor + GAP;
			matrizValores[i * tamSequenciaA + j] = maxValor(diagonal, topo, esquerda);
		}
	}
}

 // void backtrace(){
 //   int posVetor, i;
 //   char ch, *alinhamentoOtimoB, *alinhamentoOtimoA, lacuna, vazio;

 //   lacuna = '-';
 //   ch = ' ';

 //    alinhamentoOtimoA = (char*) malloc(strlen(sequenciaA) * sizeof(char));
 //    alinhamentoOtimoB = (char*) malloc(strlen(sequenciaB) * sizeof(char));
 	
 // 	strcpy(alinhamentoOtimoB, " ");
 // 	strcpy(alinhamentoOtimoA, " ");

 //   while(matrizPosicao[posMaiorElem] > 0){
 //      if(matrizPosicao[posMaiorElem] == DIAGONAL){

 //       posVetor = posMaiorElem / tamSequenciaB;

 //       ch = sequenciaB[posVetor];
       
 //       strncat(alinhamentoOtimoA, &ch, 1);
 //       strncat(alinhamentoOtimoB, &ch, 1);

 //       posMaiorElem = (posMaiorElem - tamSequenciaA) - 1;

 //     } 

 //     	if(matrizPosicao[posMaiorElem] == TOPO){
    
 //       //printf("ALINHAMENTO B: %s\n",alinhamentoOtimoB);
 //       posVetor = posMaiorElem / tamSequenciaB;
      
 //       strcat(alinhamentoOtimoA, &lacuna);

 //       ch = sequenciaB[posVetor];
 //       //printf("%c\n",ch);
 //       strncat(alinhamentoOtimoB, &ch, 1);
      
 //       posMaiorElem = posMaiorElem - tamSequenciaA;
 //    	}

 //     	if(matrizPosicao[posMaiorElem] == ESQUERDA){

 //       posVetor = posMaiorElem / tamSequenciaA;
    
 //       strcat(alinhamentoOtimoB, &lacuna);

 //       ch = sequenciaA[posVetor];
 //       strncat(alinhamentoOtimoA, &ch, 1);

 //       posMaiorElem = posMaiorElem - 1;
 //      }
 //   }

 //    for(i = strlen(alinhamentoOtimoA); i > -1; i--){
 //   		printf("%c", alinhamentoOtimoA[i]);
 //   	}

 //   	printf("\n");

 //   	for(i = strlen(alinhamentoOtimoB); i > -1; i--){
 //   		printf("%c", alinhamentoOtimoB[i]);
 //    }

 //    printf("\n");
 //  }

  void imprimeMat(smithWaterman *mat){

    printf("MATRIZ DE VALORES:\n");

  	for (int i = 0; i < tamSequenciaA; ++i){
  		for (int j = 0; j < tamSequenciaB; ++j){
  			printf("%ld ", mat[i * tamSequenciaA + j].valor);
  		}
  		printf("\n");
  	}

    printf("\n\n\n");

    printf("MATRIZ DE ORIGENS:\n");

    for (int i = 0; i < tamSequenciaA; ++i){
      for (int j = 0; j < tamSequenciaB; ++j){
        printf("%ld ", mat[i * tamSequenciaA + j].origem);
      }
      printf("\n");
    }

  }

int main(int argc, char **argv){
  
	char *nomeArq;
	int nIteracao, i;
    double start, end;

	nomeArq = argv[1];
	nIteracao = argv[2] == NULL ? 1 : atoi(argv[2]);
	
	lerSequencias(nomeArq);

	alocarMatriz();

  start = omp_get_wtime();

	for(i = 0; i < nIteracao; i++){	
		calcSmithWaterman();	
	}

  imprimeMat(matrizValores);

	// backtrace();

 	end = omp_get_wtime();

 	printf("TEMPO: %lf\n", end - start);

	return(0); 
}