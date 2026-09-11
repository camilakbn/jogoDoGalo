#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/*grupo 3: camila, betânia, sarah
ordem de apresentação: 4º grupo
tema: jogo do galo (jogo da velha)
entrega do código: 11/09
apresentação: 16/09*/

// função para mostrar o jogo do vetor[9]
// função VOID pq ela não faz nenhuma ação, apenas mostra algo
void mostrarTabuleiroAtt(char jogo[9])
{
    cout << " " << jogo[0] << " | " << jogo[1] << " | " << jogo[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << jogo[3] << " | " << jogo[4] << " | " << jogo[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << jogo[6] << " | " << jogo[7] << " | " << jogo[8] << "\n";
}

// função apenas para mostrar o jogo no início do jogo, é uma matriz 3x3
// função VOID pq ela não faz nenhuma ação, apenas mostra algo
void mostrarTabuleiro(char jogo[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            cout << " " << *(*(jogo + i) + j) << " ";
            if (j < 2)
            {
                cout << "|";
            }
        }

        if (i < 2)
        {
            cout << "\n---+---+---\n";
        }
    }
}

// função guardar jogador, para salvar as estatísticas:
// essa função é VOID pq ela não devolve nenhum valor, ela faz ação: LÊ e GUARDA os dados no ficheiro
void guardarJogador(string nomeJogador, int partida, int vitoria, int derrota, int empate)
{
    string nomes[100]; // vetor de string que guarda 100 nomes
    int partidas[100], vitorias[100], derrotas[100], empates[100];
    // vetores de int para guardar as estatísticas
    int total = 0;
    // o total inicia 0 e vai adicionando ao decorrer da quantidade de partidas da pessoa com o mesmo nome

    ifstream entrada("jogoDoGalo.txt"); // abrir o ficheiro para LER as informações que já existem
    if (entrada.is_open())              // se o ficheiro tiver aberto
    {
        while (getline(entrada, nomes[total])) // esse total começa com 0
        // separei a string pq não consegui colocar a string na mesma parte dos inteiros
        {
            entrada >> partidas[total] >> vitorias[total] >> derrotas[total] >> empates[total];
            // para colocar os dados nos vetores, que vou utilizar abaixo no for de total
            entrada >> ws;
            // essa parte eu recebi algum ENTER que pode ter dado e ficado perdido
            // tipo quando recebe um int e depois uma string
            total++; // adiciona ao total, significa que já leu 1 jogador e viu se ele existe ou não
        }
        entrada.close(); // fecha o ficheiro
    } // o while termina quando não houver mais jogadores (pq ele é vinculado ao nomes[total])

    int encontrado = 0; // tipo um boolean de true ou false, onde 0 é false e 1 é true
    // esse for é pra jogadores encontrados no while acima
    for (int i = 0; i < total; i++) // esse for é pra percorrer todos os jogadores encontrados no while
    {
        if (nomes[i] == nomeJogador) // se o nome percorrido for igual ao nome de jogador existente
        {
            partidas[i] = partidas[i] + 1;
            vitorias[i] = vitorias[i] + vitoria;
            derrotas[i] = derrotas[i] + derrota;
            empates[i] = empates[i] + empate;
            // ele salva as estatísticas nos vetores de estatísticas
            // ex: se tinha partida[1], ele agora vai ser partida[2]
            encontrado = 1; // diz que foi encontrado
            break;          // para o for
        }
    }

    if (encontrado == 0) // se a pessoa não foi encontrada
    {
        nomes[total] = nomeJogador;
        partidas[total] = 1;
        vitorias[total] = vitoria;
        derrotas[total] = derrota;
        empates[total] = empate;
        total++;
        // ele salva a pessoa em um novo nome e adiciona essa pessoa ao total de jogadores
        // ex se antes tinham 2 jogadores agora vão ter 3
    }

    ofstream saida("jogoDoGalo.txt"); // abre o ficheiro pra escrever os dados que encontrei de jogadores novos/existentes
    if (saida.is_open())              // se o ficheiro estiver aberto...
    {
        for (int i = 0; i < total; i++) // esse for vai percorrer o total de jogadores
        {
            saida << nomes[i] << endl;
            saida << partidas[i] << " " << vitorias[i] << " " << derrotas[i] << " " << empates[i] << endl;
            // aqui eu SALVO os jogadores novos e existentes no ficheiro
        }
        saida.close(); // fecho o ficheiro
    }
}

// função para mostrar o jogador:
// função BOOL pq ela faz algo e devolve um TRUE or FALSE
bool mostrarJogador(ifstream &ficheiro, string &nomeJogador, int &numPartidas,
                    int &vitorias, int &derrotas, int &empates)
{
    if (!ficheiro.is_open()) // se o ficheiro NÃO abriu
    {
        cout << "Erro ao abrir ficheiro\n"; // mensagem de erro
        return false;                       // return false significa que deu erro
    }
    else // se o ficheiro abriu
    {

        // mostra as estatísticas
        cout << "Estatisticas: \n";

        while (getline(ficheiro, nomeJogador) && (ficheiro >> numPartidas >> vitorias >> derrotas >> empates))
        // o getline separado para receber a string e os ints em outro () separado
        {
            cout << "Jogador -> " << nomeJogador << ": Partidas: " << numPartidas
                 << " | Vitorias: " << vitorias << " | Derrotas: " << derrotas
                 << " | Empates: " << empates << endl;

            ficheiro >> ws; // aqui de novo para salvar algum ENTER que ficou perdido
        } // o while termina quando não tiver mais jogadores

        ficheiro.close(); // fecha o ficheiro
        return true;      // return true significa que deu certo
    }
}

// função VOID para verificar se há vencedor ou empate
void vitoriasEmpates(char jogo[9], int vitorias[8][3], char &vencedor, int &bloqueadas, int &empate)
//essa função as variáveis tem o & quando declaramos essas variáveis pq estamos modificando o valor delas
{

    // inicialização das variáveis
    vencedor = ' ';
    bloqueadas = 0;
    empate = 0;

    // verificar vencedor de acordo com a matriz vitorias[8][3]
    for (int j = 0; j < 8; j++)
    {
        if (jogo[vitorias[j][0]] != ' ' && jogo[vitorias[j][0]] == jogo[vitorias[j][1]] && jogo[vitorias[j][1]] == jogo[vitorias[j][2]])
        /*explicação do loop:
        a primeira parte verifica se o campo está vazio -> jogo[vitorias[j][0]] != ' '
        a segunda parte depois do primeiro && significa:
        o que está na posição 0 é igual ao que está na posição 1?
        e o que está na posição 1 é igual ao que está na posição 2?"
        se der falso ele pula pra o 1 do loop
        se der vddeiro significa que as 3 posicoes estão preenchidas
        com X ou 0*/
        {
            vencedor = jogo[vitorias[j][0]];
            break;
            // salva o jogador que ganhou e dá break pra ele não fazer o loop todo
        }
    } // fim do verificar o vencedor

    // funcao empate para ele parar antes das 9 jogadas
    for (int j = 0; j < 8; j++) // aqui ele vai percorrer a matriz vitorias com as possíveis vitórias
    {
        if ((jogo[vitorias[j][0]] == 'X' ||
             jogo[vitorias[j][1]] == 'X' ||
             jogo[vitorias[j][2]] == 'X') &&

            (jogo[vitorias[j][0]] == 'O' ||
             jogo[vitorias[j][1]] == 'O' ||
             jogo[vitorias[j][2]] == 'O'))
        // ele aqui percorre todas as posições 00,01,02...
        // e vê se elas podem dar vitória ao X ou ao O
        {
            bloqueadas++; // se nenhum dos dois puder vencer elas adicionam 1 valor à variável bloqueadas
        }
    }

    if (bloqueadas == 8) // se a variável bloqueadas contabiliza o bloqueio das 8 possibilidades de vitória
    {
        empate = 1; // dá empate
    }
}

//função VOID para verificar quem ganhou entre jogador1 e 2
void verificarVitoriaJogadores(char vencedor, char jogador1, char jogador2, string nomeJogador1, string nomeJogador2, char jogo[9])
//essa função não tem o & pq não estou modificando os valores das variáveis, apenas consultando
{
    if (vencedor == jogador1) // se o vencedor for o jogador1...
    {
        cout << "\n\n"
             << nomeJogador1 << " venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 1, 0, 0); // partida, vitoria, derrota, empate
        guardarJogador(nomeJogador2, 1, 0, 1, 0);
        return;
    }
    else if (vencedor == jogador2) // se o vencedor for o jogador 2...
    {
        cout << "\n\n"
             << nomeJogador2 << " venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 1, 0);
        guardarJogador(nomeJogador2, 1, 1, 0, 0);
        return;
    }
    else // se não...
    {
        cout << "\n\nEmpate!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 0, 1);
        guardarJogador(nomeJogador2, 1, 0, 0, 1);
        return;
    }
}

// função de jogada do computador NORMAL:
// função INT pq ela vai retornar um valor inteiro relativo à posição que o pcInteligente quer jogar
// essa função vai ser salva na variável posição na parte da jogada do pcInteligente no int main
int jogadaComputadorInteligente(char jogo[9], char pcInteligente, char jogador, int jaJogou)
{

    // isso daqui é a primeira jogada de sempre
    if (jaJogou == 0) // tipo um boolean, onde o 0 é não e 1 é sim
    // então ele diz, se o pcInteligente NÃO jogou
    {
        int posicaoDesejada; // variável criada pra informar a posição desejada no tabuleiro char jogo de 1 a 9
        if (jogo[4] == ' ')  // se a posição (que é 0 based) 4, que é a posição do meio, estiver vazia
        {
            posicaoDesejada = 5; // jogar na posição 5, que se o jogador digitar 5 equivale a posição 4
        }

        else if (jogo[0] == ' ') // se a posição 4 estiver ocupada, e a 0 estiver vazia
        {
            posicaoDesejada = 1; // jogar nela
        }
        return posicaoDesejada; // retorna a posição desejada, ou seja, joga na posição livre escolhida, sendo a primeira a 4 (meio)
    }

    int vitorias[8][3] = {// matriz 8x3 com as possíveis vitórias dentro do tabuleiro, que são 8
                          {0, 1, 2},
                          {3, 4, 5},
                          {6, 7, 8},
                          {0, 3, 6},
                          {1, 4, 7},
                          {2, 5, 8},
                          {0, 4, 8},
                          {2, 4, 6}};

    for (int c = 0; c < 8; c++) // esse for para percorrer o tabuleiro de 8 possíveis vitórias do pc
    // ou seja, ele tenta ganhar
    {

        if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == pcInteligente)
        // esse c vai ser 0,1,2... seguindo o loop
        // se jogo[vitorias[0][0]] tiver vazio
        //&& jogo[vitorias[0][1]] for igual a [0][2]
        //&& jogo [0][1] for igual ao pcInteligente
        // ou seja se o 01 for o pc inteligente e o 02 for igual ao 01, entao quer dizer que o 02 também é pcInteligente
        {
            return vitorias[c][0] + 1; // joga em vitorias [0][0] para completar o jogo
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == pcInteligente)
        // mesma lógica do de cima só que com outra combinação
        // se 00 for igual a 02 e 01 estiver vazio e 00 for o pcInteligente
        {
            return vitorias[c][1] + 1;
        }
        else if (jogo[vitorias[c][0]] == (jogo[vitorias[c][1]] && jogo[vitorias[c][2]] == ' ') && jogo[vitorias[c][1]] == pcInteligente)
        // se 00 for igual a 01 e 02 estiver vazio e 01 for pcInteligente
        {
            return vitorias[c][2] + 1;
        }
    }

    for (int c = 0; c < 8; c++)
    // esse for é com a mesma lógica só que para parar a vitória do jogador
    {

        if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == jogador)
        // note que ele compara o jogovitorias ao jogador!!!
        {
            return vitorias[c][0] + 1;
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == jogador)
        {
            return vitorias[c][1] + 1;
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][1]]) && jogo[vitorias[c][2]] == ' ' && jogo[vitorias[c][1]] == jogador)
        {
            return vitorias[c][2] + 1;
        }
    }

    // esse é o random, se nenhuma das duas opções de cima funcionarem
    int posicao;
    do
    {
        posicao = (rand() % 9);
    } while (jogo[posicao] != ' '); // while pq ele pode escolher uma posição randomica que esteja ocupada
    // então ele fica no loop até encontrar uma posição vazia randomica
    return posicao + 1; // joga na posicao (+1 pq salvamos como posicao -1 por conta dos zero based)
}

