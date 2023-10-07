#include <stdio.h>
#include <stdlib.h> 
#include <locale.h> //necessário para usar setlocale
#include <ctype.h>
#include <unistd.h>
#include <time.h> // necessário para comparar data de termino


// ESTRUTURAS
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

// PROTÓTIPOS DAS FUNÇÕES

// Protótipos das  Funções de Menu e texto
int menu(); 
void mensagemFinal();
void voltaMenu();

//Protótipos das Funções de Fila
Fila* criaFila();
void inserirFila(Fila *fila,Tarefa tarefa);
No * insFim(No *fim,Tarefa tarefa);

//protótipos das Funções de Tarefa
Tarefa criarTarefa();
void imprimirTarefa(Tarefa nova);
No concluirTarefa();
void editarTarefa(Fila * inicio, int codigo);

//Protótipos das Funções auxiliares
int compararData(Data dataInicio,Data dataTermino);
void limparTela();
void limparBuffer();
char* leituraString(char str[]);



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
            limparTela();
            break;
        }
        inserirFila(filaTarefas,tarefa);
        voltaMenu();
       
    

        break;
    case 2:


        limparTela();
        printf("Por gentileza digita o codigo da tarefa a ser editada :\n");
        scanf("%d",&codigo);
        editarTarefa(filaTarefas,codigo);

    break;

    case 3:
    voltaMenu();
        // limparTela();
        // printf("Por gentileza digita o codigo da tarefa a ser concluida :\n");
        // scanf("%d",&codigo);
        // concluirTarefa(filaTarefas,codigo);

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
    
    }while(resp=='s');

    return 0;
}


// funções da Tarefa! 
Tarefa criarTarefa(){
    Tarefa nova;
    char resp;
    printf("Digite o codigo da tarefa a ser criada :\n");
    scanf("%d",&nova.codigo);
    limparTela();

    printf("Digite o nome da Tarefa use no maximo 30 caracteres : \n");
    limparBuffer();
    leituraString(nova.tarefa);
    limparTela();




    printf("Digite o nome do Projeto use no maximo 30 caracteres : \n");
    leituraString(nova.projeto);
    limparTela();

    printf("Digite a data de inicio da Tarefa neste formato dd/mm/aaaa :\n");
    scanf("%d/%d/%d", &nova.dataInicio.dia, &nova.dataInicio.mes, &nova.dataInicio.ano);
    limparTela();
    



   

    printf("Digite o prazo para a entrega da Tarefa neste formato dd/mm/aaaa: \n");
    scanf("%d/%d/%d", &nova.dataTermino.dia, &nova.dataTermino.mes, &nova.dataTermino.ano);
    limparTela();
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

    
    limparTela();
    printf("Parabéns, a tarefa foi adicionada com sucesso! \n\n");
  
 return nova;

}

