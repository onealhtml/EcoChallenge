/* EcoChallenge - Monitor de H�bitos Sustent�veis
 * Lorenzo Farias, Bernardo Soares Nunes e Pedro Cabral Buchaim
 * Projeto Incremental
 * Programa��o para Resolu��o de Problemas
 * Profa. Dra. Daniela Bagatini
 * Universidade de Santa Cruz do Sul (UNISC).
 */

#include <stdio.h> // Adicionado para manipula��o de entrada/sa�da
#include <string.h> // Adicionado para manipula��o de strings
#include <locale.h> // Adicionado para acentua��o
#include <stdlib.h> // Adicionado para system("cls")
#include <windows.h> // Adicionado para Sleep()

#define MAX_USUARIOS 100 // N�mero m�ximo de usu�rios
#define MAX_ACOES_POR_USUARIO 15 // N�mero m�ximo de a��es por usu�rio

typedef struct { // Estrutura para armazenar informa��es do usu�rio
    char nome[100]; // Nome do usu�rio
    int acoes[MAX_ACOES_POR_USUARIO]; // IDs das a��es realizadas
    int num_acoes; // Contador de a��es do usu�rio
    int pontuacao; // Pontua��o total do usu�rio
    int meta_diaria; // Meta di�ria de pontos do usu�rio
} Usuario;

