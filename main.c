#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> //necessário para usar setlocale
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

// funçoes 
fila* criaFila();
void insereFila(fila*f,Tarefa tarefa);
int menu(); 

int main() {
    setlocale(LC_ALL, "Portuguese");
    Lista* head = NULL; // Inicializa a lista vazia
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
    default:
        break;
    }
    
    
    
    

 
 



    
    

    return 0;
}
fila* criaFila(){
    fila*f=(fila*)malloc(sizeof(fila));
    f->ini=f->fim= NULL;
}
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
    if(opcao >= 1 && opcao <= 8) {
printf("Numero valido!\n");
} else {
printf("NUMERO INVALIDO!\nAperte qualquer tecla para continuar\n");


}




    }
}
