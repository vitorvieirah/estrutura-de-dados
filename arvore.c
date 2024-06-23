//3. Um programador precisa desenvolver uma estrutura de dados que permita a busca
//eficiente de dados. Ele escolhe utilizar uma �rvore bin�ria de busca.
//Defina uma �rvore bin�ria de busca e implemente a fun��o em C que insere um novo
//elemento nessa �rvore.

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>


typedef struct noArv{
	int valor;
	struct noArv *esquerda, *direita;
}NoArv;


NoArv* inserirNaArvore(NoArv *raiz, int valor) {
    if (raiz == NULL) {
        NoArv *novo = (NoArv*) malloc(sizeof(NoArv));
        novo->valor = valor;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    } else {
        if (valor < raiz->valor) {
            raiz->esquerda = inserirNaArvore(raiz->esquerda, valor);
        } else {
            raiz->direita = inserirNaArvore(raiz->direita, valor);
        }
        return raiz; 
    }
}

void buscarNaArvore(NoArv *raiz, int valor, int cont) {
    int contI = cont;
    if (raiz == NULL) {
        printf("\nValor n�o encontrado");
        return;
    }
    if (valor == raiz->valor) {
        printf("\nValor encontrado na posi��o: %d", contI);
    } else {
        if (valor < raiz->valor) {
            contI++;
            buscarNaArvore(raiz->esquerda, valor, contI);
        } else {
            contI++;
            buscarNaArvore(raiz->direita, valor, contI);
        }
    }
}

void imprimirPosOrdem(NoArv *raiz){
	if(raiz){
		imprimirPosOrdem(raiz->esquerda);
		imprimirPosOrdem(raiz->direita);
		printf("%d-", raiz->valor);
	}
	
}

void imprimirInOrdem(NoArv *raiz){
	if(raiz){
		imprimirInOrdem(raiz->esquerda);
		printf("%d-", raiz->valor);
		imprimirInOrdem(raiz->direita);
	}
}

void imprimirPreOrdem(NoArv *raiz){
	if(raiz){
		printf("%d-", raiz->valor);
		imprimirPreOrdem(raiz->esquerda);
		imprimirPreOrdem(raiz->direita);
	}
}

NoArv* inserir(NoArv *raiz) {
    int valor;
    printf("Digite o valor a ser inserido: ");
    scanf("%d", &valor);

    raiz = inserirNaArvore(raiz, valor);
    return raiz;
}

void buscar(NoArv *raiz){
	int valor;
	
	printf("Digite o valor a ser buscado: ");
	scanf("%d", &valor);
	
	buscarNaArvore(raiz, valor, 0);
}


int main(void){
	setlocale(LC_ALL, "PORTUGUESE");
	
	NoArv *raiz = NULL;
	
	int op;
	
	do{
		printf("\nEscolha as op��es: ");
		printf("\n1-Inserir na arvore");
		printf("\n2-Imprimir em pr�-ordem");
		printf("\n3-Imprimir em in-ordem");
		printf("\n4-Imprimir em p�s-ordem");
		printf("\n5-Buscar na arvore");
		printf("\n6-Sair");
		printf("\nOp��o: ");
		scanf("%d", &op);
		
		switch(op){
			case 1:
				raiz = inserir(raiz);
				break;
			case 2:
				imprimirPreOrdem(raiz);
				break;
			case 3:
				imprimirInOrdem(raiz);
				break;
			case 4:
				imprimirPosOrdem(raiz);
				break;
			case 5:
				buscar(raiz);
				break;
		}
	}while(op < 6);
	
	return 0;
}
