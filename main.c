#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //necessário para usar setlocale
#include <ctype.h>
#include <unistd.h>
#include <time.h> // necessário para comparar data de termino
// vamos usar para validar a entrada de dados do tipo DATA
#define MAX_DIA 31
#define MAX_MES 12

// ESTRUTURAS
struct Data
{
    int dia;
    int mes;
    int ano;
};
typedef struct Data Data;

struct Tarefa
{
    int codigo;
    char tarefa[30];
    char projeto[30];
    Data dataInicio;
    Data dataTermino;
    int status;
};
typedef struct Tarefa Tarefa;

struct No
{
    Tarefa info;
    struct No *prox;
};
typedef struct No No;

typedef struct Fila
{
    No *ini;
    No *fim;
} Fila;

// PROTÓTIPOS DAS FUNÇÕES

// Protótipos das  Funções de Menu e texto
int menu();
void mensagemFinal();
void voltaMenu();
void filaVazia();

// Protótipos das Funções de Fila
Fila *criaFila();
void inserirFila(Fila *fila, Tarefa tarefa);
No *insFim(No *fim, Tarefa tarefa);
int percorrerLista(Fila *fila, int codigo);
void retiraFila(Fila *fila, int codigo);

// protótipos das Funções de Tarefa
Tarefa criarTarefa();
void imprimirTarefa(Tarefa nova);
Tarefa concluirTarefa();
void editarTarefa(Fila *inicio, int codigo);
Data lerDataValida();
int compararData(Data dataInicio, Data dataTermino);

// Protótipos das Funções auxiliares
void limparTela();
void limparBuffer();
char *leituraString(char str[]);
int lerCodigo();
void dataAtual(Data *data);
void pausaEnter();
char validarOpcao();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao; // variavel auxiliar do menu
    int codigo;
    char resp = 's'; // variavel auxiliar
    Tarefa tarefa;
    Fila *filaTarefas = criaFila();
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            tarefa = criarTarefa();
            imprimirTarefa(tarefa);
            if (tarefa.status == 3)
            {
                limparTela();
                break;
            }
            inserirFila(filaTarefas, tarefa);
            voltaMenu();

            break;
        case 2:

            if (filaTarefas->ini == NULL){filaVazia();break;}
            limparTela();
            printf("Por gentileza digita o codigo da tarefa a ser editada :\n");
            codigo = lerCodigo();
            editarTarefa(filaTarefas, codigo);

            break;

        case 3:

            limparTela();

            if(filaTarefas->ini==NULL){filaVazia();break;}
            printf("Por gentileza digita o codigo da tarefa a ser concluida :\n");
            codigo = lerCodigo();
            opcao = percorrerLista(filaTarefas, codigo);
            if (opcao == 1)
            {
                concluirTarefa(filaTarefas, codigo);
            }
            else if (opcao == 0)
            {
                printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
                voltaMenu();
                break;
            }
            break;
        case 4:
            pausaEnter();
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

    } while (resp == 's');

    return 0;
}

// funções da Tarefa!

Tarefa criarTarefa()
{
    Tarefa nova;
    char resp;
    nova.codigo = lerCodigo();
    limparTela();

    printf("Digite o nome da Tarefa use no maximo 30 caracteres : \n");

    leituraString(nova.tarefa);
    limparTela();

    printf("Digite o nome do Projeto use no maximo 30 caracteres : \n");
    leituraString(nova.projeto);
    limparTela();

    printf("Digite a data de inicio da Tarefa neste formato dd/mm/aaaa :\n");
    nova.dataInicio = lerDataValida();
    limparTela();

    printf("Digite a data de termino da tarefa neste formato dd/mm/aaaa: \n");
    nova.dataTermino = lerDataValida();
    limparTela();
    nova.status = compararData(nova.dataInicio, nova.dataTermino);
    imprimirTarefa(nova);
    printf("Antes de finalizar, certifique-se de que todos os campos estão preenchidos como deseja.\n");

    printf("Para SALVAR a tarefa, digite 'S'. Para DESCARTAR, digite 'N'\n");
    do
    {
        resp = tolower(getchar());
        limparBuffer();

        if (resp != 's' && resp != 'n')
        {
            printf("RESPOSTA INVALIDA! Lembre-se de digitar s para confirmar, n para descartar a tarefa!\n ");

            continue;
        }
        else if (resp == 'n')
        {
            printf("Vamos voltar ao menu principal.\n");
            nova.status = 3;
            pausaEnter();
            return nova;
        }
    } while (resp != 's');

    limparTela();
    printf("Parabéns, a tarefa foi adicionada com sucesso! \n\n");

    return nova;
}

