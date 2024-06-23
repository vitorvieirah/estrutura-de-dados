//1. Uma empresa deseja implementar um sistema de controle de estoque que utilize uma
//tabela hash para armazenar os c�digos dos produtos. Eles escolheram o m�todo do resto
//da divis�o para calcular os �ndices.
//Explique como o m�todo do resto da divis�o funciona para calcular os �ndices de uma
//tabela hash, e implemente a fun��o em C que insere um novo c�digo de produto na tabela
//hash, considerando que a tabela � um vetor de inteiros de tamanho fixo.
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int funcaoHash(int chave) {
    return chave % 10;
}

// Tabela hash com lista encadeada
typedef struct produtoList {
    char nome[100];
    char marca[100];
    int codigo;
    struct produtoList *proximo;
} ProdutoList;

ProdutoList *estoqueList[10];

// Tabela hash com vetor
typedef struct {
    char nome[100];
    char marca[100];
    int codigo;
} Produto;

Produto *estoque[23];

void inicializVetor() {
	int i;
    for (i = 0; i < 23; i++) {
        estoque[i] = NULL;
    }
}

void inserirNaTabelaComVetor(Produto *prod) {
    int posi = funcaoHash(prod->codigo);
    printf("\nPosi��o que ser� alocado de in�cio: %d", posi);
    if (estoque[posi] == NULL) {
        estoque[posi] = prod;
    } else {
        int i = posi;
        while (estoque[i] != NULL && i < 23)
            i++;

        if (i == 23) {
            printf("Vetor cheio!");
        } else {
            estoque[i] = prod;
            printf("\nNova posi��o que ser� alocado: %d", i);
        }
    }
}

void imprimirProduto(Produto *prod) {
    printf("\nNome do produto: %s", prod->nome);
    printf("\nMarca do produto: %s", prod->marca);
    printf("\nC�digo do produto: %d", prod->codigo);
}

Produto* buscarNaTabela(int cod) {
    int posi = funcaoHash(cod);

    if (estoque[posi] != NULL && estoque[posi]->codigo == cod) {
        printf("Produto encontrado na posi��o %d", posi);
        imprimirProduto(estoque[posi]);
        return estoque[posi];
    } else {
        int i = 0;
        while (i < 23 && (estoque[i] == NULL || estoque[i]->codigo != cod))
            i++;

        if (i == 23) {
            printf("Produto n�o encontrado");
            return NULL;
        } else {
            printf("Produto encontrado na posi��o %d", i);
            imprimirProduto(estoque[i]);
            return estoque[i];
        }
    }
}

void inserirProdutoAtualizado(Produto *prod) {
    int posi = funcaoHash(prod->codigo);

    if (estoque[posi] != NULL && estoque[posi]->codigo == prod->codigo) {
        estoque[posi] = prod;
    } else {
        int i = 0;
        while (i < 23 && (estoque[i] == NULL || estoque[i]->codigo != prod->codigo))
            i++;

        if (i == 23) {
            printf("Produto n�o encontrado na atualiza��o");
        } else {
            estoque[i] = prod;
        }
    }
}

void alterarProdutoNaTabela(int cod) {
    Produto *prod = buscarNaTabela(cod);
    if (prod == NULL) return;

    int op;

    printf("\n1-Alterar o nome\n2-Alterar a marca\n3-Alterar todos\nOp��o: ");
    scanf("%d", &op);
    getchar();

    switch (op) {
        case 1: {
            printf("\nDigite o novo nome: ");
            fgets(prod->nome, sizeof(prod->nome), stdin);
            prod->nome[strcspn(prod->nome, "\n")] = 0;
            inserirProdutoAtualizado(prod);
            break;
        }
        case 2: {
            printf("\nDigite a nova marca: ");
            fgets(prod->marca, sizeof(prod->marca), stdin);
            prod->marca[strcspn(prod->marca, "\n")] = 0;
            inserirProdutoAtualizado(prod);
            break;
        }
        case 3: {
            printf("\nDigite o novo nome: ");
            fgets(prod->nome, sizeof(prod->nome), stdin);
            prod->nome[strcspn(prod->nome, "\n")] = 0;
            printf("\nDigite a nova marca: ");
            fgets(prod->marca, sizeof(prod->marca), stdin);
            prod->marca[strcspn(prod->marca, "\n")] = 0;
            inserirProdutoAtualizado(prod);
            break;
        }
    }
}

