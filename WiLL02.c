#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T      100
#define true   1
#define false  0

typedef char string[100];

 typedef struct noh {
  string nome;
  int indice;
  int telefone;
  int CPF;
  int altura;
  struct noh *esquerda, *direita;
}noh;
typedef struct dado{
    noh* pont;
    struct dado *prox;
}t_dado;

typedef struct hash {
  t_dado* itens[T];
} t_hash;

// Funcoes auxliares
int menu();
noh* criaNovoNoh(string nome, int telefone, int CPF);
void insereNovoNoh(noh** arvore, noh* novo, t_hash *hash);
void mostraEmOrdem(noh* arvore);
void mostraPreOrdem(noh* arvore);
void mostraPosOrdem(noh* arvore);
void removeNoh(noh** arvore, noh* novo);
void mostrarNoh(noh* no);
int calculaAltura(noh *no);
int maior(int a, int b);
int altura(noh* no);
void ajustarAlturaArvore(noh* no);
int fatorBalanceamento(noh* arvore);
void mostrarDados(noh *dado);
int geraIndice(string nome);
void inicializaHash(t_hash *hash);
void inserirItemLista(t_hash* hash, t_dado *novo,noh* arvore);
void balancearArvore(noh** arvore);
noh* rotacaoDireita(noh* arvore);
noh* rotacaoEsquerda(noh* arvore);
noh* rotacaoEsquerdaDireita(noh* arvore);
noh* rotacaoDireitaEsquerda(noh* arvore);
t_dado *criaCelula();
noh *Localiza(t_dado *lista,string nome);



int main(){

  t_hash hash;
  inicializaHash(&hash);
  string nome;
  int telefone;
  int CPF;
  int indice;
  noh* arvore = NULL;
  noh* aux = NULL;
  t_dado dado;
  noh *carinha;


  do {

    switch (menu()) {

             printf("\n\n");
      case 1: printf("Nome? ");
              fflush(stdin);
              gets(nome);
              printf("CPF? ");
              scanf("%d", &CPF);
              printf("Telefone? ");
              scanf("%d", &telefone);
              insereNovoNoh(&arvore,criaNovoNoh(nome,telefone,CPF),&hash);
              break;
      case 2: printf("Nome? ");
              fflush(stdin);
              gets(nome);
              printf("\nNome para localizar?");
              carinha = Localiza(hash.itens[geraIndice(nome)],nome);
            if(carinha)
            {
                printf("achei!\n");
                mostrarNoh(carinha);
                system("pause");
            }
            else
            {
                printf("\nNao tem ninguem.");
            }
            break;
      case 3: mostraEmOrdem(arvore);
               system("pause");
              break;

      case 4: mostraPreOrdem(arvore);
              break;

      case 5: mostraPosOrdem(arvore);
              break;

      case 6:printf("Nome a ser excluido? ");
              fflush(stdin);
              gets(nome);
              removeNoh(&arvore,criaNovoNoh(nome,telefone,CPF));
              break;


      case 0: exit(0);

    }

  } while (1);


  return 0;
}

int menu()
{
  int opc;

  printf("1.Inserir novo noh\n");
  printf("2.Localizar noh\n");
  printf("3.Mostrar nohs em ordem\n");
  printf("4.Mostrar nohs pre ordem\n");
  printf("5.Mostrar nohs pos ordem\n");
  printf("6.Excluir noh\n");
  printf("0.Sair do programa\n");
  printf("?: ");
  scanf("%d", &opc);

  return opc;
}
void inserirItemLista(t_hash *hash, t_dado *novo, noh *arvore)
{
  if (!hash->itens[arvore->indice]) {
    hash->itens[arvore->indice] = novo;
    hash->itens[arvore->indice]->pont = arvore;
  }
  else {
    while (hash->itens[arvore->indice]->prox)
      hash->itens[arvore->indice] = hash->itens[arvore->indice]->prox;
    hash->itens[arvore->indice]->prox = novo;
  }
}

noh* criaNovoNoh(string nome, int telefone, int CPF)
{
  noh* novo;

  novo =(noh*)malloc(sizeof(noh));
  strcpy(novo->nome, nome);
  novo->CPF = CPF;
  novo->telefone = telefone;
  novo->altura = 0;
  novo->direita = novo->esquerda = NULL;
  novo->indice = geraIndice(nome);
  return novo;
}

void insereNovoNoh(noh** arvore, noh* novo, t_hash *hash)
{
    if (!*arvore){
    *arvore = novo;
    inserirItemLista(hash, criaCelula(), *arvore);
    }
    else if ((strcmp((*arvore)->nome,novo->nome))>0)
      insereNovoNoh(&(*arvore)->esquerda, novo,hash);
    else if ((strcmp((*arvore)->nome, novo->nome))<0)
      insereNovoNoh(&(*arvore)->direita, novo,hash);

  // Faz o balanceamento da árvore
  balancearArvore(arvore);
}

void mostraEmOrdem(noh* arvore)
{
  if (arvore) {
    mostraEmOrdem(arvore->esquerda);
    mostrarNoh(arvore);
    mostraEmOrdem(arvore->direita);
  }
}

void mostraPreOrdem(noh* arvore)
{
  if (arvore) {
    mostrarNoh(arvore);
    mostraPreOrdem(arvore->esquerda);
    mostraPreOrdem(arvore->direita);
  }
}