Data lerDataValida()
{

    do
    {
        Data data;
        if (scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano) != 3)
        {
            printf("Formato de data invalido, tente novamente!\nPor favor digite a data neste formato dd/mm/aaaa ex: 19/03/2023\n");
            limparBuffer();
            continue;
        }

        if (data.dia < 1 || data.dia > MAX_DIA)
        {
            printf("Dia invalido, deve ser entre 1 e %d\nPor favor digite a data neste formato dd/mm/aaaa ex: 19/03/2023\n", MAX_DIA);
            limparBuffer();
            continue;
        }

        if (data.mes < 1 || data.mes > MAX_MES)
        {
            printf("Mes invalido, deve ser entre 1 e %d\nPor favor digite a data neste formato dd/mm/aaaa ex: 19/03/2023\n", MAX_MES);
            limparBuffer();
            continue;
        }
        if (data.ano < 1000 || data.ano > 9999)
        {
            printf("Ano inválido. Lembre-se que a formatação correta pede o ano com todos os seus 4 dígitos\nPor favor digite a data neste formato dd/mm/aaaa ex: 19/03/2023\n");
            limparBuffer();
            continue;
        }
        limparBuffer();
        return data; // data válida

    } while (1);
}

int compararData(Data dataInicio, Data dataTermino)
{
    if (dataInicio.ano > dataTermino.ano)
    {
        return 1;
    }
    else if (dataInicio.ano != dataTermino.ano)
    {
        return 0;
    }
    else if (dataInicio.mes > dataTermino.mes)
    {
        return 1;
    }
    else if (dataInicio.mes == dataTermino.mes && dataInicio.dia > dataTermino.dia)
    {
        return 1;
    }
    else
        return 0;
}

void editarTarefa(Fila *fila, int codigo)
{
    int opcao;
    No *aux = fila->ini;
    limparTela();

    if (aux == NULL)
    {
        printf("FILA VAZIA!\n\n");
        voltaMenu();
        return;
    }

    while (aux->info.codigo != codigo && aux->prox != NULL) // pecorre a lista ate achar um codigo igual ou ate o ultimo elemento
    {
        limparTela();

        aux = aux->prox;
    }

    if (aux->info.codigo == codigo)
    {
        limparTela();
        printf("Tarefa encontrada!!\n\n");
        Tarefa tarefa = aux->info;
        imprimirTarefa(tarefa);
        printf("Digite o número do campo que deseja modificar:\n1. - Codigo\n2. - Nome da Tarefa\n3. - Nome do Projeto\n4. - Data de Início\n5. - Data de Término\n\n ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            do{
            printf("Codigo atual : %d\nDigite o novo Codigo : ", tarefa.codigo);
                if(scanf("%d", &tarefa.codigo) == 1){
                    limparBuffer();
                    limparTela();
                    aux->info = tarefa;
                    imprimirTarefa(tarefa);
                break; }
            else{
                limparTela();
                printf("ERRO ao salvar o codigo. lembre-se de inserir apenas numeros inteiros!\n");
                limparBuffer();
            } }while(1);
            break;
        case 2:
            printf("Nome atual : %s\nDigite o novo Nome : ", tarefa.tarefa);
            leituraString(tarefa.tarefa);
            limparTela();
            aux->info = tarefa;
            imprimirTarefa(tarefa);

            break;

        case 3:
            printf("Nome do projeto atual : %s\nDigite o novo nome de projeto: ", tarefa.projeto);
            leituraString(tarefa.projeto);
            aux->info = tarefa;
            imprimirTarefa(tarefa);

            break;

        case 4:
            printf("Data de inicio atual : %d/%d/%d\nDigite a nova data : ", tarefa.dataInicio.dia, tarefa.dataInicio.mes, tarefa.dataInicio.ano);
            tarefa.dataInicio = lerDataValida();
            limparBuffer();
            aux->info = tarefa;
            imprimirTarefa(tarefa);

            break;

        case 5:
            printf("Data de Termino atual : %d/%d/%d\nDigite a nova data : ", tarefa.dataTermino.dia, tarefa.dataTermino.mes, tarefa.dataTermino.ano);
            tarefa.dataTermino = lerDataValida();
            limparBuffer();
            aux->info = tarefa;
            imprimirTarefa(tarefa);

            break;
        }
    }
    else
    {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
        voltaMenu();
        return;
    }
}

