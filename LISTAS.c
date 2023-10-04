#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

struct NO
{
	int info;
	struct NO *prox;
};
typedef struct NO Lista;


Lista* inicializa ( )
{
	return NULL;
}

Lista* insere (Lista* recebida, int valor)
{
    Lista  *novo ;
    novo= (Lista*) malloc(sizeof(Lista));
    novo->info = valor;
    novo->prox = recebida;
    return novo;
}

/* função vazia: retorna 1 se vazia ou 0 se não vazia */
int vazia (Lista *recebida)
{
	if (recebida == NULL)
	{
		return 1;

	}
    return 0;
}


void imprime (Lista* p)
{
    if(vazia(p))
    {
        printf("\n\n\t\t => LISTA VAZIA  <==\n\n ");
    }
    else
    {
        printf("\n\n\t\t =>  ");
        for (p ; p != NULL; p = p->prox)
            printf(" %d - ", p->info);
        printf("\n\n");
    }

}


Lista* libera(Lista *receb)
{
    Lista *aux,aux1;
    while(receb!= NULL)
    {
        aux=receb;
        receb=receb->prox;
        free(aux);
    }
    return NULL;
}

Lista* UNIAO(Lista **UM, Lista **DOIS)
{
    Lista *TRES, *aux, *aux1,*aux2;
    int flag;
    TRES = *UM;
    aux2=*DOIS;
    while(aux2!=NULL)
    {
        flag=1;
        aux1=(*UM);
        while((aux1!=NULL)&&(flag==1))
        {
            if(aux1->info==aux2->info)
            {
                flag=0;
            }
            aux1=aux1->prox;
        }

        aux=aux2;
        aux2=aux2->prox;
        if(flag==1) //elemento não é repetido
        {
            aux->prox=TRES;
            TRES= aux;

        }
        else
        {
            free(aux);
        }
    }
    (*UM)=NULL;
    (*DOIS)=NULL;
    return TRES;
}


int main()
{
    Lista *Inicio, *L1,*L2, *L3;
    int num;
    char resp;
    setlocale(LC_ALL,"portuguese");
    /*Inicio=inicializa();
    do
    {
        printf("\n\t\tDigite o elemento a ser inserido na lista: ");
        scanf("%d",&num);
        Inicio=insere(Inicio,num);
        printf("\n\t\t\t =>> Deseja inserir mais um número? (S/N)");
        fflush(stdin);
        resp=getchar();
    } while(toupper(resp)=='S');
    imprime(Inicio);*/
    L1=inicializa();
    do
    {
        printf("\n\t\tDigite o elemento a ser inserido na lista 1: ");
        scanf("%d",&num);
        L1=insere(L1,num);
        printf("\n\t\t\t =>> Deseja inserir mais um número? (S/N)");
        fflush(stdin);
        resp=getchar();
    } while(toupper(resp)!='N');
    printf("\n\n\t\t==> LISTA  <==\n");
    imprime(L1);
    L2=inicializa();
    do
    {
        printf("\n\t\tDigite o elemento a ser inserido na lista 2: ");
        scanf("%d",&num);
        L2=insere(L2,num);
        printf("\n\t\t\t =>> Deseja inserir mais um número? (S/N)");
        fflush(stdin);
        resp=getchar();
    } while(toupper(resp)!='N');
    printf("\n\n\t\t==> LISTA 1 <==\n");
    imprime(L1);
    printf("\n\n\t\t==> LISTA 2 <==\n");
    imprime(L2);
    fflush(stdin);
    getchar();
    printf("\n\n\t\t\t==> tecle algo \n\n");
    system("cls");
    L3=UNIAO(&L1,&L2);
    printf("\n\n\t\t==> LISTA 1 <==\n");
    imprime(L1);
    printf("\n\n\t\t==> LISTA 2 <==\n");
    imprime(L2);
    printf("\n\n\t\t==> LISTA 3 <==\n");
    imprime(L3);


}
