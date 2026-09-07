#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*grupo 3: camila, betânia, sarah
ordem de apresentação: 4º grupo
tema: jogo do galo (jogo da velha)
entrega do código: 11/09
apresentação: 16/09*/

fstream ficheiro("jogoDoGalo.txt", ios::in | ios::out | ios::app); // ONDE COLOCAR ISSO, ANTES OU DEPOIS DO MAIN, OU
// DENTRO DA FUNÇÃO

void guardarJogador(ofstream &ficheiro, string nomeJogador, int numPartidas,
                    int vitorias, int derrotas, int empates)
{
    ficheiro << "Name: " << nomeJogador << "\nNumero de partidas: " << numPartidas << "\nVitorias: " << vitorias << "\nDerrotas: " << derrotas << "\nEmpates: " << empates << endl;
}

bool mostrarJogador(ifstream &ficheiro, string &nomeJogador, int &numPartidas,
                    int &vitorias, int &derrotas, int &empates)
{
    return bool(ficheiro >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates);
}

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

int main()
{
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
    // salvar essas variáveis
    int numPartidas;
    int vitorias;
    int derrotas;
    int empates;

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
                        jogadorAtual = jogador1;
                        cout << "\n\n" << nomeJogador1 << ", ";
                    }

                    else
                    {
                        jogadorAtual = jogador2;
                        cout << "\n\n"<< nomeJogador2 << ", ";
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

                    if (
                        (jogo[0][0] == jogadorAtual && jogo[0][1] == jogadorAtual && jogo[0][2] == jogadorAtual) ||
                        (jogo[1][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[1][2] == jogadorAtual) ||
                        (jogo[2][0] == jogadorAtual && jogo[2][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][0] == jogadorAtual && jogo[2][0] == jogadorAtual) ||
                        (jogo[0][1] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][1] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][2] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][0] == jogadorAtual))
                    {
                        if (jogadorAtual == jogador1)
                        {
                            cout << "\n" << nomeJogador1 << " venceu!\n";
                            break;
                        }
                        else if (jogadorAtual == jogador2)
                        {
                            cout << "\n" << nomeJogador2 << " venceu!\n";
                            break;
                        }
                    }

                    if (jogada == 8)
                    {

                        cout << "Empate!\n\n";
                        break;
                    }

                    mostrarTabuleiro(jogo);
                }

                mostrarTabuleiro(jogo);
            }
            else if (opcao == 2)
            {
                //adicionar o boot
            }
            else if (opcao == 3)
            {
                //adicionar as estatísticas
                
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