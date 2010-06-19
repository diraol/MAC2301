//============================================================================
// Name        : Aula_10_maio_2010_heap.cpp
// Author      : DiRaOL
// Version     :
// Copyright   : GPL v3 or later
// Description : Aula de MAC2310 de 10/05/2010 - Árvore HEAP
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "heap.h"

int main() {
	Heap h;
	Inicia(&h);

	printf("Inserindo:\n");
	for(int i=1; i<=10; i++){
		int n = rand()%100;
		printf(" - %d\n", n);
		Insira(&h, n);
	}
	printf("Acabou de inserir todos\n");
	printf("Retirando...\n");
	while(!EstahVazia(h)){
		printf("%d, ", Pop(&h));
	}
	getchar();

	return 0;
}
