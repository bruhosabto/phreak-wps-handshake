#include "telefone.h"
#include <stdio.h>

static int numero_A;
static int status_ordem = 0;
static int ddd;
static int pre;
static int contador = 0;
extern  int Total; //variavel declarada na main
static int total = 0;

void  iniciar(int p_numero,int status,int d, int p)
{

	if(p_numero == 0 && status == 0) //decremental
	{
		numero_A = 99999999;
		status_ordem = status;
	}
	if(p_numero == 0 && status == 1) //incremental
	{
		numero_A = 81000000;
		status_ordem =  status;
	}
	if(p_numero > 80000000 && p_numero < 99999999)//incremental apartir de um numero dado
	{
		numero_A = p_numero;
		status_ordem = 1;
	}
	if(d != 0 ) ddd = d;
	if(p != 0 ) pre = p;
	total = Total;

}
int Ddd()
{
	return ddd;
}
int Prefixo()
{
	return pre;
}
void Numero()
{
	contador++;

	if(status_ordem == 1 && contador < Total ) numero_A++; //verifica status, caso 1, é incrementado um ao valor dado
	else if(status_ordem == 0 && contador < Total ) numero_A--; //verifica status, caso 0, é decrementado um do valor dado
	//return numero_A;

}

int GetNumero()
{

	return numero_A;
}
