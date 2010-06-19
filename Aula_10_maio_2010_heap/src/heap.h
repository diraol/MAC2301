/*
 * heap.h
 *
 *  Created on: 10/05/2010
 *      Author: diraol
 */

#ifndef HEAP_H_
#define HEAP_H_

struct Heap{
	int* itens;
	int nalocados;
	int nusados;
};

void TrocaItens(Heap* h, int item1, int item2);
bool ComparaPaiEFilhos(Heap h, int pai, bool* TrocaComEsquerda);
	// retorna 0 se não é preciso trocar
	// retorna 1 se precisa trocar com o filho da esquerda
	// retorna 2 se precisa trocar com o filho da direita
void Inicia(Heap* h);
void Insira(Heap* h, int n);
int Pop(Heap* h);
bool EstahVazia(Heap h);

#endif /* HEAP_H_ */
