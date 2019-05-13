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
int tamSequenciaA, tamSequenciaB, posMaiorElem;

void alocarMatriz(){

 matrizPosicao = calloc(tamSequenciaA*tamSequenciaB, sizeof(int));           //aloca um vetor de ponteiros
 matrizValores = calloc(tamSequenciaA*tamSequenciaB, sizeof(int));           //aloca um vetor de ponteiros
}

void lerSequencias(char *nomeArq){
  FILE *arq;
  char seqArquivo[500000], buffer[500000];

  arq = fopen(nomeArq, "r");    

  if ( !arq ){
    perror("Erro ao abrir arquivo") ;
    exit(1);
  }

  strcpy(buffer, "x");

  fscanf(arq, "%s", seqArquivo);
  strcat(buffer, seqArquivo);
  sequenciaA = malloc(strlen(buffer) * sizeof(char));
  strcpy(sequenciaA, buffer);
  tamSequenciaA = strlen(sequenciaA);

  strcpy(buffer, "x");

  fscanf(arq, "%s", seqArquivo);
  strcat(buffer, seqArquivo);
  sequenciaB = malloc(strlen(buffer) * sizeof(char));
  strcpy(sequenciaB, buffer);
  tamSequenciaB = strlen(sequenciaB);

  fclose(arq);
}

int maxDirecao(int diag, int topo, int esq, int posVetor){
  int max = diag;

  matrizPosicao[posVetor] = DIAGONAL;

  if(topo > max){
    max = topo;
    matrizPosicao[posVetor] = TOPO;   
  }

  if(esq > max){
    max = esq;
    matrizPosicao[posVetor] = ESQUERDA;
  }

  return max;
}

void calcSmithWaterman(){

 int i, j, diag, topo, esq;
 int score;
 int max = 0;

  for(j = 1; j < tamSequenciaA; j++){
    score = sequenciaB[1] == sequenciaA[j] ? MATCH : MISMATCH;
    diag = matrizValores[j - 1] + score;
    topo = matrizValores[j] + GAP;
    esq = matrizValores[tamSequenciaA + (j - 1)] + GAP;
    matrizValores[tamSequenciaA + j] = maxDirecao(diag, topo, esq, tamSequenciaA + j);
    
    if(matrizValores[tamSequenciaA + j] > matrizValores[posMaiorElem])
      posMaiorElem = tamSequenciaA + j;
  }

  for(i = 2; i < tamSequenciaB; i++){
    for(j = 1; j < tamSequenciaB; j++){
      score = sequenciaB[i] == sequenciaA[j] ? MATCH : MISMATCH;
      diag = matrizValores[(tamSequenciaA * (i - 1)) + (j - 1)] + score;
      topo = matrizValores[(tamSequenciaA * (i - 1)) + j] + GAP;
      esq = matrizValores[(tamSequenciaA * i) + (j - 1)] + GAP;
      matrizValores[(tamSequenciaA * i) + j] = maxDirecao(diag, topo, esq, (tamSequenciaA * i) + j);
      
      if(matrizValores[(tamSequenciaA * i) + j] > matrizValores[posMaiorElem])
        posMaiorElem = (tamSequenciaA * i) + j;
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

	backtrace();

  end = omp_get_wtime();

  printf("TEMPO: %lf\n", end - start);

	return(0); 
}