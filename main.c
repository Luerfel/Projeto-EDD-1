#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> //necessário para usar setlocale
#include <ctype.h>
#include <unistd.h>

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
void inserirFila(Fila *fila,Tarefa tarefa);
void mensagemFinal();
Tarefa criarTarefa();
int compararData(Data dataInicio,Data dataTermino);
void editarTarefa(Fila * inicio, int codigo);
void imprimirTarefa(Tarefa nova);
void voltaMenu();


int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao; // variavel auxiliar do menu
    int codigo;
    char resp='s'; // variavel auxiliar
    Tarefa tarefa;
    Fila *filaTarefas = criaFila();
    do{
    opcao=menu(); 

    switch (opcao)
    {
    case 1:
        tarefa = criarTarefa();
        imprimirTarefa(tarefa);
        if(tarefa.status==3){
            system("clear");
            goto fim;
        }
        inserirFila(filaTarefas,tarefa);
        voltaMenu();
       
    

        break;
    case 2:


        system("clear");
        printf("Por gentileza digita o codigo da tarefa a ser editada :\n");
        scanf("%d",&codigo);
        editarTarefa(filaTarefas,codigo);

    break;

    case 3:
     voltaMenu();
       

    break;
    case 4:
    voltaMenu();
    break;
    case 5:
    voltaMenu();

    break;
    case 6:
    voltaMenu();

    break;
    case 7:
        mensagemFinal();
        return 0;

    return 0;
    break;
    }
    fim:
    }while(resp=='s');
    
    

 
 



    
    

    return 0;
}
Tarefa criarTarefa(){
    Tarefa nova;
    char resp;
    printf("Digite o codigo da tarefa a ser criada :\n");
    scanf("%d",&nova.codigo);
    system("clear"); //limpa a tela


    printf("Digite o nome da Tarefa use no maximo 30 caracteres : \n");
    while(getchar()!='\n');
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
    imprimirTarefa(nova);
    printf("Antes de finalizar, certifique-se de que todos os campos estão preenchidos como deseja.\n");
    
    printf("Para SALVAR a tarefa, digite 'S'. Para DESCARTAR, digite 'N'\n");
    do{
        while(getchar()!='\n'); // limpeza do buffer
        resp = tolower(getchar());
        
        
        if(resp != 's' && resp != 'n'){
            printf("RESPOSTA INVALIDA! Lembre-se de digitar s para confirmar, n para descartar a tarefa!\n ");
            
            
            continue;
            }
            else if (resp =='n'){
                printf("Vamos voltar ao menu principal. Pressione Enter para prosseguir\n");
                while(getchar()!='\n');
                nova.status = 3;
                getchar();
                return nova;
            }
        }
         while(resp!= 's');

    
    system("clear");
    printf("Parabéns, a tarefa foi adicionada com sucesso! \n\n");
  
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

    system("clear");
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

  // validação de entrada
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

void mensagemFinal(){
      system("clear");
       printf("   /\\"); 
    printf("\n  /  \\");
    printf("\n /____\\");
    printf("  Sistema de gerenciamento Triangulus\n");
    printf("\nFim do programa!\n");
    printf("Obrigado por usar nosso software. Ficamos felizes em poder ajudar. Até a próxima vez!\n");
}

void editarTarefa(Fila * fila, int codigo){
    int opcao;
    No *aux = fila->ini;
    system("clear");

    if(aux==NULL){
        printf("FILA VAZIA!\n\n");
        voltaMenu();
    }

    while (aux->info.codigo!= codigo && aux->prox!=NULL)  // pecorre a lista ate achar um codigo igual ou ate o ultimo elemento
    {
        system("clear");
        aux = aux->prox;
    
    }
  
    if (aux->info.codigo == codigo){
        system("clear");
        printf("Tarefa encontrada!!\n\n");
        Tarefa tarefa = aux->info;
        imprimirTarefa(tarefa);
        printf("Digite o número do campo que deseja modificar:\n1 - Codigo\n2 - Tarefa\n3 - Projeto\n4 - Data de Início\n5 - Data de Término\n\n ");
        fflush(stdin);
        scanf("%d",&opcao);
        switch (opcao){
            case 1:
            printf("Codigo atual : %d\nDigite o novo Codigo : ",tarefa.codigo);
            scanf("%d",&tarefa.codigo);
            imprimirTarefa(tarefa);
            
            break;
            
            case 2:

            break;

            case 3:

            break;

            case 4:

            break;

            case 5:

            break;
        }


    }
    else {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
        voltaMenu();
      }
        
  
  
}
void imprimirTarefa(Tarefa nova){
    printf("Codigo : %d\nNOME : %s\nPROJETO : %s\nDATA DE INICIO : %d/%d/%d\nDATA DE TERMINO : %d/%d/%d\nSTATUS : %d\n\n",nova.codigo,nova.tarefa,nova.projeto,nova.dataInicio.dia
    ,nova.dataInicio.mes,nova.dataInicio.ano,nova.dataTermino.dia,nova.dataTermino.mes,nova.dataTermino.ano,nova.status);

}

void voltaMenu(){

    char opcao;
    printf("Deseja voltar para o menu principal? S/N\n");
    while(getchar()!='\n');
    opcao = getchar();
    if(tolower(opcao)=='s'){
        main();

    }
    else if(tolower(opcao=='n')){
        mensagemFinal();
        exit(0);
    }
    else {
        printf("Opção inválida. Por favor, digite S para voltar ao menu ou N para sair \n");
        voltaMenu();
    }



}