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
Tarefa criarTarefa();
int compararData(Data dataInicio,Data dataTermino);



int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    Tarefa tarefa;
    Fila *filaTarefas = criaFila();
    opcao=menu(); 
    switch (opcao)
    {
    case 1:
        tarefa = criarTarefa();
        inserirFila(filaTarefas,tarefa);
        printf("Codigo : %d\nNome : %s\nProjeto : %s\nData de inicio: %d/%d/%d\nPrazo de entrega : %d/%d/%d\nStatus : %d",tarefa.codigo,tarefa.tarefa,tarefa.projeto,tarefa.dataInicio.dia,tarefa.dataInicio.mes,tarefa.dataInicio.ano,tarefa.dataTermino.dia,tarefa.dataTermino.mes,tarefa.dataTermino.ano,tarefa.status);
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
Tarefa criarTarefa(){
    Tarefa nova;
    printf("Digite o codigo da tarefa a ser criada :\n");
    scanf("%d",&nova.codigo);
    system("clear"); //limpa a tela


    printf("Digite o nome da Tarefa use no maximo 30 caracteres : \n");
    getchar();
    fgets(nova.tarefa, 30, stdin);
    system("clear"); //limpa a tela



    printf("Digite o nome do Projeto use no maximo 30 caracteres : \n");
    fgets(nova.projeto, 30, stdin);
    system("clear"); //limpa a tela



    printf("Digite a data de inicio da Tarefa neste formato dd/mm/aaaa :\n ");
    scanf("%d/%d/%d", &nova.dataInicio.dia, &nova.dataInicio.mes, &nova.dataInicio.ano);
    system("clear"); //limpa a tela


   

    printf("Digite o prazo para a entrega da Tarefa neste formato dd/mm/aaaa: \n");
    scanf("%d/%d/%d", &nova.dataTermino.dia, &nova.dataTermino.mes, &nova.dataTermino.ano);
    system("clear"); //limpa a tela
    nova.status = compararData(nova.dataInicio,nova.dataTermino);
    


 return nova;

}

// cria a fila
Fila* criaFila(){
    Fila*f=(Fila*)malloc(sizeof(Fila));
    f->ini=f->fim= NULL;
}

// função que insere um elemento no fim da lista
No* insFim(No* fim,Tarefa tarefa){
    No *novo = malloc(sizeof(No)); // alocação dinamica
    novo->info = tarefa;   // o novo nó recebe a tarefa
    novo->prox = NULL; // como é uma fila o novo elemento adicionado aponta para NULL
    if(fim != NULL) { // Verifica se a lista esta vazia
        fim ->prox = novo;  // se a lista nao estiver vazia o nó anterior vai apontar para esse novo nó 
    }
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
// função que define os status automaticamente 
int compararData(Data dataInicio, Data dataTermino){
    if (dataInicio.ano>dataTermino.ano){
        return 1;
    }
    else if (dataInicio.ano!=dataTermino.ano){
        return -1;
    }
    else if (dataInicio.mes>dataTermino.mes){
        return 1;
    }
    else if(dataInicio.mes == dataTermino.mes && dataInicio.dia>dataTermino.dia){
        return 1;
    }
    else
     return -1;
    

}
