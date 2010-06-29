#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "awl.h"

/*
 * As descricoes das funcoes estao no awl.h
 */

Node * aloca()
{
	Node * ret;
	ret=(Node *)malloc(sizeof(Node));
	ret->n=0;
	ret->f1=ret->f2=NULL;
	ret->val=INT_MIN;
	return ret;
}


Node * insere(Node * now, int k)
{
	if(!now) // tem que ser inserido neste Node
	{
		now=aloca();
		now->val=k;
		now->n = 1;
		return now;
	}
	if(k < now->val)
		now->f1 = insere(now->f1,k);
	else if(k >= now->val)
		now->f2 = insere(now->f2,k);
	++now->n;

	now=balanceia(now);
	return now;
}

Node * remove(Node * now, int k)
{
	--now->n; // decrementar o contador
	if(k < now->val) // na esquerda
	{
		now->f1=remove(now->f1,k);
		now=balanceia(now);
		return now;
	}
	if(k > now->val) // na direita
	{
		now->f2=remove(now->f2,k);
		now=balanceia(now);
		return now;
	}

	// tenho que retirar o now
	Node * ret;
	int mi;
	if(!now->f1)
		ret=now->f2;
	else if(!now->f2)
		ret=now->f1;
	else
	{
		mi=fMin(now->f2);
		ret=aloca();
		ret->val=mi;
		ret->f1=now->f1;
		ret->f2=remove(now->f2,mi);
	}
	free(now);
	ret = balanceia(ret);
	return ret;
}

int fMin(Node * k)
{
	while(k->f1)
		k=k->f1;
	return k->val;
}

Node * balanceia(Node * now)
{
	int n1=0,n2=0; // numero de elementos de cada filho (dir e esq)
	Node * v;
	int a=0,b=0; // numero de elementos nos netos relevantes

	if(!now)
		return NULL;
	if(now->f1)
		n1 = now->f1->n;
	if(now->f2)
		n2 = now->f2->n;

	if(3*n1+1 >= n2 && 3*n2+1 >= n1) // ja balanceada
		return now;

	if(3*n1+1 < n2) // rotacionar AHor
	{
		v = now->f2;
		if(v->f2)
			a = v->f2->n;
		if(v->f1)
			b = v->f1->n;

		// testar se uma rotacao simples NAO resolve
		if(3*a+1 < 1+n1+b)
			now->f2 = rotHor(now->f2);
		now = rotAHor(now); // efetua a rotacao
	}
	else 		// rotacionar Hor
	{
		v = now->f1;
		if(v->f1)
			a = v->f1->n;
		if(v->f2)
			b = v->f2->n;

		// testar se uma rotacao simples NAO resolve
		if(3*a+1 < 1+n2+b)
			now->f1 = rotAHor(now->f1);
		now = rotHor(now); // efetua a rotacao
	}

	// Verificar se os filhos estao balanceados
	// (apenas em casos muito especificos nao o estarao)
	now->f1 = balanceia(now->f1);
	now->f2 = balanceia(now->f2);
	return now;
}

Node * rotHor(Node * now)
{
	Node *u,*v;
	u = now;
	v = now->f1;
	u->f1 = v->f2;
	v->f2 = u;
	u->n = 1+ ((u->f1)?(u->f1->n):0) + ((u->f2)?(u->f2->n):0);
	v->n = 1+ ((v->f1)?(v->f1->n):0) + ((v->f2)?(v->f2->n):0);
	return v;
}

Node * rotAHor(Node * now)
{
	Node *u,*v;
	u = now;
	v = now->f2;
	u->f2 = v->f1;
	v->f1 = u;
	u->n = 1+ ((u->f1)?(u->f1->n):0) + ((u->f2)?(u->f2->n):0);
	v->n = 1+ ((v->f1)?(v->f1->n):0) + ((v->f2)?(v->f2->n):0);
	return v;
}

void imprime(Node * now)
{
	if(!now)
		return;
	printf("[");
	imprime(now->f1);
	printf(" %d ",now->val);
	imprime(now->f2);
	printf("]");
}
