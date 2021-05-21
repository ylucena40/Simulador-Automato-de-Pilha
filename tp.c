#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tp.h"

void NEstados(){
	FILE *arquivo;
	arquivo = fopen("Tabela.txt","r");
	
	char texto[MAX];
	int i=-1;
	while(!feof(arquivo)){
		fscanf(arquivo,"%[^\n] %s",texto,texto);
		i++;
	}
	fclose(arquivo);
	TotalEstados = i;
}

void NSimb(){
	FILE *arquivo;
	arquivo = fopen("Tabela.txt","r");
	
	char texto[MAX];
	int i=0, cont=0;
	fscanf(arquivo,"%[^\n]",texto);
	while(1){
		if(texto[i] == '\0') break;
		if(texto[i] != ' ') cont++;
		i++;
	}
	
	fclose(arquivo);
	NSimbolos = cont;
}

void MontaSimbolos(char Alfabeto[]){
	FILE *arquivo;
	arquivo = fopen("Tabela.txt","r");
	
	char texto[MAX];
	int i=0,cont=0;
	fscanf(arquivo,"%[^\n]",texto);
	while(1){
		if(texto[i] == '\0') break;
		if(texto[i] != ' '){
			Alfabeto[cont] = texto[i];
			cont++;
		}
		i++;
	}
	
	fclose(arquivo);
}

void AdicionaTransicao(Estados *e, char tr, char ec, int ei, char desemp, char empi){
	
	Estados *Aux;
	Estados *NovoEstado;
	
	Aux = e;
	
	while(Aux->ProximoEstado != NULL){
		Aux = Aux->ProximoEstado;
	}
	
	NovoEstado = (Estados*)malloc(sizeof(Estados));
	NovoEstado->transicao = tr;
	NovoEstado->estadoc = ec;
	NovoEstado->estadoi = ei;
	NovoEstado->desempillha = desemp;
	NovoEstado->empilha = empi;
	NovoEstado->ProximoEstado = NULL;
	
	Aux->ProximoEstado = NovoEstado;
}

int ConverteNumero(char t[]){
	
	char texto[MAX];
	int i = 2;
	while(t[i] != ','){
		texto[i-2] = t[i];
		i++;
	}
	int valor = atoi(texto);
	return valor;
}


int VerificaAFNAFD(char texto[]){
	int i=0, verifica=0;
	while(texto[i] != '\0'){
		if(texto[i] == '/'){
			verifica = 1;
			break;
		}
		i++;
	}
	return verifica;
}

void VetorAFN(char texto1[], char texto2[]){
	
	int i=0, aux=0, i2 =0;
	while(texto1[i] != '\0'){
		if(aux > 0){
			texto2[i2] = texto1[i];
			texto1[i] = ' ';
			i2++;
		}
		if(texto1[i] == '/'){
			aux++;
			texto1[i] = ' ';
		}
		i++;
	}
	texto2[i2] = texto1[i];
}

char CaracterEmpilha(char vetor[]){
	int i=0, cont=0;
	char e;
	while(vetor[i]!='\0'){
		if(cont == 2){
			e = vetor[i];
			break;
		}
		if(vetor[i] == ',')cont++;
		i++;
	}
	return e;
}

char CaracterDesempilha(char vetor[]){
	int i=0, cont=0;
	char e;
	while(vetor[i]!='\0'){
		if(cont == 1){
			e = vetor[i];
			break;
		}
		if(vetor[i] == ',')cont++;
		i++;
	}
	return e;
}


int VerificaPalavra(Estados *Automato,char estadoc, int estado,int estadoanterior, int contador){
	int cont1 = 0;
	Estados *P;
	Estados *verif;

	if(PalavraValida == 0)
	printf("->%c%d\n",estadoc,estado);

	if(contador == 0 && Palavra[contador] == 'E' || contador != 0 && Palavra[contador] == '\0'){
		verif = Automato[estado].ProximoEstado;
		while(verif != NULL){
			if(verif->transicao == '?')
				break;
			verif = verif->ProximoEstado;
		}
		
		if(verif != NULL){
			if(verif->transicao == '?'){
				if(pilha->contador == 0){
					if(Palavra[contador] == 'E' || Palavra[contador] == '\0'){
						printf("->%c%d\n",verif->estadoc,verif->estadoi);
						PalavraValida = 1;
					}
					else
						PalavraValida = 0;
					return;
				}
			}
		}
	}
	else{
		P = Automato[estado].ProximoEstado;
		
		while(P!=NULL && Palavra[contador]!='\0'){
			if(P->transicao == Palavra[contador]){
				if(PalavraValida == 0){
					if(P->empilha != 'E'){
						printf("Empilha: %c\n",P->empilha);
						Empilhar(P->empilha);
					}
					if(P->desempillha != 'E'){
						printf("Desempilha: %c\n",P->desempillha);
						if(Desempilhar(P->desempillha) == 0)
						printf("\nErro ao Desempilhar, palavra nao valida\n");
					}
				}
				VerificaPalavra(Automato,P->estadoc,P->estadoi,estado,contador+1);
				if(P->desempillha != 'E'){
					printf("Retorna estado\nEmpilha novamente: %c\n",P->desempillha);
					Empilhar(P->desempillha);
				}
				if(P->empilha != 'E'){
					printf("Retorna estado\nDesempilha caminho invalido: %c\n",P->empilha);
					if(Desempilhar(P->empilha) == 0)
					printf("\nErro ao Desempilhar, palavra nao valida\n");
				}
			}
			P = P->ProximoEstado;
		}
	}
	
	if(PalavraValida == 1){
		return 1;
	}

	return 0;
}

void CopiaVetor(char Texto1[], char Texto2[]){
	int i=0;
	while(Texto2[i] != '\0'){
		Texto1[i] = Texto2[i];
		Texto2[i] = ' ';
		i++;
	}
}

void Empilhar(char e){
	if(pilha->contador == 0){
		pilha->elemento = e;
		pilha->contador = 1;
	}
	else{
		Pilha *aux;
		aux = pilha;
		while(aux->Prox != NULL){
			aux = aux->Prox;
		}
		Pilha *Novo;
		Novo = (Pilha*)malloc(sizeof(Pilha));
		Novo->contador = aux->contador++;
		Novo->elemento = e;
		Novo->Prox = NULL;
		aux->Prox = Novo;
	}
}

int Desempilhar(char e){
	int valida;
	Pilha *aux;
	Pilha *desemp;

	if(pilha->Prox == NULL){
		if(pilha->elemento == e){
			pilha->contador = 0;
			pilha->elemento = 'E';
			valida = 1;
		}
		else if(pilha->elemento == 'E'){
			pilha->contador = 0;
			pilha->elemento = 'E';
			valida = 1;
		}
	}
	else{
		aux = pilha;
		desemp = aux;
		while(aux->Prox != NULL){
			desemp = aux;
			aux = aux->Prox;
		}
		if(aux->elemento == e){
			desemp->Prox = NULL;
			free(aux);
			valida = 1;
		}
		else
			valida = 0;
	}
	return valida;
}

void LimpaPilha(){
	Pilha *aux;
	Pilha *aux1;
	aux = pilha;
	aux1=aux;
	while(aux->Prox!=NULL){
		aux1 = aux;
		aux = aux->Prox;
		free(aux1);
	}
	aux->contador = 0;
	aux->elemento = 'E';
	aux->Prox = NULL;
}