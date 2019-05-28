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

char *sequenciaA, *sequenciaB, *alinhamentoOtimoA, *alinhamentoOtimoB;
int *matrizValores, *matrizPosicao;
long tamSequenciaA, tamSequenciaB, posMaiorElem;

void alocarMatriz(){
	// matrizPosicao = malloc((tamSequenciaA*tamSequenciaB) * sizeof(int));           //aloca um vetor de ponteiros
	matrizValores = malloc((tamSequenciaA*tamSequenciaB) * sizeof(int));           //aloca um vetor de ponteiros


	for (int i = 0; i < tamSequenciaA; ++i){
		for (int j = 0; j < tamSequenciaB; ++j) {
			matrizValores[i * tamSequenciaA + j] = 0;
		
		}
	}
}

void lerSequencias(char *nomeArq){
	FILE *arq;
	char *seqArquivo, *buffer;
	long tamSeqA, tamSeqB;

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
  	buffer = malloc(tamSequenciaA * sizeof(char));

  	strcpy(buffer, "x");

	fscanf(arq, "%s", sequenciaA);
	strcat(buffer, sequenciaA);
	strcpy(sequenciaA, buffer);

	strcpy(buffer, "x");
  	
  	fscanf(arq, "%s", sequenciaB);
	strcat(buffer, sequenciaB);
	strcpy(sequenciaB, buffer);  	 
  	
  	fclose(arq);
}

int maxDirecao(int diag, int topo, int esq, int posVetor){
  int max = 0;

  // matrizPosicao[posVetor] = DIAGONAL;

  if(topo > max){
    max = topo;
    // matrizPosicao[posVetor] = TOPO;   
  }

  if(esq > max){
    max = esq;
    // matrizPosicao[posVetor] = ESQUERDA;
  }

  return max;
}

int maxValor(int a, int b, int c){
	int max = 0;

	max = max > a ? max : a;
	max = max > b ? max : b;
	max = max > c ? max : c;

	return max; 
}

void calcSmithWaterman(){

	int i, j, diag, topo, esq;
	int score;

	for(i = 1; i < tamSequenciaA; ++i){
		for(j = 1; j < tamSequenciaB; ++j){
			score = sequenciaB[i] == sequenciaA[j] ? MATCH : MISMATCH;
			diag = matrizValores[(i - 1) * tamSequenciaA + (j - 1)] + score;
			topo = matrizValores[(i - 1) * tamSequenciaA + j] + GAP;
			esq = matrizValores[i * tamSequenciaA + (j - 1)] + GAP;
			matrizValores[i * tamSequenciaA + j] = maxValor(diag, topo, esq);
		}
	}
}

 void backtrace(){
   int posVetor, i;
   char ch, *alinhamentoOtimoB, *alinhamentoOtimoA, lacuna, vazio;

   lacuna = '-';
   ch = ' ';

    alinhamentoOtimoA = (char*) malloc(strlen(sequenciaA) * sizeof(char));
    alinhamentoOtimoB = (char*) malloc(strlen(sequenciaB) * sizeof(char));
 	
 	strcpy(alinhamentoOtimoB, " ");
 	strcpy(alinhamentoOtimoA, " ");

   while(matrizPosicao[posMaiorElem] > 0){
      if(matrizPosicao[posMaiorElem] == DIAGONAL){

       posVetor = posMaiorElem / tamSequenciaB;

       ch = sequenciaB[posVetor];
       
       strncat(alinhamentoOtimoA, &ch, 1);
       strncat(alinhamentoOtimoB, &ch, 1);

       posMaiorElem = (posMaiorElem - tamSequenciaA) - 1;

     } 

     	if(matrizPosicao[posMaiorElem] == TOPO){
    
       //printf("ALINHAMENTO B: %s\n",alinhamentoOtimoB);
       posVetor = posMaiorElem / tamSequenciaB;
      
       strcat(alinhamentoOtimoA, &lacuna);

       ch = sequenciaB[posVetor];
       //printf("%c\n",ch);
       strncat(alinhamentoOtimoB, &ch, 1);
      
       posMaiorElem = posMaiorElem - tamSequenciaA;
    	}

     	if(matrizPosicao[posMaiorElem] == ESQUERDA){

       posVetor = posMaiorElem / tamSequenciaA;
    
       strcat(alinhamentoOtimoB, &lacuna);

       ch = sequenciaA[posVetor];
       strncat(alinhamentoOtimoA, &ch, 1);

       posMaiorElem = posMaiorElem - 1;
      }
   }

    for(i = strlen(alinhamentoOtimoA); i > -1; i--){
   		printf("%c", alinhamentoOtimoA[i]);
   	}

   	printf("\n");

   	for(i = strlen(alinhamentoOtimoB); i > -1; i--){
   		printf("%c", alinhamentoOtimoB[i]);
    }

    printf("\n");
  }



  void imprimeMat(int *mat){

  	for (int i = 0; i < tamSequenciaA; ++i){
  		for (int j = 0; j < tamSequenciaB; ++j){
  			printf("%d ", mat[i * tamSequenciaA + j]);
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

	// backtrace();

  	end = omp_get_wtime();

  	printf("TEMPO: %lf\n", end - start);

	return(0); 
}