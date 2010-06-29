//============================================================================
// Name        : Arvores_Binarias.cpp
// Author      : DiRaOL
// Version     :
// Copyright   : CC-By-sa
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
using namespace std;

struct Node{
	int valor;
	int tam;
	Node* fe;
	Node* fd;
};

// Aloca e zera um Node
Node * aloca(){
	Node* novo;
	novo = (Node *) malloc(sizeof(Node));
	novo->tam=0;
	novo->valor=INT_MIN;
	novo->fd=0;
	novo->fe=0;
	return novo;
}

// Acha o valor do minimo elemento da sub-arvore
int fMin(Node * raiz){
	while (raiz->fe)
		raiz = raiz->fe;
	return raiz->valor;
}

// Funcao que faz o balanceamento da sub-arvore
// E retorna a resultante
Node * balanceia(Node * raiz){
	int ne=0, nd=0; //Numero de elementos de cada filho;
	int a=0, b=0; //Numero de elementos nos netos relevantes;
	Node * aux;

	if (!raiz)
		return NULL;
	if(raiz->fe)
		ne = raiz->fe->tam;
	if(raiz->fd)
		nd = raiz->fd->tam;

	if(3*ne+1 >= nd && 3*nd+1 >= ne) // ja balanceada
		return raiz;

	if(3*ne+1 < nd){ // rotacionar AHor
		aux = raiz->fd;
		if(aux->fd)
			a = aux->fd->tam;
		if(aux->fe)
			b = aux->fe->tam;

		// testar se uma rotacao simples NAO resolve
		if(3*a+1 < 1+ne+b)
			raiz->fd = rotHor(raiz->fd);

		raiz = rotAHor(raiz); // efetua a rotacao
	}else{ 		// rotacionar Hor
		aux = raiz->fe;
		if(aux->fe)
			a = aux->fe->tam;
		if(aux->fd)
			b = aux->fd->tam;

		// testar se uma rotacao simples NAO resolve
		if(3*a+1 < 1+nd+b)
			raiz->fe = rotAHor(raiz->fe);
		raiz = rotHor(raiz); // efetua a rotacao
	}





	return raiz;
}

// Insere o valor k na sub-arvore raiz
Node * insere(Node * raiz, int k){

	++raiz->tam;
	if(!raiz){
		raiz = aloca();
		raiz->valor=k;
		raiz->tam=1;
	}else if(k < raiz->valor)
		raiz->fe = insere(raiz->fe, k);
	else
		raiz->fd = insere(raiz->fd, k);

	return balanceia(raiz);
}

// Remove k	da sub-arvore now e retorna sub-arvore resultante
Node * remove(Node * raiz, int k){

	--raiz->tam;

	//Procurando o nó
	if (k < raiz->valor){
		remove(raiz->fe, k);
		return balanceia(raiz);

	} else if(k > raiz->valor){
		remove(raiz->fd, k);
		return balanceia(raiz);
	}

	//Nó encontrado, agora vamos retirá-lo
	Node * retorna;
	if(!raiz->fe)
		retorna = raiz->fd;
	else if(!raiz->fd)
		retorna = raiz->fe;
	else{
		int min = fMin(raiz->fd);
		retorna = aloca();
		retorna->valor = min;
		retorna->fe = raiz->fe;
		retorna->fd = remove(raiz->fd, min);
	}
	free(raiz);
	return balanceia(retorna);
}

// Funcao que rotaciona a sub-arvore no sentido Horario
// E retorna a resultante
Node * rotHor(Node * raiz);

// Funcao que rotaciona a sub-arvore no sentido Anti-horario
// E retorna a resultante
Node * rotAHor(Node * raiz);

// Funcao que imprime a arvore "em ordem", sub arvores delimitadas por [ ]
void imprime(Node * raiz);






int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
