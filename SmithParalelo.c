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
long tamSequenciaA, tamSequenciaB, maxI, maxJ;

void alocarMatriz(){

	matrizValores = malloc((tamSequenciaA*tamSequenciaB) * sizeof(smithWaterman));           //aloca um vetor de ponteiros

	for (int i = 0; i < tamSequenciaA; ++i){
		for (int j = 0; j < tamSequenciaB; ++j) {
			matrizValores[i * tamSequenciaA + j].valor = 1;
      		matrizValores[i * tamSequenciaA + j].origem = 1;
		}
	}

	for (int i = 0; i < tamSequenciaA; ++i){
		matrizValores[i * tamSequenciaA].valor = 0;
		matrizValores[i * tamSequenciaA].origem = 0;
	}

	for (int i = 0; i < tamSequenciaA; ++i){
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

	fscanf(arq, "%ld %ld", &tamSequenciaA, &tamSequenciaB);

	tamSequenciaA++;
	tamSequenciaB++;

 	sequenciaA = malloc((tamSequenciaA * 2) * sizeof(char));
 	sequenciaB = malloc((tamSequenciaB * 2) * sizeof(char));

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

 	max_i = tamSequenciaA - 1;
	
	for(int i = 0; i < 2*tamSequenciaA - 1; i++){
		printf("NOVA DIAGONAL:\n");

		if((tamSequenciaA - 1 - i) >= 0)
		{
			#pragma omp parallel for firstprivate(score, diagonal, topo, esquerda)
			for(int j = 0; j <= i; j++){
				
				int flagI = i - j;
				if(matrizValores[flagI * tamSequenciaA + j].valor == 1){
		               score = sequenciaB[flagI - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
					diagonal.valor = matrizValores[(flagI - 1) * tamSequenciaA + (j - 1)].valor + score;
					topo.valor = matrizValores[(flagI - 1) * tamSequenciaA + j].valor + GAP;
					esquerda.valor = matrizValores[flagI * tamSequenciaA + (j - 1)].valor + GAP;
					matrizValores[flagI * tamSequenciaA + j] = maxValor(diagonal, topo, esquerda);
				        	#pragma omp critical
		        	{
						if(matrizValores[flagI * tamSequenciaA + j].valor >= matrizValores[maxI * tamSequenciaA + maxJ].valor){
		        				maxI = flagI;
		       					maxJ = j;
		       			}
					} 
				}
			}
			printf("\n\n\n\n");
		
		} else {

			int min_i = abs(2*tamSequenciaA - i - 1 - max_i);
				
			#pragma omp parallel for firstprivate(score, diagonal, topo, esquerda)
			for (int j = max_i; j > min_i ; j--){
			
				int flagI = i - j;
				if(matrizValores[flagI * tamSequenciaA + j].valor == 1){
					printf("THREAD:%d  -  MATRIZ[%d][%d]\n", omp_get_thread_num(), flagI, j);
	                score = sequenciaB[flagI - 1] == sequenciaA[j - 1] ? MATCH : MISMATCH;
					diagonal.valor = matrizValores[(flagI - 1) * tamSequenciaA + (j - 1)].valor + score;
					topo.valor = matrizValores[(flagI - 1) * tamSequenciaA + j].valor + GAP;
					esquerda.valor = matrizValores[flagI * tamSequenciaA + (j - 1)].valor + GAP;
					matrizValores[flagI * tamSequenciaA + j] = maxValor(diagonal, topo, esquerda);
	
		        	#pragma omp critical
		        	{
						if(matrizValores[flagI * tamSequenciaA + j].valor >= matrizValores[maxI * tamSequenciaA + maxJ].valor){
		        				maxI = flagI;
		       					maxJ = j;
		       			}
					} 
				
				}
			}
			printf("\n\n\n\n");
		}
	}
}


char *insertChar(char *string, char *ch, int pos){
	char *buffer;
    int tam;

    buffer = malloc((strlen(string) * 2) * sizeof(char));

	strncpy(buffer, string, pos);
    tam = strlen(buffer);
    strcpy(buffer + tam, ch);
    tam++;
    strcpy(buffer + tam, string + pos);

    strcpy(string, buffer); 

    free(buffer);

    return string;
}

void backtrace(long maiorElemento){
  //char *ch;

  // ch = '-';

  while(matrizValores[maxI * tamSequenciaA + maxJ].valor > 0){
    
    if(matrizValores[maxI * tamSequenciaA + maxJ].origem == DIAGONAL){

      	maxI--;
      	maxJ--;
    
    } else if(matrizValores[maxI * tamSequenciaA + maxJ].origem == TOPO){
   
      	sequenciaA = insertChar(sequenciaA, "-", maxJ);

      	maxI--;

   	} else if(matrizValores[maxI * tamSequenciaA + maxJ].origem == ESQUERDA){
       
   		sequenciaB = insertChar(sequenciaB, "-", maxI);

      	maxJ--;
    }

  }

  printf("%s\n", sequenciaA);
  printf("%s\n", sequenciaB);
}

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
	int nIteracao;
  	long maiorElemento;
  	double start, end;

	nomeArq = argv[1];
	nIteracao = argv[2] == NULL ? 1 : atoi(argv[2]);
	
	lerSequencias(nomeArq);

	alocarMatriz();

	calcSmithWaterman();
	
  	imprimeMat(matrizValores);


 //  	start = omp_get_wtime();

	// for(i = 0; i < nIteracao; i++){	
	// 	calcSmithWaterman();	
	// }

	// printf("\n\n\n");


	// backtrace(maiorElemento);

 // 	end = omp_get_wtime();

 // 	printf("TEMPO: %lf\n", end - start);

 // 	free(sequenciaA);
 // 	free(sequenciaB);
 // 	free(matrizValores);

	return(0); 
}