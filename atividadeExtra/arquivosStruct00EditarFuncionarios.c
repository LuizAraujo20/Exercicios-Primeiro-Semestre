/*
Name: arquivosStruct00EditarFuncionarios.c
Copyright: MIT License
Author: Luiz Araujo - luizcarlos_bsb2006@hotmail.com
Date: 13/12/20 14:31
Description: Manipula��o de Arquivos - edita cadastro de funcionarios.
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<locale.h>

#define MAX_FUNC 100

struct dados_pessoais{
	unsigned short codigo;	//2bytes
	char nome[31];			//31bytes
	unsigned short idade;	//2bytes
	char sexo;				//1bytes
	char cargo[21];			//21bytes
	float salario;			//4bytes
};

void lerValidarNome(char nome[]);
int lerValidarIdade();
char lerValidarSexo();
void lerValidarCargo(char cargo[]);
float lerValidarSalario();
void editarFuncionario();
void listarFuncionarios(char tipo);
unsigned short int lerArquivo(struct dados_pessoais funcionario[]);

int main(void){
	setlocale(LC_COLLATE, "Portuguese");
	setlocale(LC_MONETARY, "Portuguese");
	setlocale(LC_NUMERIC, "Portuguese");
	setlocale(LC_TIME, "Portuguese");	
	char continuar;

	listarFuncionarios('h');
	editarFuncionario();

	printf("\n\n\nPRESSIONE QUALQUER TECLA PARA ENCERRAR.\n");
	getch();
	return 0;
}

unsigned short int lerArquivo(struct dados_pessoais funcionario[]){
	unsigned short int contador_entradas;
	
	FILE *arq;
	arq = fopen("dados_funcionarios.bin", "rb");
	if(arq == NULL){
		puts("\a\a\a\nSEM FUNCIONARIOS CADASTRADOS, VERIFIQUE OS DADOS SALVOS E TENTE NOVAMENTE!");
		sleep(3);
		exit(1);
	}
	contador_entradas = fread(funcionario, sizeof(struct dados_pessoais), MAX_FUNC, arq);
	fclose(arq);	
	return contador_entradas;
}

void listarFuncionarios(char tipo){	
	struct dados_pessoais funcionario[MAX_FUNC];
	unsigned short int indice, contador_entradas;
	
	contador_entradas = lerArquivo(funcionario);	
	system("CLS");
	printf("QUANTIDADE DE FUNCIONARIOS: %i\n", contador_entradas);
	if((tipo == 'v') || (tipo == 'V')){
//		LISTA VERTICALIZADA
		for(indice = 0; indice < contador_entradas; indice++){//mostra nome de todos os func
			printf("\nCodigo : %03u ", funcionario[indice].codigo);
			printf("\nNome   : %s",funcionario[indice].nome);
			printf("\nIdade  : %d",funcionario[indice].idade);
			if(funcionario[indice].sexo == 'f'){
				printf("\nSexo   : feminino");
			}else if(funcionario[indice].sexo == 'm'){
				printf("\nSexo   : masculino");
			}else{
				printf("\nSexo   : indefinido");
			}
			printf("\nCargo  : %s",funcionario[indice].cargo);
			printf("\nSALARIO: R$ %10.2f",funcionario[indice].salario);
			printf("\n");
		}
	}else{
//		LISTA HORIZONTAL
		printf("COD %-30s%-6s%-6s%-20s%-10s\n","NOME","IDADE","SEXO","CARGO","SALARIO(R$)");
		for(indice = 0; indice < contador_entradas; indice++){//mostra nome de todos os func	
			printf("%03u ", funcionario[indice].codigo);
			printf("%-30s",funcionario[indice].nome);
			printf("%-6d",funcionario[indice].idade);
			if(funcionario[indice].sexo == 'f'){
				printf("%-6s%","FEM");
			}else if(funcionario[indice].sexo == 'm'){
				printf("%-6s%","MASC");
			}else{
				printf("%-6s%","INDEF");
			}
			printf("%-20s",funcionario[indice].cargo);
			printf("%10.2f",funcionario[indice].salario);
			printf("\n");
		}
	}
}

void editarFuncionario(){	
	FILE *arq;
	char continuar = 's', opcao;
	int indice, posicao, cod, resultado, controle_erros, contadorTemp, contador_entradas;
//	struct dados_pessoais c[MAX_FUNC];
	struct dados_pessoais funcionario[MAX_FUNC];

	do{	
		system("CLS");
		puts("EDITAR CADASTRO DE FUNCIONARIOS");
		
		contador_entradas = lerArquivo(funcionario);
		puts("TEM O CODIGO DO FUNCIONARIO?\n(s para sim)");
		fflush(stdin);
		continuar = getche();
		if(continuar != 's' && continuar != 'S'){			
			listarFuncionarios('h');
		}
		//pesquisar por codigo
		controle_erros = 0;
		printf("\nCODIGO: ");
		fflush(stdin);
		scanf("%d", &cod);
		while((cod < 0) || (cod >= MAX_FUNC)){
			controle_erros++;
			if(controle_erros > 2){
				printf("\nCODIGO INVALIDO, INFORME ALGO ENTRE 0 E %d.", (contador_entradas - 1));
			}				
			printf("\nCODIGO DO FUNCIONARIO: ");
			scanf("%d", &cod);

		}
//		pegar a posicao do cod inserido
		for(indice = 0; indice < contador_entradas; indice++){
			if(funcionario[indice].codigo == cod){
				posicao = indice;
//				break;
			}
		}
		do{
			system("CLS");
			printf("CADASTRO DO FUNCIONARIO:");
			printf("\nCODIGO : %u ", funcionario[posicao].codigo);
			printf("\n1 - NOME   : %s", funcionario[posicao].nome);
			printf("\n2 - IDADE  : %d", funcionario[posicao].idade);

			if(funcionario[posicao].sexo == 'f'){
				printf("\n3 - SEXO   : %s","FEMININO");
			}else if(funcionario[posicao].sexo == 'm'){
				printf("\n3 - SEXO   : %s","MASCULINO");
			}else{
				printf("\n3 - SEXO   : %s","INDEFINIDO");
			}
			printf("\n4 - CARGO  : %s", funcionario[posicao].cargo);
			printf("\n5 - SALARIO: R$ %.2f", funcionario[posicao].salario);
//			fclose(arq);		
			printf("\n0 - CANCELAR");
			printf("\nALTERAR:");
			fflush(stdin);
			opcao = getche();		

			controle_erros = 0;
			if(opcao != '!'){			
				while((opcao > '5') || (isdigit(opcao) == 0)){
					controle_erros++;
					if(controle_erros > 2){		
						printf("\n\nINFORME UM NUMERO DE 0 a 5.");		
						puts("\n1 - NOME");
						puts("2 - IDADE");
						puts("3 - SEXO");
						puts("4 - CARGO");
						puts("5 - SALARIO");
						puts("0 - CANCELAR");
						printf("ALTERAR:");
					}else{
						printf("\nOPCAO INVALIDA: ");
					}		 
					fflush(stdin);
					opcao = getche();
				}
			}
			if(opcao != '0'){			
				switch(opcao){
					char texto_temp[31], sexo_temp;
					float salario_temp;
					int idade_temp;
					case '1':
						do{
							puts("\nNOME COMPLETO:");
							fflush(stdin);
							gets(texto_temp);
							if((strlen(texto_temp) <= 5)){
								puts("informe um nome v�lido!");
							}
							if((strlen(texto_temp) > 30)){
								puts("informe um nome menor!");
							}
						}while((strlen(texto_temp) <= 5) || (strlen(texto_temp) > 30));							
						printf("\nANTES : %s", funcionario[posicao].nome);
						printf("\nDEPOIS: %s", texto_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");//tive que passar todos pra dentro dos IFs, pois, �s vezes, qndo fechava o prg apagava o arquivo
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								strcpy(funcionario[posicao].nome, texto_temp);
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}						
						break;
					case '2':			
						do{
							printf("\nIDADE:");
							scanf("%d", &idade_temp);
							if(idade_temp < 14){
								puts("Na CLT, a idade m�nima prevista � de 14 anos, desde que o menor seja contratado na condi��o de aprendiz.");
							}
							if(idade_temp > 120){
								puts("Informe uma idade v�lida, pois com mais de 120 anos � improv�vel que ainda esteja trabalhando.");
							}
						}while((idade_temp < 14) || (idade_temp > 120));						
						printf("\nANTES : %d", funcionario[posicao].idade);
						printf("\nDEPOIS: %d", idade_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].idade = idade_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);							
						}
						break;
					case '3':
						do{
							printf("\nSEXO: ");
							fflush(stdin);
							sexo_temp = getche();
							sexo_temp = tolower(sexo_temp);
							if(sexo_temp != 'f' && sexo_temp != 'm' && sexo_temp != 'x'){
								puts("F para feminino | M para masculino | X para indefinido ");
							}		
						}while(sexo_temp != 'f' && sexo_temp != 'm' && sexo_temp != 'x');						
						printf("\nANTES : %c", funcionario[posicao].sexo);
						printf("\nDEPOIS: %c", sexo_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].sexo = sexo_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}
						break;
					case '4':
						do{
							puts("\nCARGO:");
							fflush(stdin);
							gets(texto_temp);
							if(strlen(texto_temp) < 3){
								puts("Informe um cargo v�lido!");
							}
							if(strlen(texto_temp) > 20){
								puts("Informe um cargo menor que 20!");
							}
						}while((strlen(texto_temp) < 3)||(strlen(texto_temp) > 20));
						printf("\nANTES : %s", funcionario[posicao].cargo);
						printf("\nDEPOIS: %s", texto_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								strcpy(funcionario[posicao].cargo, texto_temp);
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}						
						break;
					case '5':					      
						do{  
							printf("\nSALARIO:\nR$ ");
							scanf("%f", &salario_temp);
						//		sal�rio m�nimoR$ 1.045,00 
							if(salario_temp < 400){
								puts("Informe um sal�rio v�lido, pois menos que R$ 400,00 nem jovem aprendiz recebe...");
							}    
						}while(salario_temp < 400);						
						printf("\nANTES : R$%.2f", funcionario[posicao].salario);
						printf("\nDEPOIS: R$%.2f", salario_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's'|| continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].salario = salario_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
							}
							fclose(arq);
						}
						break;	
					case '!':
							printf("\nALTERAR CODIGO DESSE FUNCIONARIO? ");
							printf("\n('s' para sim | 'x' para cancelar):  ");

							fflush(stdin);
							continuar = getche();
							if(continuar == 'x' || continuar == 'X'){
								break;
							}
							if(continuar != 's' && continuar != 'S'){
								int cod_errado = 0;
								do{
									printf("\nINFORME OUTRO CODIGO: ");		
									fflush(stdin);
									scanf("%d", &cod);
									for(indice = 0; indice < contador_entradas; indice++){
										if(funcionario[indice].codigo == cod){
											posicao = indice;
											cod_errado++;
										}
									}
									if(cod_errado == 0){
										printf("\nCODIGO INVALIDO!");		
									}
								}while(cod_errado == 0);

								printf("\nCODIGO : %u ", funcionario[posicao].codigo);
								printf("\n1 - NOME   : %s", funcionario[posicao].nome);
								printf("\n2 - IDADE  : %d", funcionario[posicao].idade);

								if(funcionario[posicao].sexo == 'f'){
									printf("\n3 - SEXO   : %s","FEMININO");
								}else if(funcionario[posicao].sexo == 'm'){
									printf("\n3 - SEXO   : %s","MASCULINO");
								}else{
									printf("\n3 - SEXO   : %s","INDEFINIDO");
								}
								printf("\n4 - CARGO  : %s", funcionario[posicao].cargo);
								printf("\n5 - SALARIO: R$ %.2f", funcionario[posicao].salario);

							}
						int codigo_temp;
						printf("\n\nCODIGO NOVO: ");
						scanf("%d", &codigo_temp);

						printf("\nANTES : %d", funcionario[posicao].codigo);
						printf("\nDEPOIS: %d", codigo_temp);
						printf("\n's' PARA CONFIRMAR ALTERACAO: ");
						fflush(stdin);
						continuar = getchar();
						if(continuar == 's' || continuar == 'S'){
							arq = fopen("dados_funcionarios.bin","w+b");
							if(arq == NULL){
								printf("\a\a\a\nERRO AO SALVAR NO ARQUIVO: dados_funcionarios.bin!");
								sleep(5);
								exit(1);
							}else{
								funcionario[posicao].codigo = codigo_temp;
								fwrite(funcionario, sizeof(struct dados_pessoais), contador_entradas, arq);
								printf("\a\nAlteracao realizada com sucesso!");
								fclose(arq);
							}
						}
						break;							
				}//fim switch
			}//fim if != '0'
			printf("\nEditar o mesmo funcionario? (s para sim) ");
			fflush(stdin);
			continuar = getche();
//			contador_entradas = lerArquivo(c);
		}while(continuar == 's' || continuar == 'S');

		printf("\nEditar outro funcionario? (s para sim) ");
		fflush(stdin);
		continuar = getche();
		if(continuar != 's' && continuar != 'S'){
			break;
		}			
	}while(contador_entradas < MAX_FUNC);
}
