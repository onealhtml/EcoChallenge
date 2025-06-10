#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h> // Adicionado para system("cls")
#include <windows.h> // Adicionado para Sleep()

#define MAX_USUARIOS 100
#define MAX_ACOES_POR_USUARIO 15

typedef struct {
    char nome[100];
    int acoes[MAX_ACOES_POR_USUARIO]; // IDs das ações realizadas
    int num_acoes; // Contador de ações do usuário
    int pontuacao; // Pontuação total do usuário
} Usuario;

// Variáveis globais para acessar em todas as funções
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
        printf("EcoChallenge - Monitor de Hábitos Sustentáveis\n");
        printf("\nDigite a opção desejada:\n");
        printf("1 - Registrar ação sustentável\n");
        printf("2 - Visualizar ações de algum participante\n");
        printf("3 - Ver ranking de pontuação\n");
        printf("4 - Sair\n");
        printf("##############################\n");
        if (scanf("%d", &opcao) != 1) {
            opcao = 0; // Define uma opção inválida para tratar o erro
            printf("ERRO: Entrada inválida!\n");
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
                printf("ERRO: Opção inválida! Tente novamente.\n");
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
    printf("EcoChallenge - Registro de Ação\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;


    int id_usuario = buscarUsuario(nome);
    if (id_usuario == -1) {
        id_usuario = adicionarUsuario(nome);
        if (id_usuario == -1) {
            printf("ERRO: Limite de usuários atingido (%d)!\n", MAX_USUARIOS);
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
        printf("Digite a ação feita:\n");
        printf("1 - Separar lixo - 10\n");
        printf("2 - Economia de água - 15\n");
        printf("3 - Economia de energia - 15\n");
        printf("4 - Compostagem - 15\n");
        printf("5 - Reciclagem de materiais - 20\n");
        printf("6 - Organização de trocas (brecho) - 25\n");
        printf("7 - Meios de transportes não poluentes - 30\n");
        printf("8 - Reaproveitamento de água da chuva - 30\n");
        printf("9 - Plantar árvores - 50\n");
        printf("0 - Voltar\n");
        printf("##############################\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &acao_escolhida) != 1) {
            acao_escolhida = -1; // Define uma opção inválida para tratar o erro
            printf("ERRO: Entrada inválida!\n");
        }
        getchar();

        // Armazenar a ação escolhida e pontuação
        if (acao_escolhida >= 1 && acao_escolhida <= 9) {
            if (usuarios[id_usuario].num_acoes >= MAX_ACOES_POR_USUARIO) {
                printf("ERRO: Limite de ações atingido (%d)!\n", MAX_ACOES_POR_USUARIO);
            } else {
                adicionarAcao(id_usuario, acao_escolhida);
                pontos = calcularPontos(acao_escolhida);
                printf("Ação %d registrada para %s! Pontos: %d\n", acao_escolhida, nome, pontos);
            }
            printf("Pressione Enter para continuar...");
            getchar();
        } else if (acao_escolhida == 0) {
            printf("Retornando ao menu principal...\n");
        } else {
            printf("ERRO: Opção inválida!\n");
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
    printf("EcoChallenge - Visualização de Ações\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    int id_usuario = buscarUsuario(nome);

    if (id_usuario == -1) {
        printf("\nERRO: Participante não encontrado!\n");
    } else {
        system("cls");
        printf("##############################\n");
        printf("EcoChallenge - Visualização de Ações\n\n");
        printf("Participante: %s\n", usuarios[id_usuario].nome);
        printf("Pontuação total: %d pontos\n\n", usuarios[id_usuario].pontuacao);

        if (usuarios[id_usuario].num_acoes == 0) {
            printf("Este participante ainda não registrou nenhuma ação.\n");
        } else {
            printf("Ações registradas:\n");
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
        case 2: return "Economia de água";
        case 3: return "Economia de energia";
        case 4: return "Compostagem";
        case 5: return "Reciclagem de materiais";
        case 6: return "Organização de trocas (brechó)";
        case 7: return "Meios de transportes não poluentes";
        case 8: return "Reaproveitamento de água da chuva";
        case 9: return "Plantar árvores";
        default: return "Ação desconhecida";
    }
}

void ranking() {
    system("cls");
    printf("##############################\n");
    printf("EcoChallenge - Ranking de Pontuação\n");
    printf("##############################\n\n");

    if (contador_usuarios == 0) {
        printf("ERRO: Nenhum participante registrado ainda.\n");
    } else {
        // Ordenar usuários por pontuação
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