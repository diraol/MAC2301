/*
 * escreve_arvore-tela.cpp
 *
 *  Created on: 03/05/2010
 *      Author: diraol
 */

#ifndef EAT_H
#define EAT_H

struct Noh{
	int posicao;
	int valor;
	Noh* direita;
	Noh* esquerda;
};

struct Arvore{
	Noh* raiz;
};

int TamanhoDoNoh(Noh Raiz);

int TrataSubArvore(Noh* raiz, int deslocamento);

void TrateArvore(Arvore* a);

#endif
