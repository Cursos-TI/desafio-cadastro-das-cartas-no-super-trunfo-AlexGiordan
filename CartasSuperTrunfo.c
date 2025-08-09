#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char Estado;
    char CodigoCarta[4];
    char NomeCidade[30];
    int Populacao;
    float Area;
    float PIB;
    int NumeroPontosTuristicos;
} Carta;

void limpar_nova_linha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    int QuantidadeCartas;
    char buffer[100];

    printf("Iniciando Cadastro Super Trunfo\n\n");

    printf("> Informe a quantidade de cartas desejadas:\n");
    fgets(buffer, sizeof(buffer), stdin);
    QuantidadeCartas = atoi(buffer);

    Carta *Baralho = malloc(QuantidadeCartas * sizeof(Carta));
    if (!Baralho) {
        printf(">> Erro ao alocar memoria.\n");
        return 1;
    }
    printf(">> Memoria alocada com sucesso.\n");

    int used[8][4] = {0};
    srand((unsigned)time(NULL));

    printf("> Iniciando cadastro das cartas.\n");

    for (int i = 0; i < QuantidadeCartas; i++) {
        printf("\n>> Cadastro da carta [%d]\n", i + 1);

        while (1) {
            printf(">>> Informe o Estado (A-H): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (strlen(buffer) < 1) continue;
            Baralho[i].Estado = (char)toupper(buffer[0]);
            if (Baralho[i].Estado >= 'A' && Baralho[i].Estado <= 'H') break;
            printf(">> Estado invalido! Use A..H.\n");
        }

        int e = Baralho[i].Estado - 'A';
        int livres = 0;
        for (int k = 0; k < 4; k++) if (!used[e][k]) livres++;
        if (livres == 0) {
            printf(">> Para o estado %c ja existem 4 cartas (01..04). Escolha outro estado.\n", Baralho[i].Estado);
            i--;
            continue;
        }

        int num;
        do { num = (rand() % 4) + 1; } while (used[e][num - 1]);
        used[e][num - 1] = 1;

        snprintf(Baralho[i].CodigoCarta, sizeof(Baralho[i].CodigoCarta), "%c%02d", Baralho[i].Estado, num);

        printf(">>> Informe o nome da cidade:\n");
        fgets(Baralho[i].NomeCidade, sizeof(Baralho[i].NomeCidade), stdin);
        limpar_nova_linha(Baralho[i].NomeCidade);

        printf(">>> Informe a populacao:\n");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].Populacao = atoi(buffer);

        printf(">>> Informe a area total:\n");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].Area = atof(buffer);

        printf(">>> Informe o PIB:\n");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].PIB = atof(buffer);

        printf(">>> Informe o numero de pontos turisticos:\n");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].NumeroPontosTuristicos = atoi(buffer);
    }

    printf("> Finalizado cadastro das cartas.\n");
    printf("> Exibindo cadastro das cartas.\n");

    for (int i = 0; i < QuantidadeCartas; i++) {
        printf("\n----\n");
        printf("Carta: %d \n", i + 1);
        printf("Estado: %c\n", Baralho[i].Estado);
        printf("Codigo: %s\n", Baralho[i].CodigoCarta);
        printf("Nome da cidade: %s\n", Baralho[i].NomeCidade);
        printf("Populacao: %d\n", Baralho[i].Populacao);
        printf("Area: %.2f\n", Baralho[i].Area);
        printf("PIB: %.2f\n", Baralho[i].PIB);
        printf("Numero de pontos turisticos: %d\n", Baralho[i].NumeroPontosTuristicos);
        printf("----\n");
    }

    free(Baralho);
    printf("Finalizando Cadastro Super Trunfo\n\n");
    return 0;
}
