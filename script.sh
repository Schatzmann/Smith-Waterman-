#!/bin/bash

echo -e

echo "Iniciando o processamento em Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz"

echo -e


# ------------------------------ TRECHO DE EXECUÇÃO PARA SEQUENCIAL N (6K) --------------------------------


echo "EXECUÇÃO DAS SEQUENCIAS COM TAMANHO N"
echo -e

echo "Executando os sequenciais 20 vezes para 6k..."
for i in {1..20}; do ./smithSequencial examples/SeqArua6k.txt 30; done > resultados/sequencialArua6k.txt
for i in {1..20}; do ./smithSequencial examples/SeqMouse6k.txt 30; done > resultados/sequencialMouse6k.txt

echo -e

export OMP_NUM_THREADS=2

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando os paralelos 20 vezes para 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_2th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse6k.txt 30; done > resultados/paraleloMouse_6k_2th.txt

echo -e

export OMP_NUM_THREADS=4

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando os paralelos 20 vezes para 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_4th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse6k.txt 30; done > resultados/paraleloMouse_6k_4th.txt

echo -e

export OMP_NUM_THREADS=8

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando os paralelos 20 vezes para 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_8th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse6k.txt 30; done > resultados/paraleloMouse_6k_8th.txt



echo -e

export OMP_NUM_THREADS=16

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando os paralelos 20 vezes para 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_16th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse6k.txt 30; done > resultados/paraleloMouse_6k_16th.txt


# ------------------------------ TRECHO DE EXECUÇÃO PARA SEQUENCIAL 2N (13K) --------------------------------


echo "EXECUÇÃO DAS SEQUENCIAS COM TAMANHO 2N"
echo -e

echo "Executando 20 vezes o sequencial 13k..."
for i in {1..20}; do ./smithSequencial examples/SeqArua13k.txt 30; done > resultados/sequencialArua13k.txt
for i in {1..20}; do ./smithSequencial examples/SeqMouse13k.txt 30; done > resultados/sequencialMouse13k.txt


export OMP_NUM_THREADS=2

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_2th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse13k.txt 30; done > resultados/paraleloMouse_13k_2th.txt


export OMP_NUM_THREADS=4

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_4th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse13k.txt 30; done > resultados/paraleloMouse_13k_4th.txt

echo -e

export OMP_NUM_THREADS=8

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_8th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse13k.txt 30; done > resultados/paraleloMouse_13k_8th.txt


echo -e

export OMP_NUM_THREADS=16

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_16th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse13k.txt 30; done > resultados/paraleloMouse_13k_16th.txt

# ------------------------------ TRECHO DE EXECUÇÃO PARA SEQUENCIAL 4N (26K) --------------------------------

echo "EXECUÇÃO DAS SEQUENCIAS COM TAMANHO 4N"
echo -e

echo "Executando 20 vezes o sequencial 26k"
for i in {1..20}; do ./smithSequencial examples/SeqArua26k.txt 30; done > resultados/sequencialArua26k.txt
for i in {1..20}; do ./smithSequencial examples/SeqMouse26k.txt 30; done > resultados/sequencialMouse26k.txt

echo -e

export OMP_NUM_THREADS=2

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_2th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse26k.txt 30; done > resultados/paraleloMouse_26k_2th.txt

echo -e

export OMP_NUM_THREADS=4

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_4th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse26k.txt 30; done > resultados/paraleloMouse_26k_4th.txt


echo -e

export OMP_NUM_THREADS=8

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_8th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse26k.txt 30; done > resultados/paraleloMouse_26k_8th.txt

echo -e

export OMP_NUM_THREADS=16

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo -e

echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_16th.txt
for i in {1..20}; do ./smithParalelo examples/SeqMouse26k.txt 30; done > resultados/paraleloMouse_26k_16th.txt