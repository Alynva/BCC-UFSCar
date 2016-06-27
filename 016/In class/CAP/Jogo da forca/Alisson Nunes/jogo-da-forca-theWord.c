#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
	int i;
	char *dados = NULL;
	
	char theWord[50] = {'\n'};
	
			
	dados = getenv("QUERY_STRING");
	FILE *lf;
	
	if (sscanf(dados, "theWord=%s", theWord) == 1) {
		for (i = 0; i < strlen(theWord); i++) {
			theWord[i] = tolower(theWord[i]);
		}
		lf = fopen("jogo-da-forca.txt", "w+");
		fprintf(lf, "%s ", theWord);
		
		for (i = 0; i < strlen(theWord); i++) {
			fprintf(lf, "%c", '_');
		}
		fclose(lf);
	}
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta http-equiv=\"refresh\" content=\" 0 ;url=jogo-da-forca.cgi\">");
			printf("<meta charset=\"utf-8\">");
			printf("<title>Jogo da forca - CGI + Arquivos</title>");
		printf("</head>");
		printf("<body>");
		printf("</body>");
	printf("</html>");
	
	return 0;
}
