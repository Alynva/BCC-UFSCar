#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAXPIXELSTRING 71910
#define MAXPIXEL 4794

int main() {
	int i = 0;
	int j, k;
	char *dados = NULL;
	int ope;
	char artName[50];
	char fileName[50] = {""};
	char theColor[10];
	char allPixels[MAXPIXELSTRING];
	char coloredPixel[MAXPIXEL][10];
	int index;
	char aPixel[10];
	
	FILE *fileArt;
	
	dados = getenv("QUERY_STRING");
	
	if (sscanf(dados, "ope=%d&artName=%s", &ope, artName) == 2) {
		strcat(fileName, "jogo-de-printar-");
		strcat(fileName, artName);
		strcat(fileName, ".txt");
		if (ope == 0) {
			// CRIANDO O ARQUIVO EM BRANCO
			fileArt = fopen(fileName, "w");
			fprintf(fileArt, "Name=%s\n", artName);
		} else if (ope == 1) {
			// LEITURA DO ARQUIVO
			fileArt = fopen(fileName, "r");
			fscanf(fileArt, "Name=%[^\n]\n", artName);
			
			while (!feof(fileArt)) {
				fscanf(fileArt, "%i=%[^\n]\n", &index, aPixel);
				strcpy(coloredPixel[index], aPixel);
			}
		}
		fclose(fileArt);
	} else if (sscanf(dados, "artName=%[^&]&theColor=%%23%[^&]&%s", artName, theColor, allPixels) == 3) {
		strcat(fileName, "jogo-de-printar-");
		strcat(fileName, artName);
		strcat(fileName, ".txt");
		
		// LEITURA DO ARQUIVO
		fileArt = fopen(fileName, "r");
		fscanf(fileArt, "Name=%[^\n]\n", artName);
		
		while (!feof(fileArt)) {
			fscanf(fileArt, "%i=%[^\n]\n", &index, aPixel);
			strcpy(coloredPixel[index], aPixel);
		}
		
		// Processando novos dados
		char *pch = strtok(allPixels, "=on&pixel");
		char colorPixel[MAXPIXEL][10];
		while (pch != NULL) {
			strcpy(colorPixel[i], pch);
			i++;
			pch = strtok(NULL, "=on&pixel");
		}
		
		// Adicionando os novos dados ao vetor
		for (j = 0; j < i; j++) {
			k = atoi(colorPixel[j]);
			strcpy(coloredPixel[k], theColor);
		}
		
		// REESCRITA DO ARQUIVO	
		fileArt = freopen(fileName, "w", fileArt);	
		fprintf(fileArt, "Name=%s\n", artName);
		for (i = 0; i < MAXPIXEL; i++) {
			if (strcmp(coloredPixel[i], ""))
				fprintf(fileArt, "%i=%s\n", i, coloredPixel[i]);
		}
		
//		strcpy(artName, colorPixel[j]);
		fclose(fileArt);
	}
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta charset=\"utf-8\">");
			printf("<title>Jogo de pintar</title>");
			printf("<link rel=\"stylesheet\" href=\"../jogo-de-pintar.css\">");
		printf("</head>");
		printf("<body>");
			printf("<a href=\"../jogo-de-pintar.html\">Voltar</a>");
			printf("<h1>%s</h1>", artName);
			perror("Nada");
			printf("<form action=\"jogo-de-pintar.cgi\" method=\"get\">");
				printf("<input type=\"hidden\" name=\"artName\" value=\"%s\">", artName);
				printf("<input type=\"color\" name=\"theColor\" required>");
				printf("<input type=\"submit\" value=\"Pintar\">");
				printf("<div id=\"tela\">");
					for (i = 0; i < 4794; i++) {
						printf("<input type=\"checkbox\" id=\"%d\" name=\"pixel%d\">", i, i);
						printf("<label for=\"%d\"", i);
						if (strcmp(coloredPixel[i], ""))
							printf(" style=\"background-color:#%s\"", coloredPixel[i]);
						printf("></label>");
					}
				printf("</div>");
			printf("</form>");
		printf("</body>");
	printf("</html>");
	
	return 0;
}