void imprimirTarefa(Tarefa nova)
{
    printf("CODIGO : %d\nNOME : %s\nPROJETO : %s\nDATA DE INICIO : %d/%d/%d\nDATA DE TERMINO : %d/%d/%d\nSTATUS : %d\n\n", nova.codigo, nova.tarefa, nova.projeto, nova.dataInicio.dia, nova.dataInicio.mes, nova.dataInicio.ano, nova.dataTermino.dia, nova.dataTermino.mes, nova.dataTermino.ano, nova.status);
}

Tarefa concluirTarefa(Fila *fila, int codigo)
{
    char opcao;
    int opcao2;
    No *aux = fila->ini;
    Data data;
    dataAtual(&data);
    limparTela();

    if (aux == NULL)
    {
        filaVazia();
    }

    while (aux->info.codigo != codigo && aux->prox != NULL) // pecorre a lista ate achar um codigo igual ou ate o ultimo elemento
    {
        limparTela();
        aux = aux->prox;
    }

    if (aux->info.codigo == codigo)
    {
        limparTela();
        printf("Tarefa encontrada!!\n\n");
        Tarefa tarefa = aux->info;
        imprimirTarefa(tarefa);

        printf("Deseja marcar como concluida? (s/n):");
        opcao = validarOpcao();

        if (opcao == 's')
        {
            do
            {
                printf("Para finalizar, define a data de conclusão em umas das opções abaixo:\n1 - Data de hoje (%d/%d/%d)\n2 - Inserir uma data de conclusão diferente\n Sua escolha 1 ou 2 : \n", data.dia, data.mes, data.ano);
                scanf("%d", &opcao2);
                limparBuffer();
                limparTela();
                if (opcao2 == 1)
                {
                    tarefa.dataTermino = data;
                    tarefa.status = compararData(tarefa.dataInicio, tarefa.dataTermino);
                    if (tarefa.status == 0)
                    { // se a tarefa foi finalizada sem esta atrasada ela recebe o status de em dia
                        printf("PARABÉNS pela dedicação, a tarefa foi entregue sem atrasos.\n ");
                        retiraFila(fila, codigo);
                        return tarefa;
                    }
                    else
                    {
                        printf("Tarefa concluída com atraso, obrigado pelo empenho");
                        retiraFila(fila, codigo);
                        return tarefa;
                    }
                }
                else if (opcao2 == 2)
                {
                    limparTela();
                    printf("Digite a Data de termino da Tarefa neste formato dd/mm/aaaa: \n");
                    tarefa.dataTermino = lerDataValida();
                    tarefa.status = compararData(tarefa.dataInicio, tarefa.dataTermino);
                    if (tarefa.status == 0)
                    { // se a tarefa foi finalizada sem esta atrasada ela recebe o status de em dia
                        printf("PARABÉNS pela dedicação, a tarefa foi entregue sem atrasos.\n ");
                        retiraFila(fila, codigo);
                        return tarefa;
                    }
                    else
                    {
                        printf("Tarefa concluída com atraso, obrigado pelo empenho");
                        retiraFila(fila, codigo);
                        return tarefa;
                    }
                }
                else{
                    printf("opção INVALIDA!");
                    continue;
                }
            } while (2);
        }
    }
    else
    {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
    }
}

// Funções da fila

Fila *criaFila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No *insFim(No *fim, Tarefa tarefa)
{
    No *novo = malloc(sizeof(No)); // alocação dinamica
    novo->info = tarefa;           // o novo nó recebe a tarefa
    novo->prox = NULL;             // como é uma fila o novo elemento adicionado aponta para NULL
    if (fim != NULL)
    {                     // Verifica se a lista esta vazia
        fim->prox = novo; // se a lista nao estiver vazia o nó anterior vai apontar para esse novo nó
    }
    return novo;
}

