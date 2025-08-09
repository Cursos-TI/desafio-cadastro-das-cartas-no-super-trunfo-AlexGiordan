#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.
// Siga os comentários para implementar cada parte do desafio.
//Teste larissa

    typedef struct {
        char Estado;
        char CodigoCarta[4];
        char NomeCidade[30];
        int Populacao;
        float Area;
        float PIB;
        int NumeroPontosTuristicos;
    } Carta;

int main() {
    int QuandidadeCartas;

    printf("Iniciando Cadastro Super Trunfo\n\n");
    printf("> Informe a quantidade de cartas desejadas:\n");
    scanf("%d", &QuandidadeCartas);
    getchar();

    Carta * Baralho = malloc(QuandidadeCartas * sizeof(Carta));
    if (!Baralho) {
        printf(">> Erro ao alocar memoria.\n");
        return 1;
    }
    printf(">> Memoria alocada com sucesso.\n");  
    
    int used[8][4] = {0};
    srand((unsigned)time(NULL));    

    printf("> Iniciando cadastro das cartas.\n");

    for (int i = 0; i < QuandidadeCartas; i++)
    {
        printf("\n>> Cadastro da carta [%d]\n", i + 1);

        while (1) {
            printf(">>> Informe o Estado (A-H): ");
            if (scanf(" %c", &Baralho[i].Estado) != 1) {
                printf("Entrada invalida.\n");
                int c; while ((c = getchar()) != '\n' && c != EOF) {}
                continue;
            }
            Baralho[i].Estado = (char)toupper((unsigned char)Baralho[i].Estado);
            if (Baralho[i].Estado >= 'A' && Baralho[i].Estado <= 'H') break;
            printf(">> Estado invalido! Use A..H.\n");
        }

        getchar(); 

        int e = Baralho[i].Estado - 'A';

        int livres = 0;
        for (int k = 0; k < 4; k++) if (!used[e][k]) livres++;
        if (livres == 0) {
            printf(">> Para o estado %c ja existem 4 cartas (01..04). Repita com outro estado.\n", Baralho[i].Estado);
            i--;
            continue;
        }

        int num;
        do { num = (rand() % 4) + 1; } while (used[e][num - 1]);
        used[e][num - 1] = 1;

        snprintf(Baralho[i].CodigoCarta, sizeof(Baralho[i].CodigoCarta),"%c%02d", Baralho[i].Estado, num);

        printf(">>> Informe o nome da cidade:\n"); 
        fgets(Baralho[i].NomeCidade, sizeof(Baralho[i].NomeCidade), stdin); 
        Baralho[i].NomeCidade[strcspn(Baralho[i].NomeCidade, "\n")] = '\0';
        getchar(); 
        
        printf(">>> Informe a populacao:\n");
        scanf("%d", &Baralho[i].Populacao);
        getchar();      
        
        printf(">>> Informe a area total:\n");
        scanf("%f", &Baralho[i].Area);
        getchar();   
        
        printf(">>> Informe o PIB:\n");
        scanf("%f", &Baralho[i].PIB);
        getchar();  
        
        printf(">>> Informe o numero de pontos turisticos:\n");
        scanf("%d", &Baralho[i].NumeroPontosTuristicos);
        getchar();         
    }

    printf("> Finalizado cadastro das cartas.\n");

    printf("> Exibindo cadastro das cartas.\n");    

    for (int i = 0; i < QuandidadeCartas; i++)
    {
        printf("\n----\n");            
        printf("Carta: %d \n", i);
        printf("Estado: %c\n", Baralho[i].Estado);
        printf("Codigo: %s\n", Baralho[i].CodigoCarta);
        printf("Nome da cidade: %s\n", Baralho[i].NomeCidade);
        printf("Populacao: %d\n", Baralho[i].Populacao);
        printf("Area: %f\n", Baralho[i].Area);
        printf("PIB: %f\n", Baralho[i].PIB);
        printf("Numero de pontos turisticos: %d\n", Baralho[i].NumeroPontosTuristicos);

        printf("\n----\n");
    }

    printf("\n\n\n");
    
    



    printf("Finalizando Cadastro Super Trunfo\n\n");

    free(Baralho);
    return 0;
}
