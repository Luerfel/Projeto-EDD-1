#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> //necessário para usar setlocale

// structs
struct Data{
    int dia;
    int mes;
    int ano;
};typedef struct Data Data;

struct Tarefa{
int codigo;
char tarefa[30];
char projeto[30];
Data dataInicio;
Data dataTermino;
int status;
}; typedef struct Tarefa Tarefa;


struct No {
    Tarefa info;
    struct No *prox;
};typedef struct No No;

typedef struct Fila{
    No *ini;
    No *fim;
}Fila;

// Prototipos das funções

Fila* criaFila();
void insereFila(No*fim,Tarefa tarefa);
int menu(); 
void limparBuffer();
void inserirFila(Fila *fila,Tarefa tarefa);


int main() {
    setlocale(LC_ALL, "Portuguese");
    No* head = NULL; // Inicializa a lista vazia
    int opcao;
    opcao=menu(); 
    switch (opcao)
    {
    case 1:
        
        break;
    case 2:


    break;

    case 3:

    break;
    case 4:

    break;
    case 5:

    break;
    case 6:

    break;
    case 7:

    break;
    }
    
    
    
    

 
 



    
    

    return 0;
}
// cria a fila
Fila* criaFila(){
    Fila*f=(Fila*)malloc(sizeof(Fila));
    f->ini=f->fim= NULL;
}

// função que insere um elemento no fim da lista
No* insFim(No* fim,Tarefa tarefa){
    No *aux = fim;
    No *novo = malloc(sizeof(No));
    novo->info = tarefa;
    novo->prox = NULL; // como é uma fila o novo elemento adicionado aponta para NULL
    if(fim == NULL) { // Verifica se a lista esta vazia
    fim ->prox = novo;
    return novo;
    }
    // faz o ultimo elemento aponta para esse novo elemento;
    while (aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
    
    return novo;



}
void inserirFila(Fila *fila, Tarefa tarefa){
    fila->fim = insFim(fila->fim,tarefa);
    if (fila->ini == NULL){                      // verifica se a fila esta vazia
        fila->ini = fila->fim;
    }

}



// Função para imprimir o menu e selecioanr a opção
int menu(){
  int opcao;

    
    while(1){
    printf("   /\\"); 
    printf("\n  /  \\");
    printf("\n /____\\");
    printf("\nSistema de Gerenciamento de Tarefas Triangulus \n\n");
    printf("1 - Adicionar uma nova Tarefa\n");
    printf("2 - Modificar uma Tarefa.\n"); 
    printf("3 - Concluir Tarefa\n");
    printf("4 - Lista de Tarefas Pendentes\n");
    printf("5 - Lista de Tarefas Concluídas \n"); 
    printf("6 - Lista de Tarefas Concluídas com e sem Atrasos\n");
    printf("7 - Sair do Programa\n\n"); 
   
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    system("clear"); //limpa a tela


    if(opcao >= 1 && opcao <= 8) {
        return opcao;
} else {
        printf("OPÇÃO INVALIDA!! Aperta ENTER para continuar \n");
        setbuf(stdin,NULL); //limpa o buffer do teclado para forçar a pausa em getchar
        getchar();
        system("clear"); 
   




}




    }
}
// Essa função vamos usar para a limpeza de Buffer do nosso programa, ele vai fazer o serviço de ficar pegando caracter do buffer
void limparBuffer(){
    char c;
    while((c = getchar()) != 'n' && c!= EOF); 
}
