/* EcoChallenge - Monitor de Hábitos Sustentáveis
 * Lorenzo Farias, Bernardo Soares Nunes e Pedro Cabral Buchaim
 * Projeto Incremental
 * Programação para Resolução de Problemas
 * Profa. Dra. Daniela Bagatini
 * Universidade de Santa Cruz do Sul (UNISC).
 */

#include <stdio.h> // Adicionado para manipulação de entrada/saída
#include <string.h> // Adicionado para manipulação de strings
#include <locale.h> // Adicionado para acentuação
#include <stdlib.h> // Adicionado para system("cls")
#include <windows.h> // Adicionado para Sleep()

#define MAX_USUARIOS 100 // Número máximo de usuários
#define MAX_ACOES_POR_USUARIO 15 // Número máximo de ações por usuário

typedef struct { // Estrutura para armazenar informações do usuário
    char nome[100]; // Nome do usuário
    int acoes[MAX_ACOES_POR_USUARIO]; // IDs das ações realizadas
    int num_acoes; // Contador de ações do usuário
    int pontuacao; // Pontuação total do usuário
    int meta_diaria; // Meta diária de pontos do usuário
} Usuario;

void Menu(int *contador_usuarios, Usuario *usuarios); // Declaração da função menu
void registroAcao(int *contador_usuarios, Usuario *usuarios); // Declaração da função registroAcao
int buscarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios); // Declaração da função buscarUsuario
int adicionarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios); // Declaração da função adicionarUsuario
void adicionarAcao(int id_usuario, int id_acao, Usuario *usuarios); // Declaração da função adicionarAcao
int calcularPontos(int id_acao); // Declaração da função calcularPontos
void visualizarAcoes(int *contador_usuarios, Usuario *usuarios); // Declaração da função visualizarAcoes
char* obterNomeAcao(int id_acao); // Declaração da função obterNomeAcao
void Ranking(int *contador_usuarios, Usuario *usuarios); // Declaração da função Ranking
void salvarDados(int contador_usuarios, Usuario *usuarios); // Declaração da função salvarDados
void carregarDados(int *contador_usuarios, Usuario *usuarios); // Declaração da função carregarDados
void Creditos(); // Declaração da função Creditos

int main(void) { // Função principal do programa
    setlocale(LC_ALL, "Portuguese_Brazil.1252"); // Configura o locale para português para suporte a acentuação
    system("chcp 1252"); // Configura a página de código do console para 1252 (Windows)

    Usuario usuarios[MAX_USUARIOS]; // Array para armazenar os usuários
    int contador_usuarios = 0; // Contador de usuários registrados

    carregarDados(&contador_usuarios, usuarios); // Tenta carregar os dados salvos ao iniciar o programa

    Menu(&contador_usuarios, usuarios); // Chama a função menu para iniciar o programa

    salvarDados(contador_usuarios, usuarios); // Salva os dados dos usuários antes de encerrar o programa

    Creditos(); // Exibe os créditos do programa

    return 0; // Retorna 0 para indicar que o programa terminou corretamente
}

void Menu(int *contador_usuarios, Usuario *usuarios) { // Função para exibir o menu principal

    int opcao; // Variável para armazenar a opção escolhida pelo usuário

    do { // Loop para exibir o menu até que o usuário escolha sair
        system("cls"); // Limpa a tela do console
        printf("######################################################\n");
        printf("###                                                ###\n");
        printf("### EcoChallenge - Monitor de Hábitos Sustentáveis ###\n");
        printf("###                                                ###\n");
        printf("######################################################\n\n");
        printf("Opções:\n");
        printf("1 - Registrar ação sustentável\n");
        printf("2 - Visualizar ações de algum participante\n");
        printf("3 - Ver ranking de pontuação\n");
        printf("4 - Sair e salvar\n");
        printf("######################################################\n");
        printf("Digite a opção desejada: ");
        if (scanf("%d", &opcao) != 1) { // Verifica se a entrada é válida (scanf retorna 1 se a leitura foi bem-sucedida)
            opcao = 0; // Define uma opção inválida para tratar o erro
        }
        getchar(); // Limpa o buffer do teclado

        switch (opcao) { // Verifica a opção escolhida pelo usuário
            case 1: // Opção para registrar uma ação sustentável
                registroAcao(contador_usuarios, usuarios); // Chama a função para registrar uma ação sustentável
                break; // Sai do switch
            case 2: // Opção para visualizar ações de um participante
                visualizarAcoes(contador_usuarios, usuarios); // Chama a função para visualizar ações de um participante
                break; // Sai do switch
            case 3: // Opção para ver o ranking de pontuação
                Ranking(contador_usuarios, usuarios); // Chama a função para exibir o ranking de pontuação
                break; // Sai do switch
            case 4: // Opção para sair do programa
                break; // Sai do switch
            default: // Caso de uma opção inválida
                printf("ERRO: Entrada inválida! Tente novamente.\n"); // Mensagem de erro
                system("pause"); // Pausa para o usuário ler a mensagem
                break; // Sai do switch
        }
    } while (opcao != 4); // Continua exibindo o menu até que o usuário escolha sair
}

