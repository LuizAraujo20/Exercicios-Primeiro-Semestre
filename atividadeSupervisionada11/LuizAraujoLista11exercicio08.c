/*
Name: Luiz Araujo
Description: Fazer um algoritmo que leia at� 30 caracteres e os ordene em ordem decrescente. 
� considerado que A < B < C < ... (ordem alfab�tica).
*/

#include<stdio.h>
#include<stdlib.h>

#define MAX_LETRAS 30

int main(void){
//	declara��es
	char letras[MAX_LETRAS], auxiliar;
	int controle, contadorLetras = 0, controle2;
	
//	instru��es
	printf("   INFORME ALGUMAS LETRAS");
	printf("z\n(finaliza se nao for letras)\n\n");
	
	for(controle = 0; controle < MAX_LETRAS; controle++){
		fflush(stdin);	//estava pulando "casas"
		printf("%2i%c: ", controle + 1, 166);	
		scanf("%c", &letras[controle]);
		if(((letras[controle] < 'a')&&(letras[controle] < 'z'))&&((letras[controle] < 'A')&&(letras[controle] < 'Z'))){
			break;
		}
		contadorLetras++;
	}
	
	for(controle = 0; controle < contadorLetras; controle++){		
		for(controle2 = controle; controle2 < contadorLetras; controle2++){
			if(letras[controle] <= letras[controle2]){
				auxiliar = letras[controle];
				letras[controle] = letras[controle2];
				letras[controle2] = auxiliar;
			}
		}
	}
	
	printf("\n   ORDEM DECRESCENTE:\n");
	for(controle = 0; controle < contadorLetras; controle++){
		printf("%2i%c: %c\n", controle + 1, 166, letras[controle]);
	}
//	getch(); //esperar pra fechar
	return 0;
}
