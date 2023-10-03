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


struct no {
    Tarefa info;
    struct no *prox;
};typedef struct no Lista;

typedef struct Fila{
    Lista *ini;
    Lista *fim;
}fila;

// Prototipos das funções

fila* criaFila();
void insereFila(fila*f,Tarefa tarefa);
int menu(); 
void limparBuffer();


int main() {
    setlocale(LC_ALL, "Portuguese");
    Lista* head = NULL; // Inicializa a lista vazia
    int opcao;
    opcao=menu(); 
    printf("%d ",opcao);
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
fila* criaFila(){
    fila*f=(fila*)malloc(sizeof(fila));
    f->ini=f->fim= NULL;
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