void registroAcao(int *contador_usuarios, Usuario *usuarios) { // Função para registrar uma ação sustentável
    system("cls"); // Limpa a tela do console

    char nome[100]; // Variável temporária para armazenar o nome do usuário
    int acao_escolhida; // Variável para armazenar a ação escolhida pelo usuário
    int pontos = 0; // Variável para armazenar a pontuação da ação escolhida

    printf("######################################################\n");
    printf("###                                                ###\n");
    printf("###        EcoChallenge - Registro de Ação         ###\n");
    printf("###                                                ###\n");
    printf("######################################################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin); // Lê o nome do usuário
    nome[strcspn(nome, "\n")] = 0; // Remove o caractere de nova linha do final da string


    int id_usuario = buscarUsuario(nome, contador_usuarios, usuarios); // Busca o usuário pelo nome
    if (id_usuario == -1) { // Se o usuário não foi encontrado
        id_usuario = adicionarUsuario(nome, contador_usuarios, usuarios); // Adiciona o usuário
        if (id_usuario == -1) { // Se não foi possível adicionar o usuário
            printf("ERRO: Limite de usuários atingido (%d)!\n", MAX_USUARIOS); // Mensagem de erro
            printf("Pressione Enter para voltar ao menu principal...");
            getchar(); // Pausa para o usuário ler a mensagem
            return; // Retorna para o menu principal
        }
    }

    do { // Loop para registrar ações até que o usuário escolha voltar
        system("cls"); // Limpa a tela do console
        printf("######################################################\n");
        printf("###                                                ###\n");
        printf("###     EcoChallenge - Registro de atividades      ###\n");
        printf("###                                                ###\n");
        printf("######################################################\n\n");
        printf("Participante: %s\n\n", nome);
        printf("Ações:\n");
        printf("1 - Separar lixo - 10\n");
        printf("2 - Economia de água - 15\n");
        printf("3 - Economia de energia - 15\n");
        printf("4 - Compostagem - 15\n");
        printf("5 - Reciclagem de materiais - 20\n");
        printf("6 - Organização de trocas (brechó) - 25\n");
        printf("7 - Meios de transportes não poluentes - 30\n");
        printf("8 - Reaproveitamento de água da chuva - 30\n");
        printf("9 - Plantar árvores - 50\n");
        printf("0 - Voltar\n");
        printf("######################################################\n");
        printf("Digite a ação feita: ");
        if (scanf("%d", &acao_escolhida) != 1) { // Verifica se a entrada é válida (scanf retorna 1 se a leitura foi bem-sucedida)
            acao_escolhida = -1; // Define uma opção inválida para tratar o erro
        }
        getchar(); // Limpa o buffer do teclado

        // Armazenar a ação escolhida e pontuação
        if (acao_escolhida >= 1 && acao_escolhida <= 9) { // Verifica se a ação escolhida é válida
            if (usuarios[id_usuario].num_acoes >= MAX_ACOES_POR_USUARIO) { // Verifica se o usuário já atingiu o limite de ações
                printf("ERRO: Limite de ações atingido (%d)!\n", MAX_ACOES_POR_USUARIO);
            } else { // Se o usuário ainda pode registrar ações
                adicionarAcao(id_usuario, acao_escolhida, usuarios); // Chama a função para adicionar a ação
                pontos = calcularPontos(acao_escolhida); // Calcula os pontos da ação escolhida
                printf("\nAção %d registrada para %s! Pontos: %d\n", acao_escolhida, nome, pontos); // Mensagem de sucesso
            }
            printf("Pressione Enter para continuar...");
            getchar(); // Pausa para o usuário ler a mensagem
        } else if (acao_escolhida == 0) { // Se o usuário escolheu voltar ao menu principal
            printf("Retornando ao menu principal...\n");
            Sleep(1000); // Pausa de 1 segundo para o usuário ler a mensagem
        } else { // Se o usuário escolheu uma opção inválida
            printf("ERRO: Opção inválida!\n");
            system("pause"); // Pausa para o usuário ler a mensagem
        }
    } while (acao_escolhida != 0); // Continua registrando ações até que o usuário escolha voltar
}

int buscarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios) { // Função para buscar um usuário pelo nome
    for (int i = 0; i < *contador_usuarios; i++) { // Loop para percorrer os usuários registrados
        if (strcmp(usuarios[i].nome, nome) == 0) { // Compara o nome do usuário com o nome fornecido
            return i; // Retorna o índice do usuário se encontrado
        }
    }
    return -1; // Retorna -1 se o usuário não for encontrado
}

