#include <iostream>
using namespace std;

// Verifica se uma posicao esta livre
bool posicaoLivre(char jogo[3][3], int linha, int coluna)
{
    return jogo[linha][coluna] == ' ';
}

// Verifica se um jogador ganhou
bool verificarVitoria(char jogo[3][3],
                      char jogador1, char jogador2)
{
    // Verificar linhas
    for (int linha = 0; linha < 3; linha++)
    {
        if (jogo[linha][0] == jogador1 || jogador2 &&
            jogo[linha][1] == jogador1 || jogador2 &&
            jogo[linha][2] == jogador1 || jogador2)
        {
            return true;
        }
    }

    // Verificar colunas
    for (int coluna = 0; coluna < 3; coluna++)
    {
        if (jogo[0][coluna] == jogador1 || jogador2 &&
            jogo[1][coluna] == jogador1 || jogador2 &&
            jogo[2][coluna] == jogador1 || jogador2)
        {
            return true;
        }
    }

    // Diagonal principal
    if (jogo[0][0] == jogador1 || jogador2 &&
        jogo[1][1] == jogador1 || jogador2 &&
        jogo[2][2] == jogador1 || jogador2)
    {
        return true;
    }

    // Diagonal secundaria
    if (jogo[0][2] == jogador1 || jogador2 &&
        jogo[1][1] == jogador1 || jogador2 &&
        jogo[2][0] == jogador1 || jogador2)
    {
        return true;
    }

    return false;
}

