#include<stdio.h>
int main(void){
	int qtdIngressos = 120, qtdIngressosMax;
	float valorIngressos, lucro, lucroMax, valorIngressosMax;
	const float despesas = 600;
		
	lucroMax = 0;
	
    printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n"); 
    
	for(valorIngressos = 15; valorIngressos >= 3; valorIngressos -= 3){
		lucro = qtdIngressos * valorIngressos - despesas;
		if(lucroMax <= lucro){
			lucroMax = lucro;
			valorIngressosMax = valorIngressos;
			qtdIngressosMax = qtdIngressos;
		}		
		printf("\xBA Valor: R$ %5.2f - Ingressos: %i - Lucro: R$ %7.2f.  \xBA\n", valorIngressos, qtdIngressos, lucro);
		qtdIngressos += 26; 		
	}	
    printf("\xBA\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBA\n"); 
    printf("\xBA LUCRO M\xb5XIMO = R$%.2f por %i ingressos a R$ %.2f. \xBA\n", lucroMax, qtdIngressosMax, valorIngressosMax); 
    printf("\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n"); 

	printf("\n\n\nPRESSIONE QUALQUER TECLA PARA ENCERRAR.\n");		
	getche();
}
