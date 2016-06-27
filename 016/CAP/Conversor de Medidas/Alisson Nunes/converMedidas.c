#include <stdio.h>
#include <stdlib.h>

int main() {
	char* dados = NULL;
	int input1 = 0, convert = 0, i;
	double result1 = 0.0;
	char erro[50] = {'\n'};
	char select[7][70] = {'\n'};
	
	for (i = 0; i < 7; i++) snprintf(select[i], sizeof select[i], "");
	
	dados = getenv("QUERY_STRING");
	
	if (dados == NULL) {
		snprintf(select[0], sizeof select[0], "<option disabled selected value>Selecione uma convers&#227;o</option>");
		snprintf(erro, sizeof erro, "Erro durante a extração de dados do formulário.");
	} else if (sscanf(dados, "convert=%d&input1=%d", &convert, &input1) != 2) {
		snprintf(select[0], sizeof select[0], "<option disabled selected value>Selecione uma convers&#227;o</option>");
		snprintf(erro, sizeof erro, "Entrada inv&#225;lida!");
	} else {
		if (convert == 11) { // Metros > Milhas
			result1 = input1 * 0.000621371;
			snprintf(select[1], sizeof select[0], "selected");
		} else if (convert == 12) { // Milhas > Metros
			result1 = input1 / 0.000621371;
			snprintf(select[2], sizeof select[1], "selected");
		} else if (convert == 21) { // Litros > Galões
			result1 = input1 * 0.264172;
			snprintf(select[3], sizeof select[2], "selected");
		} else if (convert == 22) { // Galões > Litros
			result1 = input1 / 0.264172;
			snprintf(select[4], sizeof select[3], "selected");
		} else if (convert == 31) { // Quilogramas > Libras
			result1 = input1 * 2.20462;
			snprintf(select[5], sizeof select[4], "selected");
		} else if (convert == 32) { // Libras > Quilogramas
			result1 = input1 / 2.20462;
			snprintf(select[6], sizeof select[5], "selected");
		}
	}
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta charset=\"utf-8\">");
			printf("<title>Mini avalia&#231;&#227;o - Conver&#231;&#245;es de medidas</title>");
			printf("<link rel=\"stylesheet\" href=\"../converMedidas.css\">");
		printf("</head>");
		printf("<body>");
			printf("<div>");
				printf("<form action=\"converMedidas.cgi\" method=\"get\">");
					printf("<select name=\"convert\">");
						printf("%s", select[0]);
						printf("<optgroup label=\"Converter dist&#226;ncia\">");
							printf("<option value=\"11\" %s>Metros &#8594; Milhas</option>", select[1]);
							printf("<option value=\"12\" %s>Milhas &#8594; Metros</option>", select[2]);
						printf("</optgroup>");
						printf("<optgroup label=\"Converter volume\">");
							printf("<option value=\"21\" %s>Litros &#8594; Gal&#245;es</option>", select[3]);
							printf("<option value=\"22\" %s>Gal&#245;es &#8594; Litros</option>", select[4]);
						printf("</optgroup>");
						printf("<optgroup label=\"Converter massa\">");
							printf("<option value=\"31\" %s>Quilogramas &#8594; Libras</option>", select[5]);
							printf("<option value=\"32\" %s>Libras &#8594; Quilogramas</option>", select[6]);
						printf("</optgroup>");
					printf("</select>");
					printf("<br>");
					printf("<br>");
					printf("<div><input type=\"number\" name=\"input1\" value=\"%d\"> &#8594; <input type=\"text\" value=\"%.1lf\" disabled></div>", input1, result1);
					printf("<br>");
					printf("<input type=\"submit\" value=\"Calcular\">");
				printf("</form>");
				printf("<span>%s</span>", erro);
			printf("</div>");
		printf("</body>");
	printf("</html>");
	return 0;
}
