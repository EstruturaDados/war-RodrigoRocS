// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct // Define struct do territorio
{
    char nome[30], cor[10];
    int tropas;
} Territorio;

void limpaBuffer() // Limpa buffer de entrada
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void cadastraMapas(Territorio *t) // cadastra 5 mapas para o jogo
{
    int numTerritorio = 0; // contador de territorios
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo: \n");
    do // inicia cadastro dos territorios
    {
        printf("\n=== Cadastrando Territorio %d ===\n", numTerritorio + 1);

        printf("Nome do territorio: ");
        fgets(t[numTerritorio].nome, 30, stdin);
        t[numTerritorio].nome[strcspn(t[numTerritorio].nome, "\n")] = 0;

        printf("Cor do territorio: ");
        fgets(t[numTerritorio].cor, 10, stdin);
        t[numTerritorio].cor[strcspn(t[numTerritorio].cor, "\n")] = 0;

        printf("Numero de tropas: ");
        scanf("%d", &t[numTerritorio].tropas);

        limpaBuffer();

        numTerritorio++; // incrementa o loop

    } while (numTerritorio < 5);
}

void exibeMapa(Territorio *t) // exibe mapa atualizado
{
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < 5; i++)
    {
        // printf("\n--- Territorio %d ---\n", i + 1);
        printf("%d - %s (Exercito %s, Tropas: %d)\n", i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

int rolarDado() // gera um numero aleatorio entre 1 e 6
{
    static int inicializado = 0;
    if (!inicializado)
    {
        srand(time(NULL));
        inicializado = 1;
    }
    return (rand() % 6) + 1;
}

void faseDeAtaque(Territorio *t)
{

    int atacante;
    int defensor;
    int dadoAta;
    int dadoDef;
    char continuar;

    do
    {

        printf("\n*** FASE DE ATAQUE ***\n");
        printf("Escolha o territorio atacante (1 a 5, ou 0 para sair): \n");
        scanf("%d", &atacante);

        if (atacante == 0)
        {
            printf("Jogo encerrado e memoria liberada. até a proxima!");
            limpaBuffer();
            return;
        }

        printf("Escolha o territorio defensor (1 a 5): \n");
        scanf("%d", &defensor);
        atacante--; // corrige para acessar os indices corretos
        defensor--;

        limpaBuffer();

        printf("\n*** RESULTADO DA BATALHA ***\n");
        dadoAta = rolarDado();
        printf("o atacante %s rolou um dado e tirou: %d\n", t[atacante].nome, dadoAta);
        dadoDef = rolarDado();
        printf("o defensor %s rolou um dado e tirou: %d\n", t[defensor].nome, dadoDef);

        if (dadoAta > dadoDef)
        {
            printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa\n");
            t[defensor].tropas--;
            if (t[defensor].tropas == 0)
            {
                strcpy(t[defensor].cor, t[atacante].cor);
                printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", t[defensor].nome, t[atacante].cor);
                t[defensor].tropas = 1;
            }
        }
        else
        {
            printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa\n");
            t[atacante].tropas--;
            if (t[atacante].tropas == 0)
            {
                strcpy(t[atacante].cor, t[defensor].cor);
                printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", t[atacante].nome, t[defensor].cor);
                t[atacante].tropas = 1;
            }
        }

        printf("\nPressione enter para continuar ao proximo turno...");
        continuar = getchar();
        exibeMapa(t);
    } while (continuar == '\n');
}

int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    Territorio *t = (Territorio *)calloc(5, sizeof(Territorio)); // alocação dinamica.
    if (t == NULL)                                               // verifica se a alocação deu certo
    {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    cadastraMapas(t); // inicia cadastro de mapas

    exibeMapa(t); // exibe territorios

    faseDeAtaque(t); // inicia fase de ataque

    free(t); // libera memoria alocada

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
