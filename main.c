#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char apelido[20];
    char cidade[50];
    char estado[20];
    int capacidade;
    int cod;
} estadio;
typedef struct
{
    char nome[50];
    char sigla[10];
    char cidade[50];
    char estado[20];
    char cor[10];
    char estadio[50];
    float patrimonio;
    int ano;
    int cod;
    int contatleta;
} time;

typedef struct
{
    char nome[50];
    int ano;
    char pos [20];
    char rg [15];
    int hab;
    float sal;
    char time [50];
    int cod_time;
    int cod;
} atletas;

int menu (void);
int sub_menu (void);
int cad_estadio(int x);
int cad_atleta(int x);
int cad_time(int x);
int tran();
void mostra_estadio(void);
void mostra_time();
void mostra_atleta();
void caso_menu(int x);
void mostra_time_indice (int i);
void mostra_atl_trans (int cod);



int it=0,ie=0,ia=0;/*it = indice time; ie = indicie estadio; ia = indice atleta*/
int itc=0,iec=0,iac=0;
time tim[20];
estadio est[20];
atletas atl[240];

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int i;
    for (i=0; i<20; i++)
        tim[i].contatleta=0;
    setlocale(LC_ALL, "Portuguese");
    FILE *indtime, *indestadio, *indatleta;
    indtime=fopen("indicetime.dat", "rb");
    if (indtime==NULL)
    {
        fclose(indtime);
    }
    else
    {
        fread(&it, sizeof(int), 1, indtime);
        fclose(indtime);
        indestadio=fopen("indiceestadio.dat", "rb");
        fread(&ie, sizeof(int), 1, indestadio);
        fclose(indestadio);
        indatleta=fopen("indiceatleta.dat", "rb");
        fread(&ia, sizeof(int), 1, indatleta);
        fclose(indatleta);
        FILE *lertime, *lerestadio, *leratleta;
        lertime=fopen("times.dat","rb");
        fread(&tim, sizeof(time), it, lertime);
        fclose(lertime);
        lerestadio=fopen("estadios.dat","rb");
        fread(&est, sizeof(estadio), ie, lerestadio);
        fclose(lerestadio);
        leratleta=fopen("atletas.dat","rb");
        fwrite(&atl, sizeof(atletas), ia, leratleta);
        fclose(leratleta);
    }
    while(menu()!=5);
    FILE *gravatim, *gravaest, *gravaatl;
    gravatim=fopen("times.dat", "wb");
    fwrite(tim, sizeof(time), it, gravatim);
    fclose(gravatim);
    gravaest=fopen("estadios.dat", "wb");
    fwrite(est, sizeof(estadio), ie, gravaest);
    fclose(gravaest);
    gravaatl=fopen("atletas.dat", "wb");
    fwrite(atl, sizeof(atletas), ia, gravaatl);
    fclose(gravaatl);
    FILE *indtim, *indest, *indatl;
    indtim=fopen("indicetime.dat", "wb");
    fwrite(&it, sizeof(int), 1, indtim);
    fclose(indtim);
    indest=fopen("indiceestadio.dat", "wb");
    fwrite(&ie, sizeof(int), 1, indest);
    fclose(indest);
    indatl=fopen("indiceatleta.dat", "wb");
    fwrite(&ia, sizeof(int), 1, indatl);
    fclose(indatl);
    return 0;
}

int menu (void)
{
    int x=0;
    system("cls");
    printf("1 - TIMES\n");
    printf("2 - ATLETAS\n");
    printf("3 - ESTADIOS\n");
    printf("4 - MOVIMENTAÇÃO DE ATLETAS\n");
    printf("5 - SAIR\n");
    scanf("%d", &x);
    caso_menu(x);
    system("pause");
    return x;
}
void caso_menu(int x)
{
    switch (x)
    {
    case 1:
        printf("TIMES\n");
        while(cad_time(sub_menu())!=5);
        break;
    case 2:
        printf("ATLETAS\n");
        while(cad_atleta(sub_menu())!=5);
        break;
    case 3:
        printf("ESTADIOS\n");
        while(cad_estadio(sub_menu())!=5);
        break;
    case 4:
        printf("MOVIMENTAÇÃO DE ATLETA\n");
        while(tran()!=3);
        break;
    case 5:
        printf("SAIR\n");
        break;
    default :
        printf("OPÇÃO INEXISTENTE\n");
        break;
    }

}
int sub_menu (void)
{
    int x;
    printf("1 - CADASTRAR\n");
    printf("2 - ATUALIZAR\n");
    printf("3 - EXCLUIR\n");
    printf("4 - PESQUISAR\n");
    printf("5 - MENU ANTERIOR\n");
    scanf("%d", &x);
    return x;
}


