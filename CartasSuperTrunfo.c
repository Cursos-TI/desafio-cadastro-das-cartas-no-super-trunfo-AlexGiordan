#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    char Estado;
    char CodigoCarta[4];
    char NomeCidade[30];
    unsigned long int Populacao;
    float Area;
    float PIB;
    int NumeroPontosTuristicos;
    float DensidadePopulacional;
    float PIBPerCapita;
    double SuperPoder;
} Carta;

void limpar_nova_linha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    int QuantidadeCartas;
    char buffer[100];

    printf("Iniciando Cadastro Super Trunfo\n\n");

    // printf("> Informe a quantidade de cartas desejadas: ");
    // fgets(buffer, sizeof(buffer), stdin);
    // QuantidadeCartas = atoi(buffer);
    printf("> Vai ser solicitado o cadastro de 2(duas) cartas! \n");
    QuantidadeCartas = 2;

    Carta *Baralho = malloc(QuantidadeCartas * sizeof(Carta));
    if (!Baralho) {
        printf(">> Erro ao alocar memória.\n");
        return 1;
    }
    printf(">> Memória alocada com sucesso.\n");

    int used[8][4] = {0};
    srand((unsigned)time(NULL));

    printf("> Iniciando cadastro das cartas.\n");

    for (int i = 0; i < QuantidadeCartas; i++) {
        printf("\n>> Cadastro da carta [%d]\n", i + 1);

        while (1) {
            printf(">>> Informe o Estado (A-H): ");
            fgets(buffer, sizeof(buffer), stdin);
            if (strlen(buffer) < 1) continue;
            Baralho[i].Estado = (char)toupper((unsigned char)buffer[0]);
            if (Baralho[i].Estado >= 'A' && Baralho[i].Estado <= 'H') break;
            printf(">> Estado inválido! Use A..H.");
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

        printf(">>> Informe o nome da cidade: ");
        fgets(Baralho[i].NomeCidade, sizeof(Baralho[i].NomeCidade), stdin);
        limpar_nova_linha(Baralho[i].NomeCidade);

        printf(">>> Informe a população em quantidade nominal: ");
        fgets(buffer, sizeof(buffer), stdin);
        {
            char *end = NULL;
            unsigned long v = strtoul(buffer, &end, 10);
            if (end == buffer) v = 0ul;
            Baralho[i].Populacao = v;
        }

        printf(">>> Informe a área total em km²: ");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].Area = (float)atof(buffer);

        printf(">>> Informe o PIB em bilhôes de reais: ");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].PIB = (float)atof(buffer);

        printf(">>> Informe o número de pontos turisticos: ");
        fgets(buffer, sizeof(buffer), stdin);
        Baralho[i].NumeroPontosTuristicos = atoi(buffer);

        printf(">>> Calculando densidade populacional!\n");
        if (Baralho[i].Area != 0.0f) {
            Baralho[i].DensidadePopulacional =
                (float)((double)Baralho[i].Populacao / (double)Baralho[i].Area);
        } else {
            Baralho[i].DensidadePopulacional = 0.0f;
            printf(">>> Atenção: área zero. Densidade definida como 0.0.\n");
        }

        printf(">>> Calculando PIB per capita!\n");
        if (Baralho[i].Populacao != 0ul) {
            Baralho[i].PIBPerCapita =
                (float)((Baralho[i].PIB * 1e9) / (double)Baralho[i].Populacao);
        } else {
            Baralho[i].PIBPerCapita = 0.0f;
            printf(">>> Atenção: população zero. PIB per capita definido como 0.0.\n");
        }

        double termo_inverso_densidade = 0.0;
        if (Baralho[i].DensidadePopulacional != 0.0f) {
            termo_inverso_densidade = 1.0 / (double)Baralho[i].DensidadePopulacional;
        }

        Baralho[i].SuperPoder =
            (double)Baralho[i].Populacao +
            (double)Baralho[i].Area +
            (double)Baralho[i].PIB +
            (double)Baralho[i].NumeroPontosTuristicos +
            (double)Baralho[i].PIBPerCapita +
            termo_inverso_densidade;

        printf("\n\n");
    }

    printf("> Finalizado cadastro das cartas.\n");
    printf("> Exibindo cadastro das cartas.\n\n");

    for (int i = 0; i < QuantidadeCartas; i++) {
        printf(">> ---------------------------------------------------------------------------------\n");
        printf(">> CARTA                       : %d \n", i + 1);
        printf(">> ESTADO                      : %c\n", Baralho[i].Estado);
        printf(">> CÓDIGO DA CARTA             : %s\n", Baralho[i].CodigoCarta);
        printf(">> NOME DA CIDADE              : %s\n", Baralho[i].NomeCidade);
        printf(">> POPULAÇÃO                   : %lu\n", Baralho[i].Populacao);          
        printf(">> ÁREA                        : %.2f km²\n", Baralho[i].Area);
        printf(">> PIB                         : %.2f bilhões de reais\n", Baralho[i].PIB);
        printf(">> NÚMERO DE PONTOS TURISTICOS : %d\n", Baralho[i].NumeroPontosTuristicos);
        printf(">> DENSIDADE POPULACIONAL      : %.2f hab/km²\n", Baralho[i].DensidadePopulacional);
        printf(">> PIB PER CAPITA              : %.2f reais\n", Baralho[i].PIBPerCapita);
        printf(">> SUPER PODER                 : %.6f \n", Baralho[i].SuperPoder);
        printf(">> ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
    }

    printf("\n\n");
    printf("Finalizando Cadastro Super Trunfo\n\n");
    printf("Comparação de cartas:\n");

    if(Baralho[0].Populacao >= Baralho[1].Populacao){
        printf("População: Carta 1 venceu (1)\n");
    } else {
        printf("População: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].Area >= Baralho[1].Area){
        printf("Área: Carta 1 venceu (1)\n");
    } else {
        printf("Área: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].PIB >= Baralho[1].PIB){
        printf("PIB: Carta 1 venceu (1)\n");
    } else {
        printf("PIB: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].NumeroPontosTuristicos >= Baralho[1].NumeroPontosTuristicos){
        printf("Pontos Turísticos: Carta 1 venceu (1)\n");
    } else {
        printf("Pontos Turísticos: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].DensidadePopulacional <= Baralho[1].DensidadePopulacional){
        printf("Densidade Populacional: Carta 1 venceu (1)\n");
    } else {
        printf("Densidade Populacional: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].PIBPerCapita >= Baralho[1].PIBPerCapita){
        printf("PIB per Capita: Carta 1 venceu (1)\n");
    } else {
        printf("PIB per Capita: Carta 2 venceu (0)\n");
    }

    if(Baralho[0].SuperPoder >= Baralho[1].SuperPoder){
        printf("Super Poder: Carta 1 venceu (1)\n");
    } else {
        printf("Super Poder: Carta 2 venceu (0)\n");
    }

    printf("Finalizado com sucesso!\n");

    free(Baralho);
    return 0;
}
