#ifndef ARQ_H
#define ARQ_H

typedef struct livro {
	char * titulo;
	char * autor;
	char * isbn;
	int codigo;
} dado;

typedef struct indice {
	int chave;
	int indice;
} tipo_dado;

typedef struct no_avl {
	tipo_dado *dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;
/*typedef struct no_bst {
	tipo_dado *dado;
	struct no_bst *esq, *dir;
} no_bst;*/

typedef no_avl * arvore;

typedef struct tabela {
	FILE *arquivo_dados;
	arvore indices;
} tabela;


int inicializarTabela(tabela *tab);
void finalizar (tabela *tab);
void adicionarLivro(tabela *tab, dado *livro);
	

void inicializar(arvore *raiz);
arvore adicionar (tipo_dado *valor, arvore raiz,int *cresceu);

int altura(arvore raiz);
int maior(int a, int b);
tipo_dado * maior_elemento(arvore raiz);
tipo_dado * menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);
void buscar(int valor,arvore raiz,tabela *tab);
void imprimir_elemento(arvore raiz, tabela *tab);
dado * ler_dados();
void tirar_enter(char *string);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);




#endif