// Verifica se há empate
bool verificarEmpate(char jogo[3][3])
{
    for (int linha = 0; linha < 3; linha++)
    {
        for (int coluna = 0; coluna < 3; coluna++)
        {
            if (jogo[linha][coluna] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

// Guarda as estatisticas no ficheiro
void guardarEstatisticas(
    string nomes[],
    int partidas[],
    int vitorias[],
    int derrotas[],
    int empates[],
    int linha);
{
    ofstream ficheiro("jogoDoGalo.txt");

    if (!ficheiro)
    {
        cout << "\nErro ao guardar as estatisticas.\n";
        return;
    }

    for (int i = 0; i < linha; i++)
    {
        ficheiro << nomes[i] << " "
                 << partidas[i] << " "
                 << vitorias[i] << " "
                 << derrotas[i] << " "
                 << empates[i]
                 << "\n";
    }

    ficheiro.close();
}

// Apresenta todas as estatisticas
void mostrarEstatisticas()
{
    string nomes[20];

    int partidas[100];
    int vitorias[100];
    int derrotas[100];
    int empates[100];

    int linha = guardarEstatisticas(
        nomes,
        partidas,
        vitorias,
        derrotas,
        empates
    );

    if (linha == 0)
    {
        cout << "Ainda nao existem estatísticas guardadas.\n";
        return;
    }

    cout << "\n";

    cout << "Jogador\t\tPartidas\tVitorias\t";
    cout << "Derrotas\tEmpates\n";

    for (int i = 0; i < linha; i++)
    {
        cout << nomes[i] << "\t\t"
             << partidas[i] << "\t\t"
             << vitorias[i] << "\t\t"
             << derrotas[i] << "\t\t"
             << empates[i] << "\n";
    }
}

// Atualiza uma vitoria
void atualizarVitoria(
    int partidas[],
    int vitorias[],
    int posicao)
{
    partidas[posicao]++;
    vitorias[posicao]++;
}

// Atualiza uma derrota
void atualizarDerrota(
    int partidas[],
    int derrotas[],
    int posicao)
{
    partidas[posicao]++;
    derrotas[posicao]++;
}

// Atualiza um empate
void atualizarEmpate(
    int partidas[],
    int empates[],
    int posicao)
{
    partidas[posicao]++;
    empates[posicao]++;
}

int main() {
    ofstream ficheiro("jogoDoGalo.txt");

    char jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int linha, coluna;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char jogadorAtual;
    string nomeJogador1 = "";
    string nomeJogador2 = "";

    int finalJogo;
    int opcao;

    /*char *ponteiro = nullptr;*/

    char posicao;

    if (!ficheiro.is_open())
    {
        cout << "Erro ao abrir ficheiro";
        return 1;
    }

    do
    {

        do
        {
            cout << "Bem vindo ao Jogo do Galo!\n\n";
            cout << "Escolha entre as opcoes: \n";
            cout << "1 - Jogador vs Jogador\n";
            cout << "2 - Jogador vs Computador\n";
            cout << "3 - Estatisticas\n";
            cout << "4 - Sair" << endl;
            cin >> opcao;

            if (opcao == 1)
            {
                // receber o espaço do int
                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                cout << "O jogador 1 sera o 'X' e o jogador 2 sera o 'O'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(jogo);
                cout << "\n\nVoces terao que escolher uma posicao de acordo com os numeros mostrados!\n";

                for (int jogada = 0; jogada < 9; jogada++)
                {

                    if (jogada % 2 == 0)
                    {
                        jogadorAtual = jogador1; // descobrir como colocar o nome do jogador

                        cout << "\n\n"
                             << nomeJogador1 << ", ";
                    }

                    else
                    {

                        jogadorAtual = jogador2;
                        cout << "\n\n"
                             << nomeJogador2 << ", ";
                    }

                    cout << "qual a posicao que deseja realizar a jogada? ";
                    cout << "Escolha a linha (entre 1 e 3): ";
                    cin >> linha;
                    cout << "Escolha a coluna (entre 1 e 3): ";
                    cin >> coluna;

                    while (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || *(*(jogo + (linha - 1)) + (coluna - 1)) != ' ')
                    {

                        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3)
                        {

                            cout << "\n\nPosicao invalida! Escolha outra posicao!";
                        }

                        else if (*(*(jogo + (linha - 1)) + (coluna - 1)) != ' ')
                        {
                            cout << "\n\nPosicao ocupada! Escolha outra posicao!";
                        }

                        cout << "\n\nQual a posicao que deseja realizar a jogada?";
                        cout << "Escolha a linha (entre 1 e 3):";
                        cin >> linha;
                        cout << "Escolha a coluna (entre 1 e 3): \n";
                        cin >> coluna;
                        // descobrir como tirar esse codigo repetido
                    }

                    *(*(jogo + (linha - 1)) + (coluna - 1)) = jogadorAtual;

                    verificarVitoria(jogo[3][3], jogadorAtual);

                    /*if (
                        (jogo[0][0] == jogadorAtual && jogo[0][1] == jogadorAtual && jogo[0][2] == jogadorAtual) ||
                        (jogo[1][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[1][2] == jogadorAtual) ||
                        (jogo[2][0] == jogadorAtual && jogo[2][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][0] == jogadorAtual && jogo[2][0] == jogadorAtual) ||
                        (jogo[0][1] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][1] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][2] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][0] == jogadorAtual))
                    {*/
                        cout << "\nO jogador " << jogadorAtual << " venceu!\n";
                        mostrarTabuleiro(jogo);
                        break;

                    if (jogada == 8)
                    {
                        verificarEmpate(jogo);
                        cout << "Empate!\n";
                        mostrarTabuleiro(jogo);
                        break;
                    }

                    cout << "\n\n";

                    mostrarTabuleiro(jogo);
                }
            }
            else if (opcao == 2)
            {
            }
            else if (opcao == 3)
            {
                ifstream in("jogoDoGalo.txt");
                string nomeJogador;
                int numPartidas;
                int vitorias;
                int derrotas;
                int empates;
                while (in >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates)
                {
                    cout << nomeJogador << "->" << numPartidas << "->" << vitorias << "->" << derrotas << "->" << empates << endl;
                }
                in.close();
            }
            else
            {
                break;
            }
        } while (opcao < 1 || opcao > 4);

        cout << "\n\nDeseja iniciar uma nova partida?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;

    } while (finalJogo == 1);

    ficheiro << jogador1 << endl;
    ficheiro.close();

    return 0;
}