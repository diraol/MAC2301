#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Verbete{
	char* chave;
	char* descricao;
	Verbete* proximo;
};

struct Dicionario{
	int nBins;
	Verbete* bins;
};

//Configura o dicionário para trabalhar com nBins bins.
void Inicie(Dicionario* d, int nBins){
	d->nBins = nBins;
	d->bins = (Verbete*) malloc(nBins * sizeof(Verbete));
};

//Calcula a soma das letras de chave módulo o número de bins.
int HashFunction(char* chave, int nBins){
	int hash = 0;
	while(*chave)
	  hash += *chave++;

	return hash % nBins;
}

//Libera toda a memória usada pelos verbetes, isto é, os verbetes, suas chaves e descrições.
void Destrua(Dicionario* d){
	int n = d->nBins;
	for(int i = 0; i < n; i++){
		Verbete* v = &d->bins[i];
		while(v->proximo){
			Verbete* v2 = v->proximo;
			free(v);
			v = v2;
		}
	}
    free(d->bins);
    d->bins = 0;
    d->nBins = 0;
}

//Insere o verbete com a chave e a descrição dada no dicionário. Se houver um verbete com esta chave,
//então sua descrição deve ser substituida por uma cópia da nova. A função insere cópias dos valores fornecidos.
void Insira(Dicionario* d, char* chave, char* descricao){
	//Calcula o Hash
	int hash = HashFunction(chave, d->nBins);
	Verbete* aux = d->bins + hash;
	bool encontrado = false;

	char* nova_descricao = (char*) malloc(strlen(descricao) + 1);
	nova_descricao = descricao;

	if( aux->chave == 0 ){
		Verbete* inserir = (Verbete*) malloc(sizeof(Verbete));
		char* nova_chave = (char*) malloc(strlen(chave) + 1);
		nova_chave = chave;
		inserir->chave = nova_chave;
		inserir->descricao = nova_descricao;
		inserir->proximo = 0;
		aux = inserir;
	} else {
		while( aux ){
			if ( strcmp(aux->chave,chave) == 0 ){
				aux->descricao = nova_descricao;
				encontrado = true;
			}
			aux = aux->proximo;
		}
		if (!encontrado){ //Insere um novo verbete
			Verbete* inserir = (Verbete*) malloc(sizeof(Verbete));
			char* nova_chave = (char*) malloc(strlen(chave) + 1);
			nova_chave = chave;
			inserir->chave = nova_chave;
			inserir->descricao = nova_descricao;
			inserir->proximo = d->bins + hash;
			d->bins[hash] = *inserir;
		}
	}


}

//Procura o verbete com a chave dada no dicionário. Se houver tal verbete a função retorna a sua descrição, caso contrário retorna NULL.
char* Busque (Dicionario* d, char* chave){
	//Calcula o Hash
	int hash = HashFunction(chave, d->nBins);
	Verbete* aux = d->bins + hash;
	if( aux->chave == 0 )
		return NULL;

	while( aux ){
		if ( strcmp(aux->chave,chave) == 0 ){
		  return aux->descricao;
		}
		aux = aux->proximo;
	}
	return NULL;
}


//Tenta remover a entrada com a chave dada do dicionário. Se houver tal entrada ela é removida e a memória que ela usava é liberada.
void Remova(Dicionario* d, char* chave);


int main(){
	Dicionario d;
	Inicie(&d,4);
	Insira(&d, "Pedro Álvares Cabral", "Navegante português que encontrou o Brasil.");
	char* v = Busque(&d, "Pedro Álvares Cabral");
	if (v){
		printf("Pedro Álvares Cabral:\n%s\n",v);
	}else{
		printf("Não há entrada para Pedro Álvares Cabral\n");
	}
	Destrua(&d);
	return 0;
}
