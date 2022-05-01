#include <stdlib.h>
#include <stdio.h>

void inserirPosicao(int *memoria, int *ocupado);
void consultarPosicao(int *memoria, int *ocupado);
void mostrarMemoria(int *memoria, int *ocupado, int tamanho);
int realocarMemoria(int *memoria, int *ocupado, int tamanho);

/*
Faça um programa que simule a memória de um computador:
o usuário irá especificar o tamanho da memória, ou seja,
quantos bytes serão alocados do tipo inteiro.
Para tanto, a memória solicitada deve ser um valor múltiplo do tamanho do tipo inteiro. 
Em seguida, o usuário terá duas opções: 
inserir um valor em uma determinada posição ou consultar o valor contido em uma determinada posição.
A memória deve iniciar com todos os dados zerados. 
*/

void menuOpcao(int *memoria, int *ocupado, int tamanho)
{
    int opcao=0;
    while(opcao!=5)
    {
        printf("\n-------------------------");
        printf("\n\nOPCOES:");
        printf("\nINSERIR UM VALOR EM DETERMINADA POSICAO [1]");
        printf("\nCONSULTAR O VALOR EM DETERMINADA POSICAO [2]");
        printf("\nMOSTRA TODOS OS VALORES DA MEMORIA [3]");
        printf("\nREALOCAR MEMORIA [4]");
        printf("\nTERMINAR O PROGRAMA [5]");
        printf("\nDIGITE A OPCAO DESEJADA: ");
        scanf("%d", &opcao);
        printf("\n-------------------------");
        switch (opcao)
        {
            case 1:
                inserirPosicao( memoria, ocupado);
                break;
            
            case 2:
                consultarPosicao( memoria, ocupado);
                break;

            case 3:
                mostrarMemoria( memoria, ocupado, tamanho);
                break;
            
            case 4:
                tamanho = realocarMemoria( memoria, ocupado, tamanho);
                printf("\nNovo tamanho = %d", tamanho);
                break;

            case 5:
                printf("\nFIM DO PROGRAMA");
                return;
            default:
                printf("\nOPCAO NAO RECONHECIDA, DIGITE NOVAMENTE");
                break;
        }
    }
}

void inserirPosicao(int *memoria, int *ocupado)
{
    int posicao;
    int valor;
    char resposta;

    printf("\nDIGITE A POSICAO QUE DESEJA PREENCHER: ");
    scanf("%d", &posicao);
    ocupado+=posicao;

    if(*ocupado == 1) //verifica se a posicao ja esta ocupada
    {
        printf("\nPOSICAO JA OCUPADA, DESEJA SOBRESCREVER POSICAO? [S/N] ");
        setbuf(stdin, NULL);
        resposta = getchar();
        if(resposta == 'N')
        {
            ocupado -=posicao;
            return;
        }
    }
    memoria += posicao;
    printf("\nDIGITE O VALOR A SER ARMAZENADO NA POSICAO: ");
    scanf("%d", &valor);
    *memoria = valor;
    *ocupado = 1;

    ocupado -= posicao;
    memoria -= posicao;
    return;
    
}

void consultarPosicao(int *memoria, int *ocupado)
{
    int posicao;
    printf("\nDIGITE A POSICAO QUE DESEJA CONSULTAR: ");
    scanf("%d", &posicao);
    memoria += posicao;
    ocupado += posicao;
    if(*ocupado == 0)
    {
        printf("\nPOSICAO VAZIA");
        return;
    }
    printf("\nVALOR NA POSICAO: %d", *memoria);

    memoria -= posicao;
    ocupado -= posicao;
    return;
}

void mostrarMemoria(int *memoria, int *ocupado, int tamanho)
{
    for(int i=0; i<tamanho; i++)
    {
        if(*ocupado == 0)   printf("\nESPACO NAO OCUPADO");
        else    printf("\nESPACO %d: %d", i+1, *memoria);
        ocupado++;
        memoria++;
    }
    ocupado-=tamanho;
    memoria-=tamanho;
    return;
}

int realocarMemoria(int *memoria, int *ocupado, int tamanho)
{
    int novoTamanho;
    char resposta;
    printf("\nDIGITE O NOVO TAMANHO DA MEMORIA: ");
    scanf("%d", &novoTamanho);

    if(novoTamanho < tamanho)
    {
        printf("\nNOVO TAMANHO DE MEMORIA MENOR QUE O TAMANHO ORIGINAL");
        printf("\nSERA PERDIDO OS VALORES DAS ULTIMAS %d MEMORIAS", tamanho-novoTamanho);
        printf("\nDESEJA CONTINUAR COM A OPERACAO? [S/N] ");
        setbuf(stdin,NULL);
        resposta = getchar();
        if(resposta == 'N') return tamanho;
    }

    ocupado = realloc(ocupado, sizeof(int) * novoTamanho);
    memoria = realloc(memoria, sizeof(int) * novoTamanho);

    if(novoTamanho > tamanho)
    {
        ocupado+=tamanho;
        memoria+=tamanho;
        for(int i=tamanho; i<novoTamanho; i++, ocupado++, memoria++)
        {
            *ocupado = 0;
            *memoria = 0; 
        }
        ocupado-=novoTamanho;
        memoria-=novoTamanho;
    }

    return novoTamanho;
}

int main()
{
    int tamanho;

    printf("digite a quantidade de inteiros a ser alocada: ");
    scanf("%d", &tamanho);

    int *memoria=malloc(sizeof(int) * tamanho); //ponteiro memoria serve para armazenar os valores
    int *ocupado=malloc(sizeof(int) * tamanho); //ponteiro ocupado serve para testar se a posicao do vetor ja foi usada antes
    int i;

    for(i=0; i<tamanho; i++, memoria++, ocupado++) 
    {
        *memoria = 0;    // inicializando a memoria com o valor 0
        *ocupado = 0;
    }
    memoria -= tamanho;     
    ocupado -= tamanho;
    menuOpcao( memoria, ocupado, tamanho);
    free (memoria);
    free (ocupado);
    return 0;
}
