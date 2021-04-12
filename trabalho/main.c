/* Alunos:
Gabriel Alves Hussein   17/0103200
Victor Amaral Cerqueira 17/0164411
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definicoes Gerais
typedef int item;
#define key(A) (A)
#define less(A,B) (key(A) < key(B))
#define exch(A,B) {item t=A; A=B, B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct Lista{
    char nome[100];
    int prioridade;
    double preco;
}LISTA;

// Chamada das Funcoes
void mostraMenu(int totalProdutos);
void exibeProdutos(LISTA *lista, int TotalProdutos);
void ordena(LISTA *v, int l, int r, int escolha);
void mergePrioridade(LISTA *v, int l, int r1, int r2);
void mergePreco(LISTA *v, int l, int r1, int r2);
void cadastroProduto (LISTA *lista, int totalProdutos);
int selecionarProdutos (LISTA *produtosMercado, LISTA *lista, int totalProdutos, int produtosSelecionados);
void geraLista(LISTA *lista, int produtosSelecionados);
int criaMercado(LISTA *produtosMercado, int totalProdutos);

int main(){
    LISTA produtosMercado[100];
    LISTA lista[100];
    int opcao, orcamento = 0, totalProdutos = 0, escolha, produtosSelecionados = 0;
    totalProdutos = criaMercado(produtosMercado, totalProdutos);

    do{
        mostraMenu(totalProdutos);
        scanf("%d",&opcao);
        system("clear");
        switch(opcao){
        case 1:
            exibeProdutos(produtosMercado, totalProdutos);
            break;
        case 2:
            cadastroProduto(produtosMercado, totalProdutos);
            totalProdutos++;
            getc(stdin);
            printf("Aperte enter para voltar ao menu.");
            break;
        case 3:
            produtosSelecionados = selecionarProdutos(produtosMercado, lista, totalProdutos, produtosSelecionados);
            getc(stdin);
            break;
        case 4:
            printf("1 - se deseja ordenar sua lista de compras por prioridade\n2 - caso deseje ordenar por preco\nDigite:");
            scanf("%d", &escolha);
            while(escolha != 1 && escolha != 2){
                printf("Valor invalido, digite um novo valor: ");
                scanf("%d", &escolha);
            }
            ordena(lista, 0, produtosSelecionados-1, escolha);
            geraLista(lista, produtosSelecionados);
            break;
        }
  }while(opcao != 0);

    return 0;
}

// Desenvolvimento das funcoes 
void mostraMenu(int totalProdutos){
  printf("\n");
  printf(" ====================================================\n");
  printf("|             >>>>>>>>> Menu <<<<<<<<<               |\n");
  printf("|            %d produto(s) cadastrado(s)             |\n", totalProdutos);
  printf("| 1 - Exibir produtos                                |\n");
  printf("| 2 - Cadastra novo Produto                          |\n");
  printf("| 3 - Selecionar produtos para lista                 |\n");
  printf("| 4 - Gerar lista de compras                         |\n");
  printf("| 0 - Sair                                           |\n");
  printf(" ====================================================\n");
  printf("Sua opcao: ");
}

void ordena(LISTA *v, int l, int r, int escolha){
    if(l>=r) return;
    int meio = (r+l)/2;
    
    ordena(v, l, meio, escolha);
    ordena(v, meio+1, r, escolha);

    if(escolha == 1)
        mergePrioridade(v, l, meio, r);
    else 
        mergePreco(v, l, meio, r);
    
}

void mergePrioridade(LISTA *v, int l, int r1, int r2){
    LISTA v2[100];
    int k = 0;
    int i = l;
    int j = r1 + 1;
    while (i <= r1 && j <= r2)
    {
        if (less(v[i].prioridade, v[j].prioridade))
            v2[k++] = v[i++];
        else
            v2[k++] = v[j++];
    }

    while (i <= r1)
        v2[k++] = v[i++];
    while (j <= r2)
        v2[k++] = v[j++];

    k = 0;
    for (int i = l; i <= r2; i++)
    {
        v[i] = v2[k++];
    }

    return;
}

void mergePreco(LISTA *v, int l, int r1, int r2){
    LISTA v2[100];
    int k = 0;
    int i = l;
    int j = r1 + 1;
    while (i <= r1 && j <= r2)
    {
        if (less(v[i].preco, v[j].preco))
            v2[k++] = v[i++];
        else
            v2[k++] = v[j++];
    }

    while (i <= r1)
        v2[k++] = v[i++];
    while (j <= r2)
        v2[k++] = v[j++];

    k = 0;
    for (int i = l; i <= r2; i++)
    {
        v[i] = v2[k++];
    }

    return;
}

void cadastroProduto (LISTA *produtosMercado, int totalProdutos) {

    printf("Digite o nome do produto a ser cadastrado: \n");
    scanf(" %[^\n]s", produtosMercado[totalProdutos].nome);

    printf("Digite o preco do produto: \n");
    scanf("%lf", &produtosMercado[totalProdutos].preco);
}

void exibeProdutos(LISTA *lista, int TotalProdutos){
    for(int i = 0; i < TotalProdutos; i++){
        printf("%d - Nome: %s\nPreco: R$%.2lf\n\n", i+1, lista[i].nome, lista[i].preco);
    } 
}

int selecionarProdutos (LISTA *produtosMercado, LISTA *lista, int totalProdutos, int produtosSelecionados){
    exibeProdutos(produtosMercado, totalProdutos);
    int escolha;
    int selecaoProduto = 0;
    int prioridade = 0;
    printf("Produtos selecionados ate o momento: %d\n", produtosSelecionados);
    printf("Digite o numero produto que deseja adicionar a lista:\n");
    scanf("%d", &selecaoProduto);
    printf("Digite a prioridade de compra desse produto(Quanto menor o numero maior a prioridade, menor valor e 1):\n");
    while(scanf("%d", &prioridade)<1){
        printf("Prioridade invalida, favor digitar valores maiores ou iguais a 1");
    }
    produtosMercado[selecaoProduto-1].prioridade = prioridade;
    lista[produtosSelecionados] = produtosMercado[selecaoProduto-1];
    produtosSelecionados++;
    printf("Produto adicionado a lista com sucesso!");

    printf("Deseja adicionar um novo produto? (1 - Sim, 2 - Nao)");
    scanf("%d", &escolha);    
    if(escolha == 1){
        system("clear");
        selecionarProdutos(produtosMercado, lista, totalProdutos, produtosSelecionados);
    }
    else
        return produtosSelecionados;
}

void geraLista(LISTA *lista, int produtosSelecionados){
    double totalPreco = 0.0, orcamento = 0.0;
    int indiceCompraveis = 0, indiceIndisponiveis = 0;

    LISTA produtosCompraveis[100];
    LISTA produtosIndisponiveis[100];

    printf("Digite seu orcamento: R$");
    scanf("%lf", &orcamento);
    
    for(int i = 0; i < produtosSelecionados; i++){
        if(totalPreco + lista[i].preco <= orcamento){
            totalPreco = totalPreco + lista[i].preco;
            produtosCompraveis[indiceCompraveis] = lista[i];
            indiceCompraveis++;
        } else if (totalPreco + lista[i].preco > orcamento){
            produtosIndisponiveis[indiceIndisponiveis] = lista[i];
            indiceIndisponiveis++;
        }
    }

    printf("Lista gerada, segue possibilidade de produtos baseada no orcamento disponivel:\n");
    printf("Produtos possiveis de se comprar:\n");
    for(int i = 0; i < indiceCompraveis; i++){
        printf("%d - Nome: %s\n Prioridade: %d\nPreco: %.2lf\n\n", i+1, produtosCompraveis[i].nome, produtosCompraveis[i].prioridade, produtosCompraveis[i].preco);
    } 
    printf("Produtos indisponiveis com o orcamento atual:\n");
    for(int i = 0; i < indiceIndisponiveis; i++){
        printf("%d - Nome: %s\n Prioridade: %d\nPreco: %.2lf\n\n", i+1, produtosIndisponiveis[i].nome, produtosIndisponiveis[i].prioridade, produtosIndisponiveis[i].preco);
    } 
    printf("Troco restante apos realizacao das compras: R$%.2lf\n", orcamento-totalPreco);
}

int criaMercado(LISTA *produtosMercado, int totalProdutos){
    strcpy(produtosMercado[0].nome, "Amendoim");
    produtosMercado[0].preco = 4.99;
    totalProdutos++;
    strcpy(produtosMercado[1].nome, "Arroz");
    produtosMercado[1].preco = 24.99;
    totalProdutos++;
    strcpy(produtosMercado[2].nome, "Feijao");
    produtosMercado[2].preco = 9.19;
    totalProdutos++;
    strcpy(produtosMercado[3].nome, "Acucar");
    produtosMercado[3].preco = 4.19;
    totalProdutos++;
    strcpy(produtosMercado[4].nome, "Sal");
    produtosMercado[4].preco = 2.39;
    totalProdutos++;
    strcpy(produtosMercado[5].nome, "Pao");
    produtosMercado[5].preco = 14.99;
    totalProdutos++;
    strcpy(produtosMercado[6].nome, "Milho");
    produtosMercado[6].preco = 2.99;
    totalProdutos++;
    strcpy(produtosMercado[7].nome, "Farinha");
    produtosMercado[7].preco = 6.99;
    totalProdutos++;
    strcpy(produtosMercado[8].nome, "Farofa temperada");
    produtosMercado[8].preco = 8.99;
    totalProdutos++;
    strcpy(produtosMercado[9].nome, "Alface");
    produtosMercado[9].preco = 1.99;
    totalProdutos++;
    strcpy(produtosMercado[10].nome, "Tomate");
    produtosMercado[10].preco = 4.99;
    totalProdutos++;
    strcpy(produtosMercado[11].nome, "Fuba");
    produtosMercado[11].preco = 3.99;
    totalProdutos++;
    strcpy(produtosMercado[12].nome, "Ovo");
    produtosMercado[12].preco = 9.99;
    totalProdutos++;

    return totalProdutos;
}