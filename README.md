# Algoritmo de Smith-Waterman

Trabalho apresentado a matéria de Programação Paralela do curso de Informática Biomédica da Univerdade Federal do Paraná.

A implementação do algoritmo é realizada em duas versões, sendo a nomeada como SmithSequencial.c uma implementação sequencial otimizada do algoritmo e o arquivo SmithParalelo.c a implementação paralela utilizando OpenMP.

Esta implementação foi realizada puramente para experimentação, tentando representar o real funcionamento do algoritmo, porém para sequências pequenas, de no máximo 26000 bases. Neste caso, usamos um *loop for* para que o cálculo do algoritmo fosse processado diversas vezes, a fim de conseguir obter um tempo suficientemente razoável para realizar as experimentações e também as comparações entre versão sequencial e versão paralela.

### Compilando o projeto

Todo o algoritmo foi desenvolvimento usando a linguagem C, sendo que outros arquivos adicionais serão apresentados mais adiante, para compilação, execute o comando:

```bash
	make
```


Para limpar o diretório de arquivos *.o* e deixar apenas os executaveis:

```bash
	make clean
```


Para limpar todo o diretório, removendo inclusive os executáveis:
```bash
	make purge
```


### Outros arquivos

O repositório ainda conta com os seguintes arquivos:

**script.sh:** Arquivo que contém toda a execução de todas as iterações necessárias para o projeto. Este arquivo mantém a mesma execução que obtivemos os resultados.

**script_metricas.py:** Arquivo com todos os cálculos de métricas utilizados, inclusive os tempos que obtivemos na máquina usada para os testes. O Modelo da máquina usada para os testes pode ser vista no arquivo **script.sh**.

**Diretório examples:** Diretório com as sequências usadas para executar os testes, as sequências são uma de rato e a outra do molusco aruá, sendo que são as mesmas sequências nos 3 arquivos diferentes para cada animal, porém com quantidades de bases diferentes, sendo 6.500 bases, 13.000 bases e 26.000 bases.