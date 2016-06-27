#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHANCES 9

int main() {
	int i, j, len, cont;
	char *dados = NULL;
	
	char theWord[50] = {'\n'};
	char myWord[50] = {'\n'};
	char temp[50] = {'\n'};
	char theErred;
	char erred[50];
	char classe[20];
	char copy[50];
	
			
	dados = getenv("QUERY_STRING");
	FILE *lf;
	
	if (sscanf(dados, "myWord=%s", myWord) == 1) {
		for (i = 0; i < strlen(myWord); i++) {
		myWord[i] = tolower(myWord[i]);
		}
		
		lf = fopen("jogo-da-forca.txt", "r+");
		
		fscanf(lf, "%s %s %s", theWord, temp, erred);
		
		for (j = 0; j < strlen(myWord); j++) {
			cont = 0;
			for (i = 0; i < strlen(theWord); i++) {
				if (theWord[i] == myWord[j]) {
					temp[i] = theWord[i];
					cont++;
				}
			}
			if (!cont) {
				cont = 0;
				for (i = 0; i < strlen(erred); i++) {
					if (myWord[j] == erred[i]) {
						cont++;
					}
				}
				strcpy(copy, erred);
				if (!cont) {
					snprintf(erred, sizeof erred, "%s%c", copy, myWord[j]);
				}
			}
		}
		
		rewind(lf);
		fprintf(lf, "%s %s %s", theWord, temp, erred);
		fclose(lf);
	}
	lf = fopen("jogo-da-forca.txt", "r+");
	rewind(lf);
	fscanf(lf, "%s %s %s", theWord, myWord, erred);
	
	j = strlen(erred);
	for (i = j - 1; i < CHANCES; i++) {
		strcpy(copy, erred);
		snprintf(erred, sizeof erred, "%s%c", copy, '-');
	}
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta charset=\"utf-8\">");
			printf("<title>Jogo da forca - CGI + Arquivos</title>");
			printf("<link rel=\"stylesheet\" href=\"../jogo-da-forca.css\">");
		printf("</head>");
		printf("<body>");
			printf("<a href=\"../jogo-da-forca.html\">Voltar</a>");
			if (strcmp(theWord, myWord) && j <= CHANCES) {
				printf("<form action=\"\">");
					printf("<input type=\"text\" name=\"myWord\" required autofocus placeholder=\"Digite uma palavra/letra\" maxlength=\"45\" autocomplete=\"off\">");
					printf("<input type=\"submit\" value=\"Tentar\">");
				printf("</form>");
			} else if (!strcmp(theWord, myWord)) {
				snprintf(classe, sizeof classe, " class=\"venceu\"");
				j = CHANCES + 1;
			} else if (j >= CHANCES) {
				snprintf(classe, sizeof classe, " class=\"perdeu\"");
			}
			printf("<br>");
			printf("<div id=\"game\"%s data-palavra=\"%s\" data-acertos=\"%s\" data-erros=\"%s\">", classe, theWord, myWord, erred);
				printf("<div></div>");
				for (i = 0; i < j; i++) {
				/*for (i = 0; i < 15; i++) {*/
					printf("<div></div>");
				}
			printf("</div>");
		printf("</body>");
	printf("</html>");
	
	return 0;
}
