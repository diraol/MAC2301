/*
 * escreve_arvore-tela.cpp
 *
 *  Created on: 03/05/2010
 *      Author: diraol
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "escreve_arvore_tela.h"

int TamanhoDoNoh(Noh Raiz){
	int tamanho = 1;
	while(Raiz.valor/10){
		tamanho++;
	}
	return tamanho;
}

int TrataSubArvore(Noh* raiz, int deslocamento){
	if(raiz == 0)
		return 0;

	if(raiz->esquerda){
		int larguraDaEsquerda = TrataSubArvore(raiz->esquerda, deslocamento);
		raiz->posicao = larguraDaEsquerda + 1;

		if(raiz->direita){ // Possui raiz direita e esquerda
			int larguraDaDireita = TrataSubArvore(raiz->direita, raiz->posicao + TamanhoDoNoh(*raiz) + 1);
			return (raiz->posicao + TamanhoDoNoh(*raiz) + 1 + larguraDaDireita + 1);

		}else{ // Possui apenas raiz esquerda
			return (raiz->posicao + TamanhoDoNoh(*raiz) + 1);
		}
	}else{ // Não tem raiz esquerda
		raiz->posicao = deslocamento;

		if(raiz->direita){ // Possui apenas raiz direita
			int larguraDaDireita = TrataSubArvore(raiz->direita, raiz->posicao + TamanhoDoNoh(*raiz) + 1);
			return (raiz->posicao + TamanhoDoNoh(*raiz) + 1 + larguraDaDireita + 1);

		}else{ // Não possui raizes
			return TamanhoDoNoh(*raiz);
		}
	}
}

void TrateArvore(Arvore* a){
	TrataSubArvore(a->raiz, 0);
}
