#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TENTATIVAS 6
#define MAX_PALAVRA 20
#define NUM_PALAVRAS 5

// Estrutura que representa o estado do jogo
struct JogoForca {
    char palavra[MAX_PALAVRA];
    char palavraEscondida[MAX_PALAVRA];
    int tentativas;
    int acertos;
    int erros;
};

// Lista de palavras possíveis para o jogo
char listaPalavras[NUM_PALAVRAS][MAX_PALAVRA] = {
    "programacao",
    "computador",
    "linguagem",
    "estrutura",
    "desenvolvimento"
    //Aqui você pode escolher qual palavras vai querer ser sorteada no jogo da forca

};

// Função para inicializar um novo jogo
void inicializarJogo(struct JogoForca *jogo) {
    // Inicializar a semente do gerador de números aleatórios com o tempo atual
    srand(time(NULL));

    // Escolher uma palavra aleatória da lista
    int indicePalavra = rand() % NUM_PALAVRAS;
    strcpy(jogo->palavra, listaPalavras[indicePalavra]);

    // Inicializar a palavra escondida com underscores
    for (int i = 0; i < strlen(jogo->palavra); i++) {
        jogo->palavraEscondida[i] = '_';
    }
    jogo->palavraEscondida[strlen(jogo->palavra)] = '\0';

    // Inicializar o número de tentativas, acertos e erros
    jogo->tentativas = MAX_TENTATIVAS;
    jogo->acertos = 0;
    jogo->erros = 0;
}

// Função para mostrar o estado atual do jogo
void mostrarJogo(struct JogoForca *jogo) {
    printf("\nPalavra: %s\n", jogo->palavraEscondida);
    printf("Tentativas restantes: %d\n", jogo->tentativas);
    printf("Erros: %d\n", jogo->erros);

    // Mostrar parte do corpo enforcado de acordo com o número de erros
    switch (jogo->erros) {
        case 1:
            printf("  O\n");
            break;
        case 2:
            printf("  O\n");
            printf("  |\n");
            break;
        case 3:
            printf("  O\n");
            printf(" /|\n");
            break;
        case 4:
            printf("  O\n");
            printf(" /|\\\n");
            break;
        case 5:
            printf("  O\n");
            printf(" /|\\\n");
            printf(" /\n");
            break;
        case 6:
            printf("  O\n");
            printf(" /|\\\n");
            printf(" / \\\n");
            break;
    }
}

// Função para fazer uma jogada
int fazerJogada(struct JogoForca *jogo, char letra) {
    int encontrou = 0;
    // Verificar se a letra está na palavra
    for (int i = 0; i < strlen(jogo->palavra); i++) {
        if (jogo->palavra[i] == letra && jogo->palavraEscondida[i] == '_') {
            // Atualizar a palavra escondida e os acertos
            jogo->palavraEscondida[i] = letra;
            jogo->acertos++;
            encontrou = 1;
        }
    }

    // Se a letra não foi encontrada, decrementar as tentativas e incrementar os erros
    if (!encontrou) {
        jogo->tentativas--;
        jogo->erros++;
    }

    //Essa função retorna 1 se a letra fornecida pelo jogador foi encontrada na palavra e 0 se a letra não foi encontrada.
  
    return encontrou;

    //Se encontrou for 1 (verdadeiro), significa que a letra foi encontrada na palavra e a função retorna 1.
  
    //Se encontrou for 0 (falso), significa que a letra não foi encontrada na palavra e a função retorna 0.

  
}

int main() {
    char jogarNovamente;

    // Loop externo para permitir jogar novamente
    do {
        // Inicializar um novo jogo
        struct JogoForca jogo;
        inicializarJogo(&jogo);

        // Loop interno para continuar o jogo até que o jogador vença ou perca
        while (jogo.tentativas > 0 && jogo.acertos < strlen(jogo.palavra)) {
            // Mostrar o estado atual do jogo
            mostrarJogo(&jogo);

            // Pedir uma letra ao jogador
            char letra;
            printf("\nDigite uma letra: ");
            scanf(" %c", &letra);

            // Fazer a jogada e informar se a letra está correta ou não
            if (fazerJogada(&jogo, letra)) {
                printf("Letra correta!\n");
            } else {
                printf("Letra incorreta. Tente novamente.\n");
            }

            // Verificar se o jogador ganhou
            if (jogo.acertos == strlen(jogo.palavra)) {
                printf("Parabéns! Você acertou a palavra: %s\n", jogo.palavra);
            }

            // Verificar se o jogador perdeu
            if (jogo.tentativas == 0) {
                printf("Você perdeu. A palavra correta era: %s\n", jogo.palavra);
            }
        }

        // Perguntar se o jogador deseja jogar novamente
        printf("Deseja jogar novamente? (S/N): ");
        scanf(" %c", &jogarNovamente);
    } while (jogarNovamente == 'S' || jogarNovamente == 's');

    return 0;
}
