#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "forca.h"

//constantes
#define TAMANHO_PALAVRA 20
#define DIFICULDADE_FACIL 6
#define DIFICULDADE_MEDIO 5
#define DIFICULDADE_DIFICIL 4
#define TAM_MAX_NOME_PLAYER 30

//variáveis globais
char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;
int chutesIncorretos;
int dificuldade;

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}

// Função que escolhe uma palavra aleatória do arquivo de palavras
void escolhePalavra() {
    FILE* f = fopen("../palavras.txt", "r");

    if (!f) {
        printf("Arquivo de palavras não encontrado.\n");
        exit(1); // Encerra o programa se o arquivo não for encontrado
    }

    int qPalavras;
    fscanf(f, "%d", &qPalavras);

    srand(time(0));
    int randomico = rand() % qPalavras;

    for (int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavraSecreta);
    }
    fclose(f);
}

// Função que lida com o palpite do usuário
void chuta() {
    char chute;
    printf("Chute uma letra maiúscula:\n> ");
    scanf(" %c", &chute);

    chute = toupper(chute); //maiúscula

    if (letraExiste(chute)) {
        printf("Correto.\n\n");
    } else {
        printf("Errou.\n\n");
        chutesIncorretos++;
    }
    
    chutes[chutesDados] = chute;
    chutesDados++;
}

// Função que verifica se a letra já foi chutada
int jaChutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesDados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

// Função que desenha a forca e a situação atual do jogo
void desenhaForca() {
    int erros = chutesErrados();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n");
    
    printf("Você já deu %d chutes\n", chutesDados);

// Mostra a palavra com as letras acertadas e os espaços para as letras não acertadas
    for(int i = 0; i < strlen(palavraSecreta); i++) {
        if(jaChutou(palavraSecreta[i])) {
            printf("%c ", palavraSecreta[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Função que verifica se a letra existe na palavra secreta
int letraExiste(char letra) {
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (letra == palavraSecreta[i]) {
            return 1;
        }
    }
    return 0;
}

// Função que conta quantos chutes errados foram dados
int chutesErrados() {
    int erros = 0;
    for (int i = 0; i < chutesDados; i++) {
        if (!letraExiste(chutes[i])) erros++;
    }
    return erros;
}

// Função que permite ao usuário escolher a dificuldade do jogo
//alteração
void escolhaDificuldade() {
    printf("Escolha a dificuldade:\n");
    printf("(1) Fácil   (2) Médio   (3) Difícil\n> ");
    scanf("%d", &dificuldade);
}

// Função que retorna a dificuldade escolhida
int defineDificuldade() {
    switch (dificuldade) {
    case 1:
        return DIFICULDADE_FACIL;
    case 2:
        return DIFICULDADE_MEDIO;
    case 3:
        return DIFICULDADE_DIFICIL;
    default:
        return DIFICULDADE_MEDIO;
    }
}

int enforcou() {
    return chutesErrados() >= defineDificuldade();
}

int ganhou() {
    for (int i = 0; i < strlen(palavraSecreta); i++) {
        if (!jaChutou(palavraSecreta[i])) {
            return 0;
        }
    }
    return 1;
}

// Função que verifica se duas palavras são iguais
// alteração
int verificarPalavrasIguais(char* palavra1, char* palavra2) {
    int saoIguais = 1;
    if (strlen(palavra1) == strlen(palavra2)) {
        for (int i = 0; i < strlen(palavra1); i++) {
            if (palavra1[i] != palavra2[i]) {
                saoIguais = 0;
                break;
            }
        }
    } else {
        saoIguais = 0;
    }
    return saoIguais;
}

// Função que verifica se a palavra já existe no arquivo de palavras
int palavraJaExiste(FILE* f, char* novaPalavra, int qtdPalavras) {
    char palavraDoArquivo[TAMANHO_PALAVRA];

    for (int i = 0; i < qtdPalavras; i++) {
        fscanf(f, "%s", palavraDoArquivo);
        if (verificarPalavrasIguais(novaPalavra, palavraDoArquivo)) {
            return 1;
        }
    }
    return 0;
}

// Função que permite ao usuário adicionar uma nova palavra ao arquivo de palavras
void adicionarPalavra() {
    char simOuNao;

    printf("Desejas adicionar uma nova palavra (S ou N)?\n> ");
    scanf(" %c", &simOuNao);
    simOuNao = toupper(simOuNao);

    if (simOuNao == 'S') {
        char novaPalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra em MAIÚSCULO:\n> ");
        scanf("%s", novaPalavra);
    
        for (int i = 0; i < strlen(novaPalavra); i++) {
            if (novaPalavra[i] < 65 || novaPalavra[i] > 90) {
            scanf("%s", novaPalavra);
                i = -1;
            }
        }

        FILE* f = fopen("../palavras.txt", "r+");
        
        int qtd;
        fscanf(f, "%d", &qtd);

        if (palavraJaExiste(f, novaPalavra, qtd)) {
            printf("A palavra já existe.\n");
            fclose(f);
        } else {
            qtd++;
            fseek(f, 0, SEEK_SET);
            fprintf(f, "%04d", qtd);
            fseek(f, 0, SEEK_END);
            fprintf(f, "\n%s", novaPalavra);
            printf("Palavra adicionada!\n");
            fclose(f);
        }
    }
}

// Função que calcula a pontuação do jogador
//alteração
int calcPontuacaoPlayer() {
    int pontuacao;
    pontuacao = (10 - chutesIncorretos) * dificuldade;

    return pontuacao;
}

// Função que insere o jogador no ranking
void insertPlayerRanking() {
    int pontuacao = calcPontuacaoPlayer();
    char nomePlayer[TAM_MAX_NOME_PLAYER-3];

    printf("Qual o seu nome para inserirmos no ranking?\n> ");
    scanf("%s", nomePlayer);

    FILE* f = fopen("../ranking.txt", "a");

    fprintf(f, "%s", nomePlayer);
    for (int i = 0; TAM_MAX_NOME_PLAYER > i- strlen(nomePlayer); i++) {
        fprintf(f, "%c", '.');
    }
    fprintf(f, "%03d", pontuacao);
    fprintf(f, "%c", '\n');
    fclose(f);
    printf("\nSua pontuação foi de %d pontos", pontuacao);
}

// Função principal
int main() {
    abertura();
    escolhePalavra();
    escolhaDificuldade();

    do {
        desenhaForca();

        chuta();

    } while (!ganhou() && !enforcou());

    if (ganhou()) {
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

        //Permite ao jogador adicionar uma nova palavra ao arquivo de palavras após vencer
        //alteração
        adicionarPalavra(); 
    } else {
        printf("\nInfelizmente, você foi enforcado\n\n");

        printf("A palavra era **%s**\n\n", palavraSecreta);
 
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    // Insere o jogador no ranking
    insertPlayerRanking();
}