void editarTarefa(Fila * fila, int codigo){
    int opcao;
    No *aux = fila->ini;
    limparTela();


    if(aux==NULL){
        printf("FILA VAZIA!\n\n");
        voltaMenu();
        return;
    }

    while (aux->info.codigo!= codigo && aux->prox!=NULL)  // pecorre a lista ate achar um codigo igual ou ate o ultimo elemento
    {
    limparTela();

        aux = aux->prox;
    
    }
  
    if (aux->info.codigo == codigo){
        limparTela();
        printf("Tarefa encontrada!!\n\n");
        Tarefa tarefa = aux->info;
        imprimirTarefa(tarefa);
        printf("Digite o número do campo que deseja modificar:\n1. - Codigo\n2. - Nome da Tarefa\n3. - Nome do Projeto\n4. - Data de Início\n5. - Data de Término\n\n ");
        fflush(stdin);
        scanf("%d",&opcao);
        
        switch (opcao){
            case 1:
                printf("Codigo atual : %d\nDigite o novo Codigo : ",tarefa.codigo);
                scanf("%d",&tarefa.codigo);
                limparTela();
                aux->info = tarefa;
                imprimirTarefa(tarefa);
            
            break;
            
            case 2:
                printf("Nome atual : %s\nDigite o novo Nome : ",tarefa.tarefa);
                while(getchar()!='\n');
                leituraString(tarefa.tarefa);
                limparTela();
                aux->info = tarefa;
                imprimirTarefa(tarefa);

            break;

            case 3:
                printf("Nome do projeto atual : %s\nDigite o novo nome de projeto: ",tarefa.projeto);
                while(getchar()!='\n');
                leituraString(tarefa.projeto);
                aux->info = tarefa;
                imprimirTarefa(tarefa);

            break;

            case 4:
                printf("Data de inicio atual : %d/%d/%d\nDigite a nova data : ", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
                scanf("%d/%d/%d", &tarefa.dataInicio.dia, &tarefa.dataInicio.mes, &tarefa.dataInicio.ano);
                aux->info = tarefa;
                imprimirTarefa(tarefa);
            
            break;

            case 5:
                printf("Data de Termino atual : %d/%d/%d\nDigite a nova data : ", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
                scanf("%d/%d/%d", &tarefa.dataTermino.dia, &tarefa.dataTermino.mes, &tarefa.dataTermino.ano);
                aux->info = tarefa;
                imprimirTarefa(tarefa);

            break;
        }


    } else {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
        voltaMenu();
        return;
    }

  
}

void imprimirTarefa(Tarefa nova){
    printf("CODIGO : %d\nNOME : %s\nPROJETO : %s\nDATA DE INICIO : %d/%d/%d\nDATA DE TERMINO : %d/%d/%d\nSTATUS : %d\n\n",nova.codigo,nova.tarefa,nova.projeto,nova.dataInicio.dia
    ,nova.dataInicio.mes,nova.dataInicio.ano,nova.dataTermino.dia,nova.dataTermino.mes,nova.dataTermino.ano,nova.status);

}

No concluirTarefa(Fila * fila, int codigo){
    char opcao;
    No *aux = fila->ini;
    limparTela();


    if(aux==NULL){
        printf("FILA VAZIA!\n\n");
        voltaMenu();
    }

    while (aux->info.codigo!= codigo && aux->prox!=NULL)  // pecorre a lista ate achar um codigo igual ou ate o ultimo elemento
    {
        limparTela();
        aux = aux->prox;
    }
  
    if (aux->info.codigo == codigo){
        limparTela();
        printf("Tarefa encontrada!!\n\n");
        Tarefa tarefa = aux->info;
        imprimirTarefa(tarefa);

        printf("Deseja marcar como concluida? (s/n):");
        fflush(stdin);
        scanf("%c",&opcao);

        if (opcao ==  's') {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            Data hoje;
            hoje.ano = tm.tm_year + 1900;
            hoje.mes = tm.tm_mon + 1;
            hoje.dia = tm.tm_mday;

            if (compararData(tarefa.dataInicio, hoje) == -1) {
                tarefa.status = 0;
                limparTela();
                aux->info = tarefa;
                imprimirTarefa(tarefa);
            }
            if (compararData(tarefa.dataInicio, hoje) == 1) {
                tarefa.status = 1;
                limparTela();
                aux->info = tarefa;
                imprimirTarefa(tarefa);
            }
        }

    } else {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
        voltaMenu();
    } 
} 

// Funções da fila 
Fila* criaFila(){
    Fila*f=(Fila*)malloc(sizeof(Fila));
    f->ini=f->fim= NULL;
    return f;
}

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


// função de menu e texto
int menu(){
  int opcao;

  char desenho[] = "   /\\\n  /  \\\n /____\\";

  printf("%s", desenho);
    
    while(1){
    limparTela();
    limparBuffer();
    printf("%s", desenho);
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
    limparTela();


  // validação de entrada
    if(opcao >= 1 && opcao <= 8) {
        return opcao;
} else {
        printf("OPÇÃO INVALIDA!! Aperta ENTER para continuar \n");
        setbuf(stdin,NULL); //limpa o buffer do teclado para forçar a pausa em getchar
        getchar();
        limparTela();

   




}




    }
}

void mensagemFinal(){
    limparTela();
       printf("   /\\"); 
    printf("\n  /  \\");
    printf("\n /____\\");
    printf("  Sistema de gerenciamento Triangulus\n");
    printf("\nFim do programa!\n");
    printf("Obrigado por usar nosso software. Ficamos felizes em poder ajudar. Até a próxima vez!\n");
}

void voltaMenu(){

    char opcao;
    printf("Deseja voltar para o menu principal? S/N\n");
    while(getchar()!='\n');
    opcao = getchar();
    if(tolower(opcao)=='s'){
        limparTela();
        return;

    }
    else if(tolower(opcao=='n')){
        limparTela();
        mensagemFinal();
        exit(0);
    }
    else {
        printf("Opção inválida. Por favor, digite S para voltar ao menu ou N para sair \n");
        voltaMenu();
    }



}


// funções auxiliares 
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
void limparTela(){
printf("\033[H\033[2J"); // Limpa tela no Linux/Mac
printf("\033[2J"); // Limpa tela no Windows


}
void limparBuffer(){
	int c;
	while((c = getchar()) != '\n' && c != EOF);

}
char* leituraString(char str[]) {
    int i = 0;
    char ch;

  //ler cada caracter até enter
    while((ch = getchar()) != '\n') {
        str[i++] = ch;
  }

  //adicionar null terminator
    str[i] = '\0';


}