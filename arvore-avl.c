#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>


typedef struct noArv{
	int valor, altura;
	struct noArv *esquerda, *direita;
}NoArv;

NoArv* novoNoArv(int x){
	NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
	
	if(novo){
		novo->valor = x;
		novo->esquerda = NULL;
		novo->direita = NULL;
		novo->altura = 0;
	}else
		printf("\nErro ao alocar memória.\n");
	
	return novo;
}

int maior(int a, int b){
	return (a > b)?a:b;
}

int alturaNo(NoArv *no){
	if(no == NULL)
		return -1;
	else
		return no->altura;
}

int fatorBalanceamento(NoArv *no){
	if(no){
		return (alturaNo(no->esquerda) - alturaNo(no->direita));
	}else{
		return 0;
	}
}

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
        printf("\nValor não encontrado");
        return;
    }
    if (valor == raiz->valor) {
        printf("\nValor encontrado na posição: %d", contI);
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


int altura(NoArv *raiz){
	if(raiz == NULL){
		return -1;
	}else{
		int esq = altura(raiz->esquerda);
		int dir = altura(raiz->direita);
		if(esq > dir)
			return esq + 1;
		else
			return dir + 1;
	}
}

int calcQuantNos(NoArv *raiz){
	if(raiz == NULL){
		return 0;
	}else{
		return 1 + calcQuantNos(raiz->esquerda) + calcQuantNos(raiz->direita);
	}
}

NoArv* remover(NoArv *raiz, int chave){
	if(raiz == NULL){
		printf("Valor não encontrado.\n");
		return NULL;
	}else{
		if(raiz->valor == chave){
			if(raiz->esquerda == NULL && raiz->direita == NULL){
				free(raiz);
				printf("Elemento removido: %d\n", chave);
				return NULL;
			}else{
				if(raiz->esquerda != NULL && raiz->direita != NULL){
					NoArv *aux = raiz->esquerda;
					while(aux->direita != NULL)
						aux = aux->direita;
					raiz->valor = aux->valor;
					aux->valor = chave;
					printf("Elemento trocado: %d\n", chave);
					raiz->esquerda = remover(raiz->esquerda, chave);
					return raiz;
				}else{
					NoArv *aux;
					if(raiz->esquerda != NULL)
						aux = raiz->esquerda;
					else 
						aux = raiz->direita;
					free(raiz);
					printf("Elemento com 1 filho removido: %d\n", chave);
					return aux;
				}
			}
		}else{
			if(chave < raiz->valor)
				raiz->esquerda = remover(raiz->esquerda, chave);
			else
				raiz->direita = remover(raiz->direita, chave);
			
			return raiz;
		}		
	}
}

int main(void){
	setlocale(LC_ALL, "PORTUGUESE");
	
	NoArv *raiz = NULL;
	
	int op;
	
	do{
		printf("\nEscolha as opções: ");
		printf("\n1-Inserir na arvore");
		printf("\n2-Imprimir em pré-ordem");
		printf("\n3-Imprimir em in-ordem");
		printf("\n4-Imprimir em pós-ordem");
		printf("\n5-Buscar na arvore");
		printf("\n6-Calcular altura");
		printf("\n7-Calcula quantidades de nós");
		printf("\n8-Remover");
		printf("\n9-Sair");
		printf("\nOpção: ");
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
			case 6:
				printf("Altura da arvore: %d", altura(raiz));
				break;
			case 7:
				printf("Quantidade de nós: %d", calcQuantNos(raiz));
				break;
			case 8:{
				int valor;
				printf("Qual vai ser o valor a remover: ");
				scanf("%d", &valor);
				raiz = remover(raiz, valor);	
				break;
			}
		}
	}while(op < 9);
	
	return 0;
}