void menu(int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o menu
void registroAcao(int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o registroAcao
int buscarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o buscarUsuario
int adicionarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o adicionarUsuario
void adicionarAcao(int id_usuario, int id_acao, Usuario *usuarios); // Declara��o da fun��o adicionarAcao
int calcularPontos(int id_acao); // Declara��o da fun��o calcularPontos
void visualizarAcoes(int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o visualizarAcoes
char* obterNomeAcao(int id_acao); // Declara��o da fun��o obterNomeAcao
void Ranking(int *contador_usuarios, Usuario *usuarios); // Declara��o da fun��o Ranking

int main(void) { // Fun��o principal do programa
    setlocale(LC_ALL, "Portuguese"); // Configura o locale para portugu�s para suporte a acentua��o

    Usuario usuarios[MAX_USUARIOS]; // Array para armazenar os usu�rios
    int contador_usuarios = 0; // Contador de usu�rios registrados

    menu(&contador_usuarios, usuarios); // Chama a fun��o menu para iniciar o programa

    return 0; // Retorna 0 para indicar que o programa terminou corretamente
}

void menu(int *contador_usuarios, Usuario *usuarios) { // Fun��o para exibir o menu principal

    int opcao; // Vari�vel para armazenar a op��o escolhida pelo usu�rio

    do { // Loop para exibir o menu at� que o usu�rio escolha sair
        system("cls"); // Limpa a tela do console
        printf("##############################\n");
        printf("EcoChallenge - Monitor de H�bitos Sustent�veis\n");
        printf("\nDigite a op��o desejada:\n");
        printf("1 - Registrar a��o sustent�vel\n");
        printf("2 - Visualizar a��es de algum participante\n");
        printf("3 - Ver ranking de pontua��o\n");
        printf("4 - Sair\n");
        printf("##############################\n");
        if (scanf("%d", &opcao) != 1) { // Verifica se a entrada � v�lida (scanf retorna 1 se a leitura foi bem-sucedida)
            opcao = 0; // Define uma op��o inv�lida para tratar o erro
        }
        getchar(); // Limpa o buffer do teclado

        switch (opcao) { // Verifica a op��o escolhida pelo usu�rio
            case 1: // Op��o para registrar uma a��o sustent�vel
                registroAcao(contador_usuarios, usuarios); // Chama a fun��o para registrar uma a��o sustent�vel
                break; // Sai do switch
            case 2: // Op��o para visualizar a��es de um participante
                visualizarAcoes(contador_usuarios, usuarios); // Chama a fun��o para visualizar a��es de um participante
                break; // Sai do switch
            case 3: // Op��o para ver o ranking de pontua��o
                Ranking(contador_usuarios, usuarios); // Chama a fun��o para exibir o ranking de pontua��o
                break; // Sai do switch
            case 4: // Op��o para sair do programa
                system("cls"); // Limpa a tela antes de sair
                printf("Feito por onealhtml, tinpack e besoaresn"); // Mensagem de agradecimento

                // Contador regressivo de 5 segundos
                for (int i = 5; i > 0; i--) {
                    printf("."); // Exibe um ponto a cada segundo
                    Sleep(1000); // Pausa por 1 segundo
                }
                break; // Sai do switch
            default: // Caso de uma op��o inv�lida
                printf("ERRO: Entrada inv�lida! Tente novamente.\n"); // Mensagem de erro
                system("pause"); // Pausa para o usu�rio ler a mensagem
                break; // Sai do switch
        }
    } while (opcao != 4); // Continua exibindo o menu at� que o usu�rio escolha sair
}

void registroAcao(int *contador_usuarios, Usuario *usuarios) { // Fun��o para registrar uma a��o sustent�vel
    system("cls"); // Limpa a tela do console

    char nome[100]; // Vari�vel tempor�ria para armazenar o nome do usu�rio
    int acao_escolhida; // Vari�vel para armazenar a a��o escolhida pelo usu�rio
    int pontos = 0; // Vari�vel para armazenar a pontua��o da a��o escolhida

    printf("##############################\n");
    printf("EcoChallenge - Registro de A��o\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin); // L� o nome do usu�rio
    nome[strcspn(nome, "\n")] = 0; // Remove o caractere de nova linha do final da string


    int id_usuario = buscarUsuario(nome, contador_usuarios, usuarios); // Busca o usu�rio pelo nome
    if (id_usuario == -1) { // Se o usu�rio n�o foi encontrado
        id_usuario = adicionarUsuario(nome, contador_usuarios, usuarios); // Adiciona o usu�rio
        if (id_usuario == -1) { // Se n�o foi poss�vel adicionar o usu�rio
            printf("ERRO: Limite de usu�rios atingido (%d)!\n", MAX_USUARIOS); // Mensagem de erro
            printf("Pressione Enter para voltar ao menu principal...");
            getchar(); // Pausa para o usu�rio ler a mensagem
            return; // Retorna para o menu principal
        }
    }

    do { // Loop para registrar a��es at� que o usu�rio escolha voltar
        system("cls"); // Limpa a tela do console
        printf("##############################\n");
        printf("EcoChallenge - Registro de atividades\n\n");
        printf("Participante: %s\n\n", nome);
        printf("Digite a a��o feita:\n");
        printf("1 - Separar lixo - 10\n");
        printf("2 - Economia de �gua - 15\n");
        printf("3 - Economia de energia - 15\n");
        printf("4 - Compostagem - 15\n");
        printf("5 - Reciclagem de materiais - 20\n");
        printf("6 - Organiza��o de trocas (brech�) - 25\n");
        printf("7 - Meios de transportes n�o poluentes - 30\n");
        printf("8 - Reaproveitamento de �gua da chuva - 30\n");
        printf("9 - Plantar �rvores - 50\n");
        printf("0 - Voltar\n");
        printf("##############################\n");
        printf("Escolha uma op��o: ");
        if (scanf("%d", &acao_escolhida) != 1) { // Verifica se a entrada � v�lida (scanf retorna 1 se a leitura foi bem-sucedida)
            acao_escolhida = -1; // Define uma op��o inv�lida para tratar o erro
            printf("ERRO: Entrada inv�lida!\n");
        }
        getchar(); // Limpa o buffer do teclado

        // Armazenar a a��o escolhida e pontua��o
        if (acao_escolhida >= 1 && acao_escolhida <= 9) { // Verifica se a a��o escolhida � v�lida
            if (usuarios[id_usuario].num_acoes >= MAX_ACOES_POR_USUARIO) { // Verifica se o usu�rio j� atingiu o limite de a��es
                printf("ERRO: Limite de a��es atingido (%d)!\n", MAX_ACOES_POR_USUARIO);
            } else { // Se o usu�rio ainda pode registrar a��es
                adicionarAcao(id_usuario, acao_escolhida, usuarios); // Chama a fun��o para adicionar a a��o
                pontos = calcularPontos(acao_escolhida); // Calcula os pontos da a��o escolhida
                printf("A��o %d registrada para %s! Pontos: %d\n", acao_escolhida, nome, pontos); // Mensagem de sucesso
            }
            printf("Pressione Enter para continuar...");
            getchar(); // Pausa para o usu�rio ler a mensagem
        } else if (acao_escolhida == 0) { // Se o usu�rio escolheu voltar ao menu principal
            printf("Retornando ao menu principal...\n");
        } else { // Se o usu�rio escolheu uma op��o inv�lida
            printf("ERRO: Op��o inv�lida!\n");
            printf("Pressione Enter para tentar novamente...");
            getchar(); // Pausa para o usu�rio ler a mensagem
        }
    } while (acao_escolhida != 0); // Continua registrando a��es at� que o usu�rio escolha voltar
}

int buscarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios) { // Fun��o para buscar um usu�rio pelo nome
    for (int i = 0; i < *contador_usuarios; i++) { // Loop para percorrer os usu�rios registrados
        if (strcmp(usuarios[i].nome, nome) == 0) { // Compara o nome do usu�rio com o nome fornecido
            return i; // Retorna o �ndice do usu�rio se encontrado
        }
    }
    return -1; // Retorna -1 se o usu�rio n�o for encontrado
}

int adicionarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios) { // Fun��o para adicionar um novo usu�rio
    if (*contador_usuarios < MAX_USUARIOS) { // Verifica se ainda h� espa�o para novos usu�rios
        strcpy(usuarios[*contador_usuarios].nome, nome); // Copia o nome do usu�rio para a estrutura
        usuarios[*contador_usuarios].num_acoes = 0; // Inicializa o contador de a��es do usu�rio
        usuarios[*contador_usuarios].pontuacao = 0; // Inicializa a pontua��o do usu�rio
        usuarios[*contador_usuarios].meta_diaria = 0; // Inicializa a meta di�ria do usu�rio

        int meta; // Vari�vel para armazenar a meta di�ria de pontos
        system("cls"); // Limpa a tela do console
        printf("Bem-vindo ao EcoChallenge, %s!\n", nome); // Mensagem de boas-vindas
        printf("Defina sua meta di�ria de pontos: "); // Solicita ao usu�rio que defina sua meta di�ria
        if (scanf("%d", &meta) != 1 || meta <= 0) { // Verifica se a entrada � v�lida (scanf retorna 1 se a leitura foi bem-sucedida)
            printf("Meta inv�lida! Definindo meta padr�o de 50 pontos.\n"); // Mensagem de erro se a entrada for inv�lida
            meta = 50; // Define uma meta padr�o de 50 pontos se a entrada for inv�lida
        }
        getchar(); // Limpa o buffer do teclado

        usuarios[*contador_usuarios].meta_diaria = meta; // Define a meta di�ria do usu�rio
        printf("Meta di�ria definida: %d pontos\n", meta);
        printf("Pressione Enter para continuar...");
        getchar(); // Pausa para o usu�rio ler a mensagem

        return (*contador_usuarios)++; // Retorna o �ndice do novo usu�rio e incrementa o contador de usu�rios
    }
    return -1; // Retorna -1 se n�o for poss�vel adicionar o usu�rio (limite atingido)
}

void adicionarAcao(int id_usuario, int id_acao, Usuario *usuarios) { // Fun��o para adicionar uma a��o realizada por um usu�rio
    if (id_usuario >= 0 && id_usuario < MAX_USUARIOS) { // Verifica se o ID do usu�rio � v�lido
        if (usuarios[id_usuario].num_acoes < MAX_ACOES_POR_USUARIO) { // Verifica se o usu�rio ainda pode registrar a��es
            int pontos_anteriores = usuarios[id_usuario].pontuacao; // Armazena a pontua��o anterior do usu�rio

            // Adiciona a a��o e atualiza a pontua��o
            usuarios[id_usuario].acoes[usuarios[id_usuario].num_acoes++] = id_acao; // Armazena a a��o realizada
            usuarios[id_usuario].pontuacao += calcularPontos(id_acao); // Atualiza a pontua��o do usu�rio com os pontos da a��o realizada

            // Verifica se o usu�rio atingiu a meta di�ria com essa a��o
            if (pontos_anteriores < usuarios[id_usuario].meta_diaria &&
                usuarios[id_usuario].pontuacao >= usuarios[id_usuario].meta_diaria) { // Se a pontua��o anterior era menor que a meta e agora atingiu ou superou a meta
                system("cls"); // Limpa a tela do console
                printf("\n**************************************\n");
                printf("PARAB�NS, %s!\n", usuarios[id_usuario].nome);
                printf("Voc� atingiu sua meta di�ria de %d pontos!\n", usuarios[id_usuario].meta_diaria);
                printf("**************************************\n");
            }
        }
    }
}

int calcularPontos(int id_acao) { // Fun��o para calcular os pontos de uma a��o com base no ID da a��o
    switch (id_acao) { // Verifica o ID da a��o e retorna os pontos correspondentes
        case 1: return 10;
        case 2: case 3: case 4: return 15;
        case 5: return 20;
        case 6: return 25;
        case 7: case 8: return 30;
        case 9: return 50;
        default: return 0;
    }
}

void visualizarAcoes(int *contador_usuarios, Usuario *usuarios) { // Fun��o para visualizar as a��es de um participante
    system("cls"); // Limpa a tela do console
    char nome[100]; // Vari�vel tempor�ria para armazenar o nome do usu�rio

    printf("##############################\n");
    printf("EcoChallenge - Visualiza��o de A��es\n");
    printf("##############################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin); // L� o nome do usu�rio
    nome[strcspn(nome, "\n")] = 0; // Remove o caractere de nova linha do final da string

    int id_usuario = buscarUsuario(nome, contador_usuarios, usuarios); // Busca o usu�rio pelo nome

    if (id_usuario == -1) { // Se o usu�rio n�o foi encontrado
        printf("\nERRO: Participante n�o encontrado!\n"); // Mensagem de erro
    } else { // Se o usu�rio foi encontrado mostra as a��es registradas
        system("cls");
        printf("##############################\n");
        printf("EcoChallenge - Visualiza��o de A��es\n\n");
        printf("Participante: %s\n", usuarios[id_usuario].nome);
        printf("Pontua��o total: %d pontos\n", usuarios[id_usuario].pontuacao);
        printf("Meta di�ria: %d pontos\n", usuarios[id_usuario].meta_diaria);

        // Mostra o progresso da meta
        if (usuarios[id_usuario].pontuacao >= usuarios[id_usuario].meta_diaria) {
            printf("Status: Meta di�ria ATINGIDA!\n\n");
        } else {
            printf("Status: Faltam %d pontos para atingir a meta di�ria\n\n",
                  usuarios[id_usuario].meta_diaria - usuarios[id_usuario].pontuacao);
        }

        // Verifica se o usu�rio registrou a��es
        if (usuarios[id_usuario].num_acoes == 0) {
            printf("Este participante ainda n�o registrou nenhuma a��o.\n");
        } else { // Se o usu�rio registrou a��es, exibe as a��es realizadas
            printf("A��es registradas:\n");
            printf("------------------------------\n");

            for (int i = 0; i < usuarios[id_usuario].num_acoes; i++) { // Loop para percorrer as a��es registradas pelo usu�rio
                int id_acao = usuarios[id_usuario].acoes[i]; // Obt�m o ID da a��o realizada
                int pontos = calcularPontos(id_acao); // Calcula os pontos da a��o realizada
                printf("%d. %s - %d pontos\n", i+1, obterNomeAcao(id_acao), pontos); // Exibe a a��o e os pontos correspondentes
            }
            printf("------------------------------\n");
            printf("##############################\n");
        }
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar(); // Pausa para o usu�rio ler a mensagem
}

char* obterNomeAcao(int id_acao) { // Fun��o para obter o nome da a��o com base no ID da a��o
    switch (id_acao) { // Verifica o ID da a��o e retorna o nome correspondente
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

void Ranking(int *contador_usuarios, Usuario *usuarios) { // Fun��o para exibir o ranking de pontua��o dos usu�rios
    system("cls"); // Limpa a tela do console
    printf("##############################\n");
    printf("EcoChallenge - Ranking de Pontua��o\n");
    printf("##############################\n\n");

    if (*contador_usuarios == 0) { // Verifica se n�o h� usu�rios registrados
        printf("ERRO: Nenhum participante registrado ainda.\n");
    } else { // Se h� usu�rios registrados, exibe o rankin
        for (int i = 0; i < *contador_usuarios - 1; i++) { // Loop para ordenar os usu�rios por pontua��o
            for (int j = i + 1; j < *contador_usuarios; j++) { // Loop aninhado para comparar os usu�rios
                if (usuarios[j].pontuacao > usuarios[i].pontuacao) { // Se o usu�rio j tem mais pontos que o usu�rio i
                    Usuario temp = usuarios[i]; // Troca os usu�rios
                    usuarios[i] = usuarios[j]; // Atribui o usu�rio j ao usu�rio i
                    usuarios[j] = temp; // Atribui o usu�rio i ao usu�rio j
                }
            }
        }

        printf("Ranking:\n");
        printf("------------------------------\n");
        for (int i = 0; i < *contador_usuarios; i++) { // Loop para exibir os usu�rios ordenados por pontua��o
            printf("%d. %s - %d pontos\n", i + 1, usuarios[i].nome, usuarios[i].pontuacao); // Exibe o ranking do usu�rio
        }
        printf("------------------------------\n");
        printf("##############################\n");
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar(); // Pausa para o usu�rio ler a mensagem
}