void retiraFila(Fila *fila, int codigo)
{
    if (fila->ini == NULL)
    {
        filaVazia();
        return;
    }
    No *atual = fila->ini;
    No *anterior = NULL;
    while (atual->info.codigo != codigo && atual->prox != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (anterior == NULL)
    { // Se anterior é igual NULL então significa que o nó que iremos tirar é o inicio da fila
        if (atual->prox == NULL)
        { // se o prox do atual tbm é igual NULL então a Fila so tem ele como elemento
            fila->ini = fila->fim = NULL;
        }
        fila->ini = atual->prox; // o segundo elemento se torna o primeiro
    }
    // remover nó no meio/fim
    else
    {
        anterior->prox = atual->prox;
    }
    free(atual);
}

void inserirFila(Fila *fila, Tarefa tarefa)
{
    fila->fim = insFim(fila->fim, tarefa);
    if (fila->ini == NULL)
    { // verifica se a fila esta vazia
        fila->ini = fila->fim;
    }
}

int percorrerLista(Fila *fila, int codigo)
{
    int opcao;
    No *aux = fila->ini;
    limparTela();

    if (aux == NULL)
    {
        filaVazia();
        return 0;
    }

    while (aux->info.codigo != codigo && aux->prox != NULL)
    {
        limparTela();

        aux = aux->prox;
    }

    if (aux->info.codigo == codigo)
    {
        return 0;
    }
    else
    {
        printf("A tarefa com o código informado NÃO FOI ENCONTRADA.\n");
        voltaMenu();
        return 1;
    }
}

// função de menu e texto

int menu()
{
    int opcao;

    while (1)
    {
        printf("   /\\\n  /  \\\n /____\\");
        printf(" Sistema de Gerenciamento de Tarefas Triangulus \n\n");
        printf("1 - Adicionar uma nova Tarefa\n");
        printf("2 - Modificar uma Tarefa.\n");
        printf("3 - Concluir Tarefa\n");
        printf("4 - Lista de Tarefas Pendentes\n");
        printf("5 - Lista de Tarefas Concluídas \n");
        printf("6 - Lista de Tarefas Concluídas com e sem Atrasos\n");
        printf("7 - Sair do Programa\n\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        limparTela();

        // validação de entrada
        if (opcao >= 1 && opcao <= 8)
        {
            return opcao;
        }
        else
        {
            printf("OPÇÃO INVALIDA!!\n");
            pausaEnter();
            limparTela();
        }
    }
}

void mensagemFinal()
{
    limparTela();
    printf("   /\\");
    printf("\n  /  \\");
    printf("\n /____\\");
    printf("  Sistema de gerenciamento Triangulus\n");
    printf("\nFim do programa!\n");
    printf("Obrigado por usar nosso software. Ficamos felizes em poder ajudar. Até a próxima vez!\n");
}

void voltaMenu()
{

    char opcao;
    printf("Deseja voltar para o menu principal? S/N\n");
    opcao = validarOpcao();

    if (tolower(opcao) == 's')
    {
        limparTela();
        return;
    }
    else if (tolower(opcao == 'n'))
    {
        limparTela();
        mensagemFinal();
        exit(0);
    }
}

void filaVazia()
{
    limparTela();
    printf("FILA VAZIA!\n\n");
    pausaEnter();
    limparTela();
}

// funções auxiliares

void limparTela()
{
    // essa função assim como todo os programas foi pensando para que ele funciona em qualquer sistema operacional
#if defined(_WIN32)
    system("cls");
#elif defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}
char *leituraString(char str[])
{
    char ch;
    do {
    int i = 0;
    // ler cada caracter até enter
    while ((ch = getchar()) != '\n')
    {
        str[i++] = ch;
    }
    if(i<30){
        str[i] = '\0';
        return str;
    }
    if(i>30){
        limparTela();
        printf("nome maior que 30 caracteres, Por favor digite novamente! caracteres atual: %d\n",i);
        continue;
    }
    }while(2);

}
int lerCodigo() {
  int codigo;
  
  do {
    printf("Digite o código: \n");
    
    if(scanf("%d", &codigo) == 1) {
        limparBuffer();
        return codigo;
    }else {
        printf("Erro! Digite apenas números inteiros.\n");
        limparBuffer(); 
    }
  } while(1);
}
void dataAtual(Data *data)
{

    time_t now = time(NULL);
    struct tm *info = localtime(&now);

    data->dia = info->tm_mday;
    data->mes = info->tm_mon + 1;
    data->ano = info->tm_year + 1900;
}
void limparBuffer()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
void pausaEnter() {

    printf("Pressione ENTER para continuar...");

    int ch = getchar();
    while(ch != '\n' && ch != EOF) {
        ch = getchar();
  }

}
char validarOpcao() {

    char opcao;

    do {
        opcao = getchar();
        limparBuffer(); 
        tolower(opcao); 
    if(opcao != 's' && opcao != 'n') {
        printf("Opção inválida. Digite apenas s ou n.\n");
    }

  } while(opcao != 's' && opcao != 'n');
    return opcao;

}