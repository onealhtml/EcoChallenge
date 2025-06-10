#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h> // Adicionado para system("cls")
#include <windows.h> // Adicionado para Sleep()

#define MAX_USUARIOS 100
#define MAX_ACOES_POR_USUARIO 15

typedef struct {
    char nome[100];
    int acoes[MAX_ACOES_POR_USUARIO]; // IDs das a��es realizadas
    int num_acoes; // Contador de a��es do usu�rio
    int pontuacao; // Pontua��o total do usu�rio
} Usuario;

// Vari�veis globais para acessar em todas as fun��es
Usuario usuarios[MAX_USUARIOS];
int contador_usuarios = 0;

void menu();
void registroacao();
int buscarUsuario(char *nome);
int adicionarUsuario(char *nome);
void adicionarAcao(int id_usuario, int id_acao);
int calcularPontos(int id_acao);
void visualizarAcoes();
char* obterNomeAcao(int id_acao);
void ranking();

int main(void){
    setlocale(LC_ALL, "Portuguese");

    menu();

    return 0;
}

void menu() {
    int opcao;

    do {
        system("cls");
        printf("##############################\n");
        printf("EcoChallenge - Monitor de H�bitos Sustent�veis\n");
        printf("\nDigite a op��o desejada:\n");
        printf("1 - Registrar a��o sustent�vel\n");
        printf("2 - Visualizar a��es de algum participante\n");
        printf("3 - Ver ranking de pontua��o\n");
        printf("4 - Sair\n");
        printf("##############################\n");
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Define uma op��o inv�lida para tratar o erro
            printf("ERRO: Entrada inv�lida!\n");
        }
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                registroacao();
                break; // Adicionado break
            case 2:
                visualizarAcoes();
                break;
            case 3:
                ranking();
                break;
            case 4:
                system("cls");
                printf("Feito por onealhtml, tinpack e besoaresn");

                // Contador regressivo de 5 segundos
                for (int i = 5; i > 0; i--) {
                    printf(".");
                    Sleep(1000);
                }
                break;
            default:
                printf("ERRO: Op��o inv�lida! Tente novamente.\n");
                system("pause");
                break;
        }
    } while (opcao != 4);
}