void deletarProdutoDaTabela(int cod) {
    int posi = funcaoHash(cod);

    if (estoque[posi] != NULL && estoque[posi]->codigo == cod) {
        printf("Produto encontrado na posi��o %d", posi);
        estoque[posi] = NULL;
        printf("\nProduto deletado com sucesso");
    } else {
        int i = 0;
        while (i < 23 && (estoque[i] == NULL || estoque[i]->codigo != cod))
            i++;

        if (i == 23) {
            printf("Produto n�o encontrado");
        } else {
            printf("Produto encontrado na posi��o %d", i);
            estoque[i] = NULL;
            printf("\nProduto deletado com sucesso");
        }
    }
}

void inserirProduto() {
    Produto *prod = (Produto*) malloc(sizeof(Produto));

    printf("Digite o nome do produto: ");
    fgets(prod->nome, sizeof(prod->nome), stdin);
    prod->nome[strcspn(prod->nome, "\n")] = 0;

    printf("Digite a marca do produto: ");
    fgets(prod->marca, sizeof(prod->marca), stdin);
    prod->marca[strcspn(prod->marca, "\n")] = 0;

    printf("Digite o c�digo do produto: ");
    scanf("%d", &prod->codigo);
    getchar();

    inserirNaTabelaComVetor(prod);
}

void buscarProduto() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    buscarNaTabela(cod);
}

void alterarProduto() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    alterarProdutoNaTabela(cod);
}

void deletarProduto() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    deletarProdutoDaTabela(cod);
}

//============================================================================
// Tabela hash com lista encadeada

void inicializarVetorList() {
    int i;
	for (i = 0; i < 10; i++) {
        estoqueList[i] = NULL;
    }
}

void inserirNaTabelaComList(ProdutoList *prod) {
    int posi = funcaoHash(prod->codigo);
    printf("\nPosi��o que ser� alocado de in�cio: %d", posi);

    if (estoqueList[posi] == NULL) {
        estoqueList[posi] = prod;
    } else {
        int cont = 1;
        ProdutoList *aux = estoqueList[posi];

        while (aux->proximo != NULL) {
            aux = aux->proximo;
            cont++;
        }

        aux->proximo = prod;

        printf("\nPosi��o da lista que ser� alocado: %d", cont);
    }
}

void imprimirProdutoList(ProdutoList *prod) {
    printf("\nNome do produto: %s", prod->nome);
    printf("\nMarca do produto: %s", prod->marca);
    printf("\nC�digo do produto: %d", prod->codigo);
}

ProdutoList* buscarNaTabelaList(int cod) {
    int posi = funcaoHash(cod);

    if (estoqueList[posi] == NULL) {
        printf("Produto n�o encontrado");
        return NULL;
    } else if (estoqueList[posi]->codigo == cod) {
        printf("Produto encontrado na posi��o: %d", posi);
        imprimirProdutoList(estoqueList[posi]);
        return estoqueList[posi];
    } else {
        int cont = 1;
        ProdutoList *aux = estoqueList[posi]->proximo;

        while (aux != NULL && aux->codigo != cod) {
            aux = aux->proximo;
            cont++;
        }

        if (aux == NULL) {
            printf("Produto n�o encontrado");
            return NULL;
        } else {
            printf("Produto encontrado na posi��o: %d e %d� Posi��o da lista", posi, cont);
            imprimirProdutoList(aux);
            return aux;
        }
    }
}

void inserirProdutoAtualizadoList(ProdutoList *prod) {
    int posi = funcaoHash(prod->codigo);

    if (estoqueList[posi] == NULL) {
        printf("\nProduto n�o encontrado para altera��o");
    } else if (estoqueList[posi]->codigo == prod->codigo) {
        estoqueList[posi] = prod;
        printf("\nProduto alterado com sucesso");
    } else {
        ProdutoList *aux = estoqueList[posi]->proximo;
        while ((aux != NULL) && (aux->codigo != prod->codigo))
            aux = aux->proximo;

        if (aux == NULL) {
            printf("\nProduto n�o encontrado para altera��o");
        } else {
            prod->proximo = aux->proximo;
            *aux = *prod;
            printf("\nProduto alterado com sucesso");
        }
    }
}

