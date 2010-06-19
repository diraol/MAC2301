/*
 * heap.cpp
 *
 *  Created on: 10/05/2010
 *      Author: DiRaOL
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>
#include "heap.h"

void TrocaItens(Heap* h, int item1, int item2){
	int aux = h->itens[item1];
	h->itens[item1] = h->itens[item2];
	h->itens[item2] = aux;
}

bool ComparaPaiEFilhos(Heap h, int pai, bool* TrocaComEsquerda){
	// retorna 0 se não é preciso trocar
	// retorna 1 se precisa trocar com o filho da esquerda
	// retorna 2 se precisa trocar com o filho da direita
	bool TemQueTrocar = false;

	if(pai*2+1 <= h.nusados){ //Verificando se é preciso realizar alguma troca caso existam 2 filhos
		int filho1 = pai*2;
		int filho2 = pai*2+1;

		if(h.itens[filho1] >= h.itens[filho2]){ //Caso filho 1 maior que filho 2
			if(h.itens[pai] < h.itens[filho1]){ //Tem que trocar pai com o filho 1
				TemQueTrocar = true;
				*TrocaComEsquerda = true;
			}
		} else {
			if(h.itens[pai] < h.itens[filho2]){ //Tem que trocar pai com o filho 2
				TemQueTrocar = true;
				TrocaComEsquerda = false;
			}
		}

	} else if(pai*2 <= h.nusados){ //Verificando se é preciso realizar alguma troca caso exista apenas 1 filho
		int filho1 = pai*2;
		if(h.itens[pai] < h.itens[filho1]) //Não em que trocar pai com o filho 1
			TemQueTrocar = true;
			*TrocaComEsquerda = true;
	}

	return TemQueTrocar;
}

void Inicia(Heap* h){
	h->nalocados = 4;
	h->itens = (int*)malloc(h->nalocados * sizeof(int));
	h->nusados = 0;
}

void Insira(Heap* h, int n){

	//Primeiro, caso o vetor esteja completamente cheio eu dobro o tamanho dele;
	if(h->nusados +1 == h->nalocados){
		h->nalocados *=2;
		int* temp = (int*)malloc(h->nalocados * sizeof(int));
		memcpy(temp, h->itens, h->nusados * sizeof(int));
		free(h->itens);
		h->itens = temp;
	}

	//Agora insere o item no vetor;
	int novo = h->nusados + 1;
	int pai = novo/2;

	h->itens[novo] = n; //Insere o novo item no fim vetor
	h->nusados = novo; //Atualiza o numero de usados;

	while(h->itens[novo] > h->itens[pai] && pai!=0){
		TrocaItens(h, pai, novo);
		novo = pai;
		pai = pai/2;
	}

}

int Pop(Heap* h){
	int retorno = h->itens[1]; //remove o primeiro item (maior)
	h->itens[1] = h->itens[h->nusados]; //coloca o último em primeiro
	h->nusados = h->nusados-1; //atualiza o número de utilizados

	int pai = 1;//define o novo primeiro item como pai, que deve ser estudado

	bool TrocaComEsquerda = true; //Se TRUE troca pai com o filho da esquerda
							//Se FALSE troca o pai com o filho da direita
	bool TemQueTrocar = ComparaPaiEFilhos(*h, pai, &TrocaComEsquerda);

	while(TemQueTrocar){
		if(TrocaComEsquerda){
			TrocaItens(h, pai, pai*2);
			pai = pai*2;
		}else{
			TrocaItens(h, pai, (pai*2+1));
			pai = pai*2 + 1;
		}
		TemQueTrocar = ComparaPaiEFilhos(*h, pai, &TrocaComEsquerda);
	}

	return retorno;
}

bool EstahVazia(Heap h){

	if(h.nusados == 0)
		return true;
	else
		return false;
}
