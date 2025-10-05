#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

// Defini��es de constantes
#define ENTER 13		// ASCII da tecla Enter
#define BACKSPACE 8		// ASCII da tecla Backspace
#define MAX 50			// Tamanho m�ximo da senha

int main(){
	
	// Declara��o de vari�veis
	char caracter, senha[MAX], senhaCorreta[MAX];
	int i = 0;
	FILE *arquivo = NULL;
	
	// Tratamento do arquivo
	arquivo = fopen ("senha.txt", "r");		// Abre o arquivo em modo leitura
	if(arquivo == NULL){					// Verifica se o arquivo existe
		printf("Arquivo nao encontrado!");
		return 1;
	}else{
		fgets(senhaCorreta, sizeof(senhaCorreta), arquivo);		// L� a senha do arquivo
	}
	fclose(arquivo);	// Fecha o arquivo
	
	senhaCorreta[strcspn(senhaCorreta, "\r\n")] = '\0';		// Remove poss�veis \n ou \r da senha lida
	
	//Entrada da senha do usu�rio (mascarada)
	printf("Digite a senha: ");		// Solicita a senha do usu�rio
	
	while(1){
		caracter = getch();			// Captura um caractere sem mostrar na tela
		if(caracter == ENTER){		// Enter finaliza a entrada
			senha[i] = '\0';
			break;
		}else if(caracter == BACKSPACE){	// Backspace apaga o �ltimo caractere
			if (i > 0){						// Garante que n�o vai apagar al�m do in�cio
				i--;
				printf("\b \b");			// Apaga o asterisco na tela
				senha[i] = '\0';			// Remove caractere da string
			}
		}else if (i < MAX - 1) {			// Garante que n�o ultrapasse o tamanho m�ximo
			senha[i] = caracter;			// Armazena o caractere na senha
			i++;
			putchar('*');					// Mostra asterisco na tela
		}
	}
	
	//Compara��o da senha
	if(strcmp(senha, senhaCorreta) == 0){
    	printf("\nSenha correta! Acesso permitido.");		// Senha correta
	}else{
	    printf("\nSenha incorreta! Acesso negado.");		// Senha incorreta
	}

	return 0;
}
