#!/bin/bash

echo -e

# echo "Iniciando o processamento em Intel(R) Core(TM) i7-4770 CPU @ 3.40GHz"
echo "Iniciando o processamento em Intel(R) Core(TM) i5-7500 CPU @ 3.40GHz"

echo -e

echo "Executando 20 vezes o sequencial 6k..."
for i in {1..20}; do ./smithSequencial examples/SeqArua6k.txt 30; done > resultados/sequencialArua6k.txt

echo "Executando 20 vezes o sequencial 13k..."
for i in {1..20}; do ./smithSequencial examples/SeqArua13k.txt 30; done > resultados/sequencialArua6k.txt


echo "Executando 20 vezes o sequencial 26k"
for i in {1..20}; 
do ./smithSequencial examples/SeqArua26k.txt 30; done > resultados/sequencialArua26k.txt

echo -e

export OMP_NUM_THREADS=2

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando 20 vezes o paralelo 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_2th.txt


echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_2th.txt


echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_2th.txt

echo -e

export OMP_NUM_THREADS=4

echo "Processamento paralelo sendo feito com $OMP_NUM_THREADS threads"

echo "Executando 20 vezes o paralelo 6k"
for i in {1..20}; do ./smithParalelo examples/SeqArua6k.txt 30; done > resultados/paraleloArua_6k_4th.txt


echo "Executando 20 vezes o paralelo 13k"
for i in {1..20}; do ./smithParalelo examples/SeqArua13k.txt 30; done > resultados/paraleloArua_13k_4th.txt


echo "Executando 20 vezes o paralelo 26k"
for i in {1..20}; do ./smithParalelo examples/SeqArua26k.txt 30; done > resultados/paraleloArua_26k_4th.txt