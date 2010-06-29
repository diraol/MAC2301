#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
using namespace std;

struct Verbete{
	char* pt_chave;
	char* pt_descricao;
	Verbete* pt_prox_verbete;
};

struct Dicionario{
	int nPos; // Número total de posições do Dicionário, cada posição relaciona-se a um HASH.
				// Em cada posição teremos uma lista ligada de verbetes, representada pelo apontador
				// para o primeiro verbete da lista ligada.
	Verbete* pt_Pos; //Lista de apontadores para os primeiros verbetes de cada posição do dicionário.
};

//Configura o dicionário para trabalhar com nBins bins.
void Inicie(Dicionario* d, int nPos){
	d->nPos = nPos;
	d->pt_Pos = (Verbete*) malloc(nPos * sizeof(Verbete));
};

//Calcula a soma das letras de chave módulo o número de bins.
int HashFunction(char* pt_chave, int nPos){
	int hash = 0;
	while(*pt_chave) //pega o valor do endereço apontado pelo apontador.
	  hash += *pt_chave++; //soma o valor do endereço apontado e faz o apontador andar 1 bit na memória.
	hash = hash % nPos;

	return hash;
}

//Libera toda a memória usada pelos verbetes, isto é, os verbetes, suas chaves e descrições.
void Destrua(Dicionario* pt_dic){
	int nPos = pt_dic->nPos;
	Verbete *pt_v1, *pt_v2;

	for(int pos = 0; pos < nPos; pos++){
		pt_v1 = &pt_dic->pt_Pos[pos];
		while(pt_v1->pt_prox_verbete){ //Limpa a lista ligada, nó por nó
			pt_v2 = pt_v1->pt_prox_verbete;
			free(pt_v1);
			pt_v1 = pt_v2;
		}
		free(pt_v1);
	}
    free(pt_dic->pt_Pos);
    pt_dic->pt_Pos = 0;
    pt_dic->nPos = 0;

}

//Insere o verbete com a chave e a descrição dada no dicionário. Se houver um verbete com esta chave,
//então sua descrição deve ser substituida por uma cópia da nova. A função insere cópias dos valores fornecidos.
void Insira(Dicionario* pt_dic, char* pt_chave, char* pt_descricao){
	//Calcula o Hash
	int hash = HashFunction(pt_chave, pt_dic->nPos);

	Verbete* pt_aux = pt_dic->pt_Pos + hash;

	bool encontrado = false;
	char* pt_nova_descricao = (char*) malloc(strlen(pt_descricao) + 1);
	pt_nova_descricao = pt_descricao;

	if( pt_aux->pt_chave == 0 ){ //Primeiro verbete para o Hash

		Verbete* pt_novo_v = (Verbete*) malloc(sizeof(Verbete));
		char* pt_nova_chave = (char*) malloc(strlen(pt_chave) + 1);
		pt_nova_chave = pt_chave;
		pt_novo_v->pt_chave = pt_nova_chave;
		pt_novo_v->pt_descricao = pt_nova_descricao;
		pt_novo_v->pt_prox_verbete = 0;
		*pt_aux = *pt_novo_v;

	} else {

		while (pt_aux && !encontrado){ // Atualiza o verbete

			if (strcmp(pt_aux->pt_chave,pt_chave) == 0 ){
				pt_aux->pt_descricao = pt_nova_descricao;
				encontrado = true;
			}
			pt_aux = pt_aux->pt_prox_verbete;
		}

		pt_aux = pt_dic->pt_Pos + hash;
		if (!encontrado){ //Insere um novo verbete no começo da lista ligada
			Verbete* pt_novo_v = (Verbete*) malloc(sizeof(Verbete));

			pt_novo_v->pt_chave = pt_aux->pt_chave;
			pt_novo_v->pt_descricao = pt_aux->pt_descricao;
			pt_novo_v->pt_prox_verbete = pt_aux->pt_prox_verbete;

			char* pt_nova_chave = (char*) malloc(strlen(pt_chave) + 1);
			pt_nova_chave = pt_chave;

			*&pt_aux->pt_chave = pt_nova_chave;
			*&pt_aux->pt_descricao = pt_nova_descricao;
			*&pt_aux->pt_prox_verbete = pt_novo_v;

		}
	}
}

//Procura o verbete com a chave dada no dicionário. Se houver tal verbete a função retorna a sua descrição, caso contrário retorna NULL.
char* Busque (Dicionario* pt_dic, char* pt_chave){
	//Calcula o Hash
	int hash = HashFunction(pt_chave, pt_dic->nPos);
	Verbete* pt_v_aux = pt_dic->pt_Pos + hash;
	if( pt_v_aux->pt_chave == 0 )
		return NULL;

	while( pt_v_aux ){
		if ( strcmp(pt_v_aux->pt_chave,pt_chave) == 0 ){
		  return pt_v_aux->pt_descricao;
		}
		pt_v_aux = pt_v_aux->pt_prox_verbete;
	}
	return NULL;
}