// função de jogada do computador DIFÍCIL:
// função INT pq ela vai retornar um valor inteiro relativo à posição que o pcInteligente quer jogar
// essa função vai ser salva na variável posição na parte da jogada do pcInteligente no int main
int jogadaComputadorDificil(char jogo[9], char pcInteligente, char jogador, int jaJogou)
{

    int possibilidades[4] = {1, 3, 7, 9};
    // possibilidades de jogo para quando o jogador jogar no meio ou outra posicao estrategica
    int posicoes[4] = {2, 4, 6, 8};
    // possibilidade de jogo para quando o pc fizer determinada jogada, explico mais abaixo
    int posicaoDesejada;
    // variável criada pra informar a posição desejada no tabuleiro char jogo de 1 a 9

    // isso daqui é a primeira jogada de sempre!!!
    if (jaJogou == 0) // tipo um boolean, onde o 0 é não e 1 é sim
    // então ele diz, se o pcInteligente NÃO jogou
    {
        if (jogo[4] == ' ') // se a posição (que é 0 based) 4, que é a posição do meio, estiver vazia
        {
            posicaoDesejada = 5; // jogar na posição 5, que se o jogador digitar 5 equivale a posição 4
        }

        else // se a posição 4 estiver ocupada, e a 0 estiver vazia
        {
            posicaoDesejada = possibilidades[(rand() % 5)]; // jogar nela
        }
        return posicaoDesejada; // retorna a posição desejada, ou seja, joga na posição livre escolhida, sendo a primeira a 4 (meio)
    }

    else // essa jogada é quando o pc já jogou uma vez
    {

        int vitorias[8][3] = {// matriz 8x3 com as possíveis vitórias dentro do tabuleiro, que são 8
                              {0, 1, 2},
                              {3, 4, 5},
                              {6, 7, 8},
                              {0, 3, 6},
                              {1, 4, 7},
                              {2, 5, 8},
                              {0, 4, 8},
                              {2, 4, 6}};

        for (int c = 0; c < 8; c++) // mesma lógica do computadorInteligente
        {
            posicaoDesejada = -1; // VALOR INCIAL QUE NAO É UM VALOR VÁLIDO DENTRO DO JOGO DA VELHA, QUE É DE 0 A 8

            if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == pcInteligente)
            {
                return vitorias[c][0] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == pcInteligente)
            {
                return vitorias[c][1] + 1;
            }
            else if (jogo[vitorias[c][0]] == (jogo[vitorias[c][1]] && jogo[vitorias[c][2]] == ' ') && jogo[vitorias[c][1]] == pcInteligente)
            {
                return vitorias[c][2] + 1;
            }
        }

        for (int c = 0; c < 8; c++) // igual pcInteligente
        {

            if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == jogador)
            {
                return vitorias[c][0] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == jogador)
            {
                return vitorias[c][1] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][1]]) && jogo[vitorias[c][2]] == ' ' && jogo[vitorias[c][1]] == jogador)
            {
                return vitorias[c][2] + 1;
            }
        }

        // jogadas do pc inteligente
        if (jogo[0] == jogador && jogo[8] == jogador && jogo[4] == pcInteligente)
        // se a posicao 1 for jogador e posicao 9 for jogador e posicao 5 for pcInteligente
        {
            posicaoDesejada = posicoes[(rand() % 5)]; // joga entre as posicoes 2, 4, 6, 8
        }
        else if (jogo[2] == jogador && jogo[6] == jogador && jogo[4] == pcInteligente)
        // se a posicao 3 for jogador e posicao 7 for jogador e posicao 5 for pcInteligente
        {
            posicaoDesejada = posicoes[(rand() % 5)]; // joga entre as posicoes 2, 4, 6, 8
        }
        else if (jogo[4] == jogador && jogo[8] == jogador && jogo[0] == pcInteligente)
        // se a posicao 5 for jogador e posicao 9 for jogador e posicao 1 for pcInteligente
        {
            int pontas[2] = {2, 6};
            posicaoDesejada = pontas[(rand() % 3)]; // joga nas pontas (2, 6)
        }
        else if (jogo[4] == jogador && jogo[6] == jogador && jogo[2] == pcInteligente)
        // se a posicao 5 for jogador e posicao 7 for jogador e posicao 3 for pcInteligente
        {
            int pontas[2] = {0, 8};
            posicaoDesejada = pontas[(rand() % 3)]; // joga nas pontas (0, 8)
        }
        else if (jogo[0] == jogador && jogo[4] == jogador && jogo[8] == pcInteligente)
        // se a posicao 1 for jogador e posicao 5 for jogador e posicao 9 for pcInteligente
        {
            int pontas[2] = {2, 6};
            posicaoDesejada = pontas[(rand() % 3)]; // joga nas pontas (2, 6)
        }
        else if (jogo[2] == jogador && jogo[4] == jogador && jogo[6] == pcInteligente)
        // se a posicao 3 for jogador e posicao 5 for jogador e posicao 7 for pcInteligente
        {
            int pontas[2] = {0, 8};
            posicaoDesejada = pontas[(rand() % 3)]; // joga nas pontas (0, 8)
        }

        // esse if é do random, pq estava dando erro
        // então eu coloquei que se a posição estiver preenchida e ela for -1 (que eu disse que ela era -1 lá em cima)
        if (jogo[posicaoDesejada] != ' ' || posicaoDesejada == -1)
        {
            do
            {
                posicaoDesejada = (rand() % 9);
            } while (jogo[posicaoDesejada] != ' '); // ele vai ficar no loop até encontrar uma posição que esteja vazia
        }

        return posicaoDesejada + 1; // joga na posição
    }
}

