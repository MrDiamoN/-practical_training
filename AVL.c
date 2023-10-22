#include <malloc.h>
#include <stdio.h>

typedef struct No {
  int valor;
  int altura;
  struct No *noDir;
  struct No *noEsq;
} NO;

NO *sWF(NO *raiz, int valor, NO **paiAtual) {
  NO *atual = raiz;
  *paiAtual = NULL;

  while (atual != NULL) {
    if (atual->valor == valor)
      return atual;

    *paiAtual = atual;
    if (valor > atual->valor)
      atual = atual->noDir;
    else
      atual = atual->noEsq;
  }

  return NULL;
}

int isSonDir(NO *no, NO *pai) {
  if (pai != NULL)
    return no->valor > pai->valor ? 1 : 0;//Operador ternario (? 1 : 0)

  return 0;
}

int isSonEsq(NO *no, NO *pai) {
  if (pai != NULL)
    return no->valor < pai->valor ? 1 : 0;

  return 0;
}

NO *delNoChild(NO *node, NO *father, NO *root) {
  free(node);

  if (father != NULL) {
    if (isSonDir(node, father) == 1)
      father->noDir = NULL;
    else if (isSonEsq(node, father) == 1)
      father->noEsq = NULL;

    return root;
  }

  return NULL;
}

NO *deleteOneChildDir(NO *node, NO *father, NO *root) {
  if (father != NULL) {
    if (isSonDir(node, father) == 1)
      father->noDir = node->noDir;
    else if (isSonEsq(node, father) == 1)
      father->noEsq = node->noDir;

    free(node);
    return root;
  }

  NO *valor = node->noDir;
  free(node);

  return valor;
}

NO *deleteOneChildEsq(NO *node, NO *father, NO *root) {
  if (father != NULL) {
    if (isSonDir(node, father) == 1)
      father->noDir = node->noEsq;
			
    else if (isSonEsq(node, father) == 1)
      father->noEsq = node->noEsq;

    free(node);
    return root;
  }

  NO *valor = node->noEsq;
  free(node);

  return valor;
}

NO *deleteTwoChild(NO *node, NO *father, NO *root) {
  NO *fatherPromoted = node;
  NO *promoted = node->noEsq;

  while (promoted->noDir != NULL) {
    fatherPromoted = promoted;
    promoted = promoted->noDir;
  }

  if (fatherPromoted != node) {
    fatherPromoted->noDir = promoted->noEsq;
    promoted->noEsq = node->noEsq;
  }

  promoted->noDir = node->noDir;

  if (father != NULL) {
    if (isSonDir(node, father) == 1)
      father->noDir = promoted;
    else if (isSonEsq(node, father) == 1)
      father->noEsq = promoted;

    free(node);

    return root;
  }

  free(node);
  return promoted;
}

NO *removerNo(NO *root, int valor) {
  NO *curr, *father;

  if (root == NULL)
    return NULL;
  curr = sWF(root, valor, &father);

  if (curr->noDir == NULL && curr->noEsq == NULL) {
    return delNoChild(curr, father, root);
  }

  if (curr->noDir != NULL && curr->noEsq == NULL) {
    return deleteOneChildDir(curr, father, root);
  }

  if (curr->noEsq != NULL && curr->noDir == NULL) {
    return deleteOneChildEsq(curr, father, root);
  }

  
  return deleteTwoChild(curr, father, root);
}

int AltNO(NO *no){
  if (no == NULL)
    return -1;
  else 
    return no -> altura;
}

int FatorNO(NO *no){
  return  labs (AltNO(no->noEsq) - AltNO (no->noDir));
}

int Maior (int x, int y){
  if( x > y)
    return x;
  else
    return y;
}

NO * rotacaoLL (NO *raiz){
   NO *aux;
  aux = raiz-> noEsq;
  raiz -> noEsq = aux -> noDir;
  aux -> noDir = raiz;
  raiz -> altura = Maior (AltNO(raiz -> noEsq),AltNO(raiz -> noDir )) + 1;
  aux -> altura = Maior (AltNO (aux->noEsq),raiz -> altura) + 1;
  raiz = aux;
  
  return raiz;
}