void registroacao() {
    system("cls");

    char nome[100];
    int acao_escolhida;
    int pontos = 0;

    printf("##############################\n");
    printf("EcoChallenge - Registro de A��o\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;


    int id_usuario = buscarUsuario(nome);
    if (id_usuario == -1) {
        id_usuario = adicionarUsuario(nome);
        if (id_usuario == -1) {
            printf("ERRO: Limite de usu�rios atingido (%d)!\n", MAX_USUARIOS);
            printf("Pressione Enter para voltar ao menu principal...");
            getchar();
            return;
        }
    }

    do {
        system("cls");
        printf("##############################\n");
        printf("EcoChallenge - Registro de atividades\n\n");
        printf("Participante: %s\n\n", nome);
        printf("Digite a a��o feita:\n");
        printf("1 - Separar lixo - 10\n");
        printf("2 - Economia de �gua - 15\n");
        printf("3 - Economia de energia - 15\n");
        printf("4 - Compostagem - 15\n");
        printf("5 - Reciclagem de materiais - 20\n");
        printf("6 - Organiza��o de trocas (brecho) - 25\n");
        printf("7 - Meios de transportes n�o poluentes - 30\n");
        printf("8 - Reaproveitamento de �gua da chuva - 30\n");
        printf("9 - Plantar �rvores - 50\n");
        printf("0 - Voltar\n");
        printf("##############################\n");
        printf("Escolha uma op��o: ");
        if (scanf("%d", &acao_escolhida) != 1) {
            acao_escolhida = -1; // Define uma op��o inv�lida para tratar o erro
            printf("ERRO: Entrada inv�lida!\n");
        }
        getchar();

        // Armazenar a a��o escolhida e pontua��o
        if (acao_escolhida >= 1 && acao_escolhida <= 9) {
            if (usuarios[id_usuario].num_acoes >= MAX_ACOES_POR_USUARIO) {
                printf("ERRO: Limite de a��es atingido (%d)!\n", MAX_ACOES_POR_USUARIO);
            } else {
                adicionarAcao(id_usuario, acao_escolhida);
                pontos = calcularPontos(acao_escolhida);
                printf("A��o %d registrada para %s! Pontos: %d\n", acao_escolhida, nome, pontos);
            }
            printf("Pressione Enter para continuar...");
            getchar();
        } else if (acao_escolhida == 0) {
            printf("Retornando ao menu principal...\n");
        } else {
            printf("ERRO: Op��o inv�lida!\n");
            printf("Pressione Enter para tentar novamente...");
            getchar();
        }
    } while (acao_escolhida != 0);
}

int buscarUsuario(char *nome) {
    for (int i = 0; i < contador_usuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int adicionarUsuario(char *nome) {
    if (contador_usuarios < MAX_USUARIOS) {
        strcpy(usuarios[contador_usuarios].nome, nome);
        usuarios[contador_usuarios].num_acoes = 0;
        usuarios[contador_usuarios].pontuacao = 0;
        return contador_usuarios++;
    }
    return -1;
}

void adicionarAcao(int id_usuario, int id_acao) {
    if (id_usuario >= 0 && id_usuario < MAX_USUARIOS) {
        if (usuarios[id_usuario].num_acoes < MAX_ACOES_POR_USUARIO) {
            usuarios[id_usuario].acoes[usuarios[id_usuario].num_acoes++] = id_acao;
            usuarios[id_usuario].pontuacao += calcularPontos(id_acao);
        }
    }
}

int calcularPontos(int id_acao) {
    switch (id_acao) {
        case 1: return 10;
        case 2: case 3: case 4: return 15;
        case 5: return 20;
        case 6: return 25;
        case 7: case 8: return 30;
        case 9: return 50;
        default: return 0;
    }
}

void visualizarAcoes() {
    system("cls");
    char nome[100];

    printf("##############################\n");
    printf("EcoChallenge - Visualiza��o de A��es\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int id_usuario = buscarUsuario(nome);

    if (id_usuario == -1) {
        printf("\nERRO: Participante n�o encontrado!\n");
    } else {
        system("cls");
        printf("##############################\n");
        printf("EcoChallenge - Visualiza��o de A��es\n\n");
        printf("Participante: %s\n", usuarios[id_usuario].nome);
        printf("Pontua��o total: %d pontos\n\n", usuarios[id_usuario].pontuacao);

        if (usuarios[id_usuario].num_acoes == 0) {
            printf("Este participante ainda n�o registrou nenhuma a��o.\n");
        } else {
            printf("A��es registradas:\n");
            printf("------------------------------\n");

            for (int i = 0; i < usuarios[id_usuario].num_acoes; i++) {
                int id_acao = usuarios[id_usuario].acoes[i];
                int pontos = calcularPontos(id_acao);
                printf("%d. %s - %d pontos\n", i+1, obterNomeAcao(id_acao), pontos);
            }
            printf("------------------------------\n");
            printf("##############################\n");
        }
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar();
}

char* obterNomeAcao(int id_acao) {
    switch (id_acao) {
        case 1: return "Separar lixo";
        case 2: return "Economia de �gua";
        case 3: return "Economia de energia";
        case 4: return "Compostagem";
        case 5: return "Reciclagem de materiais";
        case 6: return "Organiza��o de trocas (brech�)";
        case 7: return "Meios de transportes n�o poluentes";
        case 8: return "Reaproveitamento de �gua da chuva";
        case 9: return "Plantar �rvores";
        default: return "A��o desconhecida";
    }
}

void ranking() {
    system("cls");
    printf("##############################\n");
    printf("EcoChallenge - Ranking de Pontua��o\n");
    printf("##############################\n\n");

    if (contador_usuarios == 0) {
        printf("ERRO: Nenhum participante registrado ainda.\n");
    } else {
        // Ordenar usu�rios por pontua��o
        for (int i = 0; i < contador_usuarios - 1; i++) {
            for (int j = i + 1; j < contador_usuarios; j++) {
                if (usuarios[j].pontuacao > usuarios[i].pontuacao) {
                    Usuario temp = usuarios[i];
                    usuarios[i] = usuarios[j];
                    usuarios[j] = temp;
                }
            }
        }

        printf("Ranking:\n");
        printf("------------------------------\n");
        for (int i = 0; i < contador_usuarios; i++) {
            printf("%d. %s - %d pontos\n", i + 1, usuarios[i].nome, usuarios[i].pontuacao);
        }
        printf("------------------------------\n");
        printf("##############################\n");
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar();
}