#include <stdio.h>
#include <stdlib.h>

int main() {
		
	// 0 = não jogado
	// 1 = jogado o "O"
	// 2 = jogado o "X"
	
	char* dados = NULL;
	int i;
	int bloco = 0, proxJogada = 0;
	int jogador = 0;
	int placar[2] = {0,0};
	int blocos[9] = {0,0,0,0,0,0,0,0,0};
	int vencedor = -1;
	int completo = 0;
	char msg[50] = {'\n'};
	
	FILE *lf;
	
	lf = fopen("jogo-da-velha.bin", "r+b");
	
	if (lf == NULL) {
		snprintf(msg, sizeof msg, "O arquivo não pôde ser criado/lido.");
	} else {
		
		// Lendo o placar
		fseek(lf, 0, SEEK_SET);
		for (i = 0; i < 2; i++) fread(&placar[i], 1, sizeof(int), lf);
		
		// Lendo o jogador
		fseek(lf, 2*sizeof(int), SEEK_SET);
		fread(&jogador, 1, sizeof(int), lf);
		
		// Lendo as jogadas
		fseek(lf, 3*sizeof(int), SEEK_SET);
		for (i = 0; i < 9; i++) {
			fread(&blocos[i], 1, sizeof(int), lf);
			
		}
		
		dados = getenv("QUERY_STRING");
	
		if (dados == NULL) {
			snprintf(msg, sizeof msg, "Erro durante a extração de dados do formulário.");
		} else if (sscanf(dados, "bloco=%d&proxJogada=%d", &bloco, &proxJogada) != 2) {
			snprintf(msg, sizeof msg, "Placar zerado.");
			// Zerar o placar
			placar[0] = 0;
			placar[1] = 0;
			fseek(lf, 0, SEEK_SET);
			for (i = 0; i < 2; i++) fwrite(&completo, 1, sizeof(int), lf);
			fflush(lf);
		} else {
			// Alterando o jogador
			if (jogador == 0 || jogador == 2){jogador = 1;}
			else {jogador = 2;}
			fseek(lf, 2*sizeof(int), SEEK_SET);
			fwrite(&jogador, 1, sizeof(int), lf);
			fflush(lf);
			
			// Salvando a nova jogada
			if (bloco < 1) bloco = 1;
			if (bloco > 9) bloco = 9;
			fseek(lf, (2+bloco)*sizeof(int), SEEK_SET);
			fwrite(&proxJogada, 1, sizeof(int), lf);
			fflush(lf);
			
			// Atualizando o vetor para a nova jogada
			fseek(lf, (2+bloco)*sizeof(int), SEEK_SET);
			fread(&blocos[bloco - 1], 1, sizeof(int), lf);
		}
	}
	
	// Verificar ganhador
	if (blocos[0] != 0) {
		if ((blocos[0] == blocos[1] && blocos[1] == blocos[2]) || (blocos[0] == blocos[3] && blocos[3] == blocos[6]))
			vencedor = blocos[0];
	}
	if (blocos[8] != 0) {
		if ((blocos[8] == blocos[7] && blocos[7] == blocos[6]) || (blocos[8] == blocos[5] && blocos[5] == blocos[2]))
			vencedor = blocos[8];
	}
	if (blocos[4] != 0) {
		if ((blocos[4] == blocos[0] && blocos[0] == blocos[8]) || (blocos[4] == blocos[1] && blocos[1] == blocos[7]) || (blocos[4] == blocos[2] && blocos[2] == blocos[6]) || (blocos[4] == blocos[5] && blocos[5] == blocos[3]))
			vencedor = blocos[4];
	}
	
	// Verificar se o jogo está completo
	for (i = 0; i < 9; i++) if (blocos[i] != 0) completo++;
	
	
	if (completo == 9 || vencedor != -1) {
		snprintf(msg, sizeof msg, "Deu velha.");
		if (vencedor != -1) {
			if (vencedor == 1) {
				snprintf(msg, sizeof msg, "<span style=\"color:red\">O</span> venceu!");
				placar[0]++;
			}
			if (vencedor == 2) {
				snprintf(msg, sizeof msg, "<span style=\"color:blue\">X</span> venceu!");
				placar[1]++;
			}
			// Salvando o placar
			fseek(lf, 0, SEEK_SET);
			for (i = 0; i < 2; i++) fwrite(&placar[i], 1, sizeof(int), lf);
			fflush(lf);
		}
		
		// Zerando as jogadas
		for (i = 0; i < 9; i++) blocos[i] = 0;
		fseek(lf, 3*sizeof(int), SEEK_SET);
		for (i = 0; i < 9; i++) fwrite(&blocos[i], 1, sizeof(int), lf);
		fflush(lf);
	}
	
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta charset=\"utf-8\">");
			printf("<meta name=\"author\" content=\"Alisson Nunes\">");
			printf("<meta name=\"reply-to\" content=\"alynva@gmail.com\">");
			printf("<meta name=\"generator\" content=\"Dev-C++ 5.11\">");
			printf("<meta http-equiv=\"content-language\" content=\"pt-br\">");
			printf("<meta name=\"description\" content=\"Um jogo simples, com a mecânica programada em Lingaugem C.\">");
			printf("<meta name=\"viewport\" content=\"initial-scale = 1.0, maximum-scale = 1.0, user-scalable = no, width = device-width\">");
			printf("<title>Jogo da velha</title>");
			printf("<link rel=\"stylesheet\" href=\"../jogo-da-velha.css\">");
		printf("</head>");
		printf("<body class=\"prox%d\">", jogador);
			printf("<a href=\"?\"><div id=\"placar\">");
				printf("<div id=\"o\">");
					printf("<span>O</span>");
					printf("<br>");
					printf("<span>%d</span>", placar[0]);
				printf("</div>");
				printf("<div id=\"x\">");
					printf("<span>X</span>");
					printf("<br>");
					printf("<span>%d</span>", placar[1]);
				printf("</div>");
			printf("</div></a>");
			printf("<div id=\"jogo\">");
				printf("<a href=\"?bloco=1&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[0]);
				printf("<a href=\"?bloco=2&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[1]);
				printf("<a href=\"?bloco=3&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[2]);
				printf("<a href=\"?bloco=4&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[3]);
				printf("<a href=\"?bloco=5&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[4]);
				printf("<a href=\"?bloco=6&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[5]);
				printf("<a href=\"?bloco=7&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[6]);
				printf("<a href=\"?bloco=8&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[7]);
				printf("<a href=\"?bloco=9&proxJogada=%d\"><div class=\"cell%d\"></div></a>", jogador, blocos[8]);
			printf("</div>");
			
			printf("<div id=\"log\">%s</div>", msg);
		printf("</body>");
	printf("</html>");
	fclose(lf);
	return 0;
}