void mostraPosOrdem(noh* arvore)
{

      if (arvore) {
    mostraPosOrdem(arvore->esquerda);
    mostraPosOrdem(arvore->direita);
    mostrarNoh(arvore);
  }
}

void removeNoh(noh** arvore, noh* novo)
{
  noh *aux = NULL;

  if (arvore) {

    // Localizar noh a ser excluído
    if ((strcmp((*arvore)->nome,novo->nome))>0)
      removeNoh(&(*arvore)->direita, novo);
    else if ((strcmp((*arvore)->nome, novo->nome))<0)
      removeNoh(&(*arvore)->esquerda, novo);


    // Achou o noh a ser excluído
    else if (!(*arvore)->direita) {
      aux = *arvore;
      *arvore = (*arvore)->esquerda;
      free(aux);
    }
    else if (!(*arvore)->esquerda) {
      aux = *arvore;
      *arvore = (*arvore)->direita;
      free(aux);
    }

    // Faz o balanceamento da árvore
    balancearArvore(arvore);
  }
}

void mostrarNoh(noh* no)
{
    if (no) {
    printf("Noh endereco...: %p\n", no);
    printf("Nome.........: %s\n", no->nome);
    printf("Telefone.....: %d\n", no->telefone);
    printf("CPF.........: %d\n", no->CPF);
    printf("Noh altura.....: %d\n", no->altura);
    printf("\n");

  }
  else {
    printf("Nao achou!!\n");
  }
}
 // Funcoes para balanceamento da arvore AVL

int calculaAltura(noh *no)
{
  int alt_esquerda = 0, alt_direita = 0;
  if (!no) {
    return -1;
  }
  alt_esquerda = calculaAltura(no->esquerda);
  alt_direita = calculaAltura(no->direita);
  if (alt_esquerda > alt_direita) {
    return alt_esquerda + 1;
  }
  else {
    return alt_direita + 1;
  }
}

int maior(int a, int b)
{
  return a > b ? a : b;
}

int altura(noh* no)
{
  if (no)
    return no->altura;
  return -1;
}

void ajustarAlturaArvore(noh* no)
{
   if (no)
     no->altura = 1 + maior(calculaAltura(no->esquerda), calculaAltura(no->direita));
}

int fatorBalanceamento(noh* arvore)
{
   if (arvore)
     return  (altura(arvore->direita) - altura(arvore->esquerda));
   return 0;
}

noh* rotacaoDireita(noh* arvore)
{
   printf("Fazendo uma rotacao direita...\n");
   noh* aux_e = arvore->esquerda;
   noh* aux_d = aux_e->direita;
   aux_e->direita = arvore;
   arvore->esquerda = aux_d;
   ajustarAlturaArvore(arvore->esquerda);
   ajustarAlturaArvore(arvore);
   return aux_e;
}

noh* rotacaoEsquerda(noh* arvore)
{
   printf("Fazendo uma rotacao esquerda...\n");
   noh* aux_d = arvore->direita;
   noh* aux_e = aux_d->esquerda;
   aux_d->esquerda = arvore;
   arvore->direita = aux_e;
   ajustarAlturaArvore(arvore->direita);
   ajustarAlturaArvore(arvore);
   return aux_d;
}


noh* rotacaoEsquerdaDireita(noh* arvore)
{

   arvore->esquerda = rotacaoEsquerda(arvore->esquerda);
   arvore = rotacaoDireita(arvore);
   return arvore;
}

noh* rotacaoDireitaEsquerda(noh* arvore)
{

   arvore->direita = rotacaoDireita(arvore->direita);
   arvore = rotacaoEsquerda(arvore);
   return arvore;
}
void inicializaHash(t_hash *hash)
{
  int i;
  for (i = 0; i < T; i++)
    hash->itens[i] = NULL;
}

t_dado *criaCelula()
{
  t_dado *novo;

  novo = (t_dado*)malloc(sizeof(t_dado));
  novo->prox = NULL;


  return novo;
}

int geraIndice(string nome)
{
  return strlen(nome) % T;
}

noh *Localiza(t_dado *lista,string nome)
{
    noh *aux;
    while(lista)
    {
        aux = lista->pont;
        if(strcmp(aux->nome,nome)==0)
        {
            return aux;
        }
        lista = lista->prox;
    }
    return NULL;
}

void balancearArvore(noh** arvore)
{
  ajustarAlturaArvore(*arvore);
  if (fatorBalanceamento(*arvore) < -1 && fatorBalanceamento((*arvore)->esquerda) <= 0) {
     *arvore = rotacaoDireita(*arvore);
  }
  else if (fatorBalanceamento(*arvore) > 1 && fatorBalanceamento((*arvore)->direita) >= 0) {
     *arvore = rotacaoEsquerda(*arvore);
  }
  else if (fatorBalanceamento(*arvore) < -1 && (fatorBalanceamento((*arvore)->esquerda) > 0)) {
     *arvore = rotacaoEsquerdaDireita(*arvore);
  }
  else if (fatorBalanceamento(*arvore) > 1 && (fatorBalanceamento((*arvore)->direita) < 0)) {
     *arvore = rotacaoDireitaEsquerda(*arvore);
  }
}