int main()
{

    char mostrarJogo[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int linha, coluna, nivelBoot, escolha, jaJogou, finalJogo, opcao, bloqueadas = 0, empate = 0, posicao = 0;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char jogadorAtual = ' ';
    char vencedor = ' ';
    string nomeJogador1 = "";
    string nomeJogador2 = "";
    string nomeJogador = "";
    char pcInteligente = 'O';
    char boot = 'O';
    srand(time(0));

    int vitorias[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};

    do
    {

        do
        {
            cout << "=========BEM VINDO AO JOGO DO GALO=========\n\n";
            cout << "Escolha entre as opcoes: \n";
            cout << "1 - Jogador vs Jogador\n";
            cout << "2 - Jogador vs Computador\n";
            cout << "3 - Estatisticas\n";
            cout << "4 - Sair" << endl;
            cin >> opcao;

            if (opcao == 1)
            {

                char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                vencedor = ' ';

                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                cout << nomeJogador1 << " sera '" << jogador1 << "' e " << nomeJogador2 << " sera '" << jogador2 << "'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(mostrarJogo); // apenas mostra o tabuleiro
                cout << "\n\n";

                empate = 0;

                for (int i = 0; i < 9; i++) // entro no loop do char jogo[9]
                {
                    do
                    {
                        if (i % 2 == 0)
                        {
                            jogadorAtual = jogador1;
                            cout << "\n\n"
                                 << nomeJogador1 << ", ";
                        }
                        else
                        {
                            jogadorAtual = jogador2;
                            cout << "\n\n"
                                 << nomeJogador2 << ", ";
                        }

                        cout << "escolha uma posicao do jogo da velha: ";
                        cin >> posicao;

                        // validação da jogada
                        if (posicao < 1 || posicao > 9)
                        {
                            cout << "\nPosicao invalida, escolha outra posicao!\n";
                        }

                        else if (jogo[posicao - 1] != ' ')
                        {
                            cout << "\nPosicao ocupada, escolha outra posicao!\n";
                        }

                    } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                    *(jogo + (posicao - 1)) = jogadorAtual; // salvo a jogada
                    // a jogada só pode ser salva fora do while, pra ele não salvar mais de uma resposta

                    cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                    mostrarTabuleiroAtt(jogo); // mostra o tabuleiro atualizado com o vetor jogo
                    cout << "\n\nPosicoes: \n\n";
                    mostrarTabuleiro(mostrarJogo);

                    vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                    if (vencedor != ' ' || empate == 1)
                    {
                        break;
                        // se o vencedor for diferente de vazio ou o empate for 1, para esse loop
                        // esse para o loop do for i = 9
                    }
                } // fim do loop de jogo[9]

                verificarVitoriaJogadores(vencedor, jogador1, jogador2, nomeJogador1, nomeJogador2, jogo);
                break;
            }

            else if (opcao == 2) // escolha da opção jogador vs computador do menu
            {
                do
                { // início do loop para a pessoa escolher entre 1 e 3
                    cout << "Voce escolheu a opcao de jogar contra o computador\nVoce pode escolher entre dois niveis\n1 - Facil\n2 - Normal\n3 - Dificil\nEscolha um: ";
                    cin >> nivelBoot;
                    if (nivelBoot == 1) // se escolher nível 1...
                    {
                        cout << "Bem-vindo ao nivel facil!\n";

                        // essa parte é pra limpar as variáveis, pq os valores delas estão salvos da opção 1
                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';
                        // jogador1 = 'X';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

                        empate = 0;

                        for (int i = 0; i < 9; i++) // loop igual ao da opcao 1
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else // jogada do boot
                                {
                                    do // while para que ele escolha apena uma opção que esteja vazia
                                    {
                                        cout << "\n\nJogada do computador: \n";
                                        jogadorAtual = boot;
                                        cout << "\n\nBoot (O):";
                                        posicao = (rand() % 9 + 1);
                                        /*o modulo de 9 sempre vai ser de 0 a 8
                                        pq mais 1? pq quando usa o ponteiro usa com -1
                                        pq o usuario sempre vai colocar 1 acima (pq o vetor é 0 based)*/
                                        if (jogo[posicao - 1] != ' ') // se a posicao tiver preenchida
                                        {
                                            cout << "\nO computador escolheu uma posicao ocupada!\n"; // ele responde isso
                                        }
                                    } while (jogo[posicao - 1] != ' '); // fim do while de escolher uma opção vazia
                                }

                                if (posicao < 1 || posicao > 9)
                                {
                                    cout << "\nPosicao invalida, escolha outra posicao!\n";
                                }

                                else if (jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O')
                                {
                                    cout << "\nPosicao ocupada, escolha outra posicao!\n";
                                }

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo);
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        if (vencedor == jogador1)
                        {
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            break;
                        }
                        else if (vencedor == boot)
                        {
                            cout << "\n\n"
                                 << "O computador venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            break;
                        }
                        else
                        {
                            cout << "\n\nEmpate!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 0, 1);
                            break;
                        }
                    }
                    else if (nivelBoot == 2) // início do nível normal do boop
                    {
                        cout << "Bem-vindo ao nivel normal!\n";

                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';
                        // jogador1 = 'X';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << nomeJogador1 << " sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);
                        empate = 0;
                        jaJogou = 0;

                        for (int i = 0; i < 9; i++)
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else
                                {
                                    cout << "\n\nJogada do computador... \n";
                                    jogadorAtual = pcInteligente;

                                    posicao = jogadaComputadorInteligente(jogo, pcInteligente, jogador1, jaJogou);
                                    jaJogou = 1;
                                }

                                if (posicao < 1 || posicao > 9)
                                {
                                    cout << "\nPosicao invalida, escolha outra posicao!\n";
                                }

                                else if ((jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O') && i % 2 == 0)
                                {
                                    cout << "\nPosicao ocupada, escolha outra posicao!\n";
                                }

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo); // mostra o tabuleiro atualizado com o vetor jogo
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        if (vencedor == jogador1)
                        {
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            break;
                        }
                        else if (vencedor == pcInteligente)
                        {
                            cout << "\n\n"
                                 << "O computador venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            break;
                        }
                        else
                        {
                            cout << "\n\nEmpate!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 0, 1);
                            break;
                        }
                    }
                    else if (nivelBoot == 3) // início do nível difícil
                    // essa é a função extra que foi solicitada
                    {
                        cout << "Bem-vindo ao nivel dificil!\n";

                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';
                        // jogador1 = 'X';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << nomeJogador1 << " sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

                        empate = 0;
                        jaJogou = 0;

                        for (int i = 0; i < 9; i++)
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else
                                {
                                    cout << "\n\nJogada do computador... \n";
                                    jogadorAtual = pcInteligente;

                                    posicao = jogadaComputadorDificil(jogo, pcInteligente, jogador1, jaJogou);
                                    jaJogou = 1;
                                }

                                if (posicao < 1 || posicao > 9)
                                {
                                    cout << "\nPosicao invalida, escolha outra posicao!\n";
                                }

                                else if ((jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O') && i % 2 == 0)
                                {
                                    cout << "\nPosicao ocupada, escolha outra posicao!\n";
                                }

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo); // mostra o tabuleiro atualizado com o vetor jogo
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        if (vencedor == jogador1)
                        {
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            break;
                        }
                        else if (vencedor == pcInteligente)
                        {
                            cout << "\n\n"
                                 << "O computador venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            break;
                        }
                        else
                        {
                            cout << "\n\nEmpate!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 0, 1);
                            break;
                        }
                    }
                } while (nivelBoot < 1 || nivelBoot > 3); // fim do loop para a pessoa escolher entre 1 e 3
            }
            else if (opcao == 3)
            {
                ifstream ficheiro("jogoDoGalo.txt");
                int numPartidas;
                int vitorias;
                int derrotas;
                int empates;

                if (!ficheiro.is_open())
                {
                    cout << "Erro ao abrir ficheiro\n";
                    break;
                }
                else
                {
                    mostrarJogador(ficheiro, nomeJogador, numPartidas,
                                   vitorias, derrotas, empates);
                }
            }
            else
            {
                break;
            }
        } while (opcao < 1 || opcao > 4);

        cout << "\n\nDeseja sair do jogo?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;
    } while (finalJogo == 2);

    cout << "\n\nObrigada por jogar conosco!\n\n";
    cout << "Copyrights © 2026 - Camila, Betania, Sarah";

    return 0;
}