/*
 * Programa que implementa uma arvore binaria de busca balanceada
 * A propriedade eh que uma sub-arvore nao tem mais que 3* + 1 o numero
 * de nohs da irmã
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "awl.h"
#include "escreve_arvore_tela.h"

/*
 * Digite um numero positivo para inseri-lo na arvore
 * Digite um numero negativo para retirar o oposto dele da arvore
 * Digite 0 para sair
 */
int main(int argc, char *argv[])
{
	Node * raiz = NULL;
	int val;

	while(scanf("%d",&val)>0 && val!=0)
	{
		if(val<0)
			raiz = remove(raiz,-val);
		else
			raiz = insere(raiz,val);
		imprime(raiz);
		printf("\n");
	}

	system("PAUSE");
	return EXIT_SUCCESS;
}
