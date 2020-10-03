#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "telefone.h"

int  Total = (2*9*10*10*10*10*10*10); //global

struct Dados{

	int numero;
	int quantidade;
	int status;
	int ddd;
	int prefixo;
	char nome[64];
};

void work(int numero,int quantidade, int status,int ddd,int prefixo, char file[64]); //serve apenas pra printar os dados passados e empacotar e passar a diante.
void geratrix(struct Dados dados);

void Usage(char progname[20])
{

	fprintf(stderr,"Modo de usar.\n");
	fprintf(stderr,"\t%s <numero> <quantidade> <status> <ddd> <prefixo> <arquivo de saida>\n",progname);
	fprintf(stderr,"\tArgumentos requeridos:\n");
	fprintf(stderr,"\t-n\tNumero, o numero pode ser 0(zero) para todos os numeros de 80000000 ate 99999999, ou voce pode especificar um numero, por exemplo: 81234567.\n");
	fprintf(stderr,"\t-q\tQuantidade, informe a quantidade de numeros que deseja gerar.Para todos os numeros possiveis a opção -t deve ser usada\n");
	fprintf(stderr,"\t-s\tStatus, possui dois valores, 1 para incrementar, 0 para decrementar.\n");
	fprintf(stderr,"\t-d\tDDD, informe o ddd de sua regiao ou da regiao o qual deseja gerar os numeros.\n");
	fprintf(stderr,"\t-p\tPrefixo, informe o prefixo de sua regiao ou da regiao o qual deseja gerar os numeros.\n");
	fprintf(stderr,"\t-o\tArquivo de saida, informe aqui o nome e o local deseja para o arquivo de saida.\n");
	fprintf(stderr,"\tautor: brunosantos\n");
	fprintf(stderr,"\tversao 1.0\n");

	exit(0);
}

int main(int argc, char *argv[])
{
	int numero = -1;
	int quantidade = 0;
	int status = 0;
	int xddd = 0;
	int xpre = 0;
	char file[64];
	int opcao;
	FILE *arquivo;

	opterr = 0; //desabilita a saida de mensagem de erro da getopt



	while((opcao = getopt(argc,argv, "n:q:s:d:p:o:ht")) != -1) //atoi serve para converter string em inteiros
	{
		switch(opcao)
		{
			case 'n':
				numero = atoi(optarg);
				break;
			case 'q':
				quantidade = atoi(optarg);
				break;
			case 's':
				status = atoi(optarg);
				break;
			case 'd':
				xddd = atoi(optarg);
				break;
			case 'p':
				xpre = atoi(optarg);
			case 'o':
				strcpy(file,optarg);
				break;
			case 'h':
				Usage(argv[0]);
				break;
			case 't':
				quantidade = Total;
				break;
			case '?':
				if(optopt == 'n' || optopt == 'q' || optopt == 's' || optopt == 'd' || optopt == 'p' || optopt == 'o')
				{
					fprintf(stderr,"opcao -%c requer argumento, use -h para obter mais informacoes!\n",optopt);
					exit(0);
				}
			default:
				fprintf(stderr,"erro\n");
				exit(0);
		}
	}

	if(numero == -1) fprintf(stderr,"por favor, especificar o numero, caso queira deixa padrao use -n 0\n"),exit(0);
	
	if(quantidade == 0 ) fprintf(stderr,"por favor, especificar a quantidade de numeros a ser gerada!\n"),exit(0); 


	if(numero != 1 && quantidade != 0 )
	{
		work(numero,quantidade,status,xddd,xpre,file);
	}
}

 void work(int numero,int quantidade, int status,int ddd,int prefixo, char file[64])
{
	struct Dados dados;

	fprintf(stderr,"Numero          : %d\n",numero);
	fprintf(stderr,"Quantidade      : %d\n",quantidade);
	fprintf(stderr,"Status          : %s\n",status ? "Incremtal" : "decremental");
	fprintf(stderr,"DDD             : %d\n",ddd);
	fprintf(stderr,"Prefixo         : %d\n",prefixo);
	fprintf(stderr,"Arquivo de saida: %s\n",file);

//jogando dados na estrutura de passando para a função geratrix
	dados.numero = numero;
	dados.quantidade = quantidade;
	dados.status = status;
	dados.ddd = ddd;
	dados.prefixo = prefixo;
	strcpy(dados.nome,file);
	geratrix(dados);


}

 void geratrix(struct Dados dados)
{
	FILE *arquivo;
	static int contador  = 0;
	
	arquivo = fopen(dados.nome,"a+"); //cria um arquivo com o nome dado pelo usuario

	//fprintf(stderr,"nome -> %s\n",dados.nome);
	 int numero_aux ;

	if( arquivo == NULL) fprintf(stderr,"Erro ao tentar criar ou abrir o arquivo '%s'.\n",dados.nome),exit(0);
	else{

		if(dados.ddd != 0 && dados.prefixo == 0)
		{
			iniciar(dados.numero,dados.status,dados.ddd,0);
			numero_aux = GetNumero();

			while(contador != dados.quantidade)
			{
			//	fprintf(arquivo,"%d\n",Numero());
				Numero(); //incrementa
				fprintf(arquivo,"%d%d\n",Ddd(),GetNumero());
				contador++;

			}
		}
		if( dados.prefixo != 0 && dados.ddd == 0 )
		{
			iniciar(dados.numero,dados.status,0,dados.prefixo);
			numero_aux = GetNumero();

			while(contador != dados.quantidade )
			{
				//fprintf(arquivo,"%d\n",Numero());
				Numero();
				fprintf(arquivo,"%d%d\n",Prefixo(),GetNumero());
				contador++;
			}

		}
		if(dados.ddd != 0 && dados.prefixo != 0)
		{
			iniciar(dados.numero,dados.status,dados.ddd,dados.prefixo);
			numero_aux = GetNumero();

			while(contador != dados.quantidade)
			{
				//fprintf(arquivo,"%d\n",Numero());
				Numero();
				fprintf(arquivo,"%d%d%d\n",Ddd(),Prefixo(),GetNumero());
				contador++;

			}

		}
		if(dados.ddd == 0 && dados.prefixo == 0)
		{
			iniciar(dados.numero,dados.status,0,0);
			numero_aux = GetNumero();
			
			while(contador != dados.quantidade)
			{
				Numero();
				fprintf(arquivo,"%d\n",GetNumero());
				//fprintf(arquivo,"%d%d%d\n",Ddd(),Prefixo(),Numero());
				contador++;

			}

		}

	}
	fprintf(stderr,"Concluido!\n");
	fprintf(stderr,"Numero inicial   : %d\n", numero_aux);
	fprintf(stderr,"Numero final     : %d\n",GetNumero());
	fprintf(stderr,"Arquivo de saida : %s\n",dados.nome);
	fclose(arquivo); //fechando o arquivo de saida
}
