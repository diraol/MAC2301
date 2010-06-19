#ifndef AWL_H
#define AWL_H
struct Node
{
	int val; // valor guardado
	int n; // numero de nohs na sub-arvore
	Node * f1;
	Node * f2;
};

// Aloca e zera um Node
Node * aloca();

// Insere o valor k na sub-arvore now
Node * insere(Node * now, int k);

// Remove k	da sub-arvore now e retorna sub-arvore resultante
Node * remove(Node * now, int k);

// Acha o valor do minimo elemento da sub-arvore
int fMin(Node * now);

// Funcao que faz o balanceamento da sub-arvore
// E retorna a resultante
Node * balanceia(Node * now);

// Funcao que rotaciona a sub-arvore no sentido Horario
// E retorna a resultante
Node * rotHor(Node * now);

// Funcao que rotaciona a sub-arvore no sentido Anti-horario
// E retorna a resultante
Node * rotAHor(Node * now);

// Funcao que imprime a arvore "em ordem", sub arvores delimitadas por [ ]
void imprime(Node * now);
#endif
