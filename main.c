
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_PACIENTES  100
typedef enum {
 TELA_SAIR=-1,
 TELA_PRINCIPAL,
 TELA_CADASTRAR,
 TELA_DESCADASTRAR,
 TELA_LISTAR_TODOS,
} Telas;
typedef struct
{
 char separador1[8], nome[50];
 char telefone[12], endereco[100], cidade[100], estado[100], cpf[2];
 char cep[12], email[100], comorbidade[100], separador[8];
 int idade,dia,mes,ano,diaD,mesD,anoD;
} Covid;
typedef struct
{
 Telas menu;
 int totalCovids;
 Covid pacientes[MAX_PACIENTES];

} CovidPacientes;
int main (void)
{
 int aA, mA, dA;
 char usr[]="user",usuario[20];
 int senhaL, senha=1234;

while ( (strcmp(usr,usuario)!=0) || (senha!=senhaL))
{
 printf("\tDigite o usuario: \n");
 fflush(stdin);
 gets(usuario);
 printf("\tDigite a senha: \n");
 fflush(stdin);
 scanf("%d", &senhaL);
 system("cls");
}


 CovidPacientes cadastro;

 memset(&cadastro, 0x0, sizeof(cadastro));

 cadastro.menu = TELA_PRINCIPAL;

 FILE * memoria = fopen("pacientes.txt", "r");
 FILE * risco;
 if (memoria == NULL)
 {
 printf("Erro ao abrir arquivo de memoria de pacientes. \nVoce deve criar o arquivo 'pacientes.txt' vazio antes da primeira execucao\n");
 return 1;
 }

 size_t lidos = fread(cadastro.pacientes, sizeof(Covid), MAX_PACIENTES, memoria);
 printf("Lidos %zd pacientes\n", lidos);

 cadastro.totalCovids = (int)lidos;
 fclose(memoria);

 time_t mytime;
 mytime = time(NULL);
 struct tm tm = *localtime(&mytime);
 aA=tm.tm_year+1900;
 mA=tm.tm_mon+1;
 dA=tm.tm_mday;
 printf("Data: %d/%d/%d\n", dA, mA, aA);

 while (cadastro.menu != TELA_SAIR)

 {
 switch (cadastro.menu)
 {
 case TELA_PRINCIPAL:
 {
 printf("---------------------------------------------\n");
 printf("\tCADASTRO PACIENTES POSITIVOS PARA COVID 19:\n");
 printf("---------------------------------------------\n");
 int opcao = -1;
 do
 {
 printf("Escolha uma opcao:\n");
 printf("\tDigite 1 para cadastrar \n");
 printf("\tDigite 2 para remover \n");
 printf("\tDigite 3 para listar os pacientes\n");
 printf("\tDigite 0 para sair \n");
 scanf("%d", &opcao);

 int c = 0;
 while ((c = getchar()) != '\n' && c != EOF) { }
 } while (opcao < 0 || opcao > 3);
 if (opcao == 0)
 cadastro.menu = TELA_SAIR;
 if (opcao == 1)
 {

 cadastro.menu = TELA_CADASTRAR;

 if (cadastro.totalCovids >= MAX_PACIENTES)
 {
 printf("\tUti / Enfermaria com ocupaçao MAXIMA, nao e possivel admitir novos pacientes\n");

 cadastro.menu = TELA_PRINCIPAL;
 }
 }
 if (opcao == 2)
 {
 cadastro.menu = TELA_DESCADASTRAR;

 if (cadastro.totalCovids == 0)
 {
 printf("\tNao ha nenhum paciente cadastrado para remover\n");
 cadastro.menu = TELA_PRINCIPAL;
 }
 }
 if (opcao == 3)
 {
 cadastro.menu = TELA_LISTAR_TODOS;
 if (cadastro.totalCovids == 0)
 {
 printf("\tCadastro nao tem nenhum paciente para listar\n");

 cadastro.menu = TELA_PRINCIPAL;
 }
 }


 }
 break;

 case TELA_CADASTRAR:
 {
 printf("-------------------------------------\n");
 printf("\tCADASTRO:\n");
 printf("-------------------------------------\n");
 Covid novo;
 char opcao = 's';
 do
 {

 memset(&novo, 0x0, sizeof(novo));
 strcpy(novo.separador1, "---\n");
 printf("Digite o nome do paciente: ");

 fflush(stdin);
 fgets(novo.nome, 32, stdin);

 int id = 0;
 while (novo.nome[id] != '\0' && novo.nome[id] != '\n')
 id++;
 novo.nome[id] = '\0';
 novo.nome[31] = '\n';


 printf("Telefone do paciente:");
 fflush(stdin);
 fgets(novo.telefone, 14, stdin);
 id = 0;
 while (novo.telefone[id] != '\0' && novo.telefone[id] != '\n')
 id++;
 novo.telefone[id] = '\0';
 novo.telefone[13] = '\n';
 printf("Endereco do paciente: ");
 fflush(stdin);
 fgets(novo.endereco, 50, stdin);
 id = 0;
 while (novo.endereco[id] != '\0' && novo.endereco[id] != '\n')
 id++;
 novo.endereco[id] = '\0';
 novo.endereco[49] = '\n';
 printf("Cidade do paciente: ");
 fflush(stdin);
 fgets(novo.cidade, 30, stdin);
 id = 0;
 while (novo.cidade[id] != '\0' && novo.cidade[id] != '\n')
 id++;
 novo.cidade[id] = '\0';
 novo.cidade[29] = '\n';


 printf("Estado do paciente (sigla = XX): ");
 fflush(stdin);
 fgets(novo.estado, 20, stdin);
 id = 0;
 while (novo.estado[id] != '\0' && novo.estado[id] != '\n')
 id++;
 novo.estado[id] = '\0';
 novo.estado[19] = '\n';
 printf("CPF do paciente (Exmplo : XXX.XXX.XXX-XX): ");
 fflush(stdin);
 fgets(novo.cpf, 14, stdin);
 id = 0;
 while (novo.cpf[id] != '\0' && novo.cpf[id] != '\n')
 id++;
 novo.cpf[id] = '\0';
 novo.cpf[13] = '\n';
 printf("CEP do paciente (Exemplo XXXXX-XX): ");
 fflush(stdin);
 fgets(novo.cep, 12, stdin);
 id = 0;
 while (novo.cep[id] != '\0' && novo.cep[id] != '\n')
 id++;
 novo.cep[id] = '\0';
 novo.cep[11] = '\n';
 printf("Email do paciente: ");
 fflush(stdin);
 fgets(novo.email, 32, stdin);
 id = 0;
 while (novo.email[id] != '\0' && novo.email[id] != '\n')
 id++;
 novo.email[id] = '\0';
 novo.email[31] = '\n';

 printf("Informe as comorbidades do paciente caso não possuia deixe vazio): ");
 fflush(stdin);
 fgets(novo.comorbidade, 30, stdin);
 id = 0;
 while (novo.comorbidade[id] != '\0' && novo.comorbidade[id] != '\n')
 id++;
 novo.comorbidade[id] = '\0';

 printf("Data de nacimento do paciente: ");

 fflush(stdin);
 scanf("%d", &novo.dia);
 printf("Mes nascimento (dd): ");
 fflush(stdin);
 scanf("%d", &novo.mes);
 printf("Ano nascimento (mm): ");
 fflush(stdin);



 scanf("%d", &novo.ano);
 printf("Ano do diagnostico (YYYY): ");
 fflush(stdin);
 scanf("%d", &novo.diaD);
 printf("Dia do diagnostico (dd): ");
 fflush(stdin);
 scanf("%d", &novo.mesD);
 printf("Mes diagnostico (mm): ");
 fflush(stdin);
 scanf("%d", &novo.anoD);
 strcpy(novo.separador, "\n--");
 if (novo.mes<=mA && novo.dia <= dA)
 {novo.idade=aA-novo.ano; }
 else if (novo.mes>=mA && novo.dia > dA)
 {novo.idade=aA-novo.ano-1; }
 else if (novo.mes>=mA && novo.dia <= dA)
 {novo.idade=aA-novo.ano-1; }
 else if (novo.mes<=mA && novo.dia > dA)
 {novo.idade=aA-novo.ano; }
 printf(" IDADE: %d ANOS\n", novo.idade);
 printf("Adicionar o paciente ? [s/n]\n");
 opcao = getchar();

 int c = 0;
 while ((c = getchar()) != '\n' && c != EOF) { }
 } while (opcao == 'n' || opcao == 'N');

 cadastro.pacientes[cadastro.totalCovids] = novo;
 cadastro.totalCovids++;

 memoria = fopen("pacientes.txt", "w+");
 if (memoria == NULL)
 {
 printf("erro ao abrir arquivo pacientes.txt\n");
 return 0;
 }

 size_t salvos = fwrite(cadastro.pacientes, sizeof(Covid), cadastro.totalCovids,
memoria);
 if (salvos != (size_t)cadastro.totalCovids)
 {
 printf("Erro ao salvar arquivo pacientes.txt\n");
 return 1;
 }
 fclose(memoria);

 risco=fopen("Paciente_risco.txt","a");
 if (novo.idade>=65 || novo.comorbidade[strlen(novo.comorbidade)-1] != '\0')
 {
 fprintf(risco,"%s ",novo.cep);
 fprintf(risco,"%d ",novo.idade);
 fprintf(risco,"%s\n\n",novo.comorbidade);
 printf("Adicionado ao arquivo Paciente_risco.txt para enviar para secretaria de saude\n");
 }
 fclose(risco);

 cadastro.menu = TELA_PRINCIPAL;
 }
 break;

 case TELA_DESCADASTRAR:
 {
 printf("-------------------------------------\n");
 printf("\tEXCLUIR PACIENTE:\n");
 printf("-------------------------------------\n");
 int i;
 for (i = 0; i < cadastro.totalCovids; i++)
 {
 printf("Covid 19 %d\n", i);
 printf("\tNome: %s\n", cadastro.pacientes[i].nome);
 printf("\tTelefone: %s\n", cadastro.pacientes[i].telefone);
printf("\tEndereco: %s\n", cadastro.pacientes[i].endereco);
 printf("----------------------------------------------------\n");
 }
 int indice = -1;
 do
 {
 printf("Digite o codigo do paciente  para descadastrar: de 0 ate %d\n",
cadastro.totalCovids-1);
fflush(stdin);
 scanf("%d", &indice);

 int c = 0;
 while ((c = getchar()) != '\n' && c != EOF) { }
 } while (indice < 0 || indice >= cadastro.totalCovids);

 for (i = indice; i < cadastro.totalCovids - 1; i++)
 cadastro.pacientes[i] = cadastro.pacientes[i + 1];

 cadastro.totalCovids--;

 memoria = fopen("pacientes.txt", "w+");
 if (memoria == NULL)
 {
 printf("Erro arquivo pacientes.txt\n");
 return 0;

 }

 size_t salvos = fwrite(cadastro.pacientes, sizeof(Covid), cadastro.totalCovids,
memoria);
 if (salvos != (size_t)cadastro.totalCovids)
 {
 printf("Erro ao salvar arquivo pacientes.txt\n");
 return 1;
 }
 fclose(memoria);

 cadastro.menu = TELA_PRINCIPAL;
 }
 break;

 case TELA_LISTAR_TODOS:
 {
 printf("-------------------------------------\n");
 printf("\tLISTA DE PACIENTES:\n");
 printf("-------------------------------------\n");
 int i;
 for (i = 0; i < cadastro.totalCovids; i++)
 {
 printf("Covid %d\n", i);
 printf("\tNome: %s\n", cadastro.pacientes[i].nome);
 printf("\tTelefone: %s\n", cadastro.pacientes[i].telefone);
 printf("\tEndereco: %s\n", cadastro.pacientes[i].endereco);

 printf("\tCidade: %s\n", cadastro.pacientes[i].cidade);
 printf("\tEstado: %s\n", cadastro.pacientes[i].estado);
 printf("\tCpf: %s\n", cadastro.pacientes[i].cpf);
 printf("\tCep: %s\n", cadastro.pacientes[i].cep);
 printf("\tEmail: %s\n", cadastro.pacientes[i].email);
 printf("\tComorbidades: %s\n", cadastro.pacientes[i].comorbidade);
 printf("\tIdade: %d/%d/%d\n", cadastro.pacientes[i].dia, cadastro.pacientes[i].mes,
cadastro.pacientes[i].ano);
 printf("\tData diagnostico: %d/%d/%d\n", cadastro.pacientes[i].diaD,
cadastro.pacientes[i].mesD, cadastro.pacientes[i].anoD);
 printf("----------------------------------------------------\n");
 }

 cadastro.menu = TELA_PRINCIPAL;
 }
 break;
 default:
 cadastro.menu = TELA_PRINCIPAL;
 break;
 }
 }
 return 0;
}
