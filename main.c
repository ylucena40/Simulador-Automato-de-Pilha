#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp.h"

int main(){
	AF = 0;
	NEstados();
	NSimb();
	char Alfabeto[NSimbolos];
	MontaSimbolos(Alfabeto);
	
	Automato = (Estados*)malloc(TotalEstados*sizeof(Estados));
	pilha = (Pilha*)malloc(sizeof(Pilha));
	pilha->elemento = 'E';
	pilha->contador = 0;
	pilha->Prox = NULL;
	
	int i=0,inicio;
	
	while(i<TotalEstados){
		Automato[i].estadoc = 'q';
		Automato[i].estadoi = i;
		Automato[i].tipo = 0;
		Automato[i].ProximoEstado = NULL;
		Automato[i].empilha = 'E';
		Automato[i].desempillha = 'E';
		i++;
	}
	
	FILE *arquivo;
	arquivo = fopen("Tabela.txt","r");
	
	char texto1[MAX];
	char texto2[MAX];
	char aemp, adesemp;
	
	fscanf(arquivo,"%[^\n]",texto1);
	int contatrans=-1 ,contestado=0, numeroestado=0;

	while(!feof(arquivo)){
		fscanf(arquivo,"%s",texto1);
		if(contatrans < 0){
			if(texto1[0] == '>'){
				Automato[contestado].tipo = 1;
				inicio = contestado;
			}
			if(texto1[0] == '*')
				Automato[contestado].tipo = 2;
			contatrans++;
		}
		else if(texto1[0] == '-'){
			contatrans++;
		}
		else{
			if(VerificaAFNAFD(texto1) == 1){
				AF = 1;
				while(VerificaAFNAFD(texto1) == 1){
					VetorAFN(texto1,texto2);
					numeroestado = ConverteNumero(texto1);
					aemp = CaracterEmpilha(texto1);
					adesemp = CaracterDesempilha(texto1);
					if(Alfabeto[contatrans] == '*')
						AdicionaTransicao(&Automato[contestado],'?',texto1[1],numeroestado,adesemp,aemp);
					else
						AdicionaTransicao(&Automato[contestado],Alfabeto[contatrans],texto1[1],numeroestado,adesemp,aemp);
					if(VerificaAFNAFD(texto2) == 1)
						CopiaVetor(texto1,texto2);
				}
				numeroestado = ConverteNumero(texto2);
				aemp = CaracterEmpilha(texto2);
				adesemp = CaracterDesempilha(texto2);
				if(Alfabeto[contatrans] == '*')
					AdicionaTransicao(&Automato[contestado],'?',texto2[1],numeroestado,adesemp,aemp);
				else
					AdicionaTransicao(&Automato[contestado],Alfabeto[contatrans],texto2[1],numeroestado,adesemp,aemp);
			}
			else{
				numeroestado = ConverteNumero(texto1);
				aemp = CaracterEmpilha(texto1);
				adesemp = CaracterDesempilha(texto1);
				if(Alfabeto[contatrans] == '*')
					AdicionaTransicao(&Automato[contestado],'?',texto1[1],numeroestado,adesemp,aemp);
				else
					AdicionaTransicao(&Automato[contestado],Alfabeto[contatrans],texto1[1],numeroestado,adesemp,aemp);
			}
			contatrans++;
		}
		if(contatrans == NSimbolos-1){
			contatrans = -1;
			contestado++;
		}
	}
	
	fclose(arquivo);

	int menu = 0;
	int verifica=0;
	while(1){
		if(AF == 1) printf("AFN\n");
		else printf("AFD\n");
		printf("1.Testar Palavra\n2.Sair\n");
		scanf("%d",&menu);
		if(menu == 2) break;
		printf("Digite uma palavra: ");
		scanf("%s",&Palavra);
		PalavraValida = 0;
		VerificaPalavra(Automato,Automato[inicio].estadoc,Automato[inicio].estadoi,-1,0);
		if(PalavraValida == 0)
		printf("\nA palavra %s nao eh valida.\n",Palavra);
		if(PalavraValida == 1)
		printf("\nA palavra %s eh valida.\n",Palavra);
		LimpaPilha();
	}


	return 0;
}