int cad_time(int x)
{
    int h,i,j;
    char aux[50];
    system("cls");
    setbuf(stdin,NULL);
    switch(x)
    {
    case 1:
        printf("CADASTRAR\n");
        printf("DIGITE O NOME DO TIME: ");
        gets(tim[it].nome);
        printf("DIGITE A SIGLA DO TIME: ");
        gets(tim[it].sigla);
        printf("DIGITE A CIDADE DO TIME: ");
        gets(tim[it].cidade);
        printf("DIGITE O ESTADO: ");
        gets(tim[it].estado);
        printf("DIGITE A COR DO TIME: ");
        gets(tim[it].cor);
        printf("DIGITE O PATRIMONIO DO TIME: ");
        scanf("%f",&tim[it].patrimonio);
        printf("DIGITE O ANO DO TIME: ");
        scanf("%d",&tim[it].ano);
        printf("\nDIGITE 1 - PARA SELECIONAR UM ESTÁDIO CADASTRADO PARA O TIME\nDIGITE 2 - PARA CADASTRAR UM NOVO ESTADIO PARA O TIME\n");
        scanf("%d",&i);
        if(i==1)
        {
            if (ie==0)
            {
                printf("\nNão há estádios cadastrados!\n");
                return 5;
            }
            else
            {
                system("cls");
                mostra_estadio();
                printf("DIGITE O INDICE DO ESTADIO");
                scanf("%d",&h);
                h--;
                strcpy(tim[it].estadio,est[h].nome);
            }
        }
        else if(i==2)
        {
            cad_estadio(1);

            strcpy(tim[it].estadio,est[ie-1].nome);
        }
        tim[it].cod=itc;
        it++;
        itc++;
        break;
    case 2:
        printf("ATUALIZAR\n");
        mostra_time();
        printf("ESCOLHA O INDICE DO TIME QUE DESEJA ATUALIZAR\n");
        scanf("%d",&i);
        i--;
        system("cls");
        mostra_time_indice(i);
        printf("Deseja atualizar Nome e/ou sigla do Time?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        getchar();
        if(j)
        {
            printf("Insira o nome do time e, em seguida, sua sigla:\n");
            printf("NOME: ");
            gets(tim[i].nome);
            printf("SIGLA: ");
            gets(tim[i].sigla);
        }
        printf("Deseja atualizar a Cidade o Estado e/ou a cor do TIME?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        getchar();
        if(j)
        {
            printf("Insira a cidade o estado e a cor do TIME:\n");
            printf("CIDADE: ");
            gets(tim[i].cidade);
            printf("ESTADO: ");
            gets(tim[i].estado);
            printf("COR: ");
            gets(tim[i].cor);
        }
        printf("Deseja atualizar o patrimonio e/ou o ano do time?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        if(j)
        {
            printf("Insira o patrimonio e o ano do time:\n");
            printf("PATRIMONIO: ");
            scanf("%f",&tim[i].patrimonio);
            printf("ANO: ");
            scanf("%d",&tim[i].ano);
            getchar();
        }
        printf("Deseja atualizar o estádio do time?\n\
               1-sim 0-não: ");
        scanf("%d", &j);
        if (j)
        {
            printf("NOME DO ESTÁDIO: ");
            setbuf(stdin, NULL);
            gets(tim[i].estadio);
        }
        break;
    case 3:
        if (it==0)
            printf("\nNão há times cadastrados!\n");
        else{
            mostra_time();
            printf("EXCLUIR\n");
            printf("Digite o indice do time ao qual deseja excluir: ");
            scanf("%d",&h);
            if (tim[--h].contatleta>0)
            {
                for (i=0; i<240; i++)
                {
                    if (tim[h].cod==atl[i].cod_time)
                    {
                        atl[i]=atl[--ia];
                    }
                }
            }
            tim[h]=tim[--it];
            strcpy(tim[h].estadio,"sem estadio");
        }
        break;
    case 4:
        h=1;
        printf("PESQUISAR\n");
        printf("Insira o nome do time que deseja pesquisar: ");
        setbuf(stdin,NULL);
        gets(aux);
        for (i=0; i<it; i++)
        {

            if (strcmp(tim[i].nome, aux)==0)
            {
                mostra_time_indice(i);
                h=0;
                break;
            }

        }
        if(h)
            printf("\nNÃO LOCALIZADO\n\n");
        break;
    case 5:
        printf("MENU ANTERIOR\n");
        break;
    default:
        printf("OPÇÃO INEXISTENTE\n");
    }
    return x;
}
int cad_atleta(int x)
{
    int h,i,j;
    char aux[50];
    system("cls");
    fflush(stdin);
    system("cls");
    switch(x)
    {
    case 1:
        printf("CADASTRAR\n");
        printf("Insira o nome do atleta e, em seguida sua posição:\n");
        setbuf(stdin, NULL);
        printf("NOME: ");
        gets(atl[ia].nome);
        printf("POSIÇÃO: ");
        gets(atl[ia].pos);
        printf("Insira o RG do jogador:\n");
        printf("RG: ");
        gets(atl[ia].rg);
        printf("Insira a habilidade do jogador: ");
        scanf("%d", &atl[ia].hab);
        printf("Insira o salário do jogador: ");
        scanf("%f", &atl[ia].sal);
        printf("Insira a data de nascimento do jogador: ");
        scanf("%d", &atl[ia].ano);
        atl[ia].cod=iac;
        system("cls");
        printf("\nADICIONE O ATLETA A UM TIME (caso ainda não tenha cadastrado o time, cancele o cadastro\n\
do atleta e retorne ao menu anterior para cadastrar o time) ");
        printf("\n1-Prosseguir\n2-Retornar ao menu anterior\n");
        scanf("%d",&j);
        if(j==1)
        {
            mostra_time();
            printf("\n\nESCOLHA O ÍNDICE DO TIME: ");
            scanf("%d",&h);
            h--;
            if (tim[h].contatleta>=12)
            {
                printf("Não é possível cadastrar um atleta neste time!\n\
                       cadastre novamente o atleta em um time válido.");
                system("pause");
                return 5;
            }
            else
            {
                printf("\nCadastro realizado!\n\n");
                atl[ia].cod_time=tim[h].cod;
                strcpy(atl[ia].time, tim[h].nome);
            }
        }
        else if (j==2)
            return 5;
        tim[h].contatleta++;
        ia++;
        iac++;
        break;
    case 2:
        system("cls");
        printf("ATUALIZAR\n\n");
        mostra_atleta();
        printf("\nDIGITE O INDICE DO ATLETA QUE DESEJA ATUALIZAR\n\n");
        scanf("%d",&i);
        i--;
        setbuf(stdin, NULL);
        printf("\nINDICE: %d\n",i+1);
        printf("CODIGO JOGADOR: %d\n",atl[i].cod);
        printf("NOME: ");
        puts(atl[i].nome);
        printf("POSIÇÃO: ");
        puts(atl[i].pos);
        printf("RG: ");
        puts(atl[i].rg);
        printf("HABILIDADE: ");
        printf("%d\n", atl[i].hab);
        printf("SALARIO: ");
        printf("R$%.2f\n", atl[i].sal);
        printf("DATA DE NASCIMENTO: %d\n", atl[i].ano);
        printf("Insira os novos dados do atleta:\n");
        setbuf(stdin, NULL);
        printf("NOME: ");
        gets(atl[i].nome);
        printf("POSIÇÃO: ");
        gets(atl[i].pos);
        printf("Insira o RG do jogador:\n");
        printf("RG: ");
        gets(atl[i].rg);
        printf("Insira a habilidade do jogador: ");
        scanf("%d", &atl[i].hab);
        printf("Insira o salário do jogador: ");
        scanf("%f", &atl[i].sal);
        printf("Insira a data de nascimento do jogador: ");
        scanf("%d", &atl[i].ano);
        system("cls");
        break;
    case 3:
        if (ia==0)
            printf("\nNão há atletas cadastrados!\n");
        else{
            printf("EXCLUIR\n");
            mostra_atleta();
            printf("DIGITE O INDICE DO ATLETA QUE DESEJA EXCLUIR\n\n");
            scanf("%d",&i);
            i--;
            atl[i]=atl[ia-1];
            ia--;
        }
        break;
    case 4:
        h=1;
        printf("PESQUISAR\n");
        printf("DIGITE O NOME DO ATLETA QUE DESEJA PESQUISAR\n\n");
        setbuf(stdin,NULL);
        gets(aux);
        for (i=0; i<ia; i++)
        {
            if (strcmp(atl[i].nome, aux)==0)
            {
                printf("INDICE: %d\n",i+1);
                printf("CODIGO JOGADOR: %d\n",atl[i].cod);
                printf("NOME: ");
                puts(atl[i].nome);
                printf("POSIÇÃO: ");
                puts(atl[i].pos);
                printf("RG: ");
                puts(atl[i].rg);
                printf("HABILIDADE: ");
                printf("%d\n", atl[i].hab);
                printf("SALARIO: ");
                printf("R$%.2f\n", atl[i].sal);
                printf("DATA DE NASCIMENTO: %d\n", atl[i].ano);
                printf("TIME: %s\n", atl[i].time);
                printf("CODIGO DO TIME: %d\n", atl[i].cod_time);
                h=0;
                break;
            }
        }
        if(h)
            printf("NÃO LOCALIZADO\n\n");
        break;
    case 5:
        printf("RETORNANDO AO MENU ANTERIOR...\n\n");
        break;
    default:
        printf("OPÇÃO INEXISTENTE\n");
    }
    return x;
}

int cad_estadio(int x)
{
    char aux[50];
    int h,j,i;

    system("cls");
    switch(x)
    {
    case 1:
        printf("CADASTRAR\n");
        printf("Insira o nome do estádio e, em seguida, seu apelido:\n");
        setbuf(stdin, NULL);
        printf("NOME: ");
        gets(est[ie].nome);
        printf("APELIDO: ");
        gets(est[ie].apelido);
        //setbuf(stdin, NULL);
        printf("Insira a cidade e o estado do estádio:\n");
        printf("CIDADE: ");
        gets(est[ie].cidade);
        printf("ESTADO: ");
        gets(est[ie].estado);
        printf("Insira a capacidade do estádio:\n");
        printf("CAPACIDADE: ");
        scanf("%d", &est[ie].capacidade);
        est[ie].cod=iec;
        ie++;
        iec++;
        break;
    case 2:
        printf("ATUALIZAR\n");
        mostra_estadio();
        printf("ESCOLHA O INDICE DO ESTÁDIO QUE DESEJA ATUALIZAR\n");
        scanf("%d",&i);
        i--;
        system("cls");
        printf("INDICE = %d",i+1);
        printf("NOME ESTADIO: %s\n", est[i].nome);
        printf("APELIDO: %s\n", est[i].apelido);
        printf("CIDADE: %s\n", est[i].cidade);
        printf("ESTADO: %s\n", est[i].estado);
        printf("CAPACIDADE: %d\n\n", est[i].capacidade);

        printf("Deseja atualizar Nome e/ou apelido do Estadio?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        getchar();
        if(j)
        {
            printf("Insira o nome do estádio e, em seguida, seu apelido:\n");
            printf("NOME: ");
            gets(est[h].nome);
            printf("APELIDO: ");
            gets(est[h].apelido);
        }
        printf("Deseja atualizar a cidade e/ou o Estado do Estadio?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        getchar();
        if(j)
        {
            printf("Insira a cidade e o estado do estádio:\n");
            printf("CIDADE: ");
            gets(est[h].cidade);
            printf("ESTADO: ");
            gets(est[h].estado);
        }
        printf("Deseja atualizar a capacidade do Estadio?\n\
               1-sim 0-não: ");
        scanf("%d",&j);
        getchar();
        if(j)
        {
            printf("Insira a capacidade do estádio: ");
            scanf("%d", &est[h].capacidade);
        }
        break;
    case 3:
        if (ie==0)
            printf("\nNão há times cadastrados!\n");
        else{
            mostra_estadio();
            printf("EXCLUIR\n");
            printf("Digite o índice do estádio cujo qual deseja excluir: ");
            scanf("%d",&h);
            h--;
            est[h]=est[ie-1];
            ie--;
        }
        break;
    case 4:
        h=1;
        printf("PESQUISAR\n");
        printf("Insira o nome do estádio que deseja pesquisar: ");
        setbuf(stdin,NULL);
        gets(aux);
        for (i=0; i<ie; i++)
        {

            if (strcmp(est[i].nome, aux)==0)
            {
                printf("\nINDICE = %d\n",i+1);
                printf("NOME ESTÁDIO: %s\n", est[i].nome);
                printf("APELIDO: %s\n", est[i].apelido);
                printf("CIDADE: %s\n", est[i].cidade);
                printf("ESTADO: %s\n", est[i].estado);
                printf("CAPACIDADE: %d\n\n", est[i].capacidade);
                h=0;
                break;
            }

        }
        if(h)
            printf("NÃO LOCALIZADO\n\n");
        break;
    case 5:
        printf("RETORNANDO AO MENU ANTERIOR...\n\n");
        break;
    default:
        printf("OPÇÃO INEXISTENTE\n");
    }
    return x;


}

int tran(void)
{
    int x, inddestino, indorigem, indatl, esc;
    float valoratl, coef, proposta;
    system("cls");
    printf("1-TRANSFERÊNCIA\n2-DEMISSÃO\n3-MENU ANTERIOR\n");
    scanf("%d", &x);
    system("cls");
    switch (x)
    {
    case 1:
        printf("TRANSFERÊNCIA\n");
        mostra_time();
        printf("Insira o índice do seu time e, em seguida, o índice do time que deseja fazer uma proposta: \n");
        scanf("%d%d", &inddestino, &indorigem);
        indorigem--;
        inddestino--;
        if (tim[indorigem].contatleta==0){
            printf("\nNão há atletas cadastrados neste time!\n");
            break;
        }
        esc=tim[indorigem].cod;
        mostra_atl_trans (esc);
        printf("\nInsira o índice do atleta que deseja fazer uma proposta: ");
        scanf("%d", &indatl);
        if ((2018 - atl[indatl].ano)<=23)
            coef = 1;
        else if ((2018-atl[indatl].ano)<=28)
            coef = 0.8;
        else if ((2018-atl[indatl].ano)<=32)
            coef = 0.5;
        else if((2018-atl[indatl].ano)<=36)
            coef = 0.3;
        else
            coef = 0.1;
        valoratl = (12 * atl[indatl].sal + 100 * atl[indatl].hab ) * coef;
        printf("\nInsira o valor oferecido para a transferência do atleta: R$ ");
        scanf("%f", &proposta);
        if ((proposta<=tim[inddestino].patrimonio)&&(tim[inddestino].contatleta<12))
        {
            if (proposta>valoratl)
            {
                atl[indatl].cod_time=tim[inddestino].cod;
                tim[inddestino].patrimonio-= proposta;
                tim[indorigem].patrimonio+= proposta;
                strcpy(atl[indatl].time, tim[inddestino].nome);
                tim[inddestino].contatleta++;
                tim[indorigem].contatleta--;
                printf("\nTRANSFÊRENCIA CONCLUÍDA COM SUCESSO\n");
            }
            else
                printf("\nERRO NA TRANSFÊRENCIA! (valor oferecido menor que o valor do atleta)\n");
        }
        else
            printf("\nERRO NA TRANSFÊRENCIA! (valor oferecido maior que o patrimônio do clube ou o time já está cheio)\n");
        system("pause");
        break;
    case 2:
        printf("DEMISSÃO\n");
        mostra_time();
        printf("Insira o índice do time que deseja visualizar os atletas\n");
        scanf("%d", &indorigem);
        indorigem--;
        esc=tim[indorigem].cod;
        mostra_atl_trans(esc);
        printf("Escolha o índice do atleta que deseja demitir\n");
        scanf("%d", &esc);
        tim[indorigem].contatleta--;
        esc--;
        atl[esc]=atl[--ia];
        break;
    case 3:
        printf("RETORNANDO AO MENU ANTERIOR...\n\n");
        break;
    default:
        printf("OPÇÃO INEXISTENTE\n");
    }
    return x;
}

void mostra_estadio(void)
{
    int i;
    printf("\nESTÁDIOS\n\n");
    for(i=0; i<ie; i++)
    {
        printf("ÍNDICE = %d\n",i+1);
        printf("NOME ESTÁDIO: %s\n", est[i].nome);
        printf("APELIDO: %s\n", est[i].apelido);
        printf("CIDADE: %s\n", est[i].cidade);
        printf("ESTADO: %s\n", est[i].estado);
        printf("CAPACIDADE: %d\n\n", est[i].capacidade);

    }
}

void mostra_time()
{
        printf("\nLISTA DE TIMES\n\n");
    int i;
    for(i=0; i<it; i++)
    {
        printf("INDICE: %d\n",i+1);
        printf("NOME: ");
        puts(tim[i].nome);
        printf("SIGLA: ");
        puts(tim[i].sigla);
        printf("CIDADE: ");
        puts(tim[i].cidade);
        printf("ESTADO: ");
        puts(tim[i].estado);
        printf("COR: ");
        puts(tim[i].cor);
        printf("PATRIMONIO: ");
        printf("%.2f\n",tim[i].patrimonio);
        printf("ANO: ");
        printf("%d\n",tim[i].ano);
        printf("ESTÁDIO: %s\n", tim[i].estadio);
        printf("CÓDIGO DO TIME: %d\n\n",  tim[i].cod);
    }
}

void mostra_time_indice(int i)
{
    printf("INDICE: %d\n",i+1);
    printf("CÓDIGO: %d\n",tim[i].cod);
    printf("NOME: ");
    puts(tim[i].nome);
    printf("SIGLA: ");
    puts(tim[i].sigla);
    printf("CIDADE: ");
    puts(tim[i].cidade);
    printf("ESTADO: ");
    puts(tim[i].estado);
    printf("COR: ");
    puts(tim[i].cor);
    printf("PATRIMONIO: ");
    printf("%f\n",tim[i].patrimonio);
    printf("ANO: ");
    printf("%d\n",tim[i].ano);
    printf("ESTÁDIO: %s\n\n", tim[i].estadio);
}

void mostra_atleta()
{

    int i;
    printf("\nATLETAS\n\n");
    for(i=0; i<ia; i++)

    {
        printf("INDICE: %d\n",i+1);
        printf("CODIGO JOGADOR: %d\n",atl[i].cod);
        printf("NOME: ");
        puts(atl[i].nome);
        printf("POSIÇÃO: ");
        puts(atl[i].pos);
        printf("RG: ");
        puts(atl[i].rg);
        printf("HABILIDADE: ");
        printf("%d\n", atl[i].hab);
        printf("SALARIO: ");
        printf("R$%.2f\n", atl[i].sal);
        printf("DATA DE NASCIMENTO: ");
        printf("%d\n", atl[i].ano);
        printf("TIME: ");
        puts(atl[i].time);
        printf("CÓDIGO DO TIME: %d\n", atl[i].cod_time);
    }
}

void mostra_atl_trans (int cod)
{
    int i;
    printf("\nATLETAS\n\n");
    for (i=0; i<ia; i++)
    {
        if (atl[i].cod_time==cod)
        {
            printf("\nINDICE: %d\n", i+1);
            printf("NOME: %s\n", atl[i].nome);
            printf("ANO DE NASCIMENTO: %d\n", atl[i].ano);
            printf("POSICAO: %s\n", atl[i].pos);
            printf("RG: %s\n", atl[i].rg);
            printf("HABILIDADE: %d\n", atl[i].hab);
            printf("SALÁRIO: %.2f\n", atl[i].sal);
            printf("TIME: %s\n", atl[i].time);
            printf("CODIGO DO TIME: %d\n", atl[i].cod_time);
            printf("CÓDIGO DO JOGADOR: %d\n\n", atl[i].cod);
        }
    }
}