int adicionarUsuario(char *nome, int *contador_usuarios, Usuario *usuarios) { // Função para adicionar um novo usuário
    if (*contador_usuarios < MAX_USUARIOS) { // Verifica se ainda há espaço para novos usuários
        strcpy(usuarios[*contador_usuarios].nome, nome); // Copia o nome do usuário para a estrutura
        usuarios[*contador_usuarios].num_acoes = 0; // Inicializa o contador de ações do usuário
        usuarios[*contador_usuarios].pontuacao = 0; // Inicializa a pontuação do usuário
        usuarios[*contador_usuarios].meta_diaria = 0; // Inicializa a meta diária do usuário

        int meta; // Variável para armazenar a meta diária de pontos
        do
        {
            system("cls"); // Limpa a tela do console
            printf("######################################################\n");
            printf("###                                                ###\n");
            printf("###       EcoChallenge - Registro de Usuário       ###\n");
            printf("###                                                ###\n");
            printf("######################################################\n\n");
            printf("Bem-vindo ao EcoChallenge, %s!\n", nome); // Mensagem de boas-vindas
            printf("Defina sua meta diária de pontos: "); // Solicita ao usuário que defina sua meta diária
            if (scanf("%d", &meta) != 1 || meta <= 0) { // Verifica se a entrada é válida (scanf retorna 1 se a leitura foi bem-sucedida)
                printf("\nMeta inválida!\n"); // Mensagem de erro se a entrada for inválida
                meta = -1;
                system("pause");
            }

            getchar(); // Limpa o buffer do teclado

            if (meta > 0) { // Se a meta fornecida for válida (maior que 0)
                usuarios[*contador_usuarios].meta_diaria = meta; // Define a meta diária do usuário
                printf("\nMeta diária definida: %d pontos\n", meta);
                printf("Pressione Enter para continuar...");
                getchar(); // Pausa para o usuário ler a mensagem
            }
        } while (meta <= 0); // Continua solicitando a meta diária até que o usuário forneça um valor válido
        return (*contador_usuarios)++; // Retorna o índice do novo usuário e incrementa o contador de usuários
    }
    return -1; // Retorna -1 se não for possível adicionar o usuário (limite atingido)
}

void adicionarAcao(int id_usuario, int id_acao, Usuario *usuarios) { // Função para adicionar uma ação realizada por um usuário
    if (id_usuario >= 0 && id_usuario < MAX_USUARIOS) { // Verifica se o ID do usuário é válido
        if (usuarios[id_usuario].num_acoes < MAX_ACOES_POR_USUARIO) { // Verifica se o usuário ainda pode registrar ações
            int pontos_anteriores = usuarios[id_usuario].pontuacao; // Armazena a pontuação anterior do usuário

            // Adiciona a ação e atualiza a pontuação
            usuarios[id_usuario].acoes[usuarios[id_usuario].num_acoes++] = id_acao; // Armazena a ação realizada
            usuarios[id_usuario].pontuacao += calcularPontos(id_acao); // Atualiza a pontuação do usuário com os pontos da ação realizada

            // Verifica se o usuário atingiu a meta diária com essa ação
            if (pontos_anteriores < usuarios[id_usuario].meta_diaria &&
                usuarios[id_usuario].pontuacao >= usuarios[id_usuario].meta_diaria) { // Se a pontuação anterior era menor que a meta e agora atingiu ou superou a meta
                system("cls"); // Limpa a tela do console
                printf("\n*****************************************\n");
                printf("PARABÉNS, %s!\n", usuarios[id_usuario].nome);
                printf("Você atingiu sua meta diária de %d pontos!\n", usuarios[id_usuario].meta_diaria);
                printf("*****************************************\n");
            }
        }
    }
}