void alterarProdutoNaTabelaList(int cod) {
    ProdutoList *prod = buscarNaTabelaList(cod);
    if (prod == NULL) return;

    int op;

    printf("\n1-Alterar o nome\n2-Alterar a marca\n3-Alterar todos\nOp��o: ");
    scanf("%d", &op);
    getchar();

    switch (op) {
        case 1: {
            printf("\nDigite o novo nome: ");
            fgets(prod->nome, sizeof(prod->nome), stdin);
            prod->nome[strcspn(prod->nome, "\n")] = 0;
            inserirProdutoAtualizadoList(prod);
            break;
        }
        case 2: {
            printf("\nDigite a nova marca: ");
            fgets(prod->marca, sizeof(prod->marca), stdin);
            prod->marca[strcspn(prod->marca, "\n")] = 0;
            inserirProdutoAtualizadoList(prod);
            break;
        }
        case 3: {
            printf("\nDigite o novo nome: ");
            fgets(prod->nome, sizeof(prod->nome), stdin);
            prod->nome[strcspn(prod->nome, "\n")] = 0;
            printf("\nDigite a nova marca: ");
            fgets(prod->marca, sizeof(prod->marca), stdin);
            prod->marca[strcspn(prod->marca, "\n")] = 0;
            inserirProdutoAtualizadoList(prod);
            break;
        }
    }
}

void deletarProdutoDaTabelaList(int cod) {
    int posi = funcaoHash(cod);

    if(estoqueList[posi]->codigo = cod){
    	estoqueList[posi] = NULL;
    	printf("\nProduto deletado com sucesso");
	}else{
		ProdutoList *aux = estoqueList[posi]->proximo;
		
		while(aux->codigo != cod && aux != NULL)
			aux = aux->proximo;
		
		if(aux == NULL){
			printf("\nProduto n�o encontrado para altera��o");
		}else{
			aux = NULL;
			printf("\nProduto deletado com sucesso");
		}
	}
	
}

void inserirProdutoList() {
    ProdutoList *prod = (ProdutoList*) malloc(sizeof(ProdutoList));

    printf("Digite o nome do produto: ");
    fgets(prod->nome, sizeof(prod->nome), stdin);
    prod->nome[strcspn(prod->nome, "\n")] = 0;

    printf("Digite a marca do produto: ");
    fgets(prod->marca, sizeof(prod->marca), stdin);
    prod->marca[strcspn(prod->marca, "\n")] = 0;

    printf("Digite o c�digo do produto: ");
    scanf("%d", &prod->codigo);
    getchar();

    prod->proximo = NULL;

    inserirNaTabelaComList(prod);
}

void buscarProdutoList() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    buscarNaTabelaList(cod);
}

void alterarProdutoList() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    alterarProdutoNaTabelaList(cod);
}

void deletarProdutoList() {
    int cod;
    printf("Digite o c�digo do produto: ");
    scanf("%d", &cod);
    getchar();

    deletarProdutoDaTabelaList(cod);
}

//============================================================================

int main() {
    setlocale(LC_ALL, "Portuguese");

    int op;

    do {
        printf("\nMenu Principal");
        printf("\n1 - Usar Tabela Hash com Vetor");
        printf("\n2 - Usar Tabela Hash com Lista Encadeada");
        printf("\n3 - Sair");
        printf("\nOp��o: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1: {
                int opVetor;
                inicializVetor();
                do {
                    printf("\nMenu Tabela Hash com Vetor");
                    printf("\n1 - Inserir Produto");
                    printf("\n2 - Buscar Produto");
                    printf("\n3 - Alterar Produto");
                    printf("\n4 - Deletar Produto");
                    printf("\n5 - Voltar ao Menu Principal");
                    printf("\nOp��o: ");
                    scanf("%d", &opVetor);
                    getchar();

                    switch (opVetor) {
                        case 1: inserirProduto(); break;
                        case 2: buscarProduto(); break;
                        case 3: alterarProduto(); break;
                        case 4: deletarProduto(); break;
                        case 5: break;
                        default: printf("Op��o inv�lida!"); break;
                    }
                } while (opVetor != 5);
                break;
            }
            case 2: {
                int opList;
                inicializarVetorList();
                do {
                    printf("\nMenu Tabela Hash com Lista Encadeada");
                    printf("\n1 - Inserir Produto");
                    printf("\n2 - Buscar Produto");
                    printf("\n3 - Alterar Produto");
                    printf("\n4 - Deletar Produto");
                    printf("\n5 - Voltar ao Menu Principal");
                    printf("\nOp��o: ");
                    scanf("%d", &opList);
                    getchar();

                    switch (opList) {
                        case 1: inserirProdutoList(); break;
                        case 2: buscarProdutoList(); break;
                        case 3: alterarProdutoList(); break;
                        case 4: deletarProdutoList(); break;
                        case 5: break;
                        default: printf("Op��o inv�lida!"); break;
                    }
                } while (opList != 5);
                break;
            }
            case 3: printf("Saindo..."); break;
            default: printf("Op��o inv�lida!"); break;
        }
    } while (op != 3);

    return 0;
}


