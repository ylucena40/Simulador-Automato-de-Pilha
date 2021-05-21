typedef struct Struct1 Estados;

struct Struct1{
	char transicao;
	int tipo;
	char estadoc;
	int estadoi;
	char empilha;
	char desempillha;
	
	struct Struct1* ProximoEstado;
};

typedef struct Struct2 Pilha;

struct Struct2{
	char elemento;
	int contador;

	struct Struct2* Prox;
};

#define MAX 500

char Palavra[MAX];
int TotalEstados;
int NSimbolos;
int PalavraValida;
int AF;
Estados *Automato;
Pilha *pilha;

void NEstados();
void NSimb();
void MontaSimbolos(char Alfabeto[]);
void AdicionaTransicao(Estados *e, char tr, char ec, int ei,char desemp, char empi);
int ConverteNumero(char t[]);
int VerificaAFNAFD(char texto[]);
void VetorAFN(char texto1[], char texto2[]);
void ApagaAutomato(Estados *a);
char CaracterEmpilha(char vetor[]);
char CaracterDesempilha(char vetor[]);
int VerificaPalavra(Estados *Automato,char estadoc, int estado,int estadoanterior, int contador);
void CopiaVetor(char Texto1[], char Texto2[]);
void Empilhar(char e);
int Desempilhar(char e);
void LimpaPilha();