NO * rotacaoRR (NO *raiz){
   NO *aux;
  aux = raiz-> noDir;
  raiz -> noDir = aux -> noEsq;
  aux -> noEsq = raiz;
  raiz -> altura = Maior (AltNO(raiz -> noEsq),AltNO(raiz -> noDir )) + 1;
  aux -> altura = Maior (AltNO (aux->noDir),raiz -> altura) + 1;
  raiz = aux;
  
  return raiz;
}

 void rotacaoLR (NO *raiz){
  rotacaoRR(& *raiz ->noEsq);
  rotacaoLL(raiz);
  
}

 void rotacaoRL(NO *raiz){
  rotacaoLL(& *raiz -> noDir);
  rotacaoRR(raiz);
  
}

NO *inserirNo(NO *raiz, NO *filho) {
  printf("\n\n================================\n");
  printf("FUNÇÃO... START\n");
  printf("NO FILHO: %d\n", filho->valor);

  if (raiz == NULL) {

    printf("\nCONDICAO DE PARADA!\n");
    printf("NO: %d\n\n", filho->valor);
    printf("FUNÇÃO... STOP\n");
    return filho;
  }
	
  if (raiz != NULL) {
    printf("RAIZ: %d\n", raiz->valor);
    raiz->altura +=1 ;
  } else {
    printf("RAIZ NULA\n");
  }


  if (filho->valor > raiz->valor) {
    printf("\nFILHO MAIOR QUE RAIZ\n");
    printf("NO: %d\n", filho->valor);
    printf("RAIZ: %d\n\n", raiz->valor);
    raiz->noDir = inserirNo(raiz->noDir, filho);
    printf("\nNO %d SUB-ARVORE DA DIREITA\n", filho->valor);
    printf("\nDIFERENÇA DE ALTURA = %d\n",FatorNO(raiz));
    if (FatorNO (raiz) >= 2){
      
      if (raiz -> noDir -> valor < filho -> valor){
        raiz = rotacaoRR(raiz);
      }
      else{
         rotacaoRL(raiz);
      }
    }
    
  } else {
    printf("\nFILHO MENOR QUE RAIZ\n");
    printf("NO: %d\n", filho->valor);
    printf("RAIZ: %d\n", raiz->valor);
    raiz->noEsq = inserirNo(raiz->noEsq, filho);
    printf("\nNO %d SUB-ARVORE DA ESQUERDA\n", filho->valor);
    printf("\nDIFERENÇA DE ALTURA = %d\n",FatorNO(raiz));
    if (FatorNO (raiz) >= 2){
      
      if (filho -> valor < raiz -> noEsq -> valor){
        raiz = rotacaoLL(raiz);
      }
      else{
        rotacaoLR(raiz);
      }
    }
    
  }
  
  printf("FUNÇÃO... END!\n");
  printf("NO: %d\n", filho->valor);
  printf("RAIZ: %d\n", raiz->valor);
  
  

  return raiz;
}

void imprimir(NO *raiz) {
  if (raiz != NULL) {
    printf("%d", raiz->valor);
    printf("<-");
    imprimir(raiz->noEsq);
    imprimir(raiz->noDir);
    printf("->");
  }
}

/*void imprimir(No *raiz, int nivel){
    int i;
    if(raiz){
        imprimir(raiz->noDir, nivel + 1);
        printf("\n\n");

        for(i = 0; i < nivel; i++)
            printf("\t");

        printf("%d", raiz->valor);
        imprimir(raiz->noEsq, nivel + 1);
    }
}*/

void executar(NO *raiz){	
	int i;
  for (i = 0; i < 8; i++) {
    int numInf;
    printf("INSIRA QUALQUER NUMERO\n");
    scanf("%d", &numInf);

    NO *pFilho = (NO *)malloc(sizeof(NO));
    pFilho->valor = numInf;
    pFilho->altura = 0;
    pFilho->noEsq = NULL;
    pFilho->noDir = NULL;

    raiz = inserirNo(raiz, pFilho);
  }

	 imprimir(raiz);
}
int main(void) {
  NO *raiz = NULL;
executar(raiz);
	/*
  int i;
  for (i = 0; i < 8; i++) {
    int numInf;
    printf("INSIRA QUALQUER NUMERO\n");
    scanf("%d", &numInf);

    NO *pFilho = (NO *)malloc(sizeof(NO));
    pFilho->valor = numInf;
    pFilho->altura = 0;
    pFilho->noEsq = NULL;
    pFilho->noDir = NULL;

    raiz = inserirNo(raiz, pFilho);
  }
  */
  
  imprimir(raiz);

  return 0;
}