int calcularPontos(int id_acao) { // Função para calcular os pontos de uma ação com base no ID da ação
    switch (id_acao) { // Verifica o ID da ação e retorna os pontos correspondentes
        case 1: return 10;
        case 2: case 3: case 4: return 15;
        case 5: return 20;
        case 6: return 25;
        case 7: case 8: return 30;
        case 9: return 50;
        default: return 0;
    }
}

void visualizarAcoes(int *contador_usuarios, Usuario *usuarios) { // Função para visualizar as ações de um participante
    system("cls"); // Limpa a tela do console
    char nome[100]; // Variável temporária para armazenar o nome do usuário

    printf("######################################################\n");
    printf("###                                                ###\n");
    printf("###      EcoChallenge - Visualização de Ações      ###\n");
    printf("###                                                ###\n");
    printf("######################################################\n\n");
    printf("Digite o seu nome: ");
    fgets(nome, sizeof(nome), stdin); // Lê o nome do usuário
    nome[strcspn(nome, "\n")] = 0; // Remove o caractere de nova linha do final da string

    int id_usuario = buscarUsuario(nome, contador_usuarios, usuarios); // Busca o usuário pelo nome

    if (id_usuario == -1) { // Se o usuário não foi encontrado
        printf("\nERRO: Participante não encontrado!\n"); // Mensagem de erro
    } else { // Se o usuário foi encontrado mostra as ações registradas
        system("cls");
        printf("######################################################\n");
        printf("###                                                ###\n");
        printf("###      EcoChallenge - Visualização de Ações      ###\n");
        printf("###                                                ###\n");
        printf("######################################################\n\n");
        printf("Participante: %s\n", usuarios[id_usuario].nome);
        printf("Pontuação total: %d pontos\n", usuarios[id_usuario].pontuacao);
        printf("Meta diária: %d pontos\n", usuarios[id_usuario].meta_diaria);

        // Mostra o progresso da meta
        if (usuarios[id_usuario].pontuacao >= usuarios[id_usuario].meta_diaria) { // Se o usuário atingiu ou superou a meta diária
            printf("Status: Meta diária ATINGIDA!\n\n");
        } else
            printf("Status: Faltam %d pontos para atingir a meta diária\n\n", usuarios[id_usuario].meta_diaria - usuarios[id_usuario].pontuacao);


        // Verifica se o usuário registrou ações
        if (usuarios[id_usuario].num_acoes == 0) {
            printf("Este participante ainda não registrou nenhuma ação.\n");
        } else { // Se o usuário registrou ações, exibe as ações realizadas
            printf("Ações registradas:\n");
            printf("------------------------------\n");

            for (int i = 0; i < usuarios[id_usuario].num_acoes; i++) { // Loop para percorrer as ações registradas pelo usuário
                int id_acao = usuarios[id_usuario].acoes[i]; // Obtém o ID da ação realizada
                int pontos = calcularPontos(id_acao); // Calcula os pontos da ação realizada
                printf("%d. %s - %d pontos\n", i+1, obterNomeAcao(id_acao), pontos); // Exibe a ação e os pontos correspondentes
            }
            printf("------------------------------\n");
            printf("######################################################\n");
        }
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar(); // Pausa para o usuário ler a mensagem
}

char* obterNomeAcao(int id_acao) { // Função para obter o nome da ação com base no ID da ação
    switch (id_acao) { // Verifica o ID da ação e retorna o nome correspondente
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

void Ranking(int *contador_usuarios, Usuario *usuarios) { // Função para exibir o ranking de pontuação dos usuários
    system("cls"); // Limpa a tela do console
    printf("######################################################\n");
    printf("###                                                ###\n");
    printf("###      EcoChallenge - Ranking de Pontuação       ###\n");
    printf("###                                                ###\n");
    printf("######################################################\n\n");

    if (*contador_usuarios == 0) { // Verifica se não há usuários registrados
        printf("ERRO: Nenhum participante registrado ainda.\n");
    } else { // Se há usuários registrados, exibe o ranking
        for (int i = 0; i < *contador_usuarios - 1; i++) { // Loop para ordenar os usuários por pontuação
            for (int j = i + 1; j < *contador_usuarios; j++) { // Loop aninhado para comparar os usuários
                if (usuarios[j].pontuacao > usuarios[i].pontuacao) { // Se o usuário j tem mais pontos que o usuário i
                    Usuario temp = usuarios[i]; // Troca os usuários
                    usuarios[i] = usuarios[j]; // Atribui o usuário j ao usuário i
                    usuarios[j] = temp; // Atribui o usuário i ao usuário j
                }
            }
        }

        printf("Ranking:\n");
        printf("------------------------------\n");
        for (int i = 0; i < *contador_usuarios; i++) { // Loop para exibir os usuários ordenados por pontuação
            printf("%d. %s - %d pontos\n", i + 1, usuarios[i].nome, usuarios[i].pontuacao); // Exibe o ranking do usuário
        }
        printf("------------------------------\n");
        printf("######################################################\n");
    }

    printf("\nPressione Enter para voltar ao menu principal...");
    getchar(); // Pausa para o usuário ler a mensagem
}

void salvarDados(int contador_usuarios, Usuario *usuarios) { // Função para salvar os dados dos usuários em um arquivo
    FILE *arquivo = fopen("dados_usuarios.txt", "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("ERRO: Não foi possível salvar os dados!\n");
        Sleep(2000); // Pausa de 2 segundos para o usuário ler a mensagem
        return;
    }

    fprintf(arquivo, "%d\n", contador_usuarios); // Salva o número total de usuários

    // Salva os dados de cada usuário
    for (int i = 0; i < contador_usuarios; i++) { // Loop para percorrer os usuários registrados
        fprintf(arquivo, "%s\n", usuarios[i].nome); // Nome do usuário
        fprintf(arquivo, "%d\n", usuarios[i].num_acoes); // Número de ações
        fprintf(arquivo, "%d\n", usuarios[i].pontuacao); // Pontuação total
        fprintf(arquivo, "%d\n", usuarios[i].meta_diaria); // Meta diária

        // Salva as ações do usuário
        for (int j = 0; j < usuarios[i].num_acoes; j++) { // Loop para percorrer as ações registradas pelo usuário
            fprintf(arquivo, "%d\n", usuarios[i].acoes[j]); // ID da ação
        }
    }

    fclose(arquivo); // Fecha o arquivo
    printf("\nDados salvos com sucesso!\n");
    Sleep(2000); // Pausa de 2 segundos para o usuário ler a mensagem
}

void carregarDados(int *contador_usuarios, Usuario *usuarios) { // Função para carregar os dados dos usuários a partir de um arquivo
    system("cls"); // Limpa a tela do console

    FILE *arquivo = fopen("dados_usuarios.txt", "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) { // Verifica se o arquivo foi aberto com sucesso
        printf("Nenhum dado encontrado. Iniciando com usuários vazios.\n");
        Sleep(2000); // Pausa de 2 segundos para o usuário ler a mensagem
        return; // Retorna se não houver dados para carregar
    }

    fscanf(arquivo, "%d\n", contador_usuarios); // Lê o número total de usuários

    // Carrega os dados de cada usuário
    for (int i = 0; i < *contador_usuarios; i++) { // Loop para percorrer os usuários registrados
        fgets(usuarios[i].nome, 100, arquivo); // Lê o nome do usuário
        usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = 0; // Remove o caractere de nova linha

        fscanf(arquivo, "%d\n", &usuarios[i].num_acoes); // Lê o número de ações
        fscanf(arquivo, "%d\n", &usuarios[i].pontuacao); // Lê a pontuação total
        fscanf(arquivo, "%d\n", &usuarios[i].meta_diaria); // Lê a meta diária

        // Carrega as ações do usuário
        for (int j = 0; j < usuarios[i].num_acoes; j++) { // Loop para percorrer as ações registradas pelo usuário
            fscanf(arquivo, "%d\n", &usuarios[i].acoes[j]); // Lê o ID da ação
        }
    }

    fclose(arquivo); // Fecha o arquivo

    printf("Dados carregados com sucesso! %d usuário(s) registrado(s).\n", *contador_usuarios);
    Sleep(2000); // Pausa de 2 segundos para o usuário ler a mensagem
}

void Creditos() { // Função para exibir os créditos do programa
    system("cls"); // Limpa a tela antes de sair
    printf("######################################################\n");
    printf("###                                                ###\n");
    printf("###           EcoChallenge - Créditos              ###\n");
    printf("###                                                ###\n");
    printf("######################################################\n\n");
    printf("Desenvolvido por:\n");
    printf("Lorenzo Farias\n");
    printf("Bernardo Soares Nunes\n");
    printf("Pedro Cabral Buchaim\n\n");
    printf("Universidade de Santa Cruz do Sul (UNISC)\n");
    printf("Programação para Resolução de Problemas\n");
    printf("Profa. Dra. Daniela Bagatini\n\n");
    printf("######################################################\n");

    Sleep(5000); // Pausa de 5 segundos para o usuário ler os créditos
}