//Tenta remover a entrada com a chave dada do dicionário. Se houver tal entrada ela é removida e a memória que ela usava é liberada.
void Remova(Dicionario* pt_dic, char* pt_chave){
	//Calcula o Hash
	int hash = HashFunction(pt_chave, pt_dic->nPos);
	Verbete* pt_v_aux = pt_dic->pt_Pos + hash;

	while (pt_v_aux){
		if (strcmp(pt_v_aux->pt_chave,pt_chave) == 0){
			if(pt_v_aux->pt_prox_verbete){
				*pt_v_aux->pt_chave = *pt_v_aux->pt_prox_verbete->pt_chave;
				*pt_v_aux->pt_descricao = *pt_v_aux->pt_prox_verbete->pt_descricao;
				*pt_v_aux->pt_prox_verbete = *pt_v_aux->pt_prox_verbete->pt_prox_verbete;
				free(pt_v_aux->pt_prox_verbete);
			} else {
				free(pt_v_aux);
			}
		}
		pt_v_aux = pt_v_aux->pt_prox_verbete;
	}
}

int main(){

// ************************** Sistema Interativo ****************************
//	Dicionario dic;
//	int nPos;
//	printf("Digite o número de posições de seu dicionário: ");
//	cin >> nPos;
//	Inicie(&dic, nPos);
//
//	bool sair = false;
//	char* caso = "\0";
//	int opcao = 0;
//
//	while(!sair){
//		printf("Selecione a opção desejada, digitando apenas\n  a primeira letra maiúscula da Palavra:\n");
//		printf("1) Inserir; 2) Remover; 3) Buscar; 4) Sair;\n");
//		*caso = getchar();
//		printf("teste");
//		if(strcmp(caso,"I") == 0 || strcmp(caso,"i") == 0)
//			opcao = 1;
//		else if(strcmp(caso,"R") == 0 || strcmp(caso,"r") == 0)
//			opcao = 2;
//		else if(strcmp(caso,"B") == 0 || strcmp(caso,"b") == 0)
//			opcao=3;
//		else if(strcmp(caso,"S") == 0 || strcmp(caso,"s") == 0)
//			opcao=4;
//		else
//			opcao=0;
//
//		system("cls");
//		system ("pause");
//		switch (opcao){
//			case 1: //Inserir
//				printf("Inserir");
//				break;
//
//			case 2: //Remover
//				printf("Remover");
//				break;
//
//			case 3: //Buscar
//				printf("Buscar");
//				break;
//
//			case 4: //Sair
//				printf("Sair");
//				sair = true;
//				break;
//			default:
//				printf("Opção inválida.\n");
//				break;
//
//			printf("\n");
//
//		}
//
//	}
//
//	return 0;
	// ************************** Sistema Interativo ****************************

	//* //Primeiro teste
	Dicionario d;
	Inicie(&d,10);

	char* pt_verbete = "ocas";
	char* pt_desc = "1 verbete";
	Insira(&d, pt_verbete, pt_desc);

	pt_verbete = "saco";
	pt_desc = "2 verbete";
	Insira(&d, pt_verbete, pt_desc);

	pt_verbete = "asco";
	pt_desc = "3 verbete";
	Insira(&d, pt_verbete, pt_desc);

	char* verbete;

	verbete = Busque(&d, "ocas");
	if (verbete)
		printf("Ocas:\n%s\n\n",verbete);
	else
		printf("Não há entrada para Ocas\n\n");


	verbete = Busque(&d, "saco");
	if (verbete)
		printf("Saco:\n%s\n\n",verbete);
	else
		printf("Não há entrada para saco\n\n");

	verbete = Busque(&d, "asco");
	if (verbete)
		printf("Asco:\n%s\n\n",verbete);
	else
		printf("Não há entrada para saco\n\n");

	Destrua(&d);
	return 0; /*/


	//* //Segundo Teste
	Dicionario d;
	d.nPos = 4;
	d.pt_Pos = (Verbete*) malloc(4 * sizeof(Verbete));

	char* chave = "Pedro Álvares Cabral";
	char* descricao = "Navegante português que encontrou o Brasil.";

	d.pt_Pos[HashFunction(chave,4)].pt_chave = chave;
	d.pt_Pos[HashFunction(chave,4)].pt_descricao = descricao;
	d.pt_Pos[HashFunction(chave,4)].pt_prox_verbete = 0;

	char* v = Busque(&d, "Pedro Álvares Cabralaa");
	if (v){
		printf("Pedro Álvares Cabral:\n%s\n",v);
	}else{
		printf("Não há entrada para Pedro Álvares Cabral\n");
	}

	printf("Apagando\n");

	Remova(&d, "Pedro Álvares Cabral");

	printf("Procurando de novo\n");

	v = Busque(&d, "Pedro Álvares Cabral");
		if (v){
			printf("Pedro Álvares Cabral:\n%s\n",v);
		}else{
			printf("Não há entrada para Pedro Álvares Cabral\n");
		}

	Destrua(&d);
	return 0; //